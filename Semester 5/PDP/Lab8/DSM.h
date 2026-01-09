#pragma once
#include <mpi.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>

// Message Tags
#define MSG_WRITE_REQ 1
#define MSG_UPDATE 2
#define MSG_CAS_REQ 3
#define MSG_CAS_RESPONSE 4
#define MSG_EXIT 99

class DSM {
private:
    int rank, size;
    
    // Local storage of variables
    // Map: VarName -> Value
    std::unordered_map<std::string, int> variables;
    
    // Static subscriptions: VarName -> List of Subscriber Ranks
    std::unordered_map<std::string, std::vector<int>> subscribers;

    // Mutex to protect variable access (local app vs listener thread)
    std::mutex mtx;

    // Background listener thread
    std::thread listenerThread;
    bool running;

    // Helper to determine who owns a variable
    int getOwner(const std::string& varName) {
        // Simple hash: Sum of chars % num_procs
        int sum = 0;
        for (char c : varName) sum += c;
        return sum % size;
    }

    // Sends update to all subscribers (executed by Owner)
    void notifySubscribers(const std::string& var, int val) {
        for (int node : subscribers[var]) {
            if (node == rank) continue; // Don't send to self (already updated)
            
            // Pack: [NameLength, Name..., Value]
            int len = var.size();
            // In a real app we'd serialize better, here we do multiple sends for simplicity
            MPI_Send(&len, 1, MPI_INT, node, MSG_UPDATE, MPI_COMM_WORLD);
            MPI_Send(var.c_str(), len, MPI_CHAR, node, MSG_UPDATE, MPI_COMM_WORLD);
            MPI_Send(&val, 1, MPI_INT, node, MSG_UPDATE, MPI_COMM_WORLD);
        }
    }

public:
    DSM() : running(true) {}

    void init(int r, int s, const std::unordered_map<std::string, std::vector<int>>& config) {
        rank = r;
        size = s;
        subscribers = config;

        // Initialize local variables to 0 if I am a subscriber
        for (auto& pair : config) {
            bool isSub = false;
            for (int node : pair.second) if (node == rank) isSub = true;
            if (isSub) variables[pair.first] = 0;
        }

        // Start background listener
        listenerThread = std::thread(&DSM::listen, this);
    }

    void close() {
        running = false;
        // Send a dummy message to self to unblock the listener
        int dummy = 0;
        MPI_Send(&dummy, 1, MPI_INT, rank, MSG_EXIT, MPI_COMM_WORLD);
        if (listenerThread.joinable()) listenerThread.join();
    }

    // --- User Operations ---

    // Write: Send request to Owner
    void write(const std::string& var, int value) {
        int owner = getOwner(var);
        
        // If I am the owner, update and notify immediately
        if (owner == rank) {
            std::lock_guard<std::mutex> lock(mtx);
            variables[var] = value;
            printf("[%d] Writing (Owner) %s = %d\n", rank, var.c_str(), value);
            notifySubscribers(var, value);
        } else {
            // Send Request to Owner
            printf("[%d] Sending Write Req for %s to %d\n", rank, var.c_str(), owner);
            int len = var.size();
            MPI_Send(&len, 1, MPI_INT, owner, MSG_WRITE_REQ, MPI_COMM_WORLD);
            MPI_Send(var.c_str(), len, MPI_CHAR, owner, MSG_WRITE_REQ, MPI_COMM_WORLD);
            MPI_Send(&value, 1, MPI_INT, owner, MSG_WRITE_REQ, MPI_COMM_WORLD);
        }
    }

    // Compare and Exchange: Send request to Owner, wait for reply
    bool compareExchange(const std::string& var, int expected, int newVal) {
        int owner = getOwner(var);
        
        if (owner == rank) {
            std::lock_guard<std::mutex> lock(mtx);
            if (variables[var] == expected) {
                variables[var] = newVal;
                notifySubscribers(var, newVal);
                return true;
            }
            return false;
        } else {
            // Send Request
            int len = var.size();
            MPI_Send(&len, 1, MPI_INT, owner, MSG_CAS_REQ, MPI_COMM_WORLD);
            MPI_Send(var.c_str(), len, MPI_CHAR, owner, MSG_CAS_REQ, MPI_COMM_WORLD);
            
            int data[2] = {expected, newVal};
            MPI_Send(data, 2, MPI_INT, owner, MSG_CAS_REQ, MPI_COMM_WORLD);

            // Wait specifically for a response
            int success;
            MPI_Status status;
            MPI_Recv(&success, 1, MPI_INT, owner, MSG_CAS_RESPONSE, MPI_COMM_WORLD, &status);
            return success == 1;
        }
    }
    
    // Read local value
    int read(const std::string& var) {
        std::lock_guard<std::mutex> lock(mtx);
        return variables[var];
    }

    // --- The Background Listener ---
    void listen() {
        while (running) {
            MPI_Status status;
            // Probe to see incoming message size/tag
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            
            if (status.MPI_TAG == MSG_EXIT) break;

            if (status.MPI_TAG == MSG_UPDATE) {
                // Receive Update from Owner
                int len;
                // CHANGED: MPI_NULL_STATUS -> MPI_STATUS_IGNORE
                MPI_Recv(&len, 1, MPI_INT, status.MPI_SOURCE, MSG_UPDATE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                char* buf = new char[len + 1];
                MPI_Recv(buf, len, MPI_CHAR, status.MPI_SOURCE, MSG_UPDATE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                buf[len] = '\0';
                std::string var(buf);
                int val;
                MPI_Recv(&val, 1, MPI_INT, status.MPI_SOURCE, MSG_UPDATE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                delete[] buf;

                // Update Local Memory
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (variables.count(var)) { // Check subscription
                        variables[var] = val;
                        printf("[%d] UPDATE RECEIVED: %s is now %d\n", rank, var.c_str(), val);
                    }
                }
            } 
            else if (status.MPI_TAG == MSG_WRITE_REQ) {
                // I am Owner, receive Write Request
                int len;
                MPI_Recv(&len, 1, MPI_INT, status.MPI_SOURCE, MSG_WRITE_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                char* buf = new char[len + 1];
                MPI_Recv(buf, len, MPI_CHAR, status.MPI_SOURCE, MSG_WRITE_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                buf[len] = '\0';
                std::string var(buf);
                int val;
                MPI_Recv(&val, 1, MPI_INT, status.MPI_SOURCE, MSG_WRITE_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                delete[] buf;

                // Execute Write & Broadcast
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    variables[var] = val;
                    printf("[%d] Processing Write Req from %d. %s -> %d\n", rank, status.MPI_SOURCE, var.c_str(), val);
                    notifySubscribers(var, val);
                }
            }
            else if (status.MPI_TAG == MSG_CAS_REQ) {
                // I am Owner, receive CAS Request
                int len;
                MPI_Recv(&len, 1, MPI_INT, status.MPI_SOURCE, MSG_CAS_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                char* buf = new char[len + 1];
                MPI_Recv(buf, len, MPI_CHAR, status.MPI_SOURCE, MSG_CAS_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                buf[len] = '\0';
                std::string var(buf);
                int params[2]; // [expected, new]
                MPI_Recv(params, 2, MPI_INT, status.MPI_SOURCE, MSG_CAS_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                delete[] buf;

                int response = 0;
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (variables[var] == params[0]) {
                        variables[var] = params[1];
                        notifySubscribers(var, params[1]);
                        response = 1;
                        printf("[%d] CAS SUCCESS from %d on %s\n", rank, status.MPI_SOURCE, var.c_str());
                    } else {
                         printf("[%d] CAS FAILED from %d on %s (Exp: %d, Is: %d)\n", rank, status.MPI_SOURCE, var.c_str(), params[0], variables[var]);
                    }
                }
                // Send response back
                MPI_Send(&response, 1, MPI_INT, status.MPI_SOURCE, MSG_CAS_RESPONSE, MPI_COMM_WORLD);
            }
        }
    }
};
#include "DSM.h"
#include <unistd.h> // for sleep

int main(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided < MPI_THREAD_MULTIPLE) {
        printf("Error: The MPI library does not provide full thread support.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 1. Define Subscriptions (Static Config)
    std::unordered_map<std::string, std::vector<int>> config;
    config["var_a"] = {0, 1};    // A shared by 0 and 1
    config["var_b"] = {1, 2};    // B shared by 1 and 2
    config["var_c"] = {0, 1, 2}; // C shared by all

    // 2. Init DSM
    DSM dsm;
    dsm.init(rank, size, config);

    // Sync to ensure everyone is ready
    MPI_Barrier(MPI_COMM_WORLD);

    // 3. Scenario Logic
    if (rank == 0) {
        printf("Rank 0: Writing var_a = 10\n");
        dsm.write("var_a", 10);
        
        sleep(1); // Wait a bit
        
        printf("Rank 0: Writing var_c = 30\n");
        dsm.write("var_c", 30);
        
        // CAS Test
        bool res = dsm.compareExchange("var_c", 30, 100);
        printf("Rank 0: CAS var_c (30->100) result: %s\n", res ? "Success" : "Fail");

    } 
    else if (rank == 1) {
        sleep(1); // Let rank 0 write first
        
        printf("Rank 1: Writing var_b = 20\n");
        dsm.write("var_b", 20);

        // Try CAS that should fail (if Rank 0 already changed var_c to 100)
        sleep(1);
        bool res = dsm.compareExchange("var_c", 30, 500);
        printf("Rank 1: CAS var_c (30->500) result: %s\n", res ? "Success" : "Fail");
    }
    else if (rank == 2) {
        // Just a listener for B and C
        sleep(3);
        printf("Rank 2: Final read var_b = %d\n", dsm.read("var_b"));
    }

    // Keep alive to receive all callbacks
    sleep(5);
    
    printf("Rank %d exiting\n", rank);
    dsm.close();
    MPI_Finalize();
    return 0;
}
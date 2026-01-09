#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include "sal.h"
using namespace std;

// Helpers

void printPoly(const vector<int>& poly) {
    if (poly.size() > 2010) {
        printf("[Poly too large to print: %zu elements]\n", poly.size());
        return;
    }
    for (int x : poly) printf("%d ", x);
    printf("\n");
}

// Adds two polynomials: result = A + B
vector<int> add(const vector<int>& A, const vector<int>& B) {
    size_t sizeA = A.size();
    size_t sizeB = B.size();
    size_t maxS = max(sizeA, sizeB);
    
    vector<int> res;
    res.reserve(maxS);

    for (size_t i = 0; i < maxS; i++) {
        int a = (i < sizeA) ? A[i] : 0;
        int b = (i < sizeB) ? B[i] : 0;
        res.push_back(a + b);
    }
    return res;
}

// Subtracts two polynomials: result = A - B
vector<int> subtract(const vector<int>& A, const vector<int>& B) {
    size_t sizeA = A.size();
    size_t sizeB = B.size();
    size_t maxS = max(sizeA, sizeB);

    vector<int> res;
    res.reserve(maxS);

    for (size_t i = 0; i < maxS; i++) {
        int a = (i < sizeA) ? A[i] : 0;
        int b = (i < sizeB) ? B[i] : 0;
        res.push_back(a - b);
    }
    return res;
}

// Classic algorithm O(n^2)
vector<int> multiplyNaive(const vector<int>& A, const vector<int>& B) {
    if (A.empty() || B.empty()) return {};
    vector<int> res(A.size() + B.size() - 1, 0);

    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < B.size(); j++) {
            res[i + j] += A[i] * B[j];
        }
    }
    return res;
}

// Karatsuba O(n^1.58)
vector<int> multiplyKaratsuba(const vector<int>& A, const vector<int>& B) {
    size_t n = A.size();
    size_t m = B.size();

    // if one of the vectors is smaller than the other, we use naive because its faster
    if (n <= 1024 || m <= 1024) { 
        return multiplyNaive(A, B);
    }

    size_t k = n / 2;

    vector<int> A0(A.begin(), A.begin() + k);
    vector<int> A1(A.begin() + k, A.end());
    
    vector<int> B0(B.begin(), B.begin() + min(k, m));
    vector<int> B1;
    if (m > k) B1.assign(B.begin() + k, B.end());

    vector<int> P1 = multiplyKaratsuba(A0, B0);
    vector<int> P2 = multiplyKaratsuba(A1, B1);
    
    vector<int> A_sum = add(A0, A1);
    vector<int> B_sum = add(B0, B1);
    vector<int> P3 = multiplyKaratsuba(A_sum, B_sum);

    // Compute Middle Term
    vector<int> midTerm = subtract(P3, P1);
    midTerm = subtract(midTerm, P2);

    // Assemble result
    vector<int> result(n + m - 1, 0);

    for (size_t i = 0; i < P1.size(); i++) 
        if(i < result.size()) result[i] += P1[i];

    for (size_t i = 0; i < midTerm.size(); i++) 
        if(i + k < result.size()) result[i + k] += midTerm[i];

    for (size_t i = 0; i < P2.size(); i++) 
        if(i + 2 * k < result.size()) result[i + 2 * k] += P2[i];

    return result;
}

// MPI distribution
// This function handles the "dirty work" of MPI distribution
// It takes a pointer to the multiplication function (Naive or Karatsuba)
void benchmarkDistributed(
    int rank, int nProcesses, 
    const vector<int>& globalA, const vector<int>& globalB, 
    vector<int>(*multFunc)(const vector<int>&, const vector<int>&), 
    const char* algoName
) {
    double startTime = MPI_Wtime();

    // Broadcast B
    int sizeB = globalB.size();
    MPI_Bcast((void*)&sizeB, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    vector<int> localB(sizeB);
    if (rank == 0) localB = globalB;
    MPI_Bcast(localB.data(), sizeB, MPI_INT, 0, MPI_COMM_WORLD);

    int N = globalA.size();
    if(rank != 0) N = 0; // only master knows N initially
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunkSize = N / nProcesses;
    int remainder = N % nProcesses;
    vector<int> localA;

    if (rank == 0) {
        int currentIdx = 0;
        // Send chunks to workers
        for (int i = 1; i < nProcesses; i++) {
            int currentChunk = chunkSize + (i < remainder ? 1 : 0);
            int offset = 0; 
            for(int k=0; k<i; k++) offset += chunkSize + (k < remainder ? 1 : 0);

            MPI_Send(&currentChunk, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
            MPI_Send(&globalA[offset], currentChunk, MPI_INT, i, 11, MPI_COMM_WORLD);
        }
        // Master keeps its chunk
        int mySize = chunkSize + (0 < remainder ? 1 : 0);
        localA.assign(globalA.begin(), globalA.begin() + mySize);
    } else {
        int mySize;
        MPI_Recv(&mySize, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        localA.resize(mySize);
        MPI_Recv(localA.data(), mySize, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Execute chosen algorithm
    vector<int> localResult = multFunc(localA, localB);

    // Gather results
    if (rank != 0) {
        int resSize = localResult.size();
        MPI_Send(&resSize, 1, MPI_INT, 0, 12, MPI_COMM_WORLD);
        MPI_Send(localResult.data(), resSize, MPI_INT, 0, 13, MPI_COMM_WORLD);
    } else {
        vector<int> finalResult(N + sizeB - 1, 0);

        // Add Master's part
        for(size_t i=0; i<localResult.size(); i++) finalResult[i] += localResult[i];

        int currentOffset = localA.size();

        for (int i = 1; i < nProcesses; i++) {
            int recvSize;
            MPI_Recv(&recvSize, 1, MPI_INT, i, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vector<int> recvBuf(recvSize);
            MPI_Recv(recvBuf.data(), recvSize, MPI_INT, i, 13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Add Worker's part (Shifted by currentOffset)
            for(int j=0; j<recvSize; j++) {
                if (currentOffset + j < finalResult.size()) {
                    finalResult[currentOffset + j] += recvBuf[j];
                }
            }
            // Calculate how many elements worker i processed from A
            int workerChunkA = recvSize - sizeB + 1;
            currentOffset += workerChunkA;
        }
        
        double endTime = MPI_Wtime();
        printf("[%s] Execution Time: %f seconds\n", algoName, endTime - startTime);
        printPoly(finalResult);
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, nProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    // Configuration
    const int POLY_DEGREE = 1000; 
    vector<int> A, B;

    if (rank == 0) {
        srand(time(NULL));
        A.resize(POLY_DEGREE);
        B.resize(POLY_DEGREE);
        for (int i = 0; i < POLY_DEGREE; i++) {
            A[i] = 1;
            B[i] = 1;
        }
        printf("=== Polynomial Multiplication (Degree: %d, Nodes: %d) ===\n", POLY_DEGREE, nProcesses);
    }

    // Run 1: Naive Distributed
    MPI_Barrier(MPI_COMM_WORLD); // Sync before starting
    benchmarkDistributed(rank, nProcesses, A, B, multiplyNaive, "Naive O(n^2)");

    // Run 2: Karatsuba Distributed
    MPI_Barrier(MPI_COMM_WORLD); // Sync between runs
    benchmarkDistributed(rank, nProcesses, A, B, multiplyKaratsuba, "Karatsuba O(n^1.58)");
    MPI_Finalize();
    
    return 0;
}
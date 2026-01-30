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

    std::unordered_map<std::string, std::vector<int>> config;
    config["var_a"] = {0, 1};    // A shared by 0 and 1
    config["var_b"] = {1, 2};    // B shared by 1 and 2
    config["var_c"] = {0, 1, 2}; // C shared by all

    DSM dsm;
    dsm.init(rank, size, config);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Rank 0: Writing var_a = 10\n");
        dsm.write("var_a", 10);
        
        sleep(1); 
        
        printf("Rank 0: Writing var_c = 30\n");
        dsm.write("var_c", 30);
        
        // CAS 
        bool res = dsm.compareExchange("var_c", 30, 100);
        printf("Rank 0: CAS var_c (30->100) result: %s\n", res ? "Success" : "Fail");

    } 
    else if (rank == 1) {
        sleep(1); 
        
        printf("Rank 1: Writing var_b = 20\n");
        dsm.write("var_b", 20);

        sleep(1);
        bool res = dsm.compareExchange("var_c", 30, 500);
        printf("Rank 1: CAS var_c (30->500) result: %s\n", res ? "Success" : "Fail");
    }
    else if (rank == 2) {
        sleep(3);
        printf("Rank 2: Final read var_b = %d\n", dsm.read("var_b"));
    }

    sleep(5);
    
    printf("Rank %d exiting\n", rank);
    dsm.close();
    MPI_Finalize();
    return 0;
}
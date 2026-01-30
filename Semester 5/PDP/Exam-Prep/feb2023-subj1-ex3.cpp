#include <mpi.h>
#include <vector>
#include <numeric>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // --- 1. SIMULARE DATE LOCALE ---
    // In realitate, fiecare proces ar primi o parte din matrice.
    // Aici generam date dummy: fiecare proces are o linie {1, 1, 1, 1}
    // Daca sunt 4 procese, Suma Totala ar trebui sa fie 16.
    std::vector<int> my_row = {1, 1, 1, 1}; 
    
    // Calculam suma locala (Frunza arborelui)
    int current_sum = 0;
    for (int val : my_row) {
        current_sum += val;
    }

    // --- 2. BINARY TREE REDUCTION ---
    // 'step' se dubleaza la fiecare iteratie: 1, 2, 4, 8...
    for (int step = 1; step < size; step *= 2) {
        
        // Verificam daca suntem RECEPTOR (nod parinte in acest pas)
        if (rank % (2 * step) == 0) {
            int source = rank + step;
            
            // Verificam daca sursa exista (pentru cazul cand nrProc nu e putere de 2)
            if (source < size) {
                int received_val;
                MPI_Recv(&received_val, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                
                // Adunam valoarea primita de la "copil"
                current_sum += received_val;
            }
        } 
        // Altfel, suntem EXPEDITOR (nod copil in acest pas)
        else {
            int dest = rank - step;
            MPI_Send(&current_sum, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            
            // IMPORTANT: Odata ce am trimis, am iesit din arbore.
            // Nu mai participam la pasii urmatori.
            break; 
        }
    }

    // --- 3. REZULTAT FINAL ---
    if (rank == 0) {
        std::cout << "Final Total Sum computed by Rank 0: " << current_sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}
#include <iostream>
#include <vector>
#include <future>   // Pentru std::async si std::future
#include <numeric>  // Optional, doar daca vrei std::accumulate

using namespace std;

// Functia recursiva paralela
long parallelSum(const vector<int>& v, int start, int end, int numThreads) {
    
    // 1. CAZUL DE BAZĂ: 
    // Daca avem 1 singur thread (sau 0), facem suma clasic (secvential) pe thread-ul curent.
    // Aici se opreste "ramificarea" arborelui.
    if (numThreads <= 1) {
        long sum = 0;
        for (int i = start; i < end; ++i) {
            sum += v[i];
        }
        return sum;
    }

    // 2. DIVIDE (Impartirea):
    int mid = start + (end - start) / 2;

    // 3. Lansam asincron stanga (folosind jumatate din thread-uri)
    // std::async porneste un task nou. 'handle' va tine rezultatul viitor.
    auto handle = async(launch::async, parallelSum, ref(v), start, mid, numThreads / 2);

    // 4. Calculam dreapta pe thread-ul curent (folosind restul de thread-uri)
    long rightSum = parallelSum(v, mid, end, numThreads - numThreads / 2);

    // 5. CONQUER (Combinarea):
    // handle.get() blocheaza executia pana cand partea stanga e gata
    return handle.get() + rightSum;
}

int main() {
    // Date de test
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int threads = 4; // Presupunem ca avem 4 nuclee

    // Apelul initial: index 0 pana la size, cu toate thread-urile
    long total = parallelSum(data, 0, data.size(), threads);

    cout << "Suma este: " << total << endl;

    return 0;
}
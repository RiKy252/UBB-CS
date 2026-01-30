#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>

using namespace std;

// Functie helper: Verifica daca n e divizibil cu vreun numar din lista
bool isPrime(int n, const vector<int>& smallPrimes) {
    if (n < 2) return false;
    for (int p : smallPrimes) {
        if (p * p > n) break; // Optimizare: nu are sens sa cautam peste sqrt(n)
        if (n % p == 0) return false;
    }
    return true;
}

// Worker Paralel
// Cauta primele in intervalul [start, end) folosind lista smallPrimes
void worker(int start, int end, const vector<int>& smallPrimes, int nrThreads, vector<int>& result) 
{
    // 1. Base Case (Secvential)
    if (nrThreads <= 1) {
        for (int i = start; i < end; i++) {
            if (isPrime(i, smallPrimes)) {
                result.push_back(i);
            }
        }
        return;
    }

    // 2. Divide
    int mid = start + (end - start) / 2;

    vector<int> leftResult;
    vector<int> rightResult;

    // 3. Lansam thread pentru stanga (scriem rezultatul in leftResult)
    thread t(worker, start, mid, ref(smallPrimes), nrThreads / 2, ref(leftResult));

    // 4. Calculam dreapta pe thread curent (scriem in rightResult)
    worker(mid, end, smallPrimes, nrThreads - nrThreads / 2, rightResult);

    // 5. Join
    t.join();

    // 6. Combinam rezultatele in vectorul final 'result'
    // Copiem tot din leftResult in result
    result.insert(result.end(), leftResult.begin(), leftResult.end());
    // Copiem tot din rightResult in result
    result.insert(result.end(), rightResult.begin(), rightResult.end());
}

int main() {
    int N = 100; // Vrem primele pana la 100
    int threads = 4;
    int limit = sqrt(N);

    // Pas 1: Generam lista initiala de prime pana la sqrt(N) (Secvential)
    // Putem folosi un simplu ciur sau verificare brute-force aici fiindca limit e mic
    vector<int> smallPrimes;
    for (int i = 2; i <= limit; i++) {
        bool prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prime = false; 
                break;
            }
        }
        if (prime) smallPrimes.push_back(i);
    }

    // Pas 2: Pregatim vectorul final care va contine initial primele mici
    vector<int> allPrimes = smallPrimes;
    
    // Pas 3: Lansam cautarea paralela pentru restul numerelor (de la limit + 1 pana la N)
    // Vom stoca rezultatele gasite intr-un vector temporar 'foundPrimes'
    vector<int> foundPrimes;
    
    // Apelam worker-ul doar daca mai avem interval de verificat
    if (limit + 1 < N) {
        worker(limit + 1, N + 1, smallPrimes, threads, foundPrimes);
    }

    // Pas 4: Combinam rezultatele
    allPrimes.insert(allPrimes.end(), foundPrimes.begin(), foundPrimes.end());

    // Afisare
    cout << "Numere prime pana la " << N << ":\n";
    for (int p : allPrimes) {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}
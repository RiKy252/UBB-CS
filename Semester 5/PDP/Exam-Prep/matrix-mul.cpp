#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>

using namespace std;

void worker(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int rStart, int rEnd, int nrThreads)
{
    if (nrThreads <= 1) {
        for (int i = rStart; i < rEnd; i++) {
            for (int j = 0; j < A.size(); j++) {
                C[i][j] = 0;
                for (int k = 0; k < A[0].size(); k++) {
                    C[i][j] += (A[i][k] * B[k][j]);
                }
            }
        }
        return;
    }

    int mid = rStart + (rEnd - rStart) / 2;

    // calc left
    thread t(worker, ref(A), ref(B), ref(C), rStart, mid, nrThreads / 2);

    // calc right
    worker(A, B, C, mid, rEnd, nrThreads - nrThreads / 2);

    // join
    t.join();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <numar_threaduri>" << endl;
        return 1;
    }
    int threads = atoi(argv[1]);
    vector<vector<int>> a = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4},
    };
    vector<vector<int>> b = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4},
    };
    int numRows = a.size();
    int numCols = b[0].size();
    vector<vector<int>> c(numRows, vector<int>(numCols));


    worker(a, b, c, 0, numRows, threads);
    cout << "Matricea Rezultat C:" << endl;
    for(const auto& row : c) {
        for(int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
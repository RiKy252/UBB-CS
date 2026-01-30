#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void worker(const vector<vector<int>>& m, int rStart, int rEnd, int nrThreads, long& result) {
    // base case
    if (nrThreads <= 1) {
        result = 0;
        for (int i = rStart; i < rEnd; i++) {
            for (int j = 0; j < m[i].size(); j++) {
                result += m[i][j];
            }
        }
        return ;
    }
    // divide (binary)
    int rMid = rStart + (rEnd - rStart) / 2;

    // calculate left
    long leftResult = 0;
    thread t(worker, ref(m), rStart, rMid, nrThreads / 2, ref(leftResult));

    // calculate right
    long rightResult = 0;
    worker(m, rMid, rEnd, nrThreads - nrThreads / 2, rightResult);

    // join
    t.join();
    result = leftResult + rightResult;
}

int main() 
{
    // Matrice 4x4 de exemplu
    vector<vector<int>> mat = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4},
        {4, 4, 4, 4},
        {4, 4, 4, 4},
        {4, 4, 4, 4},
        {4, 4, 4, 4},
        {4, 4, 4, 4},
        {4, 4, 4, 4}
    };
    
    int threads = 12;
    long totalSum = 0;

    worker(mat, 0, mat.size(), threads, totalSum);

    cout << "Suma elementelor matricei: " << totalSum << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void worker(const vector<int>& a, const vector<int>& b, int start, int end, int nrThreads, long& result) 
{
    if (nrThreads <= 1) 
    {
        result = 0;
        for (int i = start; i < end; i++) 
        {
            result += (a[i] * b[i]);
        }
        return;
    }

    int mid = start + (end - start) / 2;
    long leftResult = 0;
    long rightResult = 0;

    // left calculation
    thread t(worker, ref(a), ref(b), start, mid, nrThreads / 2, ref(leftResult));

    // right calculation
    worker(a, b, mid, end, nrThreads - nrThreads / 2, rightResult);

    // wait all threads
    t.join(); 
    result = leftResult + rightResult;
}

int main() 
{
    vector<int> a = {1, 4, 5, 3, 2, 1, 6, 7, 8, 9, 10};
    vector<int> b = {2, 3, 1, 4, 5, 4, 3, 2, 2, 1, 2};
    int nrThreads = 4;
    
    long totalProd = 0;
    
    worker(a, b, 0, a.size(), nrThreads, totalProd);

    cout << "Scalar product: " << totalProd << '\n';
    return 0;
}
#include <iostream>
#include <vector>
#include <future>

using namespace std;

long worker(const vector<int>& a, const vector<int>& b, int start, int end, int nrThreads)
{
    if (nrThreads <= 1) 
    {
        long prod = 0;
        for (int i = start; i < end; i++) 
        {
            prod += (a[i] * b[i]);
        }
        return prod;
    }
    int mid = start + (end - start) / 2;
    auto task = async(launch::async, worker, ref(a), ref(b), start, mid, nrThreads / 2);
    long rightProd = worker(a, b, mid, end, nrThreads - nrThreads / 2);
    return task.get() + rightProd;
}

int main() 
{
    vector<int> a = {1, 4, 5, 3, 2, 1, 6, 7, 8, 9, 10};
    vector<int> b = {2, 3, 1, 4, 5, 4, 3, 2, 2, 1, 2};
    int threads = 4;
    long prod = worker(a, b, 0, a.size(), threads);
    cout << "Scalar product: " << prod << '\n';
    return 0;
}
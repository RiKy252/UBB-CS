#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx;
void critical_section(int& id) {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < 1000; ++i) {
            id += 1;
        }
    std::cout << "Number IN THREAD: " << id << std::endl;
}


int main() {
    int id = 2;
    // std::cout << "Build Number: " << id << std::endl; //("Build")
    std::thread t1(critical_section, std::ref(id));
    std::cout << "Number: " << id << std::endl;

    std::thread t2(critical_section, std::ref(id));
    std::cout << "Number: " << id << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));



    t1.join();
    // t2.join();

    return 0;
}

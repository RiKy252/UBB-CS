#include <iostream>
#include <thread>

void print_numbers() {
    for (int i = 0; i < 100; ++i) {
        std::cout << "Number: " << i << std::endl;
    }
}

int main() {
    std::thread t(print_numbers);

    std::thread t2(print_numbers);

    std::thread t3(print_numbers);

    // t.join();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}
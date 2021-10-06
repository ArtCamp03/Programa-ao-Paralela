#include <iostream>

int main() {
    // run the statement after the pragma in the current team
    #pragma omp parallel num_threads(2)
    std::cout << "Hello world!" << std::endl;
}

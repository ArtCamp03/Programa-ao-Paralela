#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include "utility.h"

//  execuçao
//  g++ -pthread main.cc -o main  -I ./

// variavel global menor valor
uint64_t v_menor;

// objeto mutex compartilhado
std::mutex n_mutex;

void EncontraMenor(uint64_t &vect, uint64_t start, uint64_t end)
{
    uint64_t valor = 0;
    for (uint64_t i = start; i < end; i++)
    {
        valor = vect * i;

        if (valor < v_menor and valor > 0)          // exclui o zero como menor
        {
            //n_mutex.lock();     //bloqueia a condiçao
            std::lock_guard<std::mutex> guard(n_mutex);
            v_menor = valor;
            //n_mutex.unlock();   //desbloqueia a condiçao
        }
       

        // imprime valores do vetor
        //std::cout << "valor:" << valor << std::endl;
    }
}

int main()
{
    // NUM_THREADS da biblioteca "utility.h" sera o numero de Threads geradas
    uint64_t n_elements = 1000 * 1000 * 100;
    uint64_t step = n_elements / NUM_THREADS;
    // vetor de threads
    std::vector<std::thread> threads;

    std::vector<uint64_t> Minimo(n_elements);

    auto vec = uniformRandomVector(n_elements, 1000);

    // copia dao vetor de auto para uint64_t
    copy(vec.begin(), vec.end(), Minimo.begin());
    //std::cout << Minimo[0] << std::endl;

    // inicializa variavel global com primeiro valor de vec;
    v_menor = Minimo[0];

    for (uint64_t i = 0; i < NUM_THREADS; i++)
    {
        threads.push_back(std::thread(EncontraMenor, std::ref(Minimo[i]), i * step, (i + 1) * step));
        //std::cout << "Thread: " << i << std::endl;
    }

    // min_element esta incluso na biblioteca <algorithm>
    //std::cout << *std::min_element(Minimo.begin(), Minimo.end()) << std::endl;

    for (std::thread &t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    /*
    //PrintVector(Minimo);
    for(uint64_t m : Minimo){
        std::cout << m <<std::endl;
    }
    */

    std::cout << "Resultado menor: " << v_menor << std::endl;

    return 0;
}
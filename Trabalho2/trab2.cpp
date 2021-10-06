// BACHARELADO EM CIENCIA DA COMPUTAÇAO UFMT
// Disciplina: Programaçao Paralela
// Aluno: Artur R Campos

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <omp.h>

#include "hpc_helpers.hpp"
//g++ -O2 -std=c++14  -fopenmp trab2.cpp -o trab2

void sequencial_sort(std::vector<unsigned int > &X){
    unsigned int i,j, count, N = X.size();
    std::vector<unsigned int> tmp(N);

    std::cout << "Resultado :" << std::endl;

        # pragma omp parallel for private(j)

        for(i=0; i<N; i++){
            count = 0;
            
            TIMERSTART(check)
            for(j=0; j<N; j++)
                if(X[j] < X[i] || X[j] == X[i] && j < i)
                    //# pragma omp atomic
                    //# pragma omp critical
                    //{
                        count++;
                    //}
                    
            TIMERSTOP(check)

            tmp[count] = X[i];
            //std::cout << tmp[count] << std::endl;
            std::cout << "contador: " << count << std::endl;
        }
        std::copy(tmp.begin(), tmp.end(), X.begin());
}

int main(){
    // Tamanho do vetor a ser preenchido
    unsigned int num = 100 * 100 * 10;
    std::vector <unsigned int> y(num);

    std::cout << "Vetor inserido :" << std::endl;
    
    TIMERSTART(init)
    for(int k = 0 ; k < num ; k++){
        //srand(i);
        y[k] = rand();
        std::cout << y[i] << std::endl;
    }
    TIMERSTOP(init)

    std::cout <<  std::endl;

    sequencial_sort(y);

}
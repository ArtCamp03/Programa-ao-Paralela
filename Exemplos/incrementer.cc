#include<iostream>
#include<omp.h>

int g_counter;


void incrementer(){
  for(int i = 0; i<100; i++)
    #pragma omp critical
    {
      g_counter++;
   }
}

int main(){
  int N = 1000, count=0;
  for(int i = 0; i<N; i++){
    g_counter = 0;

    #pragma omp parallel for
    for(int j=0; j<100; j++){
        incrementer();
    }

    if(g_counter<10000)
        std::cout << g_counter <<" ";
  }
  // std::cout << count <<" times"<<std::endl;

}

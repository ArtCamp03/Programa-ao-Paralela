#include <iostream>
#include <omp.h>



int main(){

  uint64_t partial_Sum, total_Sum;

    #pragma omp parallel private(partial_Sum) shared(total_Sum) num_threads(8)
    {
        partial_Sum = 0;
        total_Sum = 0;

        #pragma omp parallel for
            for(int i = 0; i <= (1000*1000*1000); i++){
                partial_Sum += i;
            }

        //Create thread safe region.
        #pragma omp critical
        {
                //add each threads partial sum to the total sum
                total_Sum += partial_Sum;
        }
    }
    std::cout <<"Total Sum: "<<total_Sum;
    return 0;

}

#include <iostream>

int main(){
  int i, j;
  #pragma omp parallel for private(j)
  for(i=0; i<4; i++){
    for(j=0; j<4; j++)
      printf("%d %d\n",i,j);
  }




}

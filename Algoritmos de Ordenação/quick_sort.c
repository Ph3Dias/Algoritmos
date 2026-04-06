#include <stdio.h>

int partition(int* array, int r, int p){
  chave = *(array+p)

  int j=0, i=j-1, aux;

  for(j; j<p; j++){
    
    if(*(array+j)<chave){
      i++;
      aux = *(array+i);
      *(array+i) = *(array+j);
      *(array+j) = aux;
    }
    
  }
  aux = *(array+i+1);
  *(array+i+1) = *(array+p);
  *(array+p) = aux;
  return i+1;
}

void quick_sort(int* array, int r, int p){
  if r<p{
    q = partition(array, r, p);
    quick_sort(array, r, q-1);
    quick_sort(array. q+1, p);
  }
}

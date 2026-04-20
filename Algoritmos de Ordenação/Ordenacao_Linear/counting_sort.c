#include <stdio.h>
void counting_sort(int* array, int n, int k){
  int array_contagem[k];
  int array_ordenada[n];
  
  int i = 0;
  
  for(i = 0; i < k; i++)
    array_contagem[i] = 0;
    
  for( i = 0; i < n; i++)
    array_contagem[array[i]] = array_contagem[array[i]] + 1;
    
  for(i = 1; i < k; i++)
    array_contagem[i] = array_contagem[i] + array_contagem[i-1];
    
  for(i = n-1; i>=0; i--){
    array_ordenada[array_contagem[array[i]]-1] = array[i];
    array_contagem[array[i]] = array_contagem[array[i]]-1;
  }
  
  for(i = 0; i<n; i++)
    array[i] = array_ordenada[i];
  
}

void counting_sort_adaptado(int* array, int n, int exp){

    int array_contagem[10];
    int array_ordenada[n];

    int i, digito;

  
    for(i = 0; i < 10; i++){

        array_contagem[i] = 0;
  
    }   

    for( i = 0; i < n; i++){

        digito = (array[i]/exp)%10;
        array_contagem[digito] = array_contagem[digito]+1;
    
    }

    for(i = 1; i < 10; i++){

        array_contagem[i] = array_contagem[i] + array_contagem[i-1];
    
    }

    for(i = n-1; i >= 0; i--){
        
        digito = (array[i]/exp)%10;
        array_ordenada[array_contagem[digito]-1] = array[i];
        array_contagem[digito] = array_contagem[digito]-1;
    
    }
    for(i=0;i<n;i++)
        array[i]=array_ordenada[i];

}
void radix_sort(int* array, int n, int digitos){
    
    int i;
    int exp = 1;

    for(i = 0; i< digitos; i++){
        
        counting_sort_adaptado(array,n,exp);
        exp = exp*10;

    }

}


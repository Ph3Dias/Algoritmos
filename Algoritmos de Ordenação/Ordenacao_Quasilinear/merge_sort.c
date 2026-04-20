void merge(int* array, int min, int med, int max){
    
    int n1, n2;
    int i, j, k;
    int array_esquerda[n1];
    int array_direita[n2];
    

    n1 = med - min + 1;
    n2 = max - med;
    

    for(i=0; i < n1; i++){
        
        array_esquerda[i] = array[min + i];
   
    }

    for(j; j<n2; j++){

        array_direita[j] = array[med + j + 1];

    }

    i = 0; j = 0; k = min;
    
    while((k<=max) && (i<n1) && (j<n2)){

        if(array_esquerda[i]<array_direita[j]){

            array[k] = array_esquerda[i];
            i++;

        }
        else{

            array[k] = array_direita[j];
            j++;

        }

        k++;
    }

    while(i < n1){

        array[k] = array_esquerda[i];
        k++; i++;

    }

    while(j < n2){
        
        array[k] = array_direita[j];
        k++; j++;
    }
    
}

void merge_sort(int* array, int min, int max){

    if(min < max){
        int med = (max + min)/2;
        merge_sort(array, min, med);
        merge_sort(array, med + 1, max);
        merge(array, min, med, max);
    }

}
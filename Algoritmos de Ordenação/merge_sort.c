void merge(int* array, int min, int med, int max){
    
    int n1, n2; // n1 é o número de elementos da equerda e n2 o número de elementos da direita
    n1 = med-min+1;
    n2 = max -(med+1)+1;

    // max = posição do último elemento da lista original. a b c d 
    // min = posição do primeiro elemento da lista original
    // med = posição que divide a lista original em dois intervalos, A[min, med] e A[med+1, max]
    
    int array_esquerda[n1];
    int array_direita[n2];

    int i=0, j=0;

    for(i;i<n1;i++){
        array_esquerda[i] = *(array+min+i);
    }
    for(j; j<n2; j++){

        array_direita[j] = *(array+med+j+1);
    }
    i = 0;
    j = 0;
    int k;
    
    for(k = min; k <= max; k++){
        if (i < n1 && j < n2){
            if (array_esquerda[i] <= array_direita[j]){
                array[k] = array_esquerda[i++];
            } 
            else {
                array[k] = array_direita[j++];
            }   
        }
        else if (i < n1){
            array[k] = array_esquerda[i++];
        }
        else{
            array[k] = array_direita[j++];
        }
    }
    
}

void merge_sort(int* array, int min, int max){
    if (min<max){
        int med = (max+min)/2;
        merge_sort(array, min, med);
        merge_sort(array, med+1, max);
        merge(array, min, med, max);
    }

}
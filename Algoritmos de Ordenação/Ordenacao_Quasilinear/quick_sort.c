int Partition(int* array, int inicio, int fim){

    int pivot, aux;
    int j, i;

    i = inicio - 1;
    pivot = array[fim];

    for(j = inicio; j < fim; j++){

        if(array[j] <= pivot){
            i++;
            aux = array[j];
            array[j] = array[i];
            array[i] = aux;
        }
    }
    
    aux = array[fim];
    array[fim] = array[i+1];
    array[i+1] = aux; 

    return i+1;
}

void quick_sort(int* array, int inicio, int fim){

    if (inicio < fim){
        
        int pivot_index = Partition(array, inicio, fim);

        quick_sort(array, inicio, pivot_index - 1);
        quick_sort(array, pivot_index + 1, fim);

    }
}

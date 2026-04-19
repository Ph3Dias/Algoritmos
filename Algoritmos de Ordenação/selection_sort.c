void selection_sort(int* array, int tamanho_array){
    
    int menor_elemento_index;
    int i, j, aux;

    for( i = 0 ; i < tamanho_array; i++){

        menor_elemento_index = i;

        for( j = i + 1; j < tamanho_array; j++){
            
            if(array[menor_elemento_index] > array[j]){

                menor_elemento_index = j;

            }

        }

        aux = array[menor_elemento_index];
        array[menor_elemento_index] = array[i];
        array[i] = aux;
    }

}


void bubble_sort(int* array, int tamanho_array){

    int i, j, aux;
 

    for(i = 0; i < tamanho_array; i++){

        for(j = 0; j < tamanho_array - i - 1; j++){

            if(array[j] > array[j + 1]){
            
                aux = array[j];
                array[j] =  array[j+1];
                array[j+1] = aux; 
                
            }
        }
    }
}




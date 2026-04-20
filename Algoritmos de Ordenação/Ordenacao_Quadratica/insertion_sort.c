
void insertion_sort(int *array, int tamanho_array){

    int j, i, chave;

    for(j = 1; j < tamanho_array; j++){

        chave = array[j];
        i = j - 1;

        while((i >= 0) && (array[i] > chave)){

            array[i + 1] = array[i];
            i--;

        }
        
        array[i + 1] = chave;

    }
}
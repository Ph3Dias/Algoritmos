
void bubble_sort(int* array, int tam){

    int i, j;
    int elemento_atual_index = 0;
    int aux;
    for(i = 0;i < tam;i++){
        
        for(j = 0;j < tam-i-1;j++){

            if(*(array + j) > *(array + j+1)){
                aux = *(array + j);
                *(array + j) =  *(array + j + 1);
                *(array + j + 1) = aux;
            }

        }

    }

}




void selection_sort(int* array, int tam){
    
    int menor_candidato_index;
    int i, j, aux;

    for(i=0;i<tam;i++){

        menor_candidato_index = i;

        for(j=i;j<tam;j++){
            
            if(*(array + menor_candidato_index)> *(array+j)){

                menor_candidato_index = j;

            }

        }
        aux = *(array + menor_candidato_index);
        *(array  + menor_candidato_index) = *(array + i);
        *(array + i) = aux;
    }

}


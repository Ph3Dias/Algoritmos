
int* insertion_sort(int *array, int tamanho_array){

    int j, i;

    for(j=1; j<tamanho_array;j++){

        int chave = *(array+j);
        i= j-1;

        while((i >= 0) && (*(array + i) > chave)){
            *(array + i+1) = *(array+i);
            i--;
        }
        *(array+i+1)= chave;
    }
    return array;
}
/*Funcionamento: dado uma array, esse algoritmo ordena de forma crescente, usando invariante de laço.
Primeiramente, vamos considerar o caso base, onde a array possui apenas um elemento. Por definição, uma lista de elemento
único está ordenada. Para os próximos passos, vamos considerar que, para um elemento j, os elementos do intervalo [0, j-1] estão ordenados.
O while aninhado usa dessa hipotese ao fazer comparações sucessivas e arredamentos para encontrar a posição em que o elemento de posição j
deve passar a ocupar. A condição desse while só funciona por considerarmos que o intervalo [0, j-1] está ordenado, como a relação "maior que"
é uma relação de ordem, podemos encontrar a posição onde o elemento de j deveria estar, pois é garantido que o elemento de uma posição k é
maior que um elemento da posição k-1. Se esse while fosse utilizado em um intervalo não ordenado [0,j-1], a posição onde o elemento j
seria encaixado é a anterior à primeira ocorrência de um elemento maior que j. */

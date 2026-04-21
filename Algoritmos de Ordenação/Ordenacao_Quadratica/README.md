# Algoritmos de Ordenação em Tempo Quadrático

## Motivação

Esses algoritmos são os primeiros a serem apresentados para o aluno de TI, dado sua simplicidade e facilidade de implementação.

## Bubble Sort

### Lógica do Bubble Sort

Esse algoritmo funciona deslocando os elementos da entrada para direita até encontrarem sua posição adequada. Vale destacar que o `Bubble Sort` começa ordenando a direita da array.

``` C
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
```

O algoritmo começa selecionando o primeiro elemento da array. No **laço aninhado**, é feito a comparação entre o elemento atual e o seu sucessor. Caso o sucessor seja menor que o elemento atual, é feito a troca de valores entre o atual e o sucessor. Caso contrário, nada acontece. Em ambos os casos *j* é atualizado. Ao fim do **laço aninhado**, pelo menos um elemento estará na posição correta, sendo sua posição a direita dos elementos desordenados. Dessa forma, não é necessário que o **laço aninhado** itere por toda a lista, ele precisa iterar apenas de 0 até o índice *tamanho_array -i -1*. **OBS: *i* representa a quantidade de elementos que foram ordenados.**

**Exemplo do funcionamento do *for* aninhado:** array[4] = {5,4,6,2,1}, i = 0

j | array no começo da iteração | elemento atual | array\[j]>array[j+1]\?
-- | - | - | -
0: | {5,4,6,2,1} | 5 | sim
1: | {4,5,6,2,1} | 5 | não
2: | {4,5,6,2,1} | 6 | sim
3: | {4,5,2,6,1} | 6 | sim

Fim do Laço: array = {4,5,2,1,6}.

### Tempo Assintótico do Bubble Sort

Começando pelo **laço aninhado**, temos:

``` C
    for(j = 0; j < tamanho_array - i - 1; j++){ // T(1)

        if(array[j] > array[j + 1]){ // T(tamanh_array-i-1)
            
            aux = array[j]; // T(tamanho_array-i-1)
            array[j] =  array[j+1]; // T(tamanho_array-i-1)
            array[j+1] = aux; // T(tamanho_array-i-1)
                
        }
    }
    // T(for aninhado) = T(1)+ 4*T(tamanho_array-i-1) = O(tamanho_array)
```

Substituindo o bloco de código do **laço aninhado** por uma função *laco_interno()*, temos:

``` C
    int i, j; // T(1)
    int aux; // T(1)
    

    for(i = 0; i < tamanho_array; i++){ // T(1)
        
        laco_interno(); // T(tamanho_array)*T(laco_interno)
    }

    // T(bubble_sort) = 3*T(1) + T(tamanho_array)*(T(1)+ 4*T(tamanho_array-i-1)) = T(1)*(T(tamanho_array)+3) + 4*T(tamanho_array)*T(tamanho_array) = O(n²)
```

O tempo de todos os casos são iguais, visto que o `Bubble Sort` sempre itera sobre a array fazendo comparações.

## Selection Sort

### Lógica Selection Sort

O `Selection Sort` seleciona o primeiro elemento da subarray não ordenada \[i, n] e percorre o restante da array buscando o menor elemento possível, para no final fazer a troca. Assim, o `Selection Sort` ordena a array pela esquerda.

``` C
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
```

Como consideramos que o intervalo \[i, n] dá entrada estão desordenados, cada iteração do **laço externo** começará considerando que o menor elemento é o *array[i]*. O **laço aninhado** seguirá procurando elementos menores que o menor elemento atual. Se encontrar, *menor_elemento_index* será atribuído ao *j* que satisfez a comparação. Caso contrário, *menor_elemento_index* segue inalterado. Ao fim desse laço, uma troca é feita entre o elemento na posição *i* e o elemento na posição *menor_elemento_index*. Note que essa é a única troca feita na iteração *i*.  
Vale destacar que na próxima iteração de *i*, o *for interno* começa na posição *i*+1. Isso é uma pequena otimização, pois é trivial o fato que *array[j] > array[j]* é falso.

``` C
void selection_sort(int* array, int tamanho_array){
    
    int menor_elemento_index; // T(1)
    int i, j, aux; // T(1)

    for( i = 0 ; i < tamanho_array; i++){ // T(1)

        menor_elemento_index = i; // T(tamanho_array)

        for( j = i + 1; j < tamanho_array; j++){ // T(tamanho_array)
            
            if(array[menor_elemento_index] > array[j]){ // T(tamanho_array)*T(tamanho_array-i)

                menor_elemento_index = j; // T(tamanho_array)*T(tamanho_array-i)

            }

        }

        aux = array[menor_elemento_index]; // T(tamanho_array)
        array[menor_elemento_index] = array[i]; // T(tamanho_array)
        array[i] = aux; // T(tamanho_array)
    }
    // T(selection_sort) = 3*T(1) + 5*T(tamanho_array) + 2*T(tamanho_array)*T(tamanho_array-i) = O(n²)
}
```

Apesar de ser um pouco mais eficiente que o `Bubble Sort`, o `Selection Sort` ainda é **O(n²)** para qualquer caso, pois o **laço aninhado** sempre faz checagens para tentar encontrar o menor elemento da lista.

## Insertion Sort

### Lógica do Insertion Sort

Para a implementação do `Insertion Sort`, assumimos que a array está ordenada no intervalo \[0,*i*]. Então, se um elemento *array\[i+1]* for menor que o elemento *array[i]*, então arredamos para a direita os elementos de *i* até *k*, onde *k* é o índice da posição correta do elemento *array\[i+1]. Para encontrar essa posição *k* vamos comparando o elemento *array[i+1]* com os demais elementos até encontrar um que seja maior que ele. Isso faz sentido lógico, pois estamos assumindo que a array é ordenada de \[0, i]. O caso base é `i = 0`, onde \[0, 0] possui apenas um elemento, trivialmente, uma lista de um único elemento está ordenada.

``` C
void insertion_sort(int *array, int tamanho_array){

    int i, j, chave;

    for(i = 1; i < tamanho_array; i++){

        chave = array[i];
        j = i - 1;

        while((j >= 0) && (array[j] > chave)){

            array[j + 1] = array[j];
            j--;

        }
        
        array[j + 1] = chave;

    }
}
```

Como o caso base é ordenado trivialmente, começamos com *i = 1*. A variável *chave* serve para armazenar o valor do elemento que queremos ordenar, pois o conteúdo da sua posição será sobreescrito. No *while*, é verificado se *j* é maior ou igual à zero e se o elemento *array[j]* é menor que a chave. Caso ambas comparações sejam atendidas, ocorrerá sucessivos arredamentos a direita até que uma das condições não seja satisfeita. No fim do *while*, posicionamos o elemento em *chave* na sua posição correta. **OBS: adicionamos 1 em *array[j+1]*, pois o *while* decrementa em um o *j* em toda iteração, até mesmo a iteração final.**
O procedimento se repete até que a array fique toda ordenada.

### Tempo Assintótico do Insertion Sort

``` C
void insertion_sort(int *array, int tamanho_array){

    int i, j, chave; // T(1)

    for(i = 1; i < tamanho_array; i++){ // T(1)

        chave = array[i]; // T(tamanho_array)
        j = i - 1; // T(tamanho_array)

        while((j >= 0) && (array[j] > chave)){ // T(tamanho_array)

            array[j + 1] = array[j]; // T(tamanho_array)*T(i)
            j--; // T(tamanho_array)*T(i)

        }
        
        array[j + 1] = chave; // T(tamanho_array

    }

    // T(insertion_sort) = 2*T(1) + 4*T(tamanho_array) +2*T(tamanho_array)*T(i)
}
```

O pior caso ocorre quando

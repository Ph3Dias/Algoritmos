# Algoritmos de Ordenação em tempo linear

## Motivação

Os `algoritmos de ordenação` de tempo **O(n²)** são os mais fáceis de entender e os de tempo **O(n*log n)** são ótimos quando usamos apenas os critérios de ordenação **"maior que"** e **"menor que"** sobre os elementos da entrada.  
Entretanto, ao assumir certas propriedades sobre os elementos da entrada, podemos produzir algoritmos com tempo menor que **O(n*log n)**.

## Counting Sort

### Lógica do Counting Sort

No `Counting Sort`, assumimos que os elementos da entrada pertencem a um intervalo **\[0, k\[** e a entrada tem tamanho **n**.  
Primeiramente, iremos inicializar duas arrays auxiliares, uma responsável pela contagem dos elementos da entrada e outra que servirá como uma cópia para a array original. Note que, se k for grande suficiente, a alocação do espaço dessa array_contagem não será possível. Assim, esse código não é ótimo em termos de memória.

```C
    int array_contagem[k];
    int array_copia[n];
```

Como um elemento qualquer da entrada pertence ao intervalo **\[0, k\[**, podemos usar o valor da entrada diretamente no índice da array_contagem, sendo essa a principal parte da implementação do `Counting Sort`.

``` C
    for(i = 0; i < k; i++)
        array_contagem[i] = 0;
    
    for( i = 0; i < n; i++)
        array_contagem[array[i]] = array_contagem[array[i]]+1;
```

O primeiro laço serve para zerar todos os elementos de array_contagem, o segundo serve para fazer a contagem da ocorrência dos elementos da array original, usando o valor de cada termo como índice na array_contagem.  
Exemplo\: Se k = 5 e array[4] = {4,3,1,1}, então array_contagem[5] = {0,2,0,1,1}.

``` C
 
  for(i = 1; i< k; i++)
    array_contagem[i] = array_contagem[i] + array_contagem[i-1];
```

Esse trecho faz uma soma acumulada nos elementos de array_contagem. Isso é útil, pois, dado um índice *i*, array_contagem\[ *i* ] irá conter a quantidade de elementos **menores ou iguais à** *i*; ou seja, isso fornece a posição o elemento *i* deve ocupar em uma listagem.  
Usando o exemplo anterior, temos\:  
`k = 5, array original = {4,3,1,1} e array_contagem = {0,2,0,1,1}`. Após fazer a soma acumulada, array_contagem fica igual à {0,2,2,3,4}.

Dessa forma, podemos usar array_contagem para saber qual a posição um elemento da array original deve ocupar. Como exemplo, se quisermos saber qual a posição o elemento 1 deve ocupar, acessamos o índice 1 em array_contagem e percebemos que existem 2 elementos **menores ou iguais à** 1, assim, 1 ocupa a segunda posição da array original, como as arrays em C começam em zero, 1 ocupa a posição de índice 1.

``` C
    for(i = n-1; i>=0; i--){
        array_ordenada[array_contagem[array[i]]-1] = array[i];
        array_contagem[array[i]] = array_contagem[array[i]]-1;
    }
```

Esse laço faz exatamente o processo descrito no último exemplo, percorrendo a array original da direita para esquerda, usando um iterador *i*. Descrevendo em linguagem natural, a primeira linha representa:  

1. Acessa array na posição *i*.
2. Consulta em array_contagem qual a posição do elemento array[ *i* ] deve ocupar.
3. Em array_ordenada, acessamos a posição fornecida pelo passo `2.`, reduzimos em 1 e atribuímos a essa posição o elemento do passo `1.`.

Em código, o trecho é equivalente à:

``` C
    int elemento_da_array;
    int posicao_do_elemento;

    for(i = n-1; i>=0; i--){
        elemento_da_array = array[i];
        posicao_do_elemento = array_contagem[elemento_da_array];

        array_copia[posicao_do_elemento] = elemento_da_array;
        array_contagem[elemento_da_array] = array_contagem[elemento_da_array]-1; // array_contagem[elemento_da_array]--;
     

    }
    
```

No fim de cada laço, é necessário decrementar uma unidade na posição associada em array_contagem para tratar casos de repetição de elementos.

``` C
    for(i = 0; i<n; i++)
        array[i] = array_ordenada[i];

```

Por fim, passamos a cópia ordenada de array para a própria array, concluindo o `Counting Sort`.

### Tempo Assintótico do Counting Sort

``` C
void counting_sort(int* array, int n, int k){
  int array_contagem[k]; // T(1)
  int array_ordenada[n]; // T(1)
  
  int i = 0; // T(1)
  
  for(i = 0; i < k; i++) // T(1)
    array_contagem[i] = 0; // T(k)
    
  for( i = 0; i < n; i++) // T(1)
    array_contagem[array[i]] = array_contagem[array[i]] + 1; // T(n)
    
  for(i = 1; i< k; i++) // T(1)
    array_contagem[i] = array_contagem[i] + array_contagem[i-1]; // T(k)
    
  for(i = n-1; i>=0; i--){ // T(1)
    array_ordenada[array_contagem[array[i]]-1] = array[i]; // T(n)
    array_contagem[array[i]] = array_contagem[array[i]]-1; // T(n)
  }
  
  for(i = 0; i<n; i++) // T(1)
    array[i] = array_ordenada[i]; // T(n)
  
  // T(counting_sort) = 8*T(1) + 2*T(k) + 4*T(n) = O(k+n)
}
```

O melhor tempo de execução de counting_sort ocorre quando `k é 1`. Nesse caso, T(counting_sort) = O(n).  

## Radix Sort

### Lógica do Radix Sort

O `Radix Sort` ordena uma entrada baseado em comparações nos dígitos dos elementos da entrada. Sua implementação depende de uma função de ordenação auxiliar de *tempo linear*. É possível fazer com funções de outras ordens, porém o tempo de computação fica mais custoso do que um algoritmo como o `Quick Sort`. Nesse caso, optei por utilizar `Counting Sort` como função auxiliar, podendo ser implementada com `Bucket Sort`.

Começamos o algoritmo assumindo que os elementos de uma entrada têm, no máximo, k digitos na base 10 e não-negativos, sendo k representado por *num_digitos*. Vale destacar que é possível generalizar o algoritmo para diferentes bases, mas escolhi base 10 para ficar mais didático. Com isso, o `Radix Sort` começa ordenando os elementos da entrada usando o dígito da unidades, depois da dezena, centena, até chegar no digito 10^k. Isso fica evidente no código abaixo:

``` C
void radix_sort(int* array, int n, int num_digitos){
    
    int i;
    int exp = 1;

    for(i = 0; i< num_digitos; i++){
        
        counting_sort_adaptado(array,n,exp);
        exp = exp*10;

    }

}
```

A variável *exp* indica para a função auxiliar *counting_sort_adaptado()* em qual casa decimal a ordenação deve ocorrer. Ou seja, começa com *exp = 1* \(unidade) e é multiplicado por 10 a cada iteração. **OBS: é possível dispensar o uso da variável exp passando a função pow(10,i), da biblioteca mathlib, como parâmetro, mas não utilizarei para facilitar o entendimento do código**.  
Agora vamos analisar como o algoritmo `Counting Sort` foi alterado para auxiliar o `Radix Sort`.

### Lógica counting_sort_adaptado()

``` C
  int array_contagem[10];
  int array_ordenada[n];

  int i, digito;
```

A primeira diferença entre o `Counting Sort` e sua versão adaptada é que, originalmente, a array_contagem tinha tamanho igual ao maior valor da array original, agora tem tamanho constante, no caso tamanho 10. Como o `Radix Sort` ordena os elementos atráves dos dígitos, array_contagem só precisa ter índices que variam de 0-9 (para base decimal). A variável *digito* serve para facilitar a compreensão do código e logo será detalhada.

``` C
  for(i = 0; i < 10; i++){

    array_contagem[i] = 0;
  
  }   

  for( i = 0; i < n; i++){

    digito = (array[i]/exp)%10;
    array_contagem[digito] = array_contagem[digito]+1;
    
  }
```

O primeiro laço desempenha o mesmo papel que desempenha no `Counting Sort` original. O segundo é um pouco diferente. Começa calculando o digito da casa decimal *exp* do elemento *array[i]*, depois acessa *array_contagem* na posição *digito* e incrementa. A função desse laço é contabilizar as ocorrências de cada dígito.

``` C
  for(i = 1; i < 10; i++){

    array_contagem[i] = array_contagem[i] + array_contagem[i-1];
    
  }
```

Esse laço permanece igual e tem a mesma função.

``` C
  for(i = n-1; i >= 0; i--){
        
    digito = (array[i]/exp)%10;
    array_ordenada[array_contagem[digito]-1] = array[i];
    array_contagem[digito] = array_contagem[digito]-1;
    
  }
```

Esse trecho começa fazendo o cálculo do dígito de *array[i]* para consultar na *array_contagem* a posição em que *array[i]* deve entrar, depois é decrementado em 1 a quantidade de ocorrências do digito de *array[i]*.

``` C
  for(i=0;i<n;i++)
    array[i]=array_ordenada[i];
```

Por fim, a array local ordenada é copiada para a array original. *counting_sort_auxiliar()* é executado para cada dígito dos elementos da entrada, fazendo uma ordenação similar a feita pela intuição humana.

### Tempo Assintótico do Radix Sort

``` C
void counting_sort_adaptado(int* array, int n, int exp){

    int array_contagem[10]; // T(1)
    int array_ordenada[n]; // T(1)

    int i, digito; // T(1)

  
    for(i = 0; i < 10; i++){ // T(1)

        array_contagem[i] = 0; // T(10)
  
    }   

    for( i = 0; i < n; i++){ // T(1)

        digito = (array[i]/exp)%10; // T(n)
        array_contagem[digito] = array_contagem[digito]+1; // T(n)
    
    }

    for(i = 1; i < 10; i++){ // T(1)

        array_contagem[i] = array_contagem[i] + array_contagem[i-1]; // T(10)
    
    }

    for(i = n-1; i >= 0; i--){ // T(1)
        
        digito = (array[i]/exp)%10; // T(n)
        array_ordenada[array_contagem[digito]-1] = array[i]; // T(n)
        array_contagem[digito] = array_contagem[digito]-1; // T(n)
    
    }
    for(i=0;i<n;i++) // T(1)
        array[i]=array_ordenada[i]; // T(n)

  // T(counting_sort_adaptado) = 8*T(1) + 2*T(10) + 6*T(n) = O(n)
}
```

Como fixamos a base numérica, sendo ela a base decimal, o tempo de *counting_sort_adaptado* é O\(n) apenas, mas é possível generalizar para uma base qualquer. Se for base k, podemos substituir o T\(10) por T\(k) e chegar na conclusão que T(counting_sort_adaptado) = O\(k+n). **OBS: se a base é k-ésima, então existem k dígitos nessa base**.  

``` C
void radix_sort(int* array, int n, int num_digitos){
    
    int i; // T(1)
    int exp = 1; // T(1)

    for(i = 0; i< num_digitos; i++){ // T(1)
        
        counting_sort_adaptado(array,n,exp); // T(num_digitos)* T(counting_sort_adaptado)
        exp = exp*10; // T(1)

    }
  // T(radix_sort) = 4*T(1) + T(num_digitos)*T(counting_sort_adaptado) = 4*T(1) + T(num_digitos*(10*n)) = O(num_digitos*n)
}
```

Se generalizarmos para qualquer base k, temos uma alteração no tempo de execução, que passa a ser O(num_digitos(k+n)). Portanto, esse algoritmo tem o melhor caso quando `o número de digitos é 1`.

Vamos estudar **Hash Maps** em C, seguindo um passo a passo claro para que você possa entender e juntar os códigos depois. Um Hash Map é uma estrutura de dados que associa chaves a valores, permitindo acesso rápido aos dados.

## Implementação de um Hash Map em C

### Passo 1: Definindo a Estrutura do Nó

Primeiro, vamos definir a estrutura do nó que armazenará as chaves e valores.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Tamanho máximo da tabela hash

typedef struct No {
    char chave[50];          // Chave do par chave-valor
    int valor;              // Valor associado à chave
    struct No* proximo;     // Ponteiro para o próximo nó (para lidar com colisões)
} No;
```

### Passo 2: Definindo a Estrutura do Hash Map

Agora, vamos definir a estrutura do Hash Map.

```c
typedef struct {
    No* tabela[MAX];  // Array de ponteiros para nós
} HashMap;
```

### Passo 3: Inicializando o Hash Map

Vamos criar uma função para inicializar o Hash Map.

```c
void inicializarHashMap(HashMap* hm) {
    for (int i = 0; i < MAX; i++) {
        hm->tabela[i] = NULL;  // Inicializa todas as entradas como NULL
    }
}
```

### Passo 4: Função de Hashing

Precisamos de uma função para calcular o índice da tabela hash com base na chave.

```c
int hash(char* chave) {
    int soma = 0;
    for (int i = 0; i < strlen(chave); i++) {
        soma += chave[i];  // Soma os valores ASCII da chave
    }
    return soma % MAX;  // Retorna o índice na tabela
}
```

### Passo 5: Adicionando Elementos ao Hash Map

Agora, vamos implementar uma função para adicionar pares chave-valor ao Hash Map.

```c
void adicionar(HashMap* hm, char* chave, int valor) {
    int indice = hash(chave);  // Calcula o índice usando a função de hash
    
    No* novo_no = (No*)malloc(sizeof(No));  // Aloca memória para um novo nó
    strcpy(novo_no->chave, chave);           // Copia a chave para o novo nó
    novo_no->valor = valor;                   // Define o valor
    novo_no->proximo = hm->tabela[indice];   // Aponta para o primeiro nó existente
    
    hm->tabela[indice] = novo_no;            // Insere o novo nó na tabela
}
```

### Passo 6: Buscando Elementos no Hash Map

Vamos implementar uma função para buscar um valor com base na chave.

```c
int buscar(HashMap* hm, char* chave) {
    int indice = hash(chave);  // Calcula o índice usando a função de hash
    
    No* atual = hm->tabela[indice];  // Começa a busca no índice calculado
    
    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {  // Verifica se a chave corresponde
            return atual->valor;                  // Retorna o valor se encontrado
        }
        atual = atual->proximo;                   // Move para o próximo nó
    }
    
    return -1;  // Retorna -1 se a chave não for encontrada
}
```

### Passo 7: Exibindo Elementos do Hash Map

Vamos adicionar uma função para exibir todos os pares chave-valor no Hash Map.

```c
void exibirHashMap(HashMap* hm) {
    for (int i = 0; i < MAX; i++) {
        No* atual = hm->tabela[i];
        if (atual != NULL) {
            printf("Índice %d: ", i);
            while (atual != NULL) {
                printf("(%s, %d) -> ", atual->chave, atual->valor);
                atual = atual->proximo;
            }
            printf("NULL\n");
        }
    }
}
```

### Passo 8: Testando o Hash Map

Agora, vamos testar nossa implementação.

```c
int main() {
    HashMap meu_hashmap;
    inicializarHashMap(&meu_hashmap);  // Inicializa o Hash Map

    // Adicionando elementos ao Hash Map
    adicionar(&meu_hashmap, "chave1", 10);
    adicionar(&meu_hashmap, "chave2", 20);
    adicionar(&meu_hashmap, "chave3", 30);

    // Buscando elementos no Hash Map
    printf("Valor associado à 'chave1': %d\n", buscar(&meu_hashmap, "chave1"));
    
    // Exibindo todos os elementos do Hash Map
    exibirHashMap(&meu_hashmap);

    return 0;
}
```

## Resumo

- **Estrutura do Nó**: Definimos a estrutura `No` com chaves e valores.
- **Estrutura do Hash Map**: Definimos a estrutura `HashMap` com um array de ponteiros.
- **Inicialização**: Implementamos uma função para inicializar o Hash Map.
- **Função de Hashing**: Criamos uma função que calcula o índice na tabela.
- **Adicionar Elementos**: Implementamos uma função para adicionar pares chave-valor.
- **Buscar Elementos**: Implementamos uma função para buscar valores com base nas chaves.
- **Exibir Elementos**: Implementamos uma função para mostrar todos os pares no Hash Map.
- **Testes**: Testamos as funcionalidades no `main`.

## Executando no Computador

Para rodar os códigos:

1. **Junte todos os códigos** em um único arquivo com extensão `.c`, por exemplo, `hashmap.c`.
2. **Compile** usando `gcc`:

   ```bash
   gcc hashmap.c -o hashmap
   ```

3. **Execute**:

   ```bash
   ./hashmap
   ```

Se precisar de mais ajuda ou tiver dúvidas sobre qualquer parte do processo, é só avisar!
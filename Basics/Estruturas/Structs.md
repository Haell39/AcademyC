## Estudo Completo de Estruturas em C

Estruturas (ou `structs`) em C são uma maneira poderosa de agrupar diferentes tipos de dados sob um mesmo nome. Isso permite que você crie tipos de dados complexos que podem representar entidades do mundo real, como uma pessoa, um carro ou um livro. Vamos explorar o conceito de estruturas em C passo a passo.

### **O que são Estruturas?**

Uma estrutura é uma coleção de variáveis (membros) de diferentes tipos agrupadas sob um único nome. Isso permite que você trate esses dados como uma única entidade.

**Sintaxe para declarar uma estrutura:**

```c
struct NomeDaEstrutura {
    tipo membro1;
    tipo membro2;
    // outros membros...
};
```

**Exemplo:**

```c
struct Pessoa {
    char nome[50];
    int idade;
    float altura;
};
```

### **Criando Variáveis de Estruturas**

Após definir uma estrutura, você pode criar variáveis desse tipo.

**Exemplo:**

```c
struct Pessoa pessoa1; // Declara uma variável do tipo Pessoa
```

### **Acessando Membros da Estrutura**

Para acessar os membros de uma estrutura, utilize o operador ponto (`.`).

**Exemplo:**

```c
strcpy(pessoa1.nome, "João");
pessoa1.idade = 30;
pessoa1.altura = 1.75;
```

### **Estruturas Aninhadas**

Você pode ter estruturas dentro de outras estruturas, permitindo a criação de dados mais complexos.

**Exemplo:**

```c
struct Endereco {
    char rua[100];
    int numero;
};

struct Pessoa {
    char nome[50];
    int idade;
    struct Endereco endereco; // Estrutura aninhada
};
```

### **Funções com Estruturas**

Você pode passar estruturas como argumentos para funções. Por padrão, as estruturas são passadas por valor, mas você também pode passar ponteiros para elas.

**Exemplo: Passagem por Valor**

```c
void imprimePessoa(struct Pessoa p) {
    printf("Nome: %s\n", p.nome);
}
```

**Exemplo: Passagem por Ponteiro**

```c
void alteraIdade(struct Pessoa *p) {
    p->idade += 1; // Aumenta a idade em 1
}
```

### **Exercícios Práticos**

1. **Cadastro Simples:**
   - Crie um programa que permita ao usuário cadastrar informações sobre uma pessoa (nome, idade e altura) e imprima esses dados.

   ```c
   #include <stdio.h>
   #include <string.h>

   struct Pessoa {
       char nome[50];
       int idade;
       float altura;
   };

   int main() {
       struct Pessoa pessoa1;

       printf("Digite o nome: ");
       fgets(pessoa1.nome, 50, stdin);
       printf("Digite a idade: ");
       scanf("%d", &pessoa1.idade);
       printf("Digite a altura: ");
       scanf("%f", &pessoa1.altura);

       printf("\nDados cadastrados:\n");
       printf("Nome: %s", pessoa1.nome);
       printf("Idade: %d\n", pessoa1.idade);
       printf("Altura: %.2f\n", pessoa1.altura);

       return 0;
   }
   ```

2. **Estruturas Aninhadas:**
   - Modifique o programa anterior para incluir um endereço (rua e número) na estrutura `Pessoa`.

   ```c
   #include <stdio.h>
   #include <string.h>

   struct Endereco {
       char rua[100];
       int numero;
   };

   struct Pessoa {
       char nome[50];
       int idade;
       float altura;
       struct Endereco endereco; // Estrutura aninhada
   };

   int main() {
       struct Pessoa pessoa1;

       printf("Digite o nome: ");
       fgets(pessoa1.nome, 50, stdin);
       printf("Digite a idade: ");
       scanf("%d", &pessoa1.idade);
       printf("Digite a altura: ");
       scanf("%f", &pessoa1.altura);
       
       printf("Digite a rua: ");
       getchar(); // Limpa o buffer
       fgets(pessoa1.endereco.rua, 100, stdin);
       printf("Digite o numero da casa: ");
       scanf("%d", &pessoa1.endereco.numero);

       printf("\nDados cadastrados:\n");
       printf("Nome: %s", pessoa1.nome);
       printf("Idade: %d\n", pessoa1.idade);
       printf("Altura: %.2f\n", pessoa1.altura);
       printf("Endereco: %sNumero %d\n", pessoa1.endereco.rua, pessoa1.endereco.numero);

       return 0;
   }
   ```

3. **Cálculo com Estruturas:**
   - Crie uma função que calcule e retorne a média das notas de um aluno armazenado em uma estrutura.

   ```c
   #include <stdio.h>

   struct Aluno {
       char nome[50];
       float nota1;
       float nota2;
   };

   float calculaMedia(struct Aluno aluno) {
       return (aluno.nota1 + aluno.nota2) / 2.0;
   }

   int main() {
       struct Aluno aluno;

       printf("Digite o nome do aluno: ");
       fgets(aluno.nome, 50, stdin);
       
       printf("Digite a primeira nota: ");
       scanf("%f", &aluno.nota1);
       
       printf("Digite a segunda nota: ");
       scanf("%f", &aluno.nota2);

       float media = calculaMedia(aluno);
       
       printf("A média de %s é %.2f\n", aluno.nome, media);

       return 0;
   }
   ```

### **Dicas Finais**

- **Pratique:** Experimente criar diferentes estruturas e manipular seus dados.
- **Use Comentários:** Documente seu código para facilitar a compreensão futura.
- **Explore:** Tente aninhar várias estruturas e criar matrizes de estruturas para entender melhor como elas funcionam.

Com este guia prático sobre estruturas em C, você deve estar bem preparado para utilizar esse recurso poderoso em seus programas!

Citations:
[1] http://mtm.ufsc.br/~azeredo/cursoC/aulas/cb10.html
[2] https://linguagemc.com.br/struct-em-c/
[3] https://www.inf.ufpr.br/roberto/ci067/09_estr.html
[4] https://embarcados.com.br/struct-registros-em-linguagem-c/
[5] https://edisciplinas.usp.br/pluginfile.php/4677232/mod_resource/content/1/aula11-estruturas1.pdf
[6] http://mtm.ufsc.br/~azeredo/cursoC/aulas/c510.html
[7] https://www.inf.pucrs.br/~pinho/LaproI/Structs/Structs.htm
[8] https://www.inf.pucrs.br/~pinho/LaproI/Vetores/Vetores.htm
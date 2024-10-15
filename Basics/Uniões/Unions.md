## Estudo Completo de Uniões em C

As uniões em C são uma estrutura de dados que permite armazenar diferentes tipos de dados em um único espaço de memória, mas apenas um membro pode ser acessado por vez. Isso é útil para economizar espaço quando você sabe que não precisará usar todos os membros simultaneamente. Vamos explorar as uniões em C passo a passo.

### **O que são Uniões?**

Uma união é uma estrutura de dados que permite armazenar diferentes tipos de dados em um único local na memória. Todos os membros da união compartilham o mesmo espaço de armazenamento, o que significa que a união ocupa o tamanho do maior membro.

**Sintaxe para declarar uma união:**

```c
union NomeDaUniao {
    tipo membro1;
    tipo membro2;
    // outros membros...
};
```

**Exemplo:**

```c
union Dados {
    int inteiro;
    float decimal;
    char caractere;
};
```

### **Criando Variáveis de Uniões**

Após definir uma união, você pode criar variáveis desse tipo.

**Exemplo:**

```c
union Dados dado1; // Declara uma variável do tipo Dados
```

### **Acessando Membros da União**

Para acessar os membros de uma união, utiliza-se o operador ponto (`.`). Lembre-se de que apenas um membro pode conter um valor válido por vez.

**Exemplo:**

```c
dado1.inteiro = 10; // Atribui um valor ao membro inteiro
printf("Inteiro: %d\n", dado1.inteiro);

dado1.decimal = 5.5; // Atribui um valor ao membro decimal
printf("Decimal: %f\n", dado1.decimal);
printf("Inteiro após atribuir decimal: %d\n", dado1.inteiro); // Valor inválido
```

### **Comportamento das Uniões**

Como mencionado, ao atribuir um valor a um membro da união, os valores dos outros membros podem ser corrompidos. Apenas o último valor atribuído será acessível corretamente.

**Exemplo:**

```c
union Dados dado1;
dado1.inteiro = 10;
dado1.decimal = 5.5;

printf("Inteiro: %d\n", dado1.inteiro); // Pode não ser válido
printf("Decimal: %f\n", dado1.decimal); // Válido

// O valor do inteiro não é mais confiável após atribuir ao decimal.
```

### **Uniões e Funções**

Você pode passar uniões como argumentos para funções, assim como estruturas. A passagem é feita por valor, mas você também pode passar ponteiros para uniões.

**Exemplo: Passagem por Valor**

```c
void imprimeDados(union Dados d) {
    printf("Inteiro: %d\n", d.inteiro);
}
```

**Exemplo: Passagem por Ponteiro**

```c
void alteraValor(union Dados *d) {
    d->decimal = 3.14; // Altera o valor do membro decimal
}
```

### **Exercícios Práticos**

1. **Uso Básico de União:**
   - Crie um programa que armazene um número inteiro e um número decimal em uma união e imprima ambos.

   ```c
   #include <stdio.h>

   union Dados {
       int inteiro;
       float decimal;
   };

   int main() {
       union Dados dado;

       dado.inteiro = 42;
       printf("Inteiro: %d\n", dado.inteiro);

       dado.decimal = 3.14;
       printf("Decimal: %f\n", dado.decimal);
       printf("Inteiro após atribuir decimal: %d\n", dado.inteiro); // Valor inválido

       return 0;
   }
   ```

2. **Controle de Tipo com União:**
   - Implemente uma função que recebe uma união e imprime seu valor dependendo do tipo armazenado.

   ```c
   #include <stdio.h>

   union Dados {
       int inteiro;
       float decimal;
       char caractere;
   };

   void imprimeTipo(union Dados d, char tipo) {
       if (tipo == 'i') {
           printf("Inteiro: %d\n", d.inteiro);
       } else if (tipo == 'f') {
           printf("Decimal: %f\n", d.decimal);
       } else if (tipo == 'c') {
           printf("Caractere: %c\n", d.caractere);
       }
   }

   int main() {
       union Dados dado;

       dado.inteiro = 10;
       imprimeTipo(dado, 'i');

       dado.decimal = 5.5;
       imprimeTipo(dado, 'f');

       return 0;
   }
   ```

3. **União com Enumeração:**
   - Crie uma união que armazene diferentes tipos e utilize uma enumeração para controlar qual tipo está sendo usado no momento.

   ```c
   #include <stdio.h>

   enum Tipo { INTEIRO, DECIMAL, CARACTERE };

   union Dados {
       int inteiro;
       float decimal;
       char caractere;
   };

   void imprimeDados(union Dados d, enum Tipo t) {
       switch(t) {
           case INTEIRO:
               printf("Inteiro: %d\n", d.inteiro);
               break;
           case DECIMAL:
               printf("Decimal: %f\n", d.decimal);
               break;
           case CARACTERE:
               printf("Caractere: %c\n", d.caractere);
               break;
       }
   }

   int main() {
       union Dados dado;

       dado.inteiro = 25;
       imprimeDados(dado, INTEIRO);

       dado.decimal = 7.89;
       imprimeDados(dado, DECIMAL);

       return 0;
   }
   ```

### **Dicas Finais**

- **Cuidado com o Uso:** Sempre lembre-se de que apenas um membro da união pode ter um valor válido por vez.
- **Documente seu Código:** Comente seu código para facilitar a compreensão sobre qual membro está sendo utilizado.
- **Explore:** Experimente criar uniões mais complexas e aninhadas para entender melhor suas aplicações.

Com este guia prático sobre uniões em C, você deve estar bem preparado para utilizar esse recurso eficaz em seus programas!

Citations:
[1] https://www.bosontreinamentos.com.br/programacao-em-linguagem-c/unions-em-linguagem-c/
[2] https://www.inf.ufpr.br/carmem/ci208/aulas/aula17/09a-Vetores.pdf
[3] https://www.facom.ufu.br/~backes/gci007/ListaC04.pdf
[4] https://edisciplinas.usp.br/mod/book/view.php?chapterid=25820&id=4642812
[5] https://pt.stackoverflow.com/questions/46668/o-que-s%C3%A3o-unions-por-que-utiliz%C3%A1-los-dentro-de-structs
[6] https://www.youtube.com/watch?v=Wal10kQKwAE
[7] https://www.inf.ufpr.br/roberto/ci067/09_estr.html
[8] https://www.inf.pucrs.br/~pinho/LaproI/Vetores/Vetores.htm
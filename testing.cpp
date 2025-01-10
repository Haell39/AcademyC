// Função que soma dois números
#include <iostream>

int soma(int a, int b) {
    return a + b;
}

// Função que imprime o resultado da soma
void imprimirSoma(int a, int b) {
    int resultado = soma(a, b);
    std::cout << "A soma de " << a << " + " << b << " = " << resultado << std::endl;
}

int main() {
    int a, b;
    std::cout << "Digite o primeiro número: ";
    std::cin >> a;
    std::cout << "Digite o segundo número: ";
    std::cin >> b;
    imprimirSoma(a, b);
    return 0;
}


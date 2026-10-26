#include <stdio.h>
#include <string.h>
#include <ctype.h>

//determina la prioridad de los operadores

int prioridad(char operador) {
    if (operador == '+' || operador == '-') {
        return 1;
    }

    if (operador == '*' || operador == '/') {
        return 2;
    }

    if (operador == '^') {
        return 3;
    }

    return 0;
}

int es_operador(char simbolo) {
    return simbolo == '+' || simbolo == '-' ||
           simbolo == '*' || simbolo == '/' ||
           simbolo == '^';
}

int es_operando(char simbolo) {
    return isalnum((unsigned char) simbolo);
}

int main() {
    char ExpINF[100];
    char ExpPRE[100];
    char Pila[100];

    int Tope = 0;
    int i;
    int j = 0;
    int error = 0;
    char simbolo;

    printf("Introduce una expresion infija: ");
    scanf("%99s", ExpINF);

    // Recorrer la expresion de derecha a izquierda
    for (i = (int) strlen(ExpINF) - 1; i >= 0; i--) {

        simbolo = ExpINF[i];

        // Si es parentesis derecho
        if (simbolo == ')') {
            Tope++;
            Pila[Tope] = simbolo;
        }

        // Si es parentesis izquierdo
        else if (simbolo == '(') {

            while (Tope > 0 && Pila[Tope] != ')') {
                ExpPRE[j] = Pila[Tope];
                j++;
                Tope--;
            }

            if (Tope == 0) {
                error = 1;
                break;
            }

            // Eliminar parentesis derecho
            Tope--;
        }

        // Si es operando
        else if (es_operando(simbolo)) {
            ExpPRE[j] = simbolo;
            j++;
        }

        // Si es operador
        else if (es_operador(simbolo)) {

            while (Tope > 0 && Pila[Tope] != ')' &&
                   (prioridad(simbolo) < prioridad(Pila[Tope]) ||
                   (prioridad(simbolo) == prioridad(Pila[Tope]) &&
                    simbolo == '^'))) {

                ExpPRE[j] = Pila[Tope];
                j++;
                Tope--;
            }

            Tope++;
            Pila[Tope] = simbolo;
        }

        else {
            error = 1;
            break;
        }
    }

    // Vaciar la pila
    while (Tope > 0 && !error) {

        if (Pila[Tope] == ')') {
            error = 1;
            break;
        }

        ExpPRE[j] = Pila[Tope];
        j++;
        Tope--;
    }

    ExpPRE[j] = '\0';

    if (error) {
        printf("Error: expresion no valida.\n");
        return 1;
    }

    // Invertir la expresion para obtener prefija
    printf("\nExpresion prefija: ");

    for (i = j - 1; i >= 0; i--) {
        printf("%c", ExpPRE[i]);
    }

    printf("\n");

    return 0;
}
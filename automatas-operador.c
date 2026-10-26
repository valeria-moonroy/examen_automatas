#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int es_palabra_reservada(char *token) {
    int estado = 0;

    if (strcmp(token, "for") == 0 ||
        strcmp(token, "if") == 0 ||
        strcmp(token, "while") == 0) {
        estado = 1;
    }

    return estado;
}

int es_digito(char c) {
    int estado = 0;

    if (c >= '0' && c <= '9') {
        estado = 1;
    }

    return estado;
}

int es_operador(char c) {
    int estado = 0;

    if (c == '/' || c == '*' || c == '+' || c == '-') {
        estado = 1;
    }

    return estado;
}

int es_parentesis(char c) {
    int estado = 0;

    if (c == '(' || c == ')') {
        estado = 1;
    }

    return estado;
}

void print_token(char *token) {
    printf("\nEl token es: %s\n", token);
}

void quitar_salto_de_linea(char *token) {
    token[strcspn(token, "\r\n")] = '\0';
}

int token_es_numero(char *token) {
    int i = 0;
    char c = token[i];
    int estado = 1;

    if (c == '\0') {
        return 0;
    }

    while (c != '\0') {
        estado = es_digito(c);

        if (estado == 0) {
            break;
        }

        i++;
        c = token[i];
    }

    return estado;
}

/* Funciones agregadas */

int es_asignacion(char c) {
    return c == '=';
}

int es_fin_de_instruccion(char c) {
    return c == ';';
}

int es_tipo(char *token) {
    return strcmp(token, "int") == 0 ||
           strcmp(token, "float") == 0 ||
           strcmp(token, "char") == 0 ||
           strcmp(token, "double") == 0 ||
           strcmp(token, "void") == 0;
}

int es_variable(char *token) {
    if (!isalpha((unsigned char)token[0]) && token[0] != '_') {
        return 0;
    }

    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum((unsigned char)token[i]) && token[i] != '_') {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    FILE *archivo;
    char texto[256]; // Almacenara cada linea leida
    char separado[768]; // Agregado: texto con espacios alrededor de ;

    //-----------------------
    // Abrir el archivo en modo lectura ("r")
    archivo = fopen("//Users/valeriamonroy/hola.txt", "r");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Leer línea por línea hasta llegar al final del archivo
    while (fgets(texto, sizeof(texto), archivo) != NULL) {
        //----------
        quitar_salto_de_linea(texto);

        /* Agregado: separar el punto y coma */
        int j = 0;

        for (int i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == ';') {
                separado[j++] = ' ';
                separado[j++] = ';';
                separado[j++] = ' ';
            } else {
                separado[j++] = texto[i];
            }
        }

        separado[j] = '\0';

        char *token = strtok(separado, " \t");

        while (token != NULL) {
            print_token(token);

            if (es_palabra_reservada(token)) {
                printf("=> PALABRA RESERVADA: INSTRUCCION\n");
            } else if (es_tipo(token)) {
                printf("=> PALABRA RESERVADA: TIPO\n");
            } else if (es_variable(token)) {
                printf("=> VARIABLE\n");
            } else {
                for (int i = 0; token[i] != '\0'; i++) {
                    char c = token[i];

                    if (es_digito(c)) {
                        printf("\t'%c' -> DIGITO\n", c);
                    } else if (es_operador(c)) {
                        printf("\t'%c' -> OPERADOR\n", c);
                    } else if (es_parentesis(c)) {
                        printf("\t'%c' -> PARENTESIS\n", c);
                    } else if (es_asignacion(c)) {
                        printf("\t'%c' -> ASIGNACION\n", c);
                    } else if (es_fin_de_instruccion(c)) {
                        printf("\t'%c' -> FIN DE INSTRUCCION\n", c);
                    } else {
                        printf("\t'%c' -> ERROR\n", c);
                    }
                }

                if (token_es_numero(token)) {
                    printf("=> El token es un NUMERO\n");
                }
            }

            token = strtok(NULL, " \t");
        }

        //-----------
    }

    // Cerrar siempre el archivo al terminar
    fclose(archivo);

    //-----------------------
    return 0;
}
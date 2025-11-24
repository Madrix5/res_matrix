//
// Created by Adrián Jiménez Calderón on 24/11/25.
//

// Este programa debe resolver matrices 4x4 o 4x5 por eliminación de Gauss con pivoteo parcial escalado.

#include <stdio.h>


void matrix4();
void matrix3();
void matrix2();
// void rango();
// void determinante();
// void confirmar();
void limpiar_b();
// void instrucciones();
void menu();

int main() {
    instrucciones();
    menu();
}

void matrix4() {
    double f1[];
    double f2[];
    double f3[];
    double f4[];
    double matrix[];

    printf("Introduce la fila 1: ");
    scanf(" %d", f1);
    limpiar_b();
    printf("Introduce la fila 2: ");
    scanf(" %d", f2);
    limpiar_b();
    printf("Introduce la fila 3: ");
    scanf(" %d", f3);
    limpiar_b();
    printf("Introduce la fila 4: ");
    scanf(" %d", f4);
    limpiar_b();
}

void matrix3() {
    double f1[];
    double f2[];
    double f3[];
    double matrix[];

    printf("Introduce la fila 1: ");
    scanf(" %d", f1);
    limpiar_b();
    printf("Introduce la fila 2: ");
    scanf(" %d", f2);
    limpiar_b();
    printf("Introduce la fila 3: ");
    scanf(" %d", f3);
    limpiar_b();
}

void matrix2() {
    double f1[];
    double f2[];
    double matrix[];

    printf("Introduce la fila 1: ");
    scanf(" %d", f1);
    limpiar_b();
    printf("Introduce la fila 2: ");
    scanf(" %d", f2);
    limpiar_b();
}

void limpiar_b () {
    // Limpia el buffer para asegurarse que no queda nada.
    int c;

    while (c = getchar() != '\n' || c != EOF);
}

void menu () {
    printf("\n------- MENÚ -------\n\n");
    printf("1 - Instrucciones\n");
    printf("2 - Matriz ampliada (A|b)\n");
}
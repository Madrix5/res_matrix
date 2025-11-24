//
// Created by Adrián Jiménez Calderón on 24/11/25.
//

// Este programa debe resolver matrices 4x4 o 4x5 por eliminación de Gauss con pivoteo parcial escalado.

#include <stdio.h>


// void matrix4();
// void matrix3();
// void matrix2();
// void rango();
// void determinante();
// void confirmar();
void limpiar_b();
void menu (int *);
void c_scan(int, int *);
// void instrucciones();

/*void matrix4() {
    double matrix[4][5]; // Matriz (A|b) de 4 filas y 5 columnas

}

void matrix3() {
    double matrix[3][4];
    int i;

    i = 0;
    while (i < 3) {
        i++;
        printf("Introduce la fila %d", i);
        scanf(" %d", matrix[i][0]);
        limpiar_b();
    }
}

void matrix2() {

} */

void limpiar_b () {
    // Limpia el buffer para asegurarse que no queda nada.
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void c_scan(int res, int *select) {
    if (res != 1 || (*select != 1 && *select != 2)) {
        limpiar_b();
        menu(select);
    }
}

void menu (int *select) {
    // Muestra un menú para elegir si se quieren ver las instrucciones o insertar la matriz ampliada
    int res;

    printf("\n------- MENÚ -------\n\n");
    printf("1 - Instrucciones\n");
    printf("2 - Matriz ampliada (A|b)\n");

    res = scanf(" %d", select);
    c_scan(res, select);
    return;
}

int main() {
    int select = 0;

    menu(&select);
    printf("%d", select);
}
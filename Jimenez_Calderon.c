//
// Created by Adrián Jiménez Calderón on 24/11/25.
//

// Este programa debe resolver matrices 2x3, 3x4 o 4x5 por eliminación de Gauss con pivoteo parcial escalado.

#include <stdio.h>


void matrix4(int *);
void matrix3(int *);
void matrix2(int *);
// void rango();
// void determinante();
// void confirmar();
void limpiar_b();
void menu (int *);
void c_scan(int, int *);
void c_scan_menu(int, int *);
// void instrucciones();

void matrix4(int *select) {
    // Calcula las matrices (A|b), A4x4
    int row = 4, column = 5;
    int count_row, count_column;
    double matrix_ab[row][column];
    int i, res;

    i = 0;
    count_row = 1;
    while (i < row) {
        printf("Introduce la fila %d:  ", count_row);
        res = scanf(" %lf", &matrix_ab[i][0]);
        c_scan(res, select);
        limpiar_b();
        i++;
        count_row++;
    }

}

void matrix3(int *select) {
    double matrix_ab[3][4];
    int i, res;

    i = 0;
    while (i < 3) {
        printf("Introduce la fila %d:  ", i);
        res = scanf(" %lf", &matrix_ab[i][0]);
        c_scan(res, select);
        limpiar_b();
        i++;
    }
}

void matrix2(int *select) {
    double matrix_ab[2][3];
    int i, res;

    i = 0;
    while (i < 2) {
        printf("Introduce la fila %d:  ", i);
        res = scanf(" %lf", &matrix_ab[i][0]);
        c_scan(res, select);
        limpiar_b();
        i++;
    }
}

void limpiar_b () {
    // Limpia el buffer para asegurarse que no queda nada.
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void c_scan(int res, int *select) {
    // Comprueba que los scanf de las funciones de matrices no fallen
    int ejercicio = *select;

    if (res != 1) {
        limpiar_b();
        switch (ejercicio) {
            case 2:
                matrix4(select);
                break;
            case 3:
                matrix3(select);
                break;
            case 4:
                matrix2(select);
                break;
        }
    }
}

void c_scan_menu(int res, int *select) {
    // Comprueba que los scanf del menú no falle
    if (res != 1 || (*select <= 1 && *select >= 5)) {
        limpiar_b();
        menu(select);
    }
}

void menu (int *select) {
    // Muestra un menú para elegir si se quieren ver las instrucciones o insertar la matriz ampliada
    int res;

    printf("\n------- MENÚ -------\n\n");
    printf("1 - Instrucciones\n");
    printf("2 - Matriz ampliada 4x5\n");
    printf("3 - Matriz ampliada 3x4\n");
    printf("4 - Matriz ampliada 2x3\n");
    printf("5 - Cerrar programa\n");

    res = scanf(" %d", select);
    c_scan_menu(res, select);
    return;
}

int main() {
    int select;
    short pasos = 1;
    short bucle = 1;

    menu(&select);
    switch (select) {
        // ? Implementar pregunta de si quieren mostrar todos los pasos o no.
        case 1:
            printf("Aqui nos manda a la función instrucciones\n");
            main();
            break;
        case 2:
            printf("Aqui nos manda a resolver la 4x5\n");
            matrix4(&select);
            main();
            break;
        case 3:
            printf("Aqui nos manda a resolver la 3x4\n");
            matrix3(&select);
            main();
            break;
        case 4:
            printf("Aqui nos manda a resolver la 2x3\n");
            matrix2(&select);
            main();
            break;
        case 5:
            printf("Terminamos el programa\n");
            limpiar_b();
            main();
            break;
        default:
            printf("Introduce un número valido...");
            limpiar_b();
            main();
    }
}
/*****************************************************************************************
 *                                                                                       *
 * ASIGNATURA:     Álgebra y matemática discreta                                         *
 *                                                                                       *
 * ALUMNO:         Adrián Jiménez Calderón                                               *
 * CORREO UNIR:    adrian.jimenez932@comunidadunir.net                                   *
 * FECHA:          30-11-2025                                                            *
 *                                                                                       *
 * ------------------------------------------------------------------------------------- *
 *                                                                                       *
 * TITULO:         Actividad 1 - Eliminación de Gauss con pivoteo parcial escalado       *
 *                                                                                       *
 * DESCRIPCION:                                                                          *
 * Programa desarrollado en C para resolver sistemas de ecuaciones lineales (Ax=b).      *
 * Implementa el algoritmo de Eliminación de Gauss con Pivoteo Parcial Escalado,         *
 * gestión de memoria dinámica, análisis de estabilidad numérica y visualización         *
 * avanzada en consola.                                                                  *
 *                                                                                       *
 *****************************************************************************************/

// --- LIBRERIAS Y FUNCIONES UTILIZADAS ---

#include <stdio.h> // printf, scanf, sprintf, getchar
#include <stdlib.h> // malloc, calloc, free, exit, abs
#include <string.h> // strlen
#include <math.h> // fabs, pow, sqrt, M_PI, M_E
#include <time.h> // clock, clock_t, CLOCK_PER_SEC

// Definiciones de constantes matemáticas por si el compilador no las trae por defecto
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

//----------------------------------------------------------------------------------------------------------------------

// --- COLORES ANSI PARA LA CONSOLA ---
// Códigos de escape para dar formato visual al texto en terminales compatibles.
#define RESET       "\033[0m"
#define BLACK       "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"

// Colores en Negrita (Bold) / Brillantes
#define B_BLACK     "\033[1;30m"
#define B_RED       "\033[1;31m"
#define B_GREEN     "\033[1;32m"
#define B_YELLOW    "\033[1;33m"
#define B_BLUE      "\033[1;34m"
#define B_MAGENTA   "\033[1;35m"
#define B_CYAN      "\033[1;36m"
#define B_WHITE     "\033[1;37m"

// Colores de Fondo (Background)
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

// Colores Extendidos
#define C_ORANGE    "\033[38;5;208m"
#define C_VIOLET    "\033[38;5;141m"
#define C_AQUA      "\033[38;5;51m"
#define C_PINK      "\033[38;5;201m"
#define C_LIME      "\033[38;5;118m"
#define C_GOLD      "\033[38;5;220m"

//----------------------------------------------------------------------------------------------------------------------

// --- CONSTANTES GLOBALES ---
/* EPSILON: Margen de error para comparaciones de punto flotante.
 * Cualquier número menor a esto se considerará CERO para evitar fallos numéricos. */
#define EPSILON 1e-15

// --- ESTRUCTURAS DE DATOS ---


// Contenedor principal que agrupa toda la información matemática de un sistema de ecuaciones.
typedef struct {
    int n;              // Número de incógnitas.
    double **A;         // Puntero doble para la matriz de coeficientes.
    double *b;          // Puntero para el vector de términos independientes.
    double det;         // Almacena el valor del determinante calculado.
    int rangoA;         // Rango de la matriz A.
    int rangoAmp;       // Rango de la matriz ampliada (A|b).
    int swaps;          // Contador de intercambios de fila.
    double normaInf;    // Norma infinita de la matriz.
} Sistema;


// Banderas de configuración para controlar el flujo y la visualización del programa.
typedef struct {
    int verPasos;       // 1: Mostrar todo el proceso paso a paso. 0: Ocultar.
    int verTriangular;  // 1: Mostrar la matriz triangular final.
    int verSolucion;    // 1: Calcular y mostrar las variables x[i].
    int incluirB;       // 1: Incluir el vector 'b' al calcular el vector de escalas 's' (Opción profesor).
} Config;

// --- PROTOTIPOS DE FUNCIONES (Declaraciones previas) ---
void limpiarBuffer();
void pausarEjecucion();
void reservarMemoria(Sistema *sys, int n);
void liberarMemoria(Sistema *sys);
void mostrarInstrucciones();
void leerSistema(Sistema *sys);
void cargarMatrizPrueba(Sistema *sys, int id);
int gestionarMenuPruebas(Sistema *sys);
void imprimirEstado(Sistema *sys, const char *titulo);
void calcularEscalas(Sistema *sys, double *s, int incluirB);
void calcularNormaInfinita(Sistema *sys);
void triangularizarGauss(Sistema *sys, Config config);
void analizarSistema(Sistema *sys);
void resolverSustitucionAtras(Sistema *sys);
void clasificarYMostrar(Sistema *sys, Config config, double tiempo_cpu);

// ============================================================================
//                               FUNCIÓN MAIN
// ============================================================================
int main() {
    // Declaración de variables locales del main
    Sistema sys;        // Estructura principal del sistema.
    sys.A = NULL;       // Inicializamos punteros a NULL para evitar errores de memoria.
    sys.b = NULL;

    Config config;      // Estructura de configuración visual.

    // Variables de control de menús y flujo
    int opcion;         // Selección del menú de detalle.
    int opcion_b;       // Selección de inclusión de vector b en escalado.
    int modo_entrada;   // Selección entre Manual o Pruebas.
    char continuar;     // Carácter para el bucle de repetición (s/n).
    int entrada_valida; // Bandera auxiliar para validar inputs de usuario.

    // Variables de cronometraje de la CPU
    clock_t inicio, fin;
    double tiempo_cpu;

    mostrarInstrucciones();

    do {
        // Reinicio de configuración por defecto en cada iteración
        config.verPasos = 0;
        config.verTriangular = 0;
        config.verSolucion = 0;
        config.incluirB = 0;
        sys.swaps = 0;

        // --- MENÚ: MODO DE ENTRADA ---
        entrada_valida = 0;
        do {
            printf("\n" B_BLUE "============================================" RESET "\n");
            printf(B_CYAN "  SELECCIONE MODO DE ENTRADA:" RESET "\n");
            printf(WHITE "  1. Introducir Matriz Manualmente" RESET "\n");
            printf(WHITE "  2. Cargar Matriz de Prueba" RESET "\n");
            printf(B_YELLOW ">> Opcion (1-2): " RESET);

            // Validamos que sea un entero y que sea 1 o 2
            if (scanf("%d", &modo_entrada) == 1 && (modo_entrada == 1 || modo_entrada == 2)) {
                entrada_valida = 1;
            }
            else {
                printf(B_RED " Error. Introduzca 1 o 2.\n" RESET);
                limpiarBuffer(); // Limpia basura del teclado
            }
        } while (!entrada_valida);
        limpiarBuffer(); // Limpia el salto de línea pendiente

        if (modo_entrada == 2) {
            gestionarMenuPruebas(&sys); // Carga datos predefinidos
            printf(B_GREEN ">>> Matriz cargada.\n" RESET);
        }
        else {
            leerSistema(&sys); // Pide datos al usuario
        }

        // --- MENÚ: VECTOR b ---
        entrada_valida = 0;
        do {
            printf(B_YELLOW "\nOPCION DE ESCALADO:" RESET "\n");
            printf("¿Desea incluir el vector " B_CYAN "b" RESET " en el calculo de escalas?\n");
            printf(" (" B_WHITE "0" RESET "=No | " B_WHITE "1" RESET "=Si): ");
            if (scanf("%d", &opcion_b) == 1 && (opcion_b == 0 || opcion_b == 1)) {
                entrada_valida = 1;
            } else {
                printf(B_RED " Error. Introduzca 0 o 1.\n" RESET);
                limpiarBuffer();
            }
        } while (!entrada_valida);
        limpiarBuffer();
        config.incluirB = (opcion_b == 1);

        // --- MENÚ: NIVEL DE DETALLE ---
        entrada_valida = 0;
        do {
            printf(B_CYAN"\nSeleccione nivel de detalle:\n"RESET);
            printf(CYAN"1. Ver TODO (Pasos, Escalas, Matrices)\n");
            printf("2. Ver Matriz Final + Solucion\n");
            printf("3. Ver Solo Resultado\n");
            printf("Opcion (1-3): "RESET);
            if (scanf("%d", &opcion) == 1 && (opcion >= 1 && opcion <= 3)) {
                entrada_valida = 1;
            } else {
                printf(B_RED " Error. Introduzca 1, 2 o 3.\n" RESET);
                limpiarBuffer();
            }
        } while (!entrada_valida);
        limpiarBuffer();

        // Configura flags según la opción elegida
        if (opcion == 1) { config.verPasos=1; config.verTriangular=1; config.verSolucion=1; }
        else if (opcion == 2) { config.verTriangular=1; config.verSolucion=1; }
        else { config.verSolucion=1; }

        if (config.verPasos) imprimirEstado(&sys, "Sistema Inicial");

        // Pre-cálculo de norma para análisis
        calcularNormaInfinita(&sys);

        // --- INICIO CRONOMETRO ---
        inicio = clock();

        triangularizarGauss(&sys, config); // Fase 1: Eliminación
        analizarSistema(&sys);             // Fase 2: Rangos y Determinante

        fin = clock();
        tiempo_cpu = ((double) (fin - inicio)) / CLOCKS_PER_SEC; // Cálculo de tiempo de la CPU
        // --- FIN CRONOMETRO ---

        // Mostrar resultados finales y diagnóstico
        clasificarYMostrar(&sys, config, tiempo_cpu);

        // Liberar la memoria dinámica usada en esta iteración
        liberarMemoria(&sys);

        // --- PREGUNTA: CONTINUAR ---
        entrada_valida = 0;
        do {
            printf(CYAN "\n============================================\n");
            printf("  ¿Desea resolver otro sistema? (s/n): ");

            char c_temp;
            if (scanf(" %c", &continuar) == 1) {
                if (continuar=='s' || continuar=='S' || continuar=='n' || continuar=='N') {
                    entrada_valida = 1;
                } else {
                    printf(B_RED " Error: 's' o 'n'.\n" RESET);
                }
            } else {
                while ((c_temp = getchar()) != '\n' && c_temp != EOF);
            }
            limpiarBuffer();
        } while (!entrada_valida);
        printf("\n============================================\n\n" RESET);

    } while (continuar == 's' || continuar == 'S');

    printf(B_YELLOW "Fin del programa.\n" RESET);
    return 0;
}

// ============================================================================
//                          IMPLEMENTACIÓN DE FUNCIONES
// ============================================================================

// --- LIMPIEZA STDIN ---
void limpiarBuffer() {
    // Consume todos los caracteres que queden en el buffer de entrada stdin, evita futuras lecturas erroneas de scanf.
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- TIEMPOS DE EJECUCIÓN ---
void pausarEjecucion() {
    // Pausa la ejecución del programa hasta que el usuario decide continuar
    printf(B_YELLOW "\n[PAUSA] Presione ENTER para continuar..." RESET);
    int c = getchar();
    if(c != '\n') while ((c = getchar()) != '\n' && c != EOF);
}

// --- USO DE MEMORIA ---
void reservarMemoria(Sistema *sys, int n) {
    // Reserva el espacio necesario en memoria para la matriz y el vector b.
    sys->n = n;
    // Reserva un array para las filas.
    sys->A = (double **)malloc(n * sizeof(double *));
    if (sys->A == NULL) { printf(BG_RED " ERROR CRITICO: Sin memoria RAM " RESET); exit(1); }

    // Reservar cada fila individualmente
    for(int i=0; i<n; i++) {
        sys->A[i] = (double *)malloc(n * sizeof(double));
        if (sys->A[i] == NULL) exit(1);
    }
    // Reservar el vector de resultados b
    sys->b = (double *)malloc(n * sizeof(double));
    if (sys->b == NULL) exit(1);
}

void liberarMemoria(Sistema *sys) {
    // Devuelve la memoria al sistema.
    if (sys->A != NULL) {
        for(int i=0; i<sys->n; i++) {
            free(sys->A[i]); // Libera cada fila
        }
        free(sys->A); // Libera el array de punteros
        sys->A = NULL;
    }
    if (sys->b != NULL) {
        free(sys->b); // Libera vector b
        sys->b = NULL;
    }
}

// --- INSTRUCCIONES DE USO ---
void mostrarInstrucciones() {
    printf(B_GREEN "=======================================================\n");
    printf("  SOLUCIONADOR DE SISTEMAS LINEALES (GAUSS ESCALADO) \n");
    printf("=======================================================\n"RESET);
    printf(GREEN"\nINSTRUCCIONES:\n");
    printf("- Elija entre introducir su propia matriz o usar una de\n");
    printf("  la base de datos de pruebas.\n");
    printf("- Precision cientifica 1e-15 y Memoria Dinamica.\n");
    printf("=======================================================\n\n" RESET);
}

void calcularNormaInfinita(Sistema *sys) {
    // Calcula la fiabilidad de los resultados dados por el programa.
    sys->normaInf = 0.0;
    for (int i = 0; i < sys->n; i++) {
        double sumaFila = 0.0;
        for (int j = 0; j < sys->n; j++) {
            sumaFila += fabs(sys->A[i][j]);
        }
        if (sumaFila > sys->normaInf) sys->normaInf = sumaFila;
    }
}

// --- MENÚ PRUEBAS ---
int gestionarMenuPruebas(Sistema *sys) {
    int id, valido = 0;

    printf("\n" B_MAGENTA "--- BASE DE DATOS DE MATRICES ---" RESET "\n");
    printf("1. Basica 3x3\n2. Pivoteo Obligatorio\n3. Incompatible\n4. Indeterminado\n");
    printf(B_CYAN "--- AVANZADO ---" RESET "\n");
    printf("5. Hilbert 4x4\n6. Magnitudes Extremas\n7. Wilson 4x4\n8. Irracionales\n");
    printf(B_CYAN "--- STRESS ---" RESET "\n");
    printf("9. Pascal 12x12\n10. Tridiagonal 15x15\n11. Maximo 20x20\n12. Binaria 18x18\n");
    printf("13. Vandermonde 4x4\n14. Casi Singular\n");
    printf(B_CYAN "--- TEST ALERTAS (DIAGNOSTICO) ---" RESET "\n");
    printf("15. Test Precaucion\n");
    printf("16. Test Peligro\n");
    printf("17. Test Critico\n");

    do {
        printf(B_YELLOW ">> Seleccione prueba (1-17): " RESET);
        if (scanf("%d", &id) == 1 && (id >= 1 && id <= 17)) {
            valido = 1;
        } else {
            printf(B_RED " Error: 1-17.\n" RESET);
            limpiarBuffer();
        }
    } while (!valido);

    limpiarBuffer();

    // Determinar tamaño según ID para reservar memoria
    int tamano = 0;
    if (id<=2 || id==4 || id==14) tamano=3;
    else if (id==3 || id==6 || id==8 || id==15 || id==16 || id==17) tamano=2;
    else if (id==5 || id==7 || id==13) tamano=4;
    else if (id==9) tamano=12;
    else if (id==10) tamano=15;
    else if (id==11) tamano=20;
    else if (id==12) tamano=18;

    reservarMemoria(sys, tamano);
    cargarMatrizPrueba(sys, id);
    return id;
}

void cargarMatrizPrueba(Sistema *sys, int id) {
    // "Base de datos" de las matrices de prueba.
    sys->swaps = 0;
    int i, j;

    switch(id) {
        case 1: // Básica 3x3
            sys->n=3; sys->A[0][0]=2; sys->A[0][1]=1;  sys->A[0][2]=-1; sys->A[1][0]=1; sys->A[1][1]=-1; sys->A[1][2]=1; sys->A[2][0]=3; sys->A[2][1]=2;  sys->A[2][2]=2; sys->b[0]=1; sys->b[1]=2; sys->b[2]=13; break;
        case 2: // Pivoteo
            sys->n=3; sys->A[0][0]=0; sys->A[0][1]=2;  sys->A[0][2]=1; sys->A[1][0]=1; sys->A[1][1]=-1; sys->A[1][2]=2; sys->A[2][0]=2; sys->A[2][1]=1;  sys->A[2][2]=1; sys->b[0]=5; sys->b[1]=1; sys->b[2]=5; break;
        case 3: // Incompatible
            sys->n=2; sys->A[0][0]=1; sys->A[0][1]=1; sys->A[1][0]=1; sys->A[1][1]=1; sys->b[0]=5; sys->b[1]=9; break;
        case 4: // Indeterminado
            sys->n=3; sys->A[0][0]=1; sys->A[0][1]=1; sys->A[0][2]=1; sys->A[1][0]=2; sys->A[1][1]=2; sys->A[1][2]=2; sys->A[2][0]=3; sys->A[2][1]=3; sys->A[2][2]=3; sys->b[0]=3; sys->b[1]=6; sys->b[2]=9; break;
        case 5: // Hilbert 4x4
            sys->n=4; for(i=0; i<4; i++) for(j=0; j<4; j++) sys->A[i][j] = 1.0 / (double)(i + j + 1); sys->b[0]=25.0/12.0; sys->b[1]=77.0/60.0; sys->b[2]=57.0/60.0; sys->b[3]=319.0/420.0; break;
        case 6: // Magnitudes
            sys->n=2; sys->A[0][0]=1e10; sys->A[0][1]=2.0; sys->A[1][0]=1.0; sys->A[1][1]=1.0; sys->b[0]=10000000002.0; sys->b[1]=2.0; break;
        case 7: // Wilson
            sys->n=4; sys->A[0][0]=5; sys->A[0][1]=7; sys->A[0][2]=6; sys->A[0][3]=5; sys->A[1][0]=7; sys->A[1][1]=10; sys->A[1][2]=8; sys->A[1][3]=7; sys->A[2][0]=6; sys->A[2][1]=8; sys->A[2][2]=10; sys->A[2][3]=9; sys->A[3][0]=5; sys->A[3][1]=7; sys->A[3][2]=9; sys->A[3][3]=10; sys->b[0]=23; sys->b[1]=32; sys->b[2]=33; sys->b[3]=31; break;
        case 8: // Irracionales
            sys->n=2; sys->A[0][0]=M_PI; sys->A[0][1]=M_E; sys->A[1][0]=sqrt(2); sys->A[1][1]=1.0/7.0; sys->b[0]=M_PI+M_E; sys->b[1]=sqrt(2)+1.0/7.0; break;
        case 9: // Pascal
            sys->n=12; for(i=0; i<sys->n; i++) { double sum = 0; for(j=0; j<sys->n; j++) { sys->A[i][j] = pow((double)(i+1), (double)j); sum += sys->A[i][j]; } sys->b[i] = sum; } break;
        case 10: // Tridiagonal
            sys->n=15; for(i=0; i<sys->n; i++) { double sum = 0; for(j=0; j<sys->n; j++) { sys->A[i][j] = 0.0; if(i==j) sys->A[i][j] = 4.0; else if(abs(i-j) == 1) sys->A[i][j] = 1.0; sum += sys->A[i][j]; } sys->b[i] = sum; } break;
        case 11: // Stress
            sys->n=20; for(i=0; i<sys->n; i++) { double sum = 0; for(j=0; j<sys->n; j++) { if (i==j) sys->A[i][j] = 20.0; else sys->A[i][j] = (double)( (i+j)%5 ); sum += sys->A[i][j]; } sys->b[i] = sum; } break;
        case 12: // Binaria Inversa
            sys->n=18; for(i=0; i<sys->n; i++) { double sum = 0; for(j=0; j<sys->n; j++) { if(i >= j) sys->A[i][j] = (double)(j+1); else sys->A[i][j] = 0.0; sum += sys->A[i][j]; } sys->b[i] = sum; } break;
        case 13: // Vandermonde
            sys->n=4; sys->A[0][0]=1; sys->A[0][1]=1; sys->A[0][2]=1; sys->A[0][3]=1; sys->A[1][0]=1; sys->A[1][1]=2; sys->A[1][2]=4; sys->A[1][3]=8; sys->A[2][0]=1; sys->A[2][1]=3; sys->A[2][2]=9; sys->A[2][3]=27; sys->A[3][0]=1; sys->A[3][1]=4; sys->A[3][2]=16; sys->A[3][3]=64; sys->b[0]=0; sys->b[1]=-5; sys->b[2]=-20; sys->b[3]=-51; break;
        case 14: // Casi Singular
            sys->n=3; sys->A[0][0]=1; sys->A[0][1]=1; sys->A[0][2]=1; sys->A[1][0]=1; sys->A[1][1]=1; sys->A[1][2]=1.0+1e-14; sys->A[2][0]=1; sys->A[2][1]=2; sys->A[2][2]=1; sys->b[0]=3; sys->b[1]=3.0+1e-14; sys->b[2]=4; break;
        case 15: // ALARMA AMARILLA
            sys->n=2; sys->A[0][0]=1.0; sys->A[0][1]=0.0; sys->A[1][0]=0.0; sys->A[1][1]=1.0e-5; sys->b[0]=1.0; sys->b[1]=1.0; break;
        case 16: // ALARMA ROJA
            sys->n=2; sys->A[0][0]=1.0; sys->A[0][1]=0.0; sys->A[1][0]=0.0; sys->A[1][1]=1.0e-9; sys->b[0]=1.0; sys->b[1]=1.0; break;
        case 17: // ALARMA CRITICA
            sys->n=2; sys->A[0][0]=1.0; sys->A[0][1]=0.0; sys->A[1][0]=0.0; sys->A[1][1]=1.0e-14; sys->b[0]=1.0; sys->b[1]=1.0; break;
    }
}

void leerSistema(Sistema *sys) {
    // Lee la matriz introducida por el usuario.
    sys->swaps = 0;
    int entradaValida = 0;
    int n_temp;

    printf(B_BLUE "\n>>> INTRODUCCION MANUAL DE DATOS <<<\n" RESET);
    do {
        printf(CYAN "Ingrese el numero de incognitas (n): " RESET);
        if (scanf("%d", &n_temp) == 1 && n_temp > 0) {
            entradaValida = 1;
        } else {
            limpiarBuffer();
            printf(B_RED "Error: Ingrese un entero positivo.\n" RESET);
        }
    } while (!entradaValida);
    limpiarBuffer();

    reservarMemoria(sys, n_temp);

    printf(CYAN "\nIngrese coeficientes de la matriz A.\n" RESET);
    printf(YELLOW "Instrucciones: Escriba los %d valores de la fila separados por espacios.\n" RESET, sys->n);

    for (int i = 0; i < sys->n; i++) {
        printf("Fila %d: ", i + 1);
        for (int j = 0; j < sys->n; j++) {
            if (scanf("%lf", &sys->A[i][j]) != 1) {
                printf(B_RED "Error de formato.\n" RESET);
                limpiarBuffer();
                j--;
            }
        }
        limpiarBuffer(); // Limpia sobrantes al final de la fila
    }

    // Vector b
    printf(CYAN "\nIngrese el vector de constantes b:\n" RESET);
    printf("Vector b: ");
    for (int i = 0; i < sys->n; i++) {
        if (scanf("%lf", &sys->b[i]) != 1) {
            printf(B_RED "Error. Reintroduzca b[%d]: " RESET, i);
            limpiarBuffer();
            i--;
        }
    }
    limpiarBuffer();
}

void imprimirEstado(Sistema *sys, const char *titulo) {
    // Calcula el ancho (dinámico) de la matriz para cada columna e imprime la matriz.
    if (titulo) printf(B_GREEN "\n--- %s ---\n" RESET, titulo);

    // Reservar array para guardar el ancho de cada columna.
    int *max_ancho = (int*)calloc(sys->n + 1, sizeof(int));
    if (max_ancho == NULL) exit(1); // Seguridad memoria

    char buffer[100];

    // FASE 1: Mide el ancho de todos los números
    for (int j = 0; j < sys->n; j++) {
        for (int i = 0; i < sys->n; i++) {
            double val = (fabs(sys->A[i][j]) < EPSILON) ? 0.0 : sys->A[i][j];
            sprintf(buffer, "%.15g", val); // Convierte a texto con máxima precisión
            int len = strlen(buffer);
            if (len > max_ancho[j]) max_ancho[j] = len; // Guarda el máximo
        }
    }
    // Mide el vector b
    for (int i = 0; i < sys->n; i++) {
        double val = (fabs(sys->b[i]) < EPSILON) ? 0.0 : sys->b[i];
        sprintf(buffer, "%.15g", val);
        int len = strlen(buffer);
        if (len > max_ancho[sys->n]) max_ancho[sys->n] = len;
    }

    // FASE 2: Imprime usando el ancho calculado
    for (int i = 0; i < sys->n; i++) {
        printf(B_BLUE "[ " RESET);
        for (int j = 0; j < sys->n; j++) {
            double val = (fabs(sys->A[i][j]) < EPSILON) ? 0.0 : sys->A[i][j];
            if (fabs(val) < EPSILON)
                printf(B_BLACK "%*.*g " RESET, max_ancho[j], 15, val);
            else
                printf(B_WHITE "%*.*g " RESET, max_ancho[j], 15, val);
        }
        double val_b = (fabs(sys->b[i]) < EPSILON) ? 0.0 : sys->b[i];
        printf(B_BLUE "| " RESET B_YELLOW "%*.*g " B_BLUE "]\n" RESET, max_ancho[sys->n], 15, val_b);
    }
    free(max_ancho);
    printf("\n");
}

void calcularEscalas(Sistema *sys, double *s, int incluirB) {
    // Crea el vector de escalares s[].
    for (int i = 0; i < sys->n; i++) {
        s[i] = 0.0;
        for (int j = 0; j < sys->n; j++) {
            if (fabs(sys->A[i][j]) > s[i]) s[i] = fabs(sys->A[i][j]);
        }
        if (incluirB) {
            if (fabs(sys->b[i]) > s[i]) s[i] = fabs(sys->b[i]);
        }
        if (s[i] < EPSILON) s[i] = 1.0;
    }
}

void triangularizarGauss(Sistema *sys, Config config) {
    // Convierte la matriz a triangular superior.
    // Selecciona el mejor pivote, intercambia filas si es necesario y realiza la eliminación gaussiana.
    double *s = (double *)malloc(sys->n * sizeof(double));
    if (s == NULL) exit(1);

    calcularEscalas(sys, s, config.incluirB);

    for (int k = 0; k < sys->n - 1; k++) {
        if (config.verPasos) {
            printf(GREEN "\n==================================================\n");
            printf(" ETAPA %d (Trabajando columna %d)\n", k + 1, k);
            printf("==================================================\n" RESET);
            printf(B_MAGENTA "1. Vector de Escalas (s)%s:\n   [ "RESET, config.incluirB ? " (inc. b)" : "");
            for (int z = 0; z < sys->n; z++) printf("%.3g ", s[z]);
            printf("]\n");
        }

        double max_ratio = -1.0;
        int p = k;

        // Búsqueda del pivote
        for (int i = k; i < sys->n; i++) {
            double ratio = fabs(sys->A[i][k]) / s[i];
            if (ratio > max_ratio) {
                max_ratio = ratio;
                p = i;
            }
        }

        if (fabs(sys->A[p][k]) < EPSILON) {
            if(config.verPasos) printf(RED "Aviso: Pivote casi nulo en columna %d\n" RESET, k);
            continue;
        }

        // Intercambio filas
        if (p != k) {
            if (config.verPasos) {
                printf(B_MAGENTA "2. Pivoteo: Fila %d <--> Fila %d\n"RESET, p, k);
            }
            for (int j = k; j < sys->n; j++) {
                double temp = sys->A[k][j]; sys->A[k][j] = sys->A[p][j]; sys->A[p][j] = temp;
            }
            double temp_b = sys->b[k]; sys->b[k] = sys->b[p]; sys->b[p] = temp_b;
            double temp_s = s[k]; s[k] = s[p]; s[p] = temp_s;
            sys->swaps++;
        }

        if (config.verPasos) printf(B_MAGENTA "3. Eliminacion...\n" RESET);

        // Eliminación gaussiana
        for (int i = k + 1; i < sys->n; i++) {
            double factor = sys->A[i][k] / sys->A[k][k];
            sys->A[i][k] = 0.0;
            for (int j = k + 1; j < sys->n; j++) {
                sys->A[i][j] -= factor * sys->A[k][j];
            }
            sys->b[i] -= factor * sys->b[k];
        }

        if (config.verPasos) {
            char buffer[50];
            sprintf(buffer, "Matriz tras Etapa %d", k+1);
            imprimirEstado(sys, buffer);
            pausarEjecucion();
        }
    }
    free(s); // Libera la memoria utilizada para el vector de escalares.
}

void analizarSistema(Sistema *sys) {
    // Calcula el determinante y los rangos de las matrices.
    sys->det = (sys->swaps % 2 == 0) ? 1.0 : -1.0;
    for (int i = 0; i < sys->n; i++) {
        sys->det *= sys->A[i][i];
    }
    if (fabs(sys->det) < EPSILON) sys->det = 0.0;

    sys->rangoA = 0;
    sys->rangoAmp = 0;

    for (int i = 0; i < sys->n; i++) {
        int filaA_cero = 1;
        int filaAmp_cero = 1;

        for (int j = 0; j < sys->n; j++) {
            if (fabs(sys->A[i][j]) > EPSILON) {
                filaA_cero = 0;
                break;
            }
        }
        if (!filaA_cero || fabs(sys->b[i]) > EPSILON) filaAmp_cero = 0;

        if (!filaA_cero) sys->rangoA++;
        if (!filaAmp_cero) sys->rangoAmp++;
    }
}

void resolverSustitucionAtras(Sistema *sys) {
    // Calcula el valor de cada incógnita por el método de resolución hacia atrás.
    double *x = (double *)malloc(sys->n * sizeof(double));
    if (x == NULL) exit(1);

    for (int i = sys->n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < sys->n; j++) {
            sum += sys->A[i][j] * x[j];
        }
        x[i] = (sys->b[i] - sum) / sys->A[i][i];
    }

    printf(C_PINK "\n>>> SOLUCION FINAL:\n" RESET);
    for (int i = 0; i < sys->n; i++) {
        printf(C_AQUA "x[%d] = %.15g\n" RESET, i, x[i]);
    }
    free(x);
}

void clasificarYMostrar(Sistema *sys, Config config, double tiempo_cpu) {
    // Muestra el diagnostico final: determinante, rangos, tiempo de la CPU, resultados,...
    if (config.verTriangular) imprimirEstado(sys, "Matriz Triangular Final");

    printf(C_LIME"----------------------------------------\n");
    printf("ANALISIS DE RESULTADOS:\n"RESET);
    printf(C_ORANGE "Determinante: %.15g\n", sys->det);
    printf("Rango(A): %d\n", sys->rangoA);
    printf("Rango(A|b): %d\n" RESET, sys->rangoAmp);

    // ANÁLISIS DE ESTABILIDAD
    double max_piv = 0.0, min_piv = 1e300;
    for(int i=0; i<sys->n; i++) {
        double val = fabs(sys->A[i][i]);
        if(val > max_piv) max_piv = val;
        if(val < min_piv && val > EPSILON) min_piv = val;
    }
    double ratio = (min_piv > 0) ? max_piv/min_piv : 1e300;

    if (ratio > 0) printf("Ratio de Pivotes: %.2g\n", ratio);

    if (ratio >= 1e12) {
        printf(BG_RED BLACK " [CRITICO] ESTABILIDAD NUMERICA CATASTROFICA " RESET "\n");
        printf(B_RED " > Se han perdido mas de 12 digitos de precision.\n" RESET);
        printf(B_RED " > El resultado es probablemente ruido numerico.\n" RESET);
    }
    else if (ratio >= 1e8) {
        printf(C_ORANGE " [PELIGRO] Matriz MUY inestable (Zona de Peligro) " RESET "\n");
        printf(C_ORANGE " > Se han perdido entre 8 y 12 digitos de precision.\n" RESET);
    }
    else if (ratio >= 1e4) {
        printf(B_YELLOW " [PRECAUCION] Matriz mal condicionada " RESET "\n");
        printf(YELLOW " > Se han perdido entre 4 y 8 digitos.\n" RESET);
    }
    else {
        printf(B_GREEN " [OK] Matriz estable.\n" RESET);
    }

    printf("----------------------------------------\n" RESET);

    if (sys->rangoA != sys->rangoAmp) {
        printf(C_GOLD "RESULTADO: SISTEMA INCOMPATIBLE (Sin solucion)\n"RESET);
    }
    else if (sys->rangoA < sys->n) {
        printf(C_GOLD "RESULTADO: SISTEMA COMPATIBLE INDETERMINADO (Infinitas soluciones)\n" RESET);
    }
    else {
        printf(C_GOLD "RESULTADO: SISTEMA COMPATIBLE DETERMINADO (Solucion unica)\n"RESET);
        if (config.verSolucion) {
            resolverSustitucionAtras(sys);
        }
    }

    printf("\n----------------------------------------\n");
    printf(B_BLUE " Tiempo de Computo (CPU): %.6f s " RESET "\n", tiempo_cpu);
    printf("----------------------------------------\n");
}

/*
* POSIBLE MEJORA:
* - Crear informes sobre las matrices en LaTeX, en vez de imprimirlo por terminal.
*/
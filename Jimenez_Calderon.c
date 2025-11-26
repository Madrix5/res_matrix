/*****************************************************************************************
 *                                                                                       *
 * ASIGNATURA:     [NOMBRE DE LA MATERIA, EJ: MÉTODOS NUMÉRICOS]                         *
 *                                                                                       *
 * ALUMNO:         Adrián Jiménez Calderón                                               *
 * CORREO UNIR:    adrian.jimenez932@comunidadunir.net                                   *
 * FECHA:          [FECHA ACTUAL]                                                        *
 *                                                                                       *
 * ------------------------------------------------------------------------------------- *
 *                                                                                       *
 * TITULO:         Actividad 1 - Eliminación de Gauss con pivoteo parcial escalado       *
 *                                                                                       *
 * DESCRIPCION:                                                                          *
 * Programa desarrollado en C para resolver sistemas de ecuaciones.                      *
 * Implementa el algoritmo de Eliminación de Gauss con Pivoteo Parcial Escalado.         *                                                                            *
 *                                                                                       *
 * CARACTERISTICAS PRINCIPALES:                                                          *
 * - No toma los valores de la matriz b para hacer el vector de escalares                *
 * - Se puede elegir el tamaño de la matriz (aun que da mas trabajo al usuario)          *
 * - Te dice si el sistema es S.I., S.C.D o S.C.I                                        *
 * - Puedes decir si quieres ver los pasos o ir directo al resultado                     *
 * -
 * - Compilado con las flags -Wall -Wextra -Werror para minimizar errores de código      *
 *                                                                                       *
 *  AL FINAL DEL CÓDIGO HAY UN FOOTER CON POSIBLES MEJORAS QUE NO ME HA DADO TIEMPO      *
 *  A IMPLEMENTAR.                                                                       *
 *                                                                                       *
 *****************************************************************************************/

// --- LIBRERIAS ---
#include <stdio.h> // sprintf, printf, scanf, EOF
#include <stdlib.h>
#include <math.h> // fabs

//----------------------------------------------------------------------------------------------------------------------

// --- COLORES PARA LA CONSOLA ---
// --- CONTROL ---
#define RESET       "\033[0m"
// --- TEXTO NORMAL (Oscuro) ---
#define BLACK       "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"                                                // ESTA PARTE
// --- TEXTO NEGRITA / BRILLANTE ---                                            // NO ES
#define B_BLACK     "\033[1;30m"                                                // IMPORTANTE
#define B_RED       "\033[1;31m"                                                // PARA LA
#define B_GREEN     "\033[1;32m"                                                // EJECUCIÓN
#define B_YELLOW    "\033[1;33m"
#define B_BLUE      "\033[1;34m"
#define B_MAGENTA   "\033[1;35m"
#define B_CYAN      "\033[1;36m"
#define B_WHITE     "\033[1;37m"
// --- FONDOS (Backgrounds) ---
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"
// --- COLORES EXCLUSIVOS (NUEVOS) ---
#define C_ORANGE    "\033[38;5;208m" // Naranja Vibrante (Para Análisis)
#define C_VIOLET    "\033[38;5;141m" // Violeta Claro (Para Matriz Triangular)
#define C_AQUA      "\033[38;5;51m"  // Aqua / Turquesa Neón (Para Resultados X)
// --- COLORES NUEVOS PARA TITULOS ---
#define C_PINK      "\033[38;5;201m" // Rosa Fuerte (Matriz Final)
#define C_LIME      "\033[38;5;118m" // Lima Brillante (Analisis)
#define C_GOLD      "\033[38;5;220m" // Dorado Intenso (Solución)

//----------------------------------------------------------------------------------------------------------------------

// --- CONSTANTES ---
#define MAX 20 // Indica la cantidad máxima de variables de la matriz A
#define EPSILON 1e-9 // A partir de este valor (0.000000001) empieza a considerarlos distinto de 0.

// --- ESTRUCTURAS ---
typedef struct {
    // Variables que se utilizan para guardar todo lo relacionado con las matrices, incluidas las matrices A y b
    int n; // Se utiliza para saber cuantas variables va a introducir y luego poder comparar con los rangos
    double A[MAX][MAX]; // Matriz A
    double b[MAX]; // Matriz b
    double det;
    int rangoA; // Rango de la matriz A
    int rangoAmp; // Rango de la matriz (A|b)
    int swaps; // Cuenta cuantas veces cambia las filas de posición para cambiar el signo del determinante
} Sistema;

typedef struct {
    // Variables para seleccionar que se quiere ver durante la ejecución
    int verPasos;
    int verTriangular;
    int verSolucion;
} Config;

// --- PROTOTIPOS FUNCIONES ---
void mostrarInstrucciones();
void leerSistema(Sistema *sys);
void imprimirEstado(Sistema *sys, const char *titulo);
void calcularEscalas(Sistema *sys, double s[]);
void triangularizarGauss(Sistema *sys, Config config);
void analizarSistema(Sistema *sys);
void resolverSustitucionAtras(Sistema *sys);
void clasificarYMostrar(Sistema *sys, Config config);

// --- MAIN ---
int main() {
    Sistema sys;
    Config config;
    int opcion;
    char continuar;

    mostrarInstrucciones();

    do {
        config.verPasos = 0;
        config.verTriangular = 0;
        config.verSolucion = 0;

        leerSistema(&sys);

        printf(B_CYAN"\nSeleccione nivel de detalle:\n"RESET);
        printf(CYAN"1. Ver TODO (Pasos detallados: Escalas, Multiplicadores, Matrices)\n");
        printf("2. Ver Matriz Final + Solucion\n");
        printf("3. Ver Solo Resultado\n");
        printf("Opcion: "RESET);
        scanf("%d", &opcion);

        if (opcion == 1) {
            config.verPasos = 1;
            config.verTriangular = 1;
            config.verSolucion = 1;
        }
        else if (opcion == 2) {
            config.verTriangular = 1;
            config.verSolucion = 1;
        }
        else {
            config.verSolucion = 1;
        }

        if (config.verPasos) {
            imprimirEstado(&sys, "Sistema Inicial");
        }

        triangularizarGauss(&sys, config);
        analizarSistema(&sys);
        clasificarYMostrar(&sys, config);

        printf(CYAN "\n============================================\n");
        printf("  ¿Desea resolver otro sistema? (s/n): ");
        scanf(" %c", &continuar);
        printf("============================================\n\n" RESET);

    } while (continuar == 's' || continuar == 'S');

    printf(B_YELLOW "Fin del programa.\n" RESET);
    return 0;
}

// --- FUNCIONES ---

void mostrarInstrucciones() {
    // Indica al usaurio como debe introducir los datos
    printf(B_GREEN "=======================================================\n");
    printf("  SOLUCIONADOR DE SISTEMAS LINEALES (GAUSS ESCALADO) \n");
    printf("=======================================================\n"RESET);
    printf(GREEN"\n=======================================================\n");
    printf("INSTRUCCIONES:\n");
    printf("- Se mostrarán los multiplicadores y vectores de escala\n");
    printf("  si selecciona la opcion 1.\n");
    printf("- Debe poner elemento a elemento en la matriz, no por\n");
    printf("  no por filas, el programa le indica en que posición\n");
    printf("  está.\n");
    printf("=======================================================\n\n" RESET);
}

void leerSistema(Sistema *sys) {
    sys->swaps = 0; // Obligamos a que la variable este "limpia"
    int entradaValida;

    printf(B_BLUE ">>> NUEVO SISTEMA <<<\n" RESET);
    do {
        printf(CYAN "Ingrese el numero de incognitas (n) [Max %d]: " RESET, MAX);

        int leidos = scanf("%d", &sys->n);
        int c;

        if (leidos != 1 || sys->n > MAX || sys->n <= 0) {
            /*
             * Aseguramos que:
             * - scanf no falla
             * - la cantidad de variables no supera la capacidad de la matriz
             * - la cantidad de variables sea mayor que cero para evitar tener una matriz de 0, , -3, -5 incognitas
             * Si está mal: Limpiamos buffer y avisamos
             */
            while((c = getchar()) != '\n' && c != EOF); // Limpiar basura
            printf(B_RED "Error: Debe ingresar un numero entero entre 1 y %d.\n" RESET, MAX);
            entradaValida = 0;
        } else {
            // Si está bien: Marcamos como válido para salir del bucle
            entradaValida = 1;
        }
    } while (entradaValida == 0);

    printf(CYAN "Ingrese coeficientes de la matriz A (fila por fila y elemento a elemento):\n" RESET);
    for (int i = 0; i < sys->n; i++) { // Rellena las filas
        for (int j = 0; j < sys->n; j++) { // Rellena las columnas
            printf("A[%d][%d] (X%d): ", i, j, j+1);
            scanf("%lf", &sys->A[i][j]);
        }
    }

    printf(CYAN "Ingrese el vector de constantes b (elemento a elemento):\n" RESET);
    for (int i = 0; i < sys->n; i++) {
        printf("b[%d]: ", i);
        scanf("%lf", &sys->b[i]);
    }
}

void imprimirEstado(Sistema *sys, const char *titulo) {
    // Se encarga de imprimir las matrices, se imprime los 4 primeros decimales aun que para los calculos no se redondea
    // La función fabs hace el valor absoluto
    if (titulo) printf(B_GREEN "\n--- %s ---\n" RESET, titulo);
    for (int i = 0; i < sys->n; i++) {
        printf("[ ");
        for (int j = 0; j < sys->n; j++) {
            double val = (fabs(sys->A[i][j]) < EPSILON) ? 0.0 : sys->A[i][j];
            printf("%10.4f ", val);
        }
        double val_b = (fabs(sys->b[i]) < EPSILON) ? 0.0 : sys->b[i]; // Transforma los menores que epsilon a 0
        printf("| %10.4f ]\n", val_b);
    }
    printf("\n");
}

void calcularEscalas(Sistema *sys, double s[]) {
    for (int i = 0; i < sys->n; i++) {
        s[i] = 0.0; // Limpiamos la matriz
        for (int j = 0; j < sys->n; j++) {
            if (fabs(sys->A[i][j]) > s[i]) s[i] = fabs(sys->A[i][j]);
        }
        if (s[i] < EPSILON) s[i] = 1.0; // Evita la divisiones entre 0.
    }
}

void triangularizarGauss(Sistema *sys, Config config) {
    double s[MAX];
    calcularEscalas(sys, s); // Cálculo inicial de escalas

    for (int k = 0; k < sys->n - 1; k++) {
        // --- 1. MOSTRAR VECTOR DE ESCALAS ---
        if (config.verPasos) {
            printf(GREEN "\n==================================================\n");
            printf(" ETAPA %d (Trabajando columna %d)\n", k + 1, k);
            printf("==================================================\n" RESET);
            printf(B_MAGENTA "1. Vector de Escalas (s) actual:\n   [ "RESET);
            for (int z = 0; z < sys->n; z++) printf("%.4f ", s[z]);
            printf("]\n");
            printf(MAGENTA"   -> Se usara para calcular ratios: |A[i][%d]| / s[i]\n" RESET, k);
        }

        // --- 2. PIVOTEO ---
        double max_ratio = -1.0;
        int p = k;

        for (int i = k; i < sys->n; i++) {
            double ratio = fabs(sys->A[i][k]) / s[i];

            if (config.verPasos) {
                // Muestra los ratios calculados
                printf(YELLOW "   Ratio fila %d: %.4f\n" RESET, i, ratio);
            }

            if (ratio > max_ratio) {
                // Si encontramos un ratio mejor
                max_ratio = ratio;
                p = i;
            }
        }

        if (fabs(sys->A[p][k]) < EPSILON) continue;

        if (p != k) {
            // Intercambia las filas
            if (config.verPasos) {
                printf(B_MAGENTA "2. Pivoteo: La fila %d tiene mejor ratio (%.4f) que la fila %d.\n"RESET, p, max_ratio, k);
                printf(BLUE"   >> Intercambiando filas y sus escalas s[%d] <-> s[%d]...\n" RESET, k, p);
            }

            // Swap Matriz
            for (int j = k; j < sys->n; j++) {
                double temp = sys->A[k][j]; sys->A[k][j] = sys->A[p][j]; sys->A[p][j] = temp;
            }
            // Swap b
            double temp_b = sys->b[k]; sys->b[k] = sys->b[p]; sys->b[p] = temp_b;
            // Swap Escalas
            double temp_s = s[k]; s[k] = s[p]; s[p] = temp_s;

            sys->swaps++;
        } else {
            if (config.verPasos) printf(B_MAGENTA "2. Pivoteo: La fila %d actual es el mejor pivote.\n" RESET, k);
        }


        if (config.verPasos) printf(B_MAGENTA "3. Eliminacion (Haciendo ceros):\n" RESET);

        for (int i = k + 1; i < sys->n; i++) {
            double factor = sys->A[i][k] / sys->A[k][k];

            // Muestra multiplicador
            if (config.verPasos) {
                printf(MAGENTA "   -> Fila %d: Multiplicador = A[%d][%d] / Pivote(%.4f) = %.4f / %.4f = %.4f\n" RESET,
                       i, i, k, sys->A[k][k], sys->A[i][k], sys->A[k][k], factor);
            }

            sys->A[i][k] = 0.0;
            for (int j = k + 1; j < sys->n; j++) {
                sys->A[i][j] -= factor * sys->A[k][j];
            }
            sys->b[i] -= factor * sys->b[k];
        }

        // ! PREGUNTAR!!!!!!
        if (config.verPasos) {
            char buffer[50];
            sprintf(buffer, "Matriz despues de etapa %d", k+1);
            imprimirEstado(sys, buffer);
        }
    }
}
// ----------------------------------------------------------------------

void analizarSistema(Sistema *sys) { // ! PREGUNTAR!!!!!
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

void resolverSustitucionAtras(Sistema *sys) { // ! PREGUNTAR!!!!!!
    double x[MAX];

    for (int i = sys->n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < sys->n; j++) {
            sum += sys->A[i][j] * x[j];
        }
        x[i] = (sys->b[i] - sum) / sys->A[i][i];
    }

    printf(C_PINK "\n>>> SOLUCION FINAL:\n" RESET);
    for (int i = 0; i < sys->n; i++) {
        printf(C_AQUA "x[%d] = %10.6f\n" RESET, i, x[i]);
    }
}

void clasificarYMostrar(Sistema *sys, Config config) { // ! PREGUNTAR !!!!!!
    if (config.verTriangular) imprimirEstado(sys, "Matriz Triangular Final");

    printf(C_LIME"----------------------------------------\n");
    printf("ANALISIS DE RESULTADOS:\n"RESET);
    printf(C_ORANGE "Determinante: %.4f\n", sys->det);
    printf("Rango(A): %d\n", sys->rangoA);
    printf("Rango(A|b): %d\n" RESET, sys->rangoAmp);
    printf("----------------------------------------\n" RESET);

    if (sys->rangoA != sys->rangoAmp) {
        printf(C_GOLD "RESULTADO: SISTEMA INCOMPATIBLE (Sin solucion)\n"RESET);
    }
    else if (sys->rangoA < sys->n) {
        printf(C_GOLD "RESULTADO: SISTEMA COMPATIBLE INDETERMINADO (Infinitas soluciones)\n");
        printf("Grados de libertad: %d\n"RESET, sys->n - sys->rangoA);
    }
    else {
        printf(C_GOLD "RESULTADO: SISTEMA COMPATIBLE DETERMINADO (Solucion unica)\n"RESET);
        if (config.verSolucion) {
            resolverSustitucionAtras(sys);
        }
    }
}
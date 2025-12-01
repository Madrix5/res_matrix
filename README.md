📐 Linear System Solver (Gaussian Elimination)
Un solucionador avanzado de sistemas de ecuaciones lineales (Ax=b) desarrollado en C. Implementa el método de Eliminación de Gauss con Pivoteo Parcial Escalado para maximizar la precisión numérica y minimizar errores de redondeo en sistemas mal condicionados.

El proyecto destaca por su interfaz de consola coloreada, gestión dinámica de memoria, análisis de estabilidad numérica y un banco de pruebas integrado con matrices patológicas conocidas.

🚀 Características Principales
🧠 Motor Matemático

Algoritmo Robusto: Eliminación Gaussiana con Pivoteo Parcial Escalado. Calcula vectores de escala para seleccionar el mejor pivote relativo, crucial para matrices con coeficientes de magnitudes dispares.

Precisión Científica: Ajustado a EPSILON 1e-15 para aprovechar la máxima precisión del tipo de dato double, filtrando ruido numérico.

Análisis Rouché-Frobenius: Calcula determinantes y rangos (Rango(A) vs Rango(A∣b)) para clasificar sistemas en:

Compatible Determinado (Solución Única).

Compatible Indeterminado (Infinitas Soluciones).

Incompatible (Sin Solución).

🛡️ Ingeniería de Software

Memoria Dinámica: Uso de malloc y free para manejar matrices de tamaño arbitrario (N×N), limitadas solo por la RAM del sistema (sin arrays estáticos fijos).

Entrada Robusta: Sistema de limpieza de buffer (stdin) que previene errores de lectura y permite la introducción de datos copiando y pegando filas enteras.

Benchmarking: Cronómetro de CPU integrado para medir el tiempo de cómputo exacto del algoritmo.

🎨 Interfaz y Visualización

Tabla Dinámica: Algoritmo de renderizado que calcula el ancho de columna óptimo en tiempo real para alinear perfectamente los decimales en la consola.

Diagnóstico Visual (Colores ANSI):

🟢 Verde: Sistema estable / Solución exitosa.

🟡 Amarillo: Precaución (Pérdida de 4-8 dígitos de precisión).

🟠 Naranja: Peligro (Matriz inestable).

🔴 Rojo/Fondo Rojo: Error crítico / Estabilidad catastrófica.

🧪 Banco de Pruebas Integrado
El programa incluye una base de datos interna con 17 casos de prueba para validar el algoritmo bajo estrés:

ID	Nombre	Propósito de la Prueba
1-4	Básicos	Validación de lógica SCD, SCI y SI.
5	Matriz de Hilbert	Test de mal condicionamiento clásico.
6	Magnitudes Extremas	Prueba del vector de escalado (10 
10
  vs 10 
−10
 ).
7	Matriz de Wilson	Matriz patológica muy mal condicionada.
8	Irracionales	Precisión con π, e y raíces.
9	Pascal 12x12	Desbordamiento y números grandes.
11	Estrés 20x20	Rendimiento y visualización en matrices grandes.
15-17	Tests de Alerta	Verificación del sistema de diagnóstico de errores numéricos.
⚙️ Instalación y Compilación
Este proyecto no requiere librerías externas no estándar. Se compila con gcc.

Clonar el repositorio:

Bash
git clone https://github.com/tu-usuario/linear-system-solver.git
cd linear-system-solver
Compilar (Linux/Mac/WSL): Es recomendable usar flags de advertencia para asegurar la calidad del código.

Bash
gcc main.c -o solver -lm -Wall -Wextra
(Nota: -lm es necesario para linkear la librería matemática math.h).

Ejecutar:

Bash
./solver
📖 Uso
Al iniciar, el programa ofrece un menú interactivo:

Modo de Entrada:

Manual: Introduce N y luego los coeficientes fila a fila (puedes copiar y pegar desde un excel o texto).

Base de Datos: Selecciona una de las 17 matrices de prueba.

Opción de Escalado:

Elige si deseas incluir el vector de términos independientes b en el cálculo del factor de escala (Criterio académico vs estándar).

Nivel de Detalle:

1. Ver TODO: Muestra paso a paso la triangularización, vectores de escala, multiplicadores y operaciones.

2. Matriz Final: Muestra solo el resultado triangular y la solución.

3. Solo Resultado: Muestra valores de X y métricas.

📸 Capturas (Ejemplo de Salida)
Plaintext
--- ANALISIS DE RESULTADOS ---
Determinante: 1.00000000000000
Rango(A): 3
Rango(A|b): 3
----------------------------------------
RESULTADO: SISTEMA COMPATIBLE DETERMINADO (Solucion unica)

>>> SOLUCION FINAL:
  x[0] = 1.00000000000000
  x[1] = 1.00000000000000
  x[2] = 1.00000000000000

----------------------------------------
 Tiempo de Computo (CPU): 0.000004 s 
----------------------------------------
👤 Autor
Adrián Jiménez Calderón

Estudiante de Ingeniería Informática

Asignatura: Álgebra y Matemática Discreta

Fecha: Noviembre 2025

📄 Licencia
Este proyecto está bajo la Licencia MIT - ver el archivo LICENSE para más detalles.

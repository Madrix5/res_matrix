<<<<<<< HEAD
=======
<div align="center">

# 📐 Advanced Linear System Solver
### Gaussian Elimination with Scaled Partial Pivoting

![Language](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)

<p align="center">
  <strong>Solucionador de sistemas NxN de alto rendimiento, precisión científica y análisis de estabilidad numérica.</strong>
</p>

[Reportar Error](https://github.com/Madrix5/res_matrix/issues) · [Solicitar Función](https://github.com/Madrix5/res_matrix/issues)

</div>

---

## 📖 Descripción

Este proyecto es una implementación robusta en **C (Estándar C11)** diseñada para resolver sistemas de ecuaciones lineales de la forma $Ax = b$. A diferencia de los solucionadores académicos estándar, este programa implementa **Pivoteo Parcial Escalado** y gestión de **Memoria Dinámica**, permitiendo resolver sistemas complejos y matrices mal condicionadas (como Hilbert o Wilson) con la máxima precisión que permite la arquitectura de 64 bits.

El software no solo resuelve el sistema, sino que actúa como una herramienta de diagnóstico, analizando la estabilidad numérica, calculando determinantes, rangos y clasificando el tipo de sistema según el teorema de Rouché-Frobenius.

---

## 🚀 Características Principales

### 🧠 Motor Matemático Avanzado
* **Algoritmo:** Eliminación Gaussiana con **Pivoteo Parcial Escalado** (minimiza el error de redondeo seleccionando el mejor pivote relativo a su fila).
* **Precisión Extrema:** Configurado con `EPSILON 1e-15` para aprovechar el límite de los tipos `double`.
* **Análisis Completo:**
    * Determinante (con corrección de signo por intercambios).
    * Cálculo de Rangos ($R(A)$ y $R(A|b)$).
    * Detección automática de sistemas **S.C.D.**, **S.C.I.** y **S.I.**

### 🛡️ Software
* **Memoria Dinámica:** Uso de `malloc` y `free`. Sin límites de tamaño de matriz (solo limitado por tu RAM).
* **Entrada Robusta:** Sistema de limpieza de buffer (`stdin`) que previene errores de lectura y permite copiar y pegar filas enteras.
* **Benchmarking:** Cronómetro de CPU integrado para medir el rendimiento del algoritmo en segundos (`time.h`).

### 🎨 Interfaz y Visualización (CLI)
* **Renderizado Dinámico:** La tabla de la matriz se ajusta automáticamente al ancho del número más largo para mantener una alineación perfecta.
* **Diagnóstico Visual:** Uso de códigos ANSI para alertas de colores:
    * 🟢 **Verde:** Matriz estable.
    * 🟡 **Amarillo:** Precaución (Pérdida de 4-8 dígitos).
    * 🟠 **Naranja:** Peligro (Matriz inestable).
    * 🔴 **Rojo:** Estabilidad crítica / Ruido numérico.

---

## 📥 Descarga del Proyecto

Puedes obtener el código fuente directamente desde el repositorio oficial:

### Clonar repositorio
```bash
git clone [https://github.com/Madrix5/res_matrix.git](https://github.com/Madrix5/res_matrix.git)
```
```bash
cd res_matrix
```

### Compilado y ejecución
```bash
gcc main.c -o res_matrix -std=c11 -lm -Wall -Wextra -Werror
```

#### Desglose de flags:

* std=c11: Fuerza el uso del estándar C11.

* lm: Enlaza la librería matemática (math.h).

* Wall -Wextra: Activa todas las advertencias útiles.

* Werror: Trata las advertencias como errores (asegura un código limpio).

```bash
./res_matrix
```

## 📸 Ejemplos de Uso

### 1. Menú Principal e Interacción
Al ejecutar el programa, el sistema guía al usuario a través de menús robustos y claros. Aquí se muestra cómo seleccionar una matriz de la base de datos interna:

```text
=======================================================
  SOLUCIONADOR DE SISTEMAS LINEALES (GAUSS ESCALADO) 
=======================================================

  SELECCIONE MODO DE ENTRADA:
  1. Introducir Matriz Manualmente
  2. Cargar Matriz de Prueba (Base de Datos)
>> Opcion (1-2): 2

--- BASE DE DATOS DE MATRICES ---
...
5. Matriz de Hilbert 4x4 (Prueba de precision extrema)
6. Magnitudes Extremas (Prueba de escalado)
7. Matriz de Wilson 4x4 (Muy mal condicionada)
...
>> Seleccione prueba (1-17): 7

--- MATRIZ TRIANGULAR FINAL ---
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    7 |                   10 |                    8 |                    7 |                   32 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    0 |     2.28571428571429 |     4.28571428571429 |     5.71428571428571 |     13.7142857142857 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    0 |                    0 |                  0.2 |                  0.6 |                  0.8 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    0 |                    0 |                    0 | 0.000292968750000003 | 0.000292968750000023 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+

----------------------------------------
 ANALISIS DE RESULTADOS:
 Determinante: 165
 Rango(A): 4
 Rango(A|b): 4
 Ratio de Pivotes: 2.4e+04
 [PRECAUCION] Matriz mal condicionada 
 > Se han perdido entre 4 y 8 digitos. (Ej: Matriz de Wilson/Hilbert)
----------------------------------------
 RESULTADO: SISTEMA COMPATIBLE DETERMINADO (Solucion unica)

>>> SOLUCION FINAL:
  x[0] = 1
  x[1] = 1
  x[2] = 1
  x[3] = 1

----------------------------------------
 Tiempo de Computo (CPU): 0.000005 s 
----------------------------------------
```

## 👤 Autor

**Adrián Jiménez Calderón**
* **Fecha:** Noviembre 2025
* **Contacto:** [Perfil de GitHub](https://github.com/Madrix5) [email](adrian.jimdev@gmail.com)

---

## 📄 Licencia

Este proyecto se distribuye bajo la licencia **MIT**. Esto significa que eres libre de usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software, siempre que se incluya el aviso de copyright original.

```text
MIT License

Copyright (c) 2025 Adrián Jiménez Calderón

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

>>>>>>> ed849f6e1b57489cf24688fd9db956d35fc53e5d

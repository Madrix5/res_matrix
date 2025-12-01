<div align="center">

# 📐 Advanced Linear System Solver
### Gaussian Elimination with Scaled Partial Pivoting

![Language](https://img.shields.io/badge/Language-C99-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)

<p align="center">
  <strong>Solucionador de sistemas NxN de alto rendimiento, precisión científica y análisis de estabilidad numérica.</strong>
</p>

[Report Bug] . [Request Feature]

</div>

---

## 📖 Descripción

Este proyecto es una implementación robusta en **C** diseñada para resolver sistemas de ecuaciones lineales de la forma $Ax = b$. A diferencia de los solucionadores académicos estándar, este programa implementa **Pivoteo Parcial Escalado** y gestión de **Memoria Dinámica**, permitiendo resolver sistemas complejos y matrices mal condicionadas (como Hilbert o Wilson) con la máxima precisión que permite la arquitectura de 64 bits.

El software no solo resuelve el sistema, sino que actúa como una herramienta de diagnóstico, analizando la estabilidad numérica, calculando determinantes, rangos y clasificando el tipo de sistema según el teorema de Rouché-Frobenius.

---

## 🚀 Características Principales

### 🧠 Motor Matemático Avanzado
* **Algoritmo:** Eliminación Gaussiana con **Pivoteo Parcial Escalado** (minimiza el error de redondeo seleccionando el mejor pivote relativo a su fila).
* **Precisión Extrema:** Configurado con `EPSILON 1e-15` para aprovechar el límite de los tipos `double` en C.
* **Análisis Completo:**
    * Determinante (con corrección de signo por intercambios).
    * Cálculo de Rangos ($R(A)$ y $R(A|b)$).
    * Detección automática de sistemas **S.C.D.**, **S.C.I.** y **S.I.**

### 🛡️ Software
* **Memoria Dinámica:** Uso de `malloc` y `free`. Sin límites de tamaño de matriz (solo limitado por tu RAM).
* **Entrada Robusta:** Sistema de limpieza de buffer (`stdin`) que permite copiar y pegar filas enteras desde Excel o texto sin errores de lectura.
* **Benchmarking:** Cronómetro de CPU integrado para medir el rendimiento del algoritmo en segundos (`time.h`).

### 🎨 Interfaz y Visualización (CLI)
* **Renderizado Dinámico:** La tabla de la matriz se ajusta automáticamente al ancho del número más largo para mantener una alineación perfecta.
* **Diagnóstico Visual:** Uso de códigos ANSI para alertas de colores:
    * 🟢 **Verde:** Matriz estable.
    * 🟡 **Amarillo:** Precaución (Pérdida de 4-8 dígitos).
    * 🟠 **Naranja:** Peligro (Matriz inestable).
    * 🔴 **Rojo:** Estabilidad crítica / Ruido numérico.

---

## 🛠️ Instalación y Compilación

Este proyecto no requiere dependencias externas más allá de la librería estándar y matemática.

### Prerrequisitos
* Compilador GCC (o Clang).
* Make (opcional).

### Compilación (Linux / macOS / WSL)
Se recomienda usar las flags de advertencia para asegurar la integridad del código.

```bash
gcc -Wall -Wextra -Werror -lm -o gauss main.c

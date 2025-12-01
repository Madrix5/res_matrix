<div align="right">
  
[<img src="https://flagcdn.com/24x18/es.png" alt="Español" valign="middle"> **Español**](./README.es.md)

</div>

<div align="center">

# 📐 Advanced Linear System Solver
### Gaussian Elimination with Scaled Partial Pivoting

![Language](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)

<p align="center">
  <strong>High-performance NxN system solver with scientific precision and numerical stability analysis.</strong>
</p>

[Report Bug](https://github.com/Madrix5/res_matrix/issues) · [Request Feature](https://github.com/Madrix5/res_matrix/issues)

</div>

---

## 📖 Description

This project is a robust implementation in **C (C11 Standard)** designed to solve systems of linear equations of the form $Ax = b$. Unlike standard academic solvers, this program implements **Scaled Partial Pivoting** and **Dynamic Memory** management, allowing it to solve complex systems and ill-conditioned matrices (such as Hilbert or Wilson) with the maximum precision allowed by 64-bit architecture.

The software not only solves the system but acts as a diagnostic tool, analyzing numerical stability, calculating determinants and ranks, and classifying the system type according to the Rouché-Frobenius theorem.

---

## 🚀 Key Features

### 🧠 Advanced Mathematical Engine
* **Algorithm:** Gaussian Elimination with **Scaled Partial Pivoting** (minimizes rounding errors by selecting the best pivot relative to its row).
* **Extreme Precision:** Configured with `EPSILON 1e-15` to leverage the full limit of `double` types.
* **Complete Analysis:**
    * Determinant (with sign correction for row swaps).
    * Rank Calculation ($R(A)$ and $R(A|b)$).
    * Automatic detection of **Determinate**, **Indeterminate**, and **Inconsistent** systems.

### 🛡️ Software Engineering
* **Dynamic Memory:** Uses `malloc` and `free`. No matrix size limits (limited only by your RAM).
* **Robust Input:** Input buffer cleaning system (`stdin`) that prevents reading errors and allows copying and pasting entire rows.
* **Benchmarking:** Integrated CPU chronometer to measure algorithm performance in seconds (`time.h`).

### 🎨 Interface & Visualization (CLI)
* **Dynamic Rendering:** The matrix table automatically adjusts to the width of the longest number to maintain perfect alignment.
* **Visual Diagnosis:** Uses ANSI color codes for alerts:
    * 🟢 **Green:** Stable matrix.
    * 🟡 **Yellow:** Caution (Loss of 4-8 precision digits).
    * 🟠 **Orange:** Danger (Unstable matrix).
    * 🔴 **Red:** Critical stability / Numerical noise.

---

## 📥 Download

You can get the source code directly from the official repository:

### Option 1: Clone with Git (Recommended)
Open your terminal and run:
```bash
git clone [https://github.com/Madrix5/res_matrix.git](https://github.com/Madrix5/res_matrix.git)
```
#### Flags breakdown:

* std=c11: Forces the use of the C11 standard.

* lm: Links the math library (math.h).

* Wall -Wextra: Enables all useful warnings.

* Werror: Treats warnings as errors (ensures clean code).
  
```bash
cd res_matrix
```
```
./res_matrix
```

📸 Usage Examples
1. Main Menu & Interaction

Upon execution, the system guides the user through robust menus. Here is how to select a matrix from the internal database:
```
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
 |                    0 |      2.28571428571429 |      4.28571428571429 |      5.71428571428571 |      13.7142857142857 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    0 |                    0 |                   0.2 |                   0.6 |                   0.8 |
 +----------------------+----------------------+----------------------+----------------------+----------------------+
 |                    0 |                    0 |                    0 |  0.000292968750000003 |  0.000292968750000023 |
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

### 👤 Author
Adrián Jiménez Calderón

* Date: November 2025

* Contact: GitHub Profile | Email

### 📄 License
This project is distributed under the MIT license. This means you are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software, provided the original copyright notice is included.
```
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
```

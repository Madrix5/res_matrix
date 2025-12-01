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

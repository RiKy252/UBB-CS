# Lab Documentation: Parallel Polynomial Multiplication

## 1. The Algorithms

### A. Simple Multiplication (O(n^2))
This is the classic approach based on the mathematical definition of polynomial multiplication.
* **Logic:** For two polynomials $A$ and $B$, the coefficient of the resulting polynomial at index $k$ ($Result[k]$) is calculated as the sum of products of coefficients $A[i]$ and $B[j]$ such that $i + j = k$.
* **Complexity:** Time complexity is $O(n^2)$, where $n$ is the degree of the polynomials.
* **Implementation:** It involves a double loop structure.

### B. Karatsuba Algorithm (O(n^1.58))
This is a "Divide and Conquer" algorithm that reduces the number of elementary multiplications required.
* **Logic:**
    1.  Split polynomials $A$ and $B$ into two halves (High and Low parts) at index $n/2$:
        * $A(x) = A_{high} \cdot x^{n/2} + A_{low}$
        * $B(x) = B_{high} \cdot x^{n/2} + B_{low}$
    2.  Compute three intermediate products recursively:
        * $Z_0 = A_{low} \times B_{low}$
        * $Z_2 = A_{high} \times B_{high}$
        * $Z_1 = (A_{low} + A_{high}) \times (B_{low} + B_{high})$
    3.  Compute the middle term: $Result\_Mid = Z_1 - Z_2 - Z_0$.
    4.  Combine the results: $Result = Z_2 \cdot x^n + Result\_Mid \cdot x^{n/2} + Z_0$.
* **Complexity:** Time complexity is $O(n^{\log_2 3}) \approx O(n^{1.58})$, which makes it significantly faster for large degrees.

---

## 2. Synchronization in Parallel Variants

### A. Simple Parallel Multiplication
* **Strategy:** Data Decomposition / Output Partitioning.
* **Synchronization Mechanism:**
    * No explicit synchronization primitives (locks/mutexes) were required.
    * Partition the **indices of the result array** among the available threads.
    * Each thread is responsible for computing a specific range of coefficients $[start, end)$ of the resulting polynomial.
    * Since each index $k$ in the result array is computed by exactly one thread, there are no race conditions (no two threads write to the same memory location simultaneously).

### B. Karatsuba Parallel Multiplication
* **Strategy:** Task Parallelism (Divide & Conquer).
* **Synchronization Mechanism:**
    * Used the `ForkJoinPool` framework (Java).
    * The recursion tree allows to parallelize the three main sub-tasks ($Z_0$, $Z_1$, $Z_2$).
    * **Fork:** Asynchronously submit tasks for computing $Z_0$, $Z_1$, and $Z_2$.
    * **Join:** The parent task waits for the completion of its child tasks before combining the results.
    * **Thread Safety:** The algorithm is naturally thread-safe because each step creates new polynomial objects. There is no shared mutable state between tasks.

---

## 3. Performance Measurements

### Test Case 1
* **Polynomial Degree:** 10000
* **Number of Threads:** 8

| Algorithm | Execution Time (ms) |
| :--- | :--- |
| Simple Sequential | 215ms |
| Simple Parallel | 119ms |
| Karatsuba Sequential | 252ms |
| Karatsuba Parallel | 190ms |

### Test Case 2
* **Polynomial Degree:** 100000
* **Number of Threads:** 8

| Algorithm | Execution Time (ms) |
| :--- | :--- |
| Simple Sequential | 12519ms |
| Simple Parallel | 4940ms |
| Karatsuba Sequential | 4886ms |
| Karatsuba Parallel | 1141ms |
# Lab 7 Documentation

## 1. Algorithms Implemented

### 1.1 Naive Multiplication
* **Complexity:** $O(n \times m)$ (or $O(n^2)$ if polynomials are equal size).
* **Logic:** A classic double-loop approach. Every coefficient of polynomial $A$ is multiplied by every coefficient of polynomial $B$, and the results are accumulated into the corresponding degree index of the result vector.
* **Use Case:** Used as a baseline for performance comparison and as the base-case for Karatsuba recursion when input sizes drop below 1024 elements.

### 1.2 Karatsuba Multiplication
* **Complexity:** $O(n^{\log_2 3}) \approx O(n^{1.58})$.
* **Logic:** A divide-and-conquer algorithm that splits inputs into upper and lower halves. It reduces the number of recursive multiplications from 4 (in a standard divide-and-conquer) to 3 using the identity:
    $$XY = (z^2 + z)X_1Y_1 - z(X_1 - X_0)(Y_1 - Y_0) + (z+1)X_0Y_0$$
* **Implementation:** The recursion continues until the vector size is $\le 1024$, at which point it switches to the Naive method to minimize recursive overhead.

---

## 2. Distribution & Communication Strategy

### 2.1 Data Partitioning (Scatter-Broadcast Strategy)
Instead of splitting both polynomials, the implementation assumes polynomial $B$ fits in memory on all nodes, while polynomial $A$ is distributed.
1.  **Broadcast B:** The entire polynomial $B$ is sent from the Master (Rank 0) to all Worker processes using `MPI_Bcast`.
2.  **Scatter A:** Polynomial $A$ is split into contiguous chunks.
    * *Master process* calculates chunk sizes and offsets.
    * Chunks are sent to workers using **Manual Point-to-Point Communication** (`MPI_Send`), rather than `MPI_Scatter`, to handle uneven remainders dynamically.

### 2.2 Parallel Computation
Each process $P_i$ computes a partial polynomial:
$$Result_i = A_{chunk\_i} \times B$$
This is performed locally using the selected algorithm (Naive or Karatsuba).

### 2.3 Result Aggregation (Gather & Shift)
Since $A$ was split into chunks representing different powers of $x$, the results from workers overlap in terms of polynomial degree.
1.  **Worker Action:** Sends the local result vector back to Master via `MPI_Send`.
2.  **Master Action:**
    * Initializes a final result vector.
    * Adds its own local result.
    * Receives results from workers and adds them to the final vector **shifted by the corresponding offset**.
    * $$Final[offset + j] += WorkerResult[j]$$

---

## 3. Performance Measurements

### 3.1 Test Environment
* **Input Size:** Polynomial Degree = 200,000
* **Metric:** Execution Time (seconds) measured via `MPI_Wtime()`.

### 3.2 Results: Naive Algorithm ($O(n^2)$)

| Processes (N) | Execution Time (s) | 
| :---: | :---: | 
| **1 (Serial)** | 20.995328 | 
| **2** | 9.488903 | 
| **4** | 4.564386 | 
| **8** | 3.818240 | 

### 3.3 Results: Karatsuba Algorithm ($O(n^{1.58})$)

| Processes (N) | Execution Time (s) | 
| :---: | :---: | 
| **1 (Serial)** | 2.011896 | 
| **2** | 5.938657 | 
| **4** | 4.209032 | 
| **8** | 3.428956 | 

---
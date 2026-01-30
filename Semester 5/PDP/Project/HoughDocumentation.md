# Hough Transformation: Shared Memory (Threads) vs. Distributed Memory (MPI)

## 1. Algorithms Description

### 1.1. Sobel Edge Detection
The Sobel operator is used to calculate the gradient magnitude of the image, effectively identifying edges where the intensity changes sharply. The algorithm involves convolving the input image with two 3x3 kernels:

**Gx (Horizontal):**

|  |  |  |
| :---: | :---: | :---: |
| -1 | 0 | 1 |
| -2 | 0 | 2 |
| -1 | 0 | 1 |

**Gy (Vertical):**

|  |  |  |
| :---: | :---: | :---: |
| -1 | -2 | -1 |
| 0 | 0 | 0 |
| 1 | 2 | 1 |

For each pixel, the gradient magnitude **G** is calculated as:
**G = √(Gx² + Gy²)**

A binary threshold is applied (e.g., G > 50) to classify the pixel as an edge (255) or background (0).

### 1.2. The Hough Transform
The Hough Transform converts edge points from Cartesian space (x,y) to Parameter space (ρ, θ). Unlike the slope-intercept form (y = mx + n), which fails for vertical lines, we use the normal equation:

**ρ = x cos(θ) + y sin(θ)**

Where:
* **ρ** (rho) is the perpendicular distance from the origin.
* **θ** (theta) is the angle of the normal vector.

The algorithm uses a voting mechanism in a 2D accumulator array. Local peaks in the accumulator represent the parameters of detected lines.

---

## 2. Implementation A: Shared Memory (C++ Threads)
This implementation targets multi-core Single Node architectures, utilizing `std::thread` for lightweight process management and shared memory access.

### 2.1. Parallelization Strategy: Domain Decomposition
We utilized a **Data Decomposition** approach. The input image is treated as a matrix of pixels divided horizontally into equal strips (chunks).
* **Workload Distribution:** Each thread is assigned a specific range of rows (`startRow` to `endRow`).
* **Independence:** This decomposition applies to both the Sobel filtering and the Hough voting phases. Since the Sobel operator only requires a 3x3 neighborhood, threads can process their strips with minimal dependencies.

### 2.2. Synchronization & Data Safety
A critical challenge in parallelizing the Hough Transform is the **write conflict** (Race Condition) in the Global Accumulator when multiple threads attempt to vote for the same line parameters simultaneously.

**Optimization: Data Privatization**
Using **Mutex Locks** for every vote would serialize execution and degrade performance. Instead, we implemented **Data Privatization**:
1.  **Local Accumulators:** Each thread allocates its own private Accumulator Matrix in the Heap memory.
2.  **Lock-Free Processing:** Threads vote into their private accumulators independently. No synchronization overhead is incurred during the computationally heavy voting phase.
3.  **Barrier & Reduction:** A `thread.join()` barrier ensures all threads complete. Finally, the Main Thread performs a **Reduction** operation, summing all Local Accumulators into the Global Result.

---

## 3. Implementation B: Distributed Memory (MPI)
This implementation utilizes the **Message Passing Interface (MPI)** to distribute the workload across separate processes.

### 3.1. Domain Decomposition
Similar to the threaded approach, the workload is distributed using a **Row-wise Decomposition** strategy. The input image height is divided by the number of available MPI processes (N).

**Rows per Rank = Image Height / N**

Each rank is responsible for processing a specific horizontal strip of the image.

### 3.2. Communication & Synchronization
Since MPI processes do not share memory, explicit data movement is handled via **MPI Collective Communication** primitives:

1.  **Data Distribution (Broadcast):** The Master rank (Rank 0) reads the input PGM file and uses `MPI_Bcast` to send the raw pixel data to all worker ranks. This ensures all ranks have the necessary context to compute boundary conditions.

2.  **Result Aggregation (Reduction):**
    * **Edge Map:** After local Sobel computation, `MPI_Reduce` combines local vectors into a global image on Rank 0.
    * **Hough Accumulator:** Each rank maintains a local accumulator. A final `MPI_Reduce` with the `MPI_SUM` operator aggregates these votes into the global accumulator on Rank 0.

---

## 4. Performance Analysis
Benchmarks were conducted using a high-resolution test image (**4017 x 2683 pixels**) to stress-test the computational throughput and memory bandwidth.

### 4.1. Shared Memory Scalability Results
The table below illustrates the execution time and speedup obtained using the Shared Memory implementation.

| Thread Count | Execution Time (sec) | Speedup (T1 / Tn) |
| :---: | :---: | :---: |
| **1 (Serial)** | 8.56242 | 1.00x |
| **2** | 5.43334 | 1.58x |
| **4** | 4.44144 | 1.93x |
| **8** | 3.54753 | 2.41x |
| **12** | 3.34820 | 2.56x |

### 4.2. Distributed Memory Scalability Results

| Process Count | Execution Time (sec) | Speedup (T1 / Tn) |
| :---: | :---: | :---: |
| **1 (Serial)** | 12.09912 | 1.00x |
| **2** | 6.67234 | 1.58x |
| **3** | 6.56782 | 1.93x |
| **4** | 5.14723 | 2.41x |
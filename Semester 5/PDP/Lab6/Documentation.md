# Parallel Hamiltonian Cycle Search

## 1. The Algorithms

The goal is to find a Hamiltonian cycle (a path that visits every vertex exactly once and returns to the start) in a directed graph. The problem is NP-Complete, requiring a backtracking approach.

### Backtracking Strategy
1. Start at a fixed vertex $v_0$.
2. Maintain a `path` list and a `visited` array.
3. For the `current_vertex`, look at all unvisited neighbors.
4. Recursively move to a neighbor, mark it visited, and add to path.
5. If `path.size() == num_vertices` and there is an edge back to $v_0$, a cycle is found.
6. If a path leads to a dead end, backtrack (unmark visited, remove from path).

### Variant 1: Manual Thread Management (Budgeting)
This variant implements a specific work-splitting logic based on a "thread budget".
* The search function receives a `budget` (number of threads).
* Let $K$ be the number of valid (unvisited) neighbors.
* If `budget` > 1:
    * We calculate `threadsPerBranch = budget / K`.
    * We calculate `remainder = budget % K`.
    * The first `remainder` neighbors get `threadsPerBranch + 1` threads.
    * The rest get `threadsPerBranch`.
    * New threads are spawned for these branches (parallel exploration).
* If `budget` <= 1:
    * The search continues sequentially on the current thread (standard DFS).

### Variant 2: ForkJoin Framework
This variant uses Java's `RecursiveTask` to handle parallelism naturally.
* For each valid neighbor, a new `HamiltonianTask` is created (containing a copy of the current path and visited status).
* All tasks are `forked` (submitted to the pool).
* The parent task `joins` (waits) for children.
* Optimization: We use an atomic global flag/reference to stop computation in other branches once a solution is found anywhere.

---

## 2. Synchronization

Finding a Hamiltonian cycle is a search problem where we only need **one** solution. Synchronization is critical for two things:
1.  **Terminating useless work:** Once a thread finds a cycle, all other threads should stop.
2.  **Reporting the result:** Safely storing the path.

### In Manual Threads Variant
* **`AtomicBoolean solutionFound`:** Checked at the beginning of every recursive step. If `true`, the function returns immediately.
* **`synchronized` block:** Used only when writing the final result to `resultPath` to ensure only one thread claims the victory.
* **No Graph Locking:** The graph structure is read-only, so accessing neighbors does not require locks.

### In ForkJoin Variant
* **`AtomicReference<List<Integer>> globalResult`:** Stores the result.
* **Short-circuiting:** * `compute()` checks `if (globalResult.get() != null) return null;` at the start.
    * `compareAndSet(null, path)` is used to atomically save the solution.

---

## 3. Performance Measurements

### Hardware
* Threads: 12

### Test Results (20 nodes)

| Variant | Time (ms) | 
| :--- | :--- | 
| **Manual Threads** | 19 ms | 
| **ForkJoin** | 11 ms | 

### Test Results (100 nodes)

| Variant | Time (ms) | 
| :--- | :--- | 
| **Manual Threads** | 49 ms | 
| **ForkJoin** | 27 ms | 
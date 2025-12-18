import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class HamiltonianClassic {
    private Graph graph;
    // Atomic flag to stop all threads when a solution is found
    private AtomicBoolean solutionFound = new AtomicBoolean(false);
    private List<Integer> resultPath = null;
    private final Object lock = new Object();

    public HamiltonianClassic(Graph graph) {
        this.graph = graph;
    }

    public void solve(int startNode, int numThreads) {
        solutionFound.set(false);
        resultPath = null;
        List<Integer> path = new ArrayList<>();
        path.add(startNode);
        
        boolean[] visited = new boolean[graph.getNumVertices()];
        visited[startNode] = true;

        try {
            search(startNode, path, visited, numThreads);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if (resultPath != null) {
            System.out.println("Classic Solution: " + resultPath);
        } else {
            System.out.println("Classic Solution: No Hamiltonian cycle.");
        }
    }

    private void search(int currentNode, List<Integer> path, boolean[] visited, int threadBudget) throws InterruptedException {
        // 1. Check if we already found a global solution (optimisation)
        if (solutionFound.get()) return;

        // 2. Check if cycle is complete
        if (path.size() == graph.getNumVertices()) {
            // Check if we have an edge from the last node to the first node
            if (graph.getNeighbors(currentNode).contains(path.get(0))) {
                synchronized (lock) {
                    if (!solutionFound.get()) {
                        solutionFound.set(true);
                        resultPath = new ArrayList<>(path);
                    }
                }
            }
            return;
        }

        // 3. Identify the valid neighbours (non-visited ones)
        List<Integer> neighbors = graph.getNeighbors(currentNode);
        List<Integer> validNeighbors = new ArrayList<>();
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                validNeighbors.add(neighbor);
            }
        }

        if (validNeighbors.isEmpty()) return;

        // 4. Thread distribution
        // If 1 or less threads -> continue sequentially
        if (threadBudget <= 1) {
            for (int neighbor : validNeighbors) {
                if (solutionFound.get()) return;
                
                visited[neighbor] = true;
                path.add(neighbor);
                search(neighbor, path, visited, 1);
                path.remove(path.size() - 1);
                visited[neighbor] = false;
            }
            return;
        }

        // Else we distribute the threads
        int branches = validNeighbors.size();
        int threadsPerBranch = threadBudget / branches;
        int remainder = threadBudget % branches;

        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < branches; i++) {
            int neighbor = validNeighbors.get(i);

            // Calculate the budget for this branch
            // (first 'remainder' branches get a bonus thread)
            int allocatedThreads = threadsPerBranch + (i < remainder ? 1 : 0);

            // Copy state for the new threads
            // Parallel backtracking needs separated memory for every split
            if (allocatedThreads > 0) {
                 // Copy path anad visited arrays
                 List<Integer> newPath = new ArrayList<>(path);
                 newPath.add(neighbor);
                 boolean[] newVisited = visited.clone();
                 newVisited[neighbor] = true;

                 // If we assigned > 1 thread, launch new thread
                 // If we assigned 1 thread, run the last branch on the current thread
                 // and for the N-1 branches we launch other threads
                 
                 if (i == branches - 1) {
                     search(neighbor, newPath, newVisited, allocatedThreads);
                 } else {
                     Thread t = new Thread(() -> {
                         try {
                             search(neighbor, newPath, newVisited, allocatedThreads);
                         } catch (InterruptedException e) { }
                     });
                     threads.add(t);
                     t.start();
                 }
            }
        }

        // Wait threads to finish (join)
        for (Thread t : threads) {
            t.join();
        }
    }
}
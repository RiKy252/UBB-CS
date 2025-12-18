import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.atomic.AtomicReference;

public class HamiltonianForkJoin {
    private Graph graph;
    // AtomicReference -> store the final result visible between tasks
    private static AtomicReference<List<Integer>> globalResult = new AtomicReference<>(null);
    private static final int FORK_THRESHOLD = 100; // Only fork when many nodes remain

    public HamiltonianForkJoin(Graph graph) {
        this.graph = graph;
    }

    public void solve(int startNode) {
        globalResult.set(null);
        ForkJoinPool pool = new ForkJoinPool();
        
        List<Integer> path = new ArrayList<>();
        path.add(startNode);
        boolean[] visited = new boolean[graph.getNumVertices()];
        visited[startNode] = true;

        HamiltonianTask task = new HamiltonianTask(startNode, path, visited);
        pool.invoke(task);

        List<Integer> res = globalResult.get();
        if (res != null) {
            System.out.println("ForkJoin Solution: " + res);
        } else {
            System.out.println("ForkJoin: No Hamiltonian cycle.");
        }
    }

    private class HamiltonianTask extends RecursiveTask<List<Integer>> {
        private int currentNode;
        private List<Integer> path;
        private boolean[] visited;
        private int remainingNodes;

        public HamiltonianTask(int currentNode, List<Integer> path, boolean[] visited) {
            this.currentNode = currentNode;
            this.path = path;
            this.visited = visited;
            this.remainingNodes = graph.getNumVertices() - path.size();
        }

        @Override
        protected List<Integer> compute() {
            return searchRecursive(currentNode, path, visited);
        }

        private List<Integer> searchRecursive(int node, List<Integer> currentPath, boolean[] currentVisited) {
            // 1. Check Global Stop (early exit)
            if (globalResult.get() != null) return null;

            // 2. Check Solution
            if (currentPath.size() == graph.getNumVertices()) {
                if (graph.getNeighbors(node).contains(currentPath.get(0))) {
                    // Found solution, atomic save
                    globalResult.compareAndSet(null, new ArrayList<>(currentPath));
                    return currentPath;
                }
                return null;
            }

            // 3. Find valid neighbors
            List<Integer> neighbors = graph.getNeighbors(node);
            List<Integer> validNeighbors = new ArrayList<>();
            
            for (int neighbor : neighbors) {
                if (!currentVisited[neighbor]) {
                    validNeighbors.add(neighbor);
                }
            }

            if (validNeighbors.isEmpty()) return null;

            int remaining = graph.getNumVertices() - currentPath.size();

            // 4. Decide: fork or stay sequential
            // Only fork at the top of the tree (when many nodes remain)
            if (remaining > FORK_THRESHOLD && validNeighbors.size() > 1) {
                // Fork only the first few branches, keep rest sequential
                List<HamiltonianTask> subTasks = new ArrayList<>();
                
                for (int neighbor : validNeighbors) {
                    List<Integer> newPath = new ArrayList<>(currentPath);
                    newPath.add(neighbor);
                    boolean[] newVisited = currentVisited.clone();
                    newVisited[neighbor] = true;
                    
                    subTasks.add(new HamiltonianTask(neighbor, newPath, newVisited));
                }
                
                // Fork first n-1, compute last one inline
                for (int i = 0; i < subTasks.size() - 1; i++) {
                    subTasks.get(i).fork();
                }
                
                List<Integer> result = subTasks.get(subTasks.size() - 1).compute();
                if (result != null) return result;
                
                // Join forked tasks
                for (int i = 0; i < subTasks.size() - 1; i++) {
                    if (globalResult.get() != null) return null;
                    List<Integer> res = subTasks.get(i).join();
                    if (res != null) return res;
                }
                
                return null;
            }

            // 5. Sequential execution - reuse state (no copying!)
            for (int neighbor : validNeighbors) {
                if (globalResult.get() != null) return null;
                
                currentVisited[neighbor] = true;
                currentPath.add(neighbor);
                
                List<Integer> res = searchRecursive(neighbor, currentPath, currentVisited);
                
                currentPath.remove(currentPath.size() - 1);
                currentVisited[neighbor] = false;
                
                if (res != null) return res;
            }
            
            return null;
        }
    }
}
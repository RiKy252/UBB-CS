public class Main {
    public static void main(String[] args) {
        int nodes = 500; 
        int startNode = 0; 
        int threads = Runtime.getRuntime().availableProcessors();
        
        // Generate a graph
        Graph graph = Graph.generateRandomGraph(nodes, 10);

        System.out.println("Starting tests...\n");

        // Classic test
        HamiltonianClassic solverClassic = new HamiltonianClassic(graph);
        long start = System.currentTimeMillis();
        solverClassic.solve(startNode, threads);
        long end = System.currentTimeMillis();
        System.out.println("Time for Classic: " + (end - start) + " ms\n");

        // ForkJoin test
        HamiltonianForkJoin solverFJ = new HamiltonianForkJoin(graph);
        start = System.currentTimeMillis();
        solverFJ.solve(startNode);
        end = System.currentTimeMillis();
        System.out.println("Time for ForkJoin: " + (end - start) + " ms");
    }
}

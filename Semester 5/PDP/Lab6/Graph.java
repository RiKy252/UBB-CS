import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Graph {
    private int numVertices;
    private List<List<Integer>> adjList;

    public Graph(int numVertices) {
        this.numVertices = numVertices;
        this.adjList = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; i++) {
            this.adjList.add(new ArrayList<>());
        }
    }

    public void addEdge(int src, int dest) {
        adjList.get(src).add(dest);
    }

    public List<Integer> getNeighbors(int vertex) {
        return adjList.get(vertex);
    }

    public int getNumVertices() {
        return numVertices;
    }

    // Generate a random graph with the option to determine the density (with the edgeChancePercent parameter)
    public static Graph generateRandomGraph(int vertices, int edgeChancePercent) {
        Graph g = new Graph(vertices);
        Random rand = new Random();
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (i != j && rand.nextInt(100) < edgeChancePercent) {
                    g.addEdge(i, j);
                }
            }
        }
        return g;
    }
}
import java.util.ArrayList;
import java.util.List;

public class MatrixMultiplier {

    private final Matrix A, B, C;

    public MatrixMultiplier(Matrix a, Matrix b, Matrix c) {
        this.A = a;
        this.B = b;
        this.C = c;
    }

    // Computes C[row][col] and access to threadId
    public void computeElement(int row, int col, int threadId) {
        double sum = 0;
        // A.cols == B.rows
        for (int k = 0; k < A.cols; k++) {
            sum += A.data[row][k] * B.data[k][col];
        }
        C.data[row][col] = sum;

        // Debug print (really slow if turned on)
        if (MatrixWorker.DEBUG_PRINT) {
            System.out.printf("Thread %d computing C[%d][%d]\n", threadId, row, col);
        }
    }

    // Launch and manage threads, returning execution time (in ms)
    public long multiply(int numThreads, int strategy) {
        C.reset(); // we make sure its reset already
        List<Thread> threads = new ArrayList<>();
        
        long startTime = System.nanoTime();

        // Create and start threads
        for (int i = 0; i < numThreads; i++) {
            MatrixWorker worker = new MatrixWorker(A, B, C, i, numThreads, strategy, this);
            Thread t = new Thread(worker);
            threads.add(t);
            t.start();
        }

        // Wait (join threads)
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000; // convert to ms
    }


    // Link everything to run the app
    public static void main(String[] args) {
        // Matrix sizes
        int[] sizes = {100, 500, 2500}; 
        // No. of threads
        int[] threadCounts = {4, 8, 16}; 

        System.out.printf("%-10s | %-6s | %-8s | %-8s\n", "Strategy", "Size", "Threads", "Time (ms)");
        System.out.println("---------------------------------------------------------------------");

        for (int size : sizes) {
            Matrix A = new Matrix(size, size);
            Matrix B = new Matrix(size, size);
            Matrix C = new Matrix(size, size);
            A.fillRandom();
            B.fillRandom();

            MatrixMultiplier multiplier = new MatrixMultiplier(A, B, C);

            for (int strategy = 1; strategy <= 3; strategy++) {
                for (int threads : threadCounts) {
                    long time = multiplier.multiply(threads, strategy);
                    System.out.printf("%-10d | %-6d | %-8d | %-8d\n", strategy, size, threads, time);
                }
                System.out.println("---------------------------------------------------------------------");
            }
        }
    }
}
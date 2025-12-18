public class MatrixWorker implements Runnable {

    private final Matrix A, B, C;
    private final int threadId;
    private final int numThreads;
    private final int strategy;
    private final MatrixMultiplier multiplier;

    public static final boolean DEBUG_PRINT = false;

    public MatrixWorker(Matrix A, Matrix B, Matrix C, int threadId, int numThreads, int strategy, MatrixMultiplier multiplier) {
        this.A = A;
        this.B = B;
        this.C = C;
        this.threadId = threadId;
        this.numThreads = numThreads;
        this.strategy = strategy;
        this.multiplier = multiplier;
    }

    @Override
    public void run() {
        switch (strategy) {
            case 1:
                runStrategy1();
                break;
            case 2:
                runStrategy2();
                break;
            case 3:
                runStrategy3();
                break;
        }
    }

    // Strategy 1: split by row (every thread will take a continuous block of elements)
    private void runStrategy1() {
        int totalElements = C.rows * C.cols;
        int elementsPerThread = totalElements / numThreads;

        // Calculate start and end index like in the example
        int startElement = threadId * elementsPerThread;
        int endElement = (threadId == numThreads - 1)
                ? totalElements // last thread takes everything left
                : (threadId + 1) * elementsPerThread;

        for (int index = startElement; index < endElement; index++) {
            // Convert index (ex: 42) in (row, col)
            int row = index / C.cols;
            int col = index % C.cols;
            multiplier.computeElement(row, col, threadId);
        }
    }

    // Strategy 2: split by column (similar to strategy 1 but we parse by columns)
    private void runStrategy2() {
        int totalElements = C.rows * C.cols;
        int elementsPerThread = totalElements / numThreads;

        int startElement = threadId * elementsPerThread;
        int endElement = (threadId == numThreads - 1)
                ? totalElements
                : (threadId + 1) * elementsPerThread;

        for (int index = startElement; index < endElement; index++) {
            // Reverse the logic
            int col = index / C.rows;
            int row = index % C.rows;
            multiplier.computeElement(row, col, threadId);
        }
    }

    // Strategy 3: each thread takes the k-th element (k = numThreads)
    private void runStrategy3() {
        int totalElements = C.rows * C.cols;

        // Thread 0 takes 0, k, 2k, ...
        // Thread 1 takes 1, k+1, 2k+1, ...
        for (int index = threadId; index < totalElements; index += numThreads) {
            // Convert index (ex: 42) in (row, col)
            int row = index / C.cols;
            int col = index % C.cols;
            multiplier.computeElement(row, col, threadId);
        }
    }
}
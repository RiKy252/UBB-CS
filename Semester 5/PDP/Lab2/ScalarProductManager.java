import java.util.Random;

public class ScalarProductManager {
    private static final int VECTOR_SIZE = 2000000;
    private static final int QUEUE_SIZE = 100; 

    public static void main(String[] args) {
        System.out.printf("Vector Size: %d\nQueue Size: %d\n", VECTOR_SIZE, QUEUE_SIZE);

        // initialise
        double[] v1 = new double[VECTOR_SIZE];
        double[] v2 = new double[VECTOR_SIZE];
        Random rand = new Random();
        for (int i = 0; i < VECTOR_SIZE; i++) {
            v1[i] = rand.nextDouble() * 10;
            v2[i] = rand.nextDouble() * 10;
        }

        ProductQueue queue = new ProductQueue(QUEUE_SIZE);
        ProducerTask producerTask = new ProducerTask(v1, v2, queue);
        ConsumerTask consumerTask = new ConsumerTask(queue);

        Thread producerThread = new Thread(producerTask);
        Thread consumerThread = new Thread(consumerTask);

        // start timer
        long startTime = System.nanoTime();

        producerThread.start();
        consumerThread.start();

        // join threads
        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // results
        long endTime = System.nanoTime();
        long durationMs = (endTime - startTime) / 1000000;

        double finalSum = consumerTask.getFinalSum();
        System.out.println("Simulation Finished");
        System.out.printf("Total Execution Time: %d ms\n", durationMs);
        System.out.printf("Calculated Scalar Product: %f\n", finalSum);
    }
}
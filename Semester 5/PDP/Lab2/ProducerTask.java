
public class ProducerTask implements Runnable {
    private final double[] v1;
    private final double[] v2;
    private final ProductQueue queue;

    public ProducerTask(double[] v1, double[] v2, ProductQueue queue) {
        this.v1 = v1;
        this.v2 = v2;
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < v1.length; i++) {
                double product = v1[i] * v2[i];
                // add product in queue
                queue.put(product);
                
                // debug message
                if (i % (v1.length / 10) == 0) {
                    System.out.printf("[Producer] Produced element %d/%d\n", i, v1.length);
                }
            }
            System.out.println("[Producer] FINISHED production.");
            queue.finishProduction();
        } catch (InterruptedException e) {
            System.err.println("Producer was interrupted.");
            Thread.currentThread().interrupt();
        }
    }
}

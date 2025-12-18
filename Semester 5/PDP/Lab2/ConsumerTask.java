// adds the queue products 
public class ConsumerTask implements Runnable {
    private final ProductQueue queue;
    private double finalSum = 0;

    public ConsumerTask(ProductQueue queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            int count = 0;
            while (true) {
                Double product = queue.take();
                if (product == null) {
                    break;
                }

                finalSum += product;
                count++;
                
                // debug msg
                if (count % (1000000) == 0) {
                   System.out.printf("[Consumer] Consumed element %d\n", count);
                }
            }
            System.out.printf("[Consumer] Finished consumption. Total elements: %d\n", count);

        } catch (InterruptedException e) {
            System.err.println("Consumer was interrupted.");
            Thread.currentThread().interrupt();
        }
    }

    public double getFinalSum() {
        return finalSum;
    }
}
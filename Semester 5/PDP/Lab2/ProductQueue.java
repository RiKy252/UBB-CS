import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProductQueue {
    // mutex for the queue
    private final Lock lock = new ReentrantLock();

    // cond variables
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    // queue
    private final Queue<Double> queue;
    private final int maxSize;

    // flag to notify the consumer that the producer done it's job
    private boolean productionFinished = false;

    public ProductQueue(int maxSize) {
        this.maxSize = maxSize;
        this.queue = new LinkedList<>();
    }

    // add a product in the q, if the q is full, then it will wait until its not full anymore
    public void put(double product) throws InterruptedException {
        lock.lock();
        try {
            while (queue.size() == maxSize) {
                //System.out.println("[Producer] Queue is full. Waiting...");
                notFull.await();
            }
            queue.add(product);

            // signal that the queue is not empty
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }
    
    // take a product from the queue, if q is empty then wait until production done or something will be in the q
    public Double take() throws InterruptedException {
        lock.lock();
        try {
            while (queue.isEmpty() && !productionFinished) {
                //System.out.println("[Consumer] Queue is empty. Waiting...");
                notEmpty.await();
            }
            if (queue.isEmpty() && productionFinished) {
                return null;
            }
            Double product = queue.poll();
            notFull.signal();
            return product;
        } finally {
            lock.unlock();
        }
    }

    public void finishProduction() {
        lock.lock();
        try {
            productionFinished = true;
            notEmpty.signalAll();
        } finally {
            lock.unlock();
        }
    }
}

import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Inventory {
    private final int[][] quantities;
    private final Lock[][] locks;
    private final int numWarehouses;
    private final int numProducts;
    private final int[] initialTotals;
    private volatile boolean running = true;
    private final ReentrantLock globalActivityLock = new ReentrantLock();

    public Inventory(int numWarehouses, int numProducts, int initialStock) {
        this.numWarehouses = numWarehouses;
        this.numProducts = numProducts;
        this.quantities = new int[numWarehouses][numProducts];
        this.locks = new ReentrantLock[numWarehouses][numProducts];
        this.initialTotals = new int[numProducts];

        Random rand = new Random();

        for (int p = 0; p < numProducts; p++) {
            int productTotal = 0;
            for (int w = 0; w < numWarehouses; w++) {
                this.locks[w][p] = new ReentrantLock();
                this.quantities[w][p] = initialStock;
                productTotal += initialStock;
            }
            this.initialTotals[p] = productTotal;
        }
    }

    public Lock getGlobalActivityLock() {
        return globalActivityLock;
    }
    
    public void move(int productId, int amount, int fromWarehouse, int toWarehouse) {
        if (fromWarehouse == toWarehouse) return;

        int lock1Id = Math.min(fromWarehouse, toWarehouse);
        int lock2Id = Math.max(fromWarehouse, toWarehouse);

        Lock lock1 = locks[lock1Id][productId];
        Lock lock2 = locks[lock2Id][productId];

        lock1.lock();
        try {
            lock2.lock();
            try {
                if (quantities[fromWarehouse][productId] >= amount) {
                    quantities[fromWarehouse][productId] -= amount;
                    quantities[toWarehouse][productId] += amount;
                }
            } finally {
                lock2.unlock();
            }
        } finally {
            lock1.unlock();
        }
    }

    public void stopPeriodicChecks() {
        this.running = false;
    }

    public void runPeriodicChecks(int numChecks) {
        Random rand = new Random();
        for (int i = 0; i < numChecks; i++) {
            if (!running) break;

            int productId = rand.nextInt(numProducts);
            globalActivityLock.lock();
            try {
                System.out.printf("[Checker] All threads are stopped to check product %d...\n", productId);
                checkProductTotal(productId); 
                System.out.println("[Checker] Checking done, restarting threads");
            } finally {
                globalActivityLock.unlock();
            }

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }

    public void runFinalCheck() {
        System.out.println("--- Running Final Invariant Check ---");
        boolean allOk = true;
        for (int p = 0; p < numProducts; p++) {
            int currentTotal = 0;
            for (int w = 0; w < numWarehouses; w++) {
                currentTotal += quantities[w][p];
            }

            if (currentTotal != initialTotals[p]) {
                System.err.printf("[ERROR] Invariant violated for Product %d! Expected: %d, Found: %d\n",
                        p, initialTotals[p], currentTotal);
                allOk = false;
            }
        }

        if (allOk) {
            System.out.println("[SUCCESS] Final check passed. All invariants are maintained.");
        } else {
            System.err.println("[FAILURE] Final check failed. Invariants violated.");
        }
    }

    private void checkProductTotal(int productId) {
        for (int w = 0; w < numWarehouses; w++) {
            locks[w][productId].lock();
        }

        try {
            int currentTotal = 0;
            for (int w = 0; w < numWarehouses; w++) {
                currentTotal += quantities[w][productId];
            }

            if (currentTotal != initialTotals[productId]) {
                System.err.printf("[PERIODIC CHECK FAILED] Product %d! Expected: %d, Found: %d\n",
                        productId, initialTotals[productId], currentTotal);
            } else {
                 System.out.printf("[Check OK] Product %d, Total: %d\n", productId, currentTotal);
            }

        } finally {
            for (int w = numWarehouses - 1; w >= 0; w--) {
                locks[w][productId].unlock();
            }
        }
    }

    public int getNumWarehouses() { return numWarehouses; }
    public int getNumProducts() { return numProducts; }
}
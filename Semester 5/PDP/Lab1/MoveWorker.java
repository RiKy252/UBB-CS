import java.util.Random;
import java.util.concurrent.locks.Lock;

public class MoveWorker implements Runnable {

    private final Inventory inventory;
    private final int numOperations;
    private final int maxMoveAmount;
    private final Random rand;
    private final Lock globalLock;
    
    private static final int OPERATIONS_PER_PAUSE = 1000;
    private static final int PAUSE_DURATION_MS = 1;

    public MoveWorker(Inventory inventory, int numOperations, int maxMoveAmount) {
        this.inventory = inventory;
        this.numOperations = numOperations;
        this.maxMoveAmount = maxMoveAmount;
        this.rand = new Random();
        this.globalLock = inventory.getGlobalActivityLock();
    }

    @Override
    public void run() {
        int numWarehouses = inventory.getNumWarehouses();
        int numProducts = inventory.getNumProducts();
        String threadName = Thread.currentThread().getName();

        for (int i = 0; i < numOperations; i++) {
            int productId = rand.nextInt(numProducts);
            
            int fromWarehouse = rand.nextInt(numWarehouses);
            int toWarehouse = rand.nextInt(numWarehouses);
            while (fromWarehouse == toWarehouse) {
                toWarehouse = rand.nextInt(numWarehouses);
            }

            int amount = rand.nextInt(maxMoveAmount - 1) + 1;

            globalLock.lock();
            try {
                inventory.move(productId, amount, fromWarehouse, toWarehouse);
            } finally {
                globalLock.unlock();
            }
            System.out.printf("[%s] Op %d: Move P%d, %d items, W%d -> W%d\n",
                  threadName, i, productId, amount, fromWarehouse, toWarehouse);

            if (i > 0 && i % OPERATIONS_PER_PAUSE == 0) {
                try {
                    Thread.sleep(PAUSE_DURATION_MS);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }
    }
}
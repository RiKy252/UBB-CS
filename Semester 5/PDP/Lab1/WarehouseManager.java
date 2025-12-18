import java.util.ArrayList;
import java.util.List;

public class WarehouseManager {
    private static final int NUM_THREADS = 8;
    private static final int NUM_WAREHOUSES = 10;
    private static final int NUM_PRODUCTS = 100;
    private static final int INITIAL_STOCK_PER_ITEM = 1000;
    
    private static final int OPERATIONS_PER_THREAD = 1000;
    private static final int MAX_MOVE_AMOUNT = 50;
    
    private static final int NUM_PERIODIC_CHECKS = 20;

    public static void main(String[] args) {
        System.out.println("--- Warehouse Simulation ---");
        System.out.printf("Configuration: %d Threads, %d Warehouses, %d Products\n",
                NUM_THREADS, NUM_WAREHOUSES, NUM_PRODUCTS);
        System.out.printf("Operations: %d per thread (Total %d)\n",
                OPERATIONS_PER_THREAD, (long) NUM_THREADS * OPERATIONS_PER_THREAD);

        Inventory inventory = new Inventory(NUM_WAREHOUSES, NUM_PRODUCTS, INITIAL_STOCK_PER_ITEM);
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < NUM_THREADS; i++) {
            MoveWorker worker = new MoveWorker(inventory, OPERATIONS_PER_THREAD, MAX_MOVE_AMOUNT);
            threads.add(new Thread(worker));
        }

        Thread checkerThread = new Thread(() -> inventory.runPeriodicChecks(NUM_PERIODIC_CHECKS));
        
        checkerThread.start();
        for (Thread t : threads) {
            t.start();
        }

        try {
            for (Thread t : threads) {
                t.join();
            }
            
            inventory.stopPeriodicChecks();
            checkerThread.join();
            
        } catch (InterruptedException e) {
            System.err.println("Simulation was interrupted.");
            Thread.currentThread().interrupt();
        }

        System.out.println("--- Simulation Finished ---");

        inventory.runFinalCheck();
    }
}
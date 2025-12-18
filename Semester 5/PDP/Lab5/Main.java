import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;

public class Main {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        // Config
        int degree = 10000;
        int threads = 8;
        
        System.out.println("Generating polynomials degree=" + degree + "...");
        Polynomial p1 = new Polynomial(degree);
        Polynomial p2 = new Polynomial(degree);
        p1.fillRandom();
        p2.fillRandom();

        System.out.println("Starting tests...\n");

        // 1. Simple Sequential
        long start = System.currentTimeMillis();
        Polynomial res1 = SimpleMultiplication.sequential(p1, p2);
        long end = System.currentTimeMillis();
        System.out.println("Simple Sequential: " + (end - start) + " ms");

        // 2. Simple Parallel
        start = System.currentTimeMillis();
        Polynomial res2 = SimpleMultiplication.parallel(p1, p2, threads);
        end = System.currentTimeMillis();
        System.out.println("Simple Parallel:   " + (end - start) + " ms");

        // 3. Karatsuba Sequential
        start = System.currentTimeMillis();
        Polynomial res3 = KaratsubaMultiplication.sequential(p1, p2);
        end = System.currentTimeMillis();
        System.out.println("Karatsuba Sequential: " + (end - start) + " ms");

        // 4. Karatsuba Parallel (with ForkJoinPool)
        start = System.currentTimeMillis();
        ForkJoinPool pool = new ForkJoinPool(threads);
        Polynomial res4 = pool.submit(() -> KaratsubaMultiplication.parallel(p1, p2, 0)).get();
        pool.shutdown();
        end = System.currentTimeMillis();
        System.out.println("Karatsuba Parallel:   " + (end - start) + " ms");
        
        System.out.println("\nVerification:");
        System.out.println("Res1 degree: " + res1.getDegree());
        System.out.println("Res2 degree: " + res2.getDegree());
        System.out.println("Res3 degree: " + res3.getDegree());
        System.out.println("Res4 degree: " + res4.getDegree());
    }
}

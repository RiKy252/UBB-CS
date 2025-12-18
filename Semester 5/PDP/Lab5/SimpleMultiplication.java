import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

// O(n^2)
public class SimpleMultiplication {

    // Sequential => p1 * p2 (each term)
    public static Polynomial sequential(Polynomial p1, Polynomial p2) {
        int size = p1.getDegree() + p2.getDegree();
        Polynomial result = new Polynomial(size);

        for (int i = 0; i <= p1.getDegree(); i++) {
            for (int j = 0; j <= p2.getDegree(); j++) {
                int current = result.getCoefficient(i + j);
                result.setCoefficient(i + j, current + p1.getCoefficient(i) * p2.getCoefficient(j));
            }
        }
        return result;
    }

    // Parallel
    // Split degrees between threads ex: t1 from 0-100, t2 from 101-200 
    public static Polynomial parallel(Polynomial p1, Polynomial p2, int nrThreads) throws InterruptedException {
        int resultDegree = p1.getDegree() + p2.getDegree();
        Polynomial result = new Polynomial(resultDegree);

        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(nrThreads);

        // Every thread calculates a range of coefficients of the result
        int step = (resultDegree + 1) / nrThreads;
        if (step == 0) step = 1;

        for (int i = 0; i < resultDegree + 1; i += step) {
            int start = i;
            int end = Math.min(i + step, resultDegree + 1);
            
            executor.execute(() -> {
                for (int k = start; k < end; k++) {
                    // Calculate coefficient k of the result: Result[k] = Sum(P1[x] * P2[y]), where x + y = k
                    int coeff = 0;
                    for (int x = 0; x <= k; x++) {
                        int y = k - x;
                        if (x <= p1.getDegree() && y <= p2.getDegree()) {
                            coeff += p1.getCoefficient(x) * p2.getCoefficient(y);
                        }
                    }
                    result.setCoefficient(k, coeff);
                }
            });
        }

        executor.shutdown();
        executor.awaitTermination(60, TimeUnit.SECONDS);
        return result;
    }
}
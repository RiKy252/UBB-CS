import java.util.concurrent.RecursiveTask;

public class KaratsubaMultiplication {

    private static final int THRESHOLD = 64;

    // Sequential
    public static Polynomial sequential(Polynomial p1, Polynomial p2) {
        if (p1.getDegree() < THRESHOLD || p2.getDegree() < THRESHOLD) {
            return SimpleMultiplication.sequential(p1, p2);
        }

        int len = Math.max(p1.getDegree(), p2.getDegree()) + 1;
        int halfLen = len / 2;

        Polynomial[] parts1 = Polynomial.split(p1, halfLen); // Low, High
        Polynomial[] parts2 = Polynomial.split(p2, halfLen);

        Polynomial low1 = parts1[0];
        Polynomial high1 = parts1[1];
        Polynomial low2 = parts2[0];
        Polynomial high2 = parts2[1];

        Polynomial sum1 = Polynomial.add(low1, high1);
        Polynomial sum2 = Polynomial.add(low2, high2);

        Polynomial z0 = sequential(low1, low2);
        Polynomial z2 = sequential(high1, high2);
        Polynomial z1 = sequential(sum1, sum2);

        Polynomial r1 = Polynomial.subtract(Polynomial.subtract(z1, z2), z0);

        Polynomial result = Polynomial.add(z0, Polynomial.shift(r1, halfLen));
        result = Polynomial.add(result, Polynomial.shift(z2, 2 * halfLen));

        return result;
    }

    // Parallel
    public static Polynomial parallel(Polynomial p1, Polynomial p2, int currentDepth) {
        if (currentDepth > 4 || p1.getDegree() < THRESHOLD || p2.getDegree() < THRESHOLD) {
            return sequential(p1, p2);
        }

        int len = Math.max(p1.getDegree(), p2.getDegree()) + 1;
        int halfLen = len / 2;

        Polynomial[] parts1 = Polynomial.split(p1, halfLen);
        Polynomial[] parts2 = Polynomial.split(p2, halfLen);

        Polynomial sum1 = Polynomial.add(parts1[0], parts1[1]);
        Polynomial sum2 = Polynomial.add(parts2[0], parts2[1]);

        RecursiveTask<Polynomial> taskZ0 = new RecursiveTask<>() {
            @Override
            protected Polynomial compute() {
                return parallel(parts1[0], parts2[0], currentDepth + 1);
            }
        };
        RecursiveTask<Polynomial> taskZ2 = new RecursiveTask<>() {
            @Override
            protected Polynomial compute() {
                return parallel(parts1[1], parts2[1], currentDepth + 1);
            }
        };

        taskZ0.fork();
        taskZ2.fork();

        // Compute Z1 directly to reduce task overhead
        Polynomial z1 = parallel(sum1, sum2, currentDepth + 1);
        Polynomial z0 = taskZ0.join();
        Polynomial z2 = taskZ2.join();

        Polynomial r1 = Polynomial.subtract(Polynomial.subtract(z1, z2), z0);

        Polynomial result = Polynomial.add(z0, Polynomial.shift(r1, halfLen));
        result = Polynomial.add(result, Polynomial.shift(z2, 2 * halfLen));

        return result;
    }
}
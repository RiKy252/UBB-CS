import java.util.Random;

// a0 + a1 * x + a2 * x^2 + ... + an-1 * x^(n-1) + an * x^n
public class Polynomial {
    private int[] coefficients; // ex: 2x^2 + 5x + 3 => [3, 5 ,2]
    private int degree;

    public Polynomial(int degree) {
        this.degree = degree;
        this.coefficients = new int[degree + 1];
    }

    public Polynomial(int[] coefficients) {
        this.coefficients = coefficients;
        this.degree = coefficients.length - 1;
    }

    public int getLength() {
        return coefficients.length;
    }

    public int getDegree() {
        return degree;
    }

    public int[] getCoefficients() {
        return coefficients;
    }

    public void setCoefficient(int index, int value) {
        coefficients[index] = value;
    }

    public int getCoefficient(int index) {
        if (index < 0 || index > degree) {
            return 0;
        }
        return coefficients[index];
    }

    // Generate a polynomial with random coefficients
    public void fillRandom() {
        Random r = new Random();
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = r.nextInt(10); // small coef to avoid fast overflow
        }
    }

    // Helper for pretty printing
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = degree; i >= 0; i--) {
            if (coefficients[i] == 0) continue;
            sb.append(coefficients[i]).append("x^").append(i).append(" + ");
        }
        return sb.length() > 0 ? sb.substring(0, sb.length() - 3) : "0";
    }

    // Add for Karatsuba
    public static Polynomial add(Polynomial p1, Polynomial p2) {
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        Polynomial result = new Polynomial(maxDegree);
        for (int i = 0; i <= maxDegree; i++) {
            result.setCoefficient(i, p1.getCoefficient(i) + p2.getCoefficient(i));
        }
        return result;
    }

    // Substraction for Karatsuba
    public static Polynomial subtract(Polynomial p1, Polynomial p2) {
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        Polynomial result = new Polynomial(maxDegree);
        for (int i = 0; i <= maxDegree; i++) {
            result.setCoefficient(i, p1.getCoefficient(i) - p2.getCoefficient(i));
        }
        return result;
    }

    // Shift
    public static Polynomial shift(Polynomial p, int offset) {
        Polynomial result = new Polynomial(p.getDegree() + offset);
        for (int i = 0; i <= p.getDegree(); i++) {
            result.setCoefficient(i + offset, p.getCoefficient(i));
        }
        return result;
    }

    // Split
    public static Polynomial[] split(Polynomial p, int splitIndex) {
        Polynomial low = new Polynomial(splitIndex - 1);
        Polynomial high = new Polynomial(p.getDegree() - splitIndex);

        for (int i = 0; i < splitIndex; i++) {
            if (i <= p.getDegree()) low.setCoefficient(i, p.getCoefficient(i));
        }
        for (int i = splitIndex; i <= p.getDegree(); i++) {
            high.setCoefficient(i - splitIndex, p.getCoefficient(i));
        }
        return new Polynomial[]{low, high};
    }
}
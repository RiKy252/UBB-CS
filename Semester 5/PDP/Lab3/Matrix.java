import java.util.Random;

public class Matrix {
    public final int rows;
    public final int cols;
    public final double[][] data;

    public Matrix(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.data = new double[rows][cols];
    }

    // Random values on the matrix
    public void fillRandom() {
        Random rand = new Random(42);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = rand.nextDouble();
            }
        }
    }

    // Clean up the matrix with values of zero (used for C)
    public void reset() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
}
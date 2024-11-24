package Model.ADTs;

public interface MyIStack<T> {
    T pop();
    void push(T val);
    boolean isEmpty();
    String toString();
}

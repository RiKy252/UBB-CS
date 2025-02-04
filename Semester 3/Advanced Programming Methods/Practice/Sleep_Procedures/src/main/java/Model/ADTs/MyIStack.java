package Model.ADTs;

import java.util.List;

public interface MyIStack<T> {
    T pop();
    void push(T val);
    boolean isEmpty();
    String toString();
    List<T> toList();
    MyIStack<T> copy();
    T peek();
}

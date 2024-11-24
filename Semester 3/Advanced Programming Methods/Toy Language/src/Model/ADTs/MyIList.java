package Model.ADTs;

public interface MyIList<T> {
    void add(T val);
    T get(int index);
    int size();
    String toString();
}

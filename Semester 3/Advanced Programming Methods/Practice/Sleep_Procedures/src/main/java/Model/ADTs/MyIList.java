package Model.ADTs;

import java.util.List;

public interface MyIList<T> {
    void add(T val);
    T get(int index);
    int size();
    List<T> getOutAsList();
    String toString();
}

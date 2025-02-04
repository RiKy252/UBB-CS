package Model.ADTs;

import java.util.Map;

public interface ILatchTable {
    void put(int key, int value);
    int get(int key);
    boolean contains(int key);
    void remove(int key);
    Integer allocate(Integer val);
    String toString();
    Map<Integer, Integer> getLatchTable();
}

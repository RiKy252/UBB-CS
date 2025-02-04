package Model.ADTs;

import java.util.Map;

public interface ILockTable {
    void put(int key, int value);
    int allocate(Integer value);
    int get(int key);
    boolean contains(int key);
    void remove(int key);
    Map<Integer, Integer> getLockTable();
    String toString();
}

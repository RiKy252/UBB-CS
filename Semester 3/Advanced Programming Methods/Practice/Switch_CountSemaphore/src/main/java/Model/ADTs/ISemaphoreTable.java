package Model.ADTs;

import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface ISemaphoreTable {
    int allocate(Pair<Integer, List<Integer>> value);
    void put(Integer address, Pair<Integer, List<Integer>> value);
    Pair<Integer, List<Integer>> get(Integer address);
    boolean containsKey(Integer address);
    void remove(Integer address);
    String toString();
    Map<Integer, Pair<Integer, List<Integer>>> getSemaphoreTable();
}

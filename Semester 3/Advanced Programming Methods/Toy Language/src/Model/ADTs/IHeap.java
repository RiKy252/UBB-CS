package Model.ADTs;

import Model.Expressions.Exp;
import Model.Values.Value;
import MyException.MyException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public interface IHeap<TKey, TValue> {
    Integer allocate(Value val);
    void deallocate(Integer address) throws MyException;
    Value read(Integer address) throws MyException;
    void write(int address, Value val) throws MyException;
    String toString();
    boolean isDefined(Integer address);
    Map<Integer, Value> safeGarbageCollector(List<Integer> addresses, Map<Integer, Value> heap);
    void setHeap(Map<Integer, Value> heap);
    Map<Integer, Value> getHeap();
}

package Model.ADTs;

import Model.Expressions.Exp;
import Model.Values.Value;
import MyException.MyException;

public interface IHeap<TKey, TValue> {
    Integer allocate(Value val);
    void deallocate(Integer address) throws MyException;
    Value read(Integer address) throws MyException;
    void write(int address, Value val) throws MyException;
    String toString();
    boolean isDefined(Integer address);
}

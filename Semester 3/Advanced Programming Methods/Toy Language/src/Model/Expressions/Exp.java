package Model.Expressions;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Values.Value;
import MyException.*;

public interface Exp {
    Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap)  throws MyException;
    String toString();
    Exp deepcopy();
}

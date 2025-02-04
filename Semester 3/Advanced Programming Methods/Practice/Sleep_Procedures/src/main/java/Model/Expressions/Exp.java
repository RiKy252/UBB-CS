package Model.Expressions;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.Type;
import Model.Values.Value;
import MyException.*;

public interface Exp {
    Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap)  throws MyException;
    String toString();
    Exp deepcopy();
    Type typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException;
}

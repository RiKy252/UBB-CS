package Model.Expressions;

import Model.ADTs.MyIDictionary;
import Model.Values.Value;
import MyException.*;

public class ValueExp implements Exp {
    Value e;
    public ValueExp(Value e) {
        this.e = e;
    }
    @Override
    public Value eval(MyIDictionary<String, Value> table) {
        return e;
    }
    @Override
    public String toString() {
        return e.toString();
    }
    @Override
    public Exp deepcopy() {
        return new ValueExp(e.deepcopy());
    }
}

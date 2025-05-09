package Model.Expressions;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.Type;
import Model.Values.Value;
import MyException.*;

public class VarExp implements Exp {
    String id;
    public VarExp(String id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return id;
    }
    @Override
    public Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap) throws UndefinedVariableException {
        if (table.isDefined(id)) {
            return table.lookup(id);
        }
        else {
            throw new UndefinedVariableException("Variable " + id + " not defined");
        }
    }
    @Override
    public Exp deepcopy() {
        return new VarExp(new String(id));
    }
    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv.lookup(id);
    }
}

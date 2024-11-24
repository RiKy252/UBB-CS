package Model.Expressions;

import Model.ADTs.MyIDictionary;
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
    public Value eval(MyIDictionary<String, Value> table) throws UndefinedVariableException {
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
}

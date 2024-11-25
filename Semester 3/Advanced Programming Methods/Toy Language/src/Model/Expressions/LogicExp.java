package Model.Expressions;

import Model.ADTs.IHeap;
import Model.Types.BoolType;
import Model.ADTs.MyIDictionary;
import Model.Values.BoolValue;
import Model.Values.Value;
import MyException.*;

public class LogicExp implements Exp {
    Exp e1;
    Exp e2;
    int op; // 1 - &, 2 - |
    public LogicExp(Exp e1, Exp e2, int op) {
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }
    public String toString() {
        if (op == 1)
            return e1.toString() + " and " + e2.toString();
        if (op == 2)
            return e1.toString() + " or " + e2.toString();
        return null;
    }
    public Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap) throws IncompatibleTypeException {
        Value v1, v2;
        v1 = e1.eval(table, heap);
        if (v1.getType().equals(new BoolType())) {
            v2 = e2.eval(table, heap);
            if (v2.getType().equals(new BoolType())) {
                BoolValue b1 = (BoolValue) v1;
                BoolValue b2 = (BoolValue) v2;
                boolean r1, r2;
                r1 = b1.getVal();
                r2 = b2.getVal();
                if (op == 1) return new BoolValue(r1 && r2);
                if (op == 2) return new BoolValue(r1 || r2);
                else
                    throw new IncompatibleTypeException("Operation value not valid");
            }
            else {
                throw new IncompatibleTypeException("The second operand is not a logical one");
            }
        }
        else {
            throw new IncompatibleTypeException("The first operand is not a logical one");
        }
    }
    @Override
    public Exp deepcopy() {
        return new LogicExp(e1.deepcopy(), e2.deepcopy(), op);
    }
}

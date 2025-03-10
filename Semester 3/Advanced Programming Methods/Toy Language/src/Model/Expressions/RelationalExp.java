package Model.Expressions;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.IncompatibleTypeException;
import MyException.MyException;

public class RelationalExp implements Exp {
    Exp e1, e2;
    String op;
    public RelationalExp(Exp e1, Exp e2, String op) {
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }
    @Override
    public String toString() {
        return e1 + " " + op + " " + e2;
    }
    @Override
    public Exp deepcopy() {
        return new RelationalExp(e1.deepcopy(), e2.deepcopy(), op);
    }
    @Override
    public Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap) throws IncompatibleTypeException {
        Value v1, v2;
        v1 = e1.eval(table, heap);
        if (v1.getType().equals(new IntType())) {
            v2 = e2.eval(table, heap);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1, n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                return switch (op) {
                    case "<" -> new BoolValue(n1 < n2);
                    case "<=" -> new BoolValue(n1 <= n2);
                    case ">=" -> new BoolValue(n1 >= n2);
                    case ">" -> new BoolValue(n1 > n2);
                    case "==" -> new BoolValue(n1 == n2);
                    case "!=" -> new BoolValue(n1 != n2);
                    default -> throw new IncompatibleTypeException("Invalid relational expression operator!");
                };
            } else {
                throw new IncompatibleTypeException("Second operand is not an integer");
            }
        } else {
            throw new IncompatibleTypeException("First operand is not an integer");
        }
    }
    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1 = e1.typeCheck(typeEnv);
        typ2 = e2.typeCheck(typeEnv);
        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new BoolType();
            }
            else {
                throw new MyException("Second operand is not an integer!");
            }
        }
        else {
            throw new MyException("First operand is not an integer!");
        }
    }
}

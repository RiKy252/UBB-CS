package Model.Expressions;

import Model.ADTs.IHeap;
import Model.Types.IntType;
import Model.ADTs.MyIDictionary;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.*;

public class ArithExp implements Exp{
    Exp e1;
    Exp e2;
    int op; // 1-plus, 2-minus, 3-multiplication, 4-divide
    public ArithExp(Exp e1, Exp e2, int op) {
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }
    @Override
    public String toString() {
        if (op == 1)
            return e1.toString() + " + " + e2.toString();
        if (op == 2)
            return e1.toString() + " - " + e2.toString();
        if (op == 3)
            return e1.toString() + " * " + e2.toString();
        if (op == 4)
            return e1.toString() + " / " + e2.toString();
        return null;
    }
    @Override
    public Value eval(MyIDictionary<String, Value> table, IHeap<Integer, Value> heap) throws DivisionByZeroException, IncompatibleTypeException {
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
                if (op == 1) return new IntValue(n1 + n2);
                else if (op == 2) return new IntValue(n1 - n2);
                else if (op == 3) return new IntValue(n1 * n2);
                else if (op == 4){
                    if (n2 == 0)
                        throw new DivisionByZeroException("Division by zero is not possible");
                    return new IntValue(n1 / n2);
                }
                else
                    throw new IncompatibleTypeException("Operation value not valid");
            }
            else {
                throw new IncompatibleTypeException("Second operand is not an integer");
            }
        }
        else {
            throw new IncompatibleTypeException("First operand is not an integer");
        }
    }
    @Override
    public Exp deepcopy() {
        return new ArithExp(e1.deepcopy(), e2.deepcopy(), op);
    }
    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1 = e1.typeCheck(typeEnv);
        typ2 = e2.typeCheck(typeEnv);
        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new IntType();
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

package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;
import MyException.MyException;

public class ConditionalStmt implements IStmt {
    Exp exp1, exp2, exp3;
    String id;
    public ConditionalStmt(String id, Exp exp1, Exp exp2, Exp exp3) {
        this.id = id;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
    }
    @Override
    public String toString() {
        return id + " = " + exp1.toString() + " ? " + exp2.toString() + " : " + exp3.toString();
    }
    @Override
    public IStmt deepcopy() {
        return new ConditionalStmt(new String(id), exp1.deepcopy(), exp2.deepcopy(), exp3.deepcopy());
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (!exp1.typeCheck(typeEnv).equals(new BoolType()))
            throw new MyException("Conditional Stmt: first expression is not of type bool");
        Type typeVar = typeEnv.lookup(id);
        Type typeExp2 = exp2.typeCheck(typeEnv);
        Type typeExp3 = exp3.typeCheck(typeEnv);
        if (typeVar.equals(typeExp2) && typeVar.equals(typeExp3))
            return typeEnv;
        else
            throw new MyException("Conditional Stmt: right hand side and left hand side have different types!");
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        Value cond = exp1.eval(symTbl, heap);
        Value val1 = exp2.eval(symTbl, heap);
        Value val2 = exp3.eval(symTbl, heap);
        if (cond.getType().equals(new BoolType())) {
            if (cond.equals(new BoolValue(true)))
                symTbl.update(id, val1);
            else
                symTbl.update(id, val2);
        }
        else
            throw new MyException("Conditional Stmt: first expression is not of type bool");
        return null;
    }
}

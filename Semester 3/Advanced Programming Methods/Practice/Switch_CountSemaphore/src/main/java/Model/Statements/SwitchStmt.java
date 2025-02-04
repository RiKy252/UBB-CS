package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.Value;
import MyException.MyException;

public class SwitchStmt implements IStmt {
    private Exp exp1, exp2, exp3;
    private IStmt stmt1, stmt2, stmt3;
    public SwitchStmt(Exp exp1, Exp exp2, Exp exp3, IStmt stmt1, IStmt stmt2, IStmt stmt3) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }
    @Override
    public String toString() {
        return "switch(" + exp1.toString() + ") case(" + exp2.toString() + "): " + stmt1.toString() + " case(" + exp3.toString() + "): " + stmt2.toString() + " default: " + stmt3.toString();
    }
    @Override
    public IStmt deepcopy() {
        return new SwitchStmt(exp1.deepcopy(), exp2.deepcopy(), exp3.deepcopy(), stmt1.deepcopy(), stmt2.deepcopy(), stmt3.deepcopy());
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) {
        Type type1 = exp1.typeCheck(typeEnv);
        Type type2 = exp2.typeCheck(typeEnv);
        Type type3 = exp3.typeCheck(typeEnv);
        if (!type1.equals(type2) || !type2.equals(type3)) {
            throw new MyException("Switch statement: different types");
        }
        stmt1.typeCheck(typeEnv.copy());
        stmt2.typeCheck(typeEnv.copy());
        stmt3.typeCheck(typeEnv.copy());
        return typeEnv;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        Value val1 = exp1.eval(symTbl, heap);
        Value val2 = exp2.eval(symTbl, heap);
        Value val3 = exp3.eval(symTbl, heap);
        if (val1.equals(val2))
            state.getStack().push(stmt1);
        else if (val1.equals(val3))
            state.getStack().push(stmt2);
        else
            state.getStack().push(stmt3);
        return null;
    }
}

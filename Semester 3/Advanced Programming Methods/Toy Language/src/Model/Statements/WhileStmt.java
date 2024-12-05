package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;
import MyException.MyException;

public class WhileStmt implements IStmt {
    Exp exp;
    IStmt stmt;
    public WhileStmt(Exp e, IStmt s) {
        exp = e;
        stmt = s;
    }
    @Override
    public IStmt deepcopy() {
        return new WhileStmt(exp.deepcopy(), stmt.deepcopy());
    }
    @Override
    public String toString() {
        return "while (" + exp + ") execute " + stmt;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        Value val = exp.eval(symTbl, heap);
        if (!(val.getType() instanceof BoolType))
            throw new MyException("While expression was not evaluated to BoolType!");
        if (((BoolValue) val).getVal()) {
            state.getStack().push(this);
            state.getStack().push(stmt);
        }
        return null;
    }
}

package Model.Statements;

import Model.ADTs.IHeap;
import Model.Expressions.Exp;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIList;
import Model.ADTs.MyIStack;
import Model.PrgState;
import Model.Values.Value;
import MyException.MyException;

public class PrintStmt implements IStmt {
    Exp exp;
    public PrintStmt(Exp exp) {
        this.exp = exp;
    }
    @Override
    public String toString() {
        return "print(" + exp.toString() + ")";
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStack();
        MyIDictionary<String, Value> sym = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        MyIList<Value> out = state.getOut();
        out.add(exp.eval(sym, heap));
        return state;
    }
    @Override
    public IStmt deepcopy() {
        return new PrintStmt(exp.deepcopy());
    }
}

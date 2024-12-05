package Model.Statements;

import Model.ADTs.MyStack;
import Model.PrgState;
import MyException.MyException;

public class ForkStmt implements IStmt {
    IStmt inner;
    public ForkStmt(IStmt inner) {
        this.inner = inner;
    }
    @Override
    public PrgState execute(PrgState program) throws MyException {
        PrgState newProgram = new PrgState(new MyStack<>(), program.getSymTable().copy(), program.getOut(), program.getFileTable(), program.getHeap(), inner);
        newProgram.getStack().push(inner);
        return newProgram;
    }
    @Override
    public String toString() {
        return "fork(" + inner.toString() + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new ForkStmt(inner.deepcopy());
    }
}
// TODO fork only executes the stmt inside, not from the parent thread too.
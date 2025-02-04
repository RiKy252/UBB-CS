package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.ADTs.MyStack;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Types.Type;
import MyException.MyException;

public class ForkStmt implements IStmt {
    IStmt inner;
    public ForkStmt(IStmt inner) {
        this.inner = inner;
    }
    @Override
    public PrgState execute(PrgState program) throws MyException {
        PrgState newProgram = new PrgState(new MyStack<>(), program.getSymTable().copy(), program.getOut(), program.getFileTable(), program.getHeap(), program.getLatchTable(), inner);
        // newProgram.getStack().push(inner); dont need because program state does automatically push on stack
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
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        inner.typeCheck(typeEnv.copy());
        return typeEnv;
    }
}

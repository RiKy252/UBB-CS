package Model.Statements;

import Model.PrgState;
import MyException.MyException;

public class NopStmt implements IStmt {
    public NopStmt() {}
    @Override
    public PrgState execute(PrgState state) throws MyException {
        return null;
    }
    @Override
    public String toString() {
        return "Nop";
    }
    @Override
    public IStmt deepcopy() {
        return new NopStmt();
    }
}

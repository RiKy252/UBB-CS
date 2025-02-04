package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.Type;
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
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }
}

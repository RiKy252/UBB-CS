package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.Type;
import MyException.MyException;

public class ReturnStmt implements IStmt {
    @Override
    public String toString() {
        return "return";
    }
    @Override
    public IStmt deepcopy() {
        return new ReturnStmt();
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Model.Types.Type> typeEnv) throws MyException {
        return typeEnv;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        state.getSymTableStack().pop();
        return null;
    }
}

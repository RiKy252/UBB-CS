package Model.Statements;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.Type;
import MyException.MyException;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    String toString();
    IStmt deepcopy();
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException;
}

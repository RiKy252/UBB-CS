package Model.Statements;
import Model.PrgState;
import MyException.MyException;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    String toString();
    IStmt deepcopy();
}

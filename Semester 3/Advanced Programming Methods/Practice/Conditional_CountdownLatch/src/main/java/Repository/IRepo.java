package Repository;

import Model.PrgState;
import Model.Statements.IStmt;
import MyException.MyException;

import java.util.List;

public interface IRepo {
    void addPrg(PrgState program);
    List<PrgState> getPrgList();
    void logPrgStateExec(PrgState program) throws MyException;
    void setPrgList(List<PrgState> newPrograms);
    List<IStmt> allExamples();
    void clear();
}

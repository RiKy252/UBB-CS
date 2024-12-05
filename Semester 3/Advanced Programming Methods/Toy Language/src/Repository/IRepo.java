package Repository;

import Model.PrgState;
import MyException.MyException;

import java.util.List;

public interface IRepo {
    void addPrg(PrgState program);
    List<PrgState> getPrgList();
    void logPrgStateExec(PrgState program) throws MyException;
    void setPrgList(List<PrgState> newPrograms);
}

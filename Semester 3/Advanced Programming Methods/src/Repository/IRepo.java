package Repository;

import Model.PrgState;
import MyException.MyException;

import java.util.ArrayList;

public interface IRepo {
    PrgState getCrtPrg();
    void addPrg(PrgState program);
    ArrayList<PrgState> getAll();
    void logPrgStateExec(PrgState program) throws MyException;
}

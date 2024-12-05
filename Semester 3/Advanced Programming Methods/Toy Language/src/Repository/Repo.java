package Repository;

import Model.PrgState;
import MyException.MyException;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repo implements IRepo {
    private List<PrgState> programs;
    private int index = 1;
    private String logFilePath;

    public Repo(PrgState program, String logFilePath) {
        this.programs = new ArrayList<>();
        this.programs.add(program);
        this.logFilePath = logFilePath;
    }

    @Override
    public void addPrg(PrgState program) {
        this.programs.add(program);
        index++;
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.programs;
    }

    @Override
    public void logPrgStateExec(PrgState program) throws MyException {
        if (this.logFilePath != null) {
            PrintWriter logFile = null;
            try {
                logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            } catch (IOException e) {
                throw new MyException("File writing error");
            }
            logFile.println(program.toString());
            logFile.close();
        }
    }
    @Override
    public void setPrgList(List<PrgState> newPrograms) {
        this.programs = newPrograms;
    }
}

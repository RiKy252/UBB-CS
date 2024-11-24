package Controller;

import Model.ADTs.MyIStack;
import Model.PrgState;
import Model.Statements.IStmt;
import MyException.*;
import Repository.IRepo;
import java.util.ArrayList;

public class Controller {
    private IRepo repository;
    private boolean displayFlag;
    int counter = 1;
    public Controller(IRepo repo) {
        this.repository = repo;
    }
    public PrgState oneStepExec(PrgState state) throws EmptyExecutionStackException {
        MyIStack<IStmt> stack = state.getStack();
        if (stack.isEmpty())
            throw new EmptyExecutionStackException("Program state stack is empty");
        IStmt currentStatement = stack.pop();
        return currentStatement.execute(state);
    }
    public void allStepsExec() {
        PrgState program = this.repository.getCrtPrg();
        if (counter > 1) {
            program.init();
        }
        counter++;
        try {
            repository.logPrgStateExec(program);
            while (!program.getStack().isEmpty()) {
                oneStepExec(program);
                if (displayFlag)
                    displayCurrentState(program);
                repository.logPrgStateExec(program);
            }
            if (!displayFlag)
                displayCurrentState(program);
        }
        catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }
    public void displayCurrentState(PrgState program) {
        System.out.println(program.toString());
    }
    public ArrayList<PrgState> getPrograms() {
        return this.repository.getAll();
    }
    public void setDisplayFlag(boolean flag) {
        this.displayFlag = flag;
    }
}

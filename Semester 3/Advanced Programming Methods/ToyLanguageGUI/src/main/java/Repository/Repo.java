package Repository;

import Model.PrgState;
import Model.Statements.IStmt;
import MyException.MyException;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import Model.Statements.*;
import Model.Types.*;
import Model.ADTs.*;
import Model.Expressions.*;
import Model.Values.*;

public class Repo implements IRepo {
    private List<PrgState> programs;
    private String logFilePath;

    public Repo(String logFilePath) {
        this.programs = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    public Repo(PrgState program, String logFilePath) {
        this.programs = new ArrayList<>();
        this.programs.add(program);
        this.logFilePath = logFilePath;
    }

    @Override
    public void addPrg(PrgState program) {
        this.programs.add(program);
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
    @Override
    public List<IStmt> allExamples() {
        List<IStmt> examples = new ArrayList<>();
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a",
                                new ArithExp(new ValueExp(new IntValue(2)),
                                        new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)),
                                new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)),
                                        new PrintStmt(new VarExp("b"))))));

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new
                                        IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                        VarExp("v"))))));

        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(new VarExp("varf"))))))))));

        IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(15))),
                        new CompStmt(new VarDeclStmt("b", new IntType()),
                                new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(18))),
                                        new CompStmt(new VarDeclStmt("res", new BoolType()),
                                                new CompStmt(new AssignStmt("res", new RelationalExp(new VarExp("a"), new VarExp("b"), ">")),
                                                        new PrintStmt(new VarExp("res"))))))));

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))))));

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))), new ValueExp(new IntValue(5)), 1)))))));

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                new CompStmt(new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(new ReadHeapExp(new VarExp("v")), new ValueExp(new IntValue(5)), 1))))));

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));

        IStmt ex10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",
                                        new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)), 2)))),
                                new PrintStmt(new VarExp("v")))));
        IStmt ex11 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(
                                                new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                                        new PrintStmt(new ReadHeapExp(new VarExp("a"))))))
                                        ), new CompStmt(
                                                new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                        ))))));
        examples.add(ex1);
        examples.add(ex2);
        examples.add(ex3);
        examples.add(ex4);
        examples.add(ex5);
        examples.add(ex6);
        examples.add(ex7);
        examples.add(ex8);
        examples.add(ex9);
        examples.add(ex10);
        examples.add(ex11);
        return examples;
    }
    @Override
    public void clear() {
        this.programs.clear();
    }
}

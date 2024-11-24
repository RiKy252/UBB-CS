import Controller.Controller;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyFileTable;
import Model.ADTs.MyList;
import Model.ADTs.MyStack;
import Model.Expressions.ArithExp;
import Model.Expressions.RelationalExp;
import Model.Expressions.ValueExp;
import Model.Expressions.VarExp;
import Model.PrgState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import MyException.MyException;
import Repository.IRepo;
import Repository.Repo;
import View.TextMenu;
import View.Commands.ExitCommand;
import View.Commands.RunExampleCommand;

public class Interpreter {
    public static void main(String[] args) {
        try {
            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                            new PrintStmt(new VarExp("v"))));
            PrgState program1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), ex1);
            IRepo repository1 = new Repo(program1, "log1.txt");
            Controller controller1 = new Controller(repository1);

            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new AssignStmt("a",
                            new ArithExp(new ValueExp(new IntValue(2)),
                                    new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)),
                                    new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)),
                    new PrintStmt(new VarExp("b"))))));
            PrgState program2 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), ex2);
            IRepo repository2 = new Repo(program2, "log2.txt");
            Controller controller2 = new Controller(repository2);

            IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                    new CompStmt(new VarDeclStmt("v", new IntType()),
                            new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                    new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                            IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                            VarExp("v"))))));
            PrgState program3 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), ex3);
            IRepo repository3 = new Repo(program3, "log3.txt");
            Controller controller3 = new Controller(repository3);

            IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                    new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                            new CompStmt(new OpenRFile(new VarExp("varf")),
                                    new CompStmt(new VarDeclStmt("varc", new IntType()),
                                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                    new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(new VarExp("varf"))))))))));
            PrgState program4 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), ex4);
            IRepo repository4 = new Repo(program4, "log4.txt");
            Controller controller4 = new Controller(repository4);

            IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(15))),
                            new CompStmt(new VarDeclStmt("b", new IntType()),
                                    new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(18))),
                                            new CompStmt(new VarDeclStmt("res", new BoolType()),
                                                    new CompStmt(new AssignStmt("res", new RelationalExp(new VarExp("a"),new VarExp("b"), ">")),
                                                            new PrintStmt(new VarExp("res"))))))));
            PrgState program5 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), ex5);
            IRepo repository5 = new Repo(program5,"log5.txt");
            Controller controller5 = new Controller(repository5);

            TextMenu menu = new TextMenu();
            menu.addCommand(new RunExampleCommand("1", "Run the following program:\n" + ex1, controller1));
            menu.addCommand(new RunExampleCommand("2", "Run the following program:\n" + ex2, controller2));
            menu.addCommand(new RunExampleCommand("3", "Run the following program:\n" + ex3, controller3));
            menu.addCommand(new RunExampleCommand("4", "Run the following program:\n" + ex4, controller4));
            menu.addCommand(new RunExampleCommand("5", "Run the following program:\n" + ex5, controller5));
            menu.addCommand(new ExitCommand("0", "Exit program"));
            menu.show();
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }
}

// TODO -> A4 and Delete MyIFileTable, repair file operations functions
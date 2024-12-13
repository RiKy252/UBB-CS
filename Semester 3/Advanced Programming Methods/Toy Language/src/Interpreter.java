import Controller.Controller;
import Model.ADTs.Heap;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyList;
import Model.ADTs.MyStack;
import Model.Expressions.*;
import Model.PrgState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.RefType;
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
            ex1.typeCheck(new MyDictionary<>());
            PrgState program1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex1);
            IRepo repository1 = new Repo(program1, "log1.txt");
            Controller controller1 = new Controller(repository1);

            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new AssignStmt("a",
                            new ArithExp(new ValueExp(new IntValue(2)),
                                    new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)),
                                    new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)),
                    new PrintStmt(new VarExp("b"))))));
            ex2.typeCheck(new MyDictionary<>());
            PrgState program2 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex2);
            IRepo repository2 = new Repo(program2, "log2.txt");
            Controller controller2 = new Controller(repository2);

            IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                    new CompStmt(new VarDeclStmt("v", new IntType()),
                            new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                    new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                            IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                            VarExp("v"))))));
            ex3.typeCheck(new MyDictionary<>());
            PrgState program3 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex3);
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
            ex4.typeCheck(new MyDictionary<>());
            PrgState program4 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex4);
            IRepo repository4 = new Repo(program4, "log4.txt");
            Controller controller4 = new Controller(repository4);

            IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(15))),
                            new CompStmt(new VarDeclStmt("b", new IntType()),
                                    new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(18))),
                                            new CompStmt(new VarDeclStmt("res", new BoolType()),
                                                    new CompStmt(new AssignStmt("res", new RelationalExp(new VarExp("a"),new VarExp("b"), ">")),
                                                            new PrintStmt(new VarExp("res"))))))));
            ex5.typeCheck(new MyDictionary<>());
            PrgState program5 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex5);
            IRepo repository5 = new Repo(program5,"log5.txt");
            Controller controller5 = new Controller(repository5);

            // Heap allocation
            IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))))));
            ex6.typeCheck(new MyDictionary<>());
            PrgState program6 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex6);
            IRepo repository6 = new Repo(program6, "log6.txt");
            Controller controller6 = new Controller(repository6);

            // Heap reading
            IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                    new PrintStmt(new ArithExp(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))), new ValueExp(new IntValue(5)), 1)))))));
            ex7.typeCheck(new MyDictionary<>());
            PrgState program7 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex7);
            IRepo repository7 = new Repo(program7, "log7.txt");
            Controller controller7 = new Controller(repository7);

            // Heap writing
            IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                    new CompStmt(new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(new ArithExp(new ReadHeapExp(new VarExp("v")), new ValueExp(new IntValue(5)), 1))))));
            ex8.typeCheck(new MyDictionary<>());
            PrgState program8 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex8);
            IRepo repository8 = new Repo(program8, "log8.txt");
            Controller controller8 = new Controller(repository8);

            // Garbage collector
            IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                    new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));
            ex9.typeCheck(new MyDictionary<>());
            PrgState program9 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex9);
            IRepo repository9 = new Repo(program9, "log9.txt");
            Controller controller9 = new Controller(repository9);

            // While stmt
            IStmt ex10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                            new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                    new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",
                                            new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)), 2)))),
                                    new PrintStmt(new VarExp("v")))));
            ex10.typeCheck(new MyDictionary<>());
            PrgState program10 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex10);
            IRepo repository10 = new Repo(program10, "log10.txt");
            Controller controller10 = new Controller(repository10);

            // Threads example

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
            ex11.typeCheck(new MyDictionary<>());
            PrgState program11 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), ex11);
            IRepo repository11 = new Repo(program11, "log11.txt");
            Controller controller11 = new Controller(repository11);

            TextMenu menu = new TextMenu();
            menu.addCommand(new RunExampleCommand("1", "Run the following program:\n" + ex1, controller1));
            menu.addCommand(new RunExampleCommand("2", "Run the following program:\n" + ex2, controller2));
            menu.addCommand(new RunExampleCommand("3", "Run the following program:\n" + ex3, controller3));
            menu.addCommand(new RunExampleCommand("4", "Run the following program:\n" + ex4, controller4));
            menu.addCommand(new RunExampleCommand("5", "Run the following program:\n" + ex5, controller5));
            menu.addCommand(new RunExampleCommand("6", "Run the following program:\n" + ex6, controller6));
            menu.addCommand(new RunExampleCommand("7", "Run the following program:\n" + ex7, controller7));
            menu.addCommand(new RunExampleCommand("8", "Run the following program:\n" + ex8, controller8));
            menu.addCommand(new RunExampleCommand("9", "Run the following program:\n" + ex9, controller9));
            menu.addCommand(new RunExampleCommand("10", "Run the following program:\n" + ex10, controller10));
            menu.addCommand(new RunExampleCommand("11", "Run the following program:\n" + ex11, controller11));
            menu.addCommand(new ExitCommand("0", "Exit program"));
            menu.show();
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }
}

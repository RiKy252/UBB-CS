package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.ISemaphoreTable;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;
import javafx.util.Pair;

import java.sql.Array;
import java.util.ArrayList;
import java.util.List;

public class CreateSemaphoreStmt implements IStmt {
    private String var;
    private Exp exp;
    public CreateSemaphoreStmt(String var, Exp exp) {
        this.var = var;
        this.exp = exp;
    }
    @Override
    public String toString() {
        return "createSemaphore(" + var + ", " + exp + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new CreateSemaphoreStmt(var, exp.deepcopy());
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        ISemaphoreTable semaphoreTable = state.getSemaphoreTable();
        Value number1 = exp.eval(symTable, heap);
        if (!number1.getType().equals(new IntType())) {
            throw new MyException("The expression is not an integer");
        }
        int num = ((IntValue) number1).getVal();
        List<Integer> emptyList = new ArrayList<>();
        int newLocation = semaphoreTable.allocate(new Pair<>(num, emptyList));
        if (symTable.isDefined(var) && symTable.lookup(var).getType().equals(new IntType()))
            symTable.update(var, new IntValue(newLocation));
        else
            throw new MyException("Variable " + var + " not of type int or not defined at all!");
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.lookup(var);
        Type typeExp = exp.typeCheck(typeEnv);
        if (typeVar.equals(new IntType()) && typeExp.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("createSemaphore stmt: " + var + " or " + exp + " do not have int type!");
    }
}

package Model.Statements;

import Model.ADTs.ISemaphoreTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;
import javafx.util.Pair;

import java.util.List;

public class ReleaseStmt implements IStmt {
    private String var;
    public ReleaseStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "release(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new ReleaseStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        if (symTable.isDefined(var)) {
            Value varValue = symTable.lookup(var);
            if (varValue.getType().equals(new IntType())) {
                int foundIndex = ((IntValue) varValue).getVal();
                ISemaphoreTable semaphoreTable = state.getSemaphoreTable();
                if (semaphoreTable.containsKey(foundIndex)) {
                    Pair<Integer, List<Integer>> entry = semaphoreTable.get(foundIndex);
                    List<Integer> list1 = entry.getValue();
                    if (list1.contains(state.getId()))
                        list1.remove(Integer.valueOf(state.getId()));
                } else {
                    throw new MyException("The found index " + foundIndex + " is not in the semaphore table!");
                }
            } else {
                throw new MyException("The variable " + var + " is not of type int!");
            }
        } else {
            throw new MyException("The variable " + var + " is not defined in the sym table!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type varType = typeEnv.lookup(var);
        if (varType.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("Release stmt: Variable " + var + " is not an integer!");
    }
}

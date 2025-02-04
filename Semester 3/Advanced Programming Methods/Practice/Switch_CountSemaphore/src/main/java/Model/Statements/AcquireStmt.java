package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.ISemaphoreTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;

public class AcquireStmt implements IStmt {
    String var;
    public AcquireStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "acquire(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new AcquireStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        if (symTable.isDefined(var)) {
            Value foundIndexValue = symTable.lookup(var);
            if (foundIndexValue.getType().equals(new IntType())) {
                ISemaphoreTable semaphoreTable = state.getSemaphoreTable();
                int foundIndex = ((IntValue) foundIndexValue).getVal();
                if (semaphoreTable.containsKey(foundIndex)) {
                    Pair<Integer, List<Integer>> entry = semaphoreTable.get(foundIndex);
                    int n1 = entry.getKey();
                    List<Integer> list1 = entry.getValue();
                    int nl = list1.size();
                    if (n1 > nl) {
                        if (!list1.contains(state.getId())) {
                            list1.add(state.getId());
                        }
                    } else {
                        state.getStack().push(this);
                    }
                } else {
                    throw new MyException("The found index " + foundIndex + " is not in the semaphore table!");
                }
            } else {
                throw new MyException("The variable " + var + " is not an integer!");
            }
        } else {
            throw new MyException("The variable " + var + " is not defined!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type varType = typeEnv.lookup(var);
        if (varType.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("Acquire stmt: Variable " + var + " is not an integer!");
    }
}

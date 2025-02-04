package Model.Statements;

import Model.ADTs.ILockTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class UnlockStmt implements IStmt {
    private String var;
    public UnlockStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "unlock(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new UnlockStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        ILockTable lockTable = state.getLockTable();
        if (symTable.isDefined(var)) {
            Value foundIndexValue = symTable.lookup(var);
            int foundIndex = ((IntValue) foundIndexValue).getVal();
            if (lockTable.contains(foundIndex)) {
                if (lockTable.get(foundIndex) == state.getId())
                    lockTable.put(foundIndex, -1);
            }
        } else {
            throw new MyException("Unlock Stmt: The variable " + var + " is not defined!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }
}

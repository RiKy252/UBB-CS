package Model.Statements;

import Model.ADTs.ILockTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class LockStmt implements IStmt {
    private String var;
    public LockStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "lock(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new LockStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        ILockTable lockTable = state.getLockTable();
        if (symTable.isDefined(var)) {
            Value foundIndexValue = symTable.lookup(var);
            int foundIndex = ((IntValue) foundIndexValue).getVal();
            if (lockTable.contains(foundIndex)) {
                if (lockTable.get(foundIndex) == -1)
                    lockTable.put(foundIndex, state.getId());
                else
                    state.getStack().push(this);
            } else {
                throw new MyException("Lock Stmt: The found index " + foundIndex + " is not present in the lock table!");
            }
        } else {
            throw new MyException("Lock Stmt: The variable " + var + " is not defined!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.isDefined(var)) {
            if (!typeEnv.lookup(var).equals(new IntType()))
                throw new MyException("Lock Stmt: " + var + " is not of type int!");
        } else {
            throw new MyException("Lock Stmt: " + var + " is not defined!");
        }
        return typeEnv;
    }
}

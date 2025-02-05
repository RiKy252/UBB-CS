package Model.Statements;

import Model.ADTs.ILockTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class NewLockStmt implements IStmt {
    private String var;
    public NewLockStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "newLock(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new NewLockStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        ILockTable lockTable = state.getLockTable();
        int newFreeLocation = lockTable.allocate(-1);
        if (symTable.isDefined(var))
            symTable.update(var, new IntValue(newFreeLocation));
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.isDefined(var)) {
            if (!typeEnv.lookup(var).equals(new IntType()))
                throw new MyException("NewLock Stmt: " + var + " is not of type int!");
        } else {
            throw new MyException("NewLock Stmt: " + var + " is not defined!");
        }
        return typeEnv;
    }
}

package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.ILatchTable;
import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class AwaitStmt implements IStmt {
    private String var;
    public AwaitStmt(String var) {
        this.var = var;
    }
    @Override
    public String toString() {
        return "await(" + var + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new AwaitStmt(var);
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (symTbl.isDefined(var)) {
            Value varValue = symTbl.lookup(var);
            if (varValue.getType().equals(new IntType())) {
                int foundIndex = ((IntValue) varValue).getVal();
                ILatchTable latchTable = state.getLatchTable();
                if (latchTable.contains(foundIndex)) {
                    if (latchTable.get(foundIndex) != 0) {
                        state.getStack().push(this);
                    }
                } else {
                    throw new MyException("Await Stmt: The found index " + foundIndex + " is not found in the latch table!");
                }
            } else {
                throw new MyException("Await Stmt: The variable " + var + " is not an integer!");
            }
        } else {
            throw new MyException("Await Stmt: The variable " + var + " is not defined!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        Type varType = typeEnv.lookup(var);
        if (varType.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("Await Stmt: The variable " + var + " is not an integer!");
    }
}

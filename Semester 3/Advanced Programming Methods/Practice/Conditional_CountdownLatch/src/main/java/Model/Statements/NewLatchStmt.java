package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.ILatchTable;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class NewLatchStmt implements IStmt {
    private String var;
    private Exp exp;
    public NewLatchStmt(String var, Exp exp) {
        this.var = var;
        this.exp = exp;
    }
    @Override
    public String toString() {
        return "newLatch(" + var + ", " + exp + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new NewLatchStmt(var, exp.deepcopy());
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        Value expValue = exp.eval(symTbl, heap);
        if (expValue.getType().equals(new IntType())) {
            int num1 = ((IntValue) expValue).getVal();
            ILatchTable latchTable = state.getLatchTable();
            int newLocation = latchTable.allocate(num1);
            if (symTbl.isDefined(var)) {
                Value varValue = symTbl.lookup(var);
                if (varValue.getType().equals(new IntType())) {
                    symTbl.update(var, new IntValue(newLocation));
                } else {
                    throw new MyException("The value of the variable " + var + " is not an integer!");
                }
            } else {
                throw new MyException("The variable " + var + " is not defined in the sym table!");
            }
        } else {
            throw new MyException("NewLatchStmt: expression result is not an integer!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        Type varType = typeEnv.lookup(var);
        Type expType = exp.typeCheck(typeEnv);
        if (varType.equals(new IntType())) {
            if (expType.equals(new IntType())) {
                return typeEnv;
            } else {
                throw new MyException("New Latch Stmt: The expression is not evaluated to an integer!");
            }
        } else {
            throw new MyException("New Latch Stmt: The variable " + var + " is not an integer!");
        }
    }
}

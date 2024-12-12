package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Value;
import MyException.MyException;

public class NewStmt implements IStmt {
    private String varName;
    private Exp exp;

    public NewStmt(String varName, Exp exp) {
        this.varName = varName;
        this.exp = exp;
    }

    public String getVarName() {
        return varName;
    }

    public Exp getExp() {
        return exp;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        if (!symTbl.isDefined(varName)) {
            throw new MyException("Variable " + varName + " is not defined");
        }
        if (!(symTbl.lookup(varName).getType() instanceof RefType)) {
            throw new MyException("Variable " + varName + " is not of type RefType");
        }
        Value val = exp.eval(symTbl, heap);
        RefValue varNameValue = (RefValue) symTbl.lookup(varName);
        if (!val.getType().equals(varNameValue.getLocationType())) {
            throw new MyException("Types do not match");
        }
        int addr = heap.allocate(val);
        symTbl.update(varName, new RefValue(addr, val.getType()));
        return null;
    }
    @Override
    public IStmt deepcopy() {
        return new NewStmt(varName, exp.deepcopy());
    }
    @Override
    public String toString() {
        return "new(" + varName + ", " + exp.toString() + ")";
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.lookup(varName);
        Type typeExp = exp.typeCheck(typeEnv);
        if (typeVar.equals(new RefType(typeExp)))
            return typeEnv;
        else
            throw new MyException("New Stmt: right hand side and left hand side have different types!");
    }
}

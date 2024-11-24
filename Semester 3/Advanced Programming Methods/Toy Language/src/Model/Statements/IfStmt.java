package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;
import MyException.*;

public class IfStmt implements IStmt {
    private Exp exp;
    private IStmt thenS;
    private IStmt elseS;
    public IfStmt(Exp e, IStmt th, IStmt el) {
        this.exp = e;
        this.thenS = th;
        this.elseS = el;
    }
    @Override
    public PrgState execute(PrgState state) throws IncompatibleTypeException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        Value val = exp.eval(symTbl);
        if (!val.getType().equals(new BoolType())) {
            throw new IncompatibleTypeException("The if expression is not a boolean");
        }
        else {
            BoolValue v = (BoolValue) val;
            if (v.getVal()) {
                state.getStack().push(thenS);
            }
            else {
                state.getStack().push(elseS);
            }
        }
        return state;
    }
    @Override
    public String toString() {
        return "if (" + exp + ") then { " + thenS + " } else { " + elseS + " }";
    }
    @Override
    public IStmt deepcopy() {
        return new IfStmt(exp.deepcopy(), thenS.deepcopy(), elseS.deepcopy());
    }
}

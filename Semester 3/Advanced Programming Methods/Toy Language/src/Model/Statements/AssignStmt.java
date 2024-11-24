package Model.Statements;

import Model.Expressions.Exp;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIStack;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.Value;
import MyException.*;

public class AssignStmt implements IStmt {
    String id;
    Exp exp;
    public AssignStmt(String id, Exp exp) {
        this.id = id;
        this.exp = exp;
    }
    @Override
    public String toString() {
        return id + " = " + exp.toString();
    }
    @Override
    public PrgState execute(PrgState state) throws IncompatibleTypeException {
        MyIStack<IStmt> stack = state.getStack();
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (symTbl.isDefined(id)) {
            Value val = exp.eval(symTbl);
            Type typeId = (symTbl.lookup(id)).getType();
            if (val.getType().equals(typeId))
                symTbl.update(id, val);
            else
                throw new IncompatibleTypeException("Declared type of variable " + id + " and type of the assigned expression do not match");
        }
        else {
            throw new IncompatibleTypeException("The used variable " + id + " was not declared before");
        }
        return state;
    }
    @Override
    public IStmt deepcopy() {
        return new AssignStmt(new String(id), exp.deepcopy());
    }
}

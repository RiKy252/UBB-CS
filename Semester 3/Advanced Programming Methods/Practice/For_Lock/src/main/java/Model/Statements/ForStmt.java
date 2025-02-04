package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.Expressions.RelationalExp;
import Model.Expressions.VarExp;
import Model.PrgState;
import Model.Types.Type;
import MyException.MyException;

public class ForStmt implements IStmt {
    private String var;
    private Exp exp1, exp2, exp3;
    private IStmt stmt;
    public ForStmt(String var, Exp exp1, Exp exp2, Exp exp3, IStmt stmt) {
        this.var = var;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.stmt = stmt;
    }
    @Override
    public String toString() {
        return "for(" + var + "=" + exp1.toString() + ";" + var + "<" + exp2.toString() + ";" + var + "=" + exp3.toString() + "){" + stmt.toString() + "}";
    }
    @Override
    public IStmt deepcopy() {
        return new ForStmt(var, exp1.deepcopy(), exp2.deepcopy(), exp3.deepcopy(), stmt.deepcopy());
    }
    @Override
    public PrgState execute(PrgState state) {
        IStmt newStmt =
                new CompStmt(new AssignStmt(var, exp1), new WhileStmt(new RelationalExp(new VarExp(var), exp2, "<"), new CompStmt(stmt, new AssignStmt(var, exp3))));
        state.getStack().push(newStmt);
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }
}

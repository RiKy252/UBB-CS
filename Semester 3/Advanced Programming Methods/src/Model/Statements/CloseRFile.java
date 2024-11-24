package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

public class CloseRFile implements IStmt {
    Exp exp;
    public CloseRFile(Exp expression) {
        this.exp = expression;
    }
    @Override
    public String toString() {
        return "CloseRFile(" + exp.toString() + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new CloseRFile(exp.deepcopy());
    }
    @Override
    public PrgState execute(PrgState program) {
        MyIDictionary<String, Value> symTable = program.getSymTable();
        Value val = exp.eval(symTable);
        if (!(val.getType() instanceof StringType)) {
            throw new MyException("Expression type is not string!");
        }
        program.getFileTable().closeFile(((StringValue) val).getVal());
        return program;
    }
}

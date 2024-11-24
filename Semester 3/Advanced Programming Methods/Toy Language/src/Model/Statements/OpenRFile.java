package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIFileTable;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

public class OpenRFile implements IStmt {
    Exp exp;
    public OpenRFile(Exp expression) {
        this.exp = expression;
    }
    @Override
    public String toString() {
        return "OpenRFile(" + exp.toString() + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new OpenRFile(exp.deepcopy());
    }
    @Override
    public PrgState execute(PrgState program) throws MyException {
        MyIDictionary<String, Value> symTable = program.getSymTable();
        Value val = exp.eval(symTable);
        if (!(val.getType() instanceof StringType)) {
            throw new MyException("Expression type is not string!");
        }
        MyIFileTable fileTable = program.getFileTable();
        fileTable.openFile(((StringValue) val).getVal());
        return program;
    }
}

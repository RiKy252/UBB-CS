package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

import java.io.BufferedReader;
import java.io.FileReader;

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
        IHeap<Integer, Value> heap = program.getHeap();
        Value val = exp.eval(symTable, heap);
        if (!(val.getType() instanceof StringType)) {
            throw new MyException("Expression type is not string!");
        }
        MyIDictionary<String, BufferedReader> fileTable = program.getFileTable();
        String name = ((StringValue) val).getVal();
        if (fileTable.isDefined(name)) {
            throw new MyException("File already opened!");
        }
        try {
            BufferedReader reader = new BufferedReader(new FileReader(name));
            fileTable.update(name, reader);
        } catch (Exception e) {
            throw new MyException("Error opening file!");
        }
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExp = exp.typeCheck(typeEnv);
        if (typeExp.equals(new StringType()))
            return typeEnv;
        else
            throw new MyException("openFile expression is not of type string!");
    }
}

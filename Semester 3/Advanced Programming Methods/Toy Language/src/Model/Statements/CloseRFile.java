package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

import java.io.BufferedReader;
import java.io.IOException;

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
    public PrgState execute(PrgState program) throws MyException{
        MyIDictionary<String, Value> symTable = program.getSymTable();
        IHeap<Integer, Value> heap = program.getHeap();
        Value val = exp.eval(symTable, heap);
        if (!(val.getType() instanceof StringType)) {
            throw new MyException("Expression type is not string!");
        }
        MyIDictionary<String, BufferedReader> fileTable = program.getFileTable();
        String name = ((StringValue) val).getVal();
        try {
            BufferedReader reader = fileTable.lookup(name);
            reader.close();
            fileTable.remove(name);
        } catch (IOException e) {
            throw new MyException("Error closing file!");
        } catch (MyException e) {
            throw new MyException("File could not be found!");
        }
        return program;
    }
}

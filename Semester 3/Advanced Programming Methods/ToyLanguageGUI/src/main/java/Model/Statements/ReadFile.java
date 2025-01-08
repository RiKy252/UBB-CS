package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStmt {
    Exp exp;
    String varName;
    public ReadFile(Exp expression, String name) {
        exp = expression;
        varName = name;
    }
    @Override
    public String toString() {
        return "ReadFile(" + this.exp.toString() + ", " + this.varName + ")";
    }
    @Override
    public IStmt deepcopy() { return new ReadFile(exp.deepcopy(), varName); }
    @Override
    public PrgState execute(PrgState program) throws MyException {
        MyIDictionary<String, Value> symTable = program.getSymTable();
        IHeap<Integer, Value> heap = program.getHeap();
        if (!(symTable.lookup(varName).getType() instanceof IntType))
            throw new MyException("Variable is not of type int or is not declared!");
        Value val = this.exp.eval(symTable, heap);
        if (!(val.getType() instanceof StringType))
            throw new MyException("Expression value is not a string!");
        BufferedReader reader = null;
        try {
            reader = program.getFileTable().lookup(((StringValue) val).getVal());
        } catch (MyException e) {
            throw new MyException("Cannot read file " + ((StringValue) val).getVal());
        }
        String content;
        try {
            content = reader.readLine();
        } catch (IOException e) {
            throw new MyException("Invalid line in file!");
        }
        if (content == null) {
            content = "0";
        }
        int answer = 0;
        try {
            answer = Integer.parseInt(content);
        } catch (MyException e) {
            throw new MyException("Invalid line in file");
        }
        symTable.update(varName, new IntValue(answer));
        return null;
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (!typeEnv.isDefined(varName))
            throw new MyException("Variable " + varName + " is not declared!");
        Type varType = typeEnv.lookup(varName);
        if (!varType.equals(new IntType()))
            throw new MyException("Variable " + varName + " is not of type int!");
        Type expType = exp.typeCheck(typeEnv);
        if (!expType.equals(new StringType()))
            throw new MyException("Expression " + exp + " does not evaluate to a string!");
        return typeEnv;
    }
}

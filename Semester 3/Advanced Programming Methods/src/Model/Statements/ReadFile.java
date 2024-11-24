package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import MyException.MyException;

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
    public IStmt deepcopy() {
        return new ReadFile(exp.deepcopy(), varName);
    }
    @Override
    public PrgState execute(PrgState program) throws MyException {
        MyIDictionary<String, Value> symTable = program.getSymTable();
        if (!(symTable.lookup(varName).getType() instanceof IntType))
            throw new MyException("Variable is not of type int or is not declared!");
        Value val = this.exp.eval(symTable);
        if (!(val.getType() instanceof StringType))
            throw new MyException("Expression value is not a string!");
        int numberInsideFile = program.getFileTable().readFile(((StringValue) val).getVal());
        symTable.update(varName, new IntValue(numberInsideFile));
        return program;
    }
}

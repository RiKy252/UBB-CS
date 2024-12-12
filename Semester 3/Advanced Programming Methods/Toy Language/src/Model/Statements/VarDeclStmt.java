package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.*;
import Model.Values.*;
import MyException.*;

public class VarDeclStmt implements IStmt {
    private Type type;
    private String id;
    public VarDeclStmt(String id, Type type) {
        this.type = type;
        this.id = id;
    }
    @Override
    public PrgState execute(PrgState state) throws AlreadyDefinedException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (symTbl.isDefined(id))
            throw new AlreadyDefinedException("Variable is already defined");
        Value defaultValue = type.defaultValue();
        symTbl.add(id, defaultValue);
        return null;
    }
    @Override
    public String toString() {
        return type + " " + id;
    }
    @Override
    public IStmt deepcopy() {
        return new VarDeclStmt(id, type.deepcopy());
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        typeEnv.add(id, type);
        return typeEnv;
    }
}

package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
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
        else {
            if (type.equals(new BoolType())) {
                BoolType t = new BoolType();
                BoolValue value = (BoolValue) t.defaultValue();
                symTbl.add(id, value);
            }
            else if (type.equals(new IntType())) {
                IntType t = new IntType();
                IntValue value = (IntValue) t.defaultValue();
                symTbl.add(id, value);
            }
            else {
                StringType t = new StringType();
                StringValue value = (StringValue) t.defaultValue();
                symTbl.add(id, value);
            }
        }
        return state;
    }
    @Override
    public String toString() {
        return type + " " + id;
    }
    @Override
    public IStmt deepcopy() {
        return new VarDeclStmt(id, type.deepcopy());
    }
}

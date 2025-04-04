package Model.Statements;

import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Value;
import MyException.MyException;

public class WriteHeapStmt implements IStmt {
    private String varName;
    private Exp exp;

    public WriteHeapStmt(String varName, Exp exp) {
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        IHeap<Integer, Value> heap = state.getHeap();
        if (symTable.isDefined(varName)) {
            if (symTable.lookup(varName).getType() instanceof RefType) {
                RefValue refValue = (RefValue) state.getSymTable().lookup(varName);
                if (heap.isDefined(refValue.getAddress())) {
                    Value val = exp.eval(state.getSymTable(), state.getHeap());
                    if (val.getType().equals(refValue.getLocationType())) {
                        state.getHeap().write(refValue.getAddress(), val);
                    } else {
                        throw new MyException("Type of expression and type of location do not match");
                    }
                } else {
                    throw new MyException("Address not found in heap");
                }
            } else {
                throw new MyException("Variable is not a reference type");
            }
        } else {
            throw new MyException("Variable not found in sym table");
        }
        return null;
    }

    @Override
    public String toString() {
        return "writeHeap(" + varName + ", " + exp.toString() + ")";
    }

    @Override
    public IStmt deepcopy() {
        return new WriteHeapStmt(varName, exp.deepcopy());
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (!typeEnv.isDefined(varName))
            throw new MyException("Variable " + varName + " is not defined!");
        Type varType = typeEnv.lookup(varName);
        if (!(varType instanceof RefType))
            throw new MyException("Variable " + varName + " is not a reference type!");
        RefType refType = (RefType) varType;
        Type locationType = refType.getInner();
        Type expType = exp.typeCheck(typeEnv);
        if (!expType.equals(locationType))
            throw new MyException("writeHeap error: type of the expression does not match the referenced type of the variable!");
        return typeEnv;
    }
}

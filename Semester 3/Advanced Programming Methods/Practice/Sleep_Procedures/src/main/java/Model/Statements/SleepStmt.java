package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;
import MyException.MyException;

public class SleepStmt implements IStmt {
    private Value number;
    public SleepStmt(Value number) {
        this.number = number;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        int actualNumber = ((IntValue) number).getVal();
        if (actualNumber != 0)
            state.getStack().push(new SleepStmt(new IntValue(actualNumber - 1)));
        return null;
    }
    @Override
    public String toString() {
        return "sleep(" + number + ")";
    }
    @Override
    public IStmt deepcopy() {
        return new SleepStmt(number);
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type valueType = number.getType();
        if (valueType.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("Sleep Stmt: The parameter passed \"" + number + "\" is not a number!");
    }
}

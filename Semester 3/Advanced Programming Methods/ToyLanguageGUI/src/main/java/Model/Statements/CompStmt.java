package Model.Statements;

import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIStack;
import Model.PrgState;
import Model.Types.Type;
import MyException.MyException;

public class CompStmt implements IStmt {
    IStmt first;
    IStmt second;
    public CompStmt(IStmt first, IStmt second) {
        this.first = first;
        this.second = second;
    }
    @Override
    public String toString() {
        return first.toString() + ";\n" + second.toString();
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStack();
        stack.push(second);
        stack.push(first);
        return null;
    }
    @Override
    public IStmt deepcopy() {
        return new CompStmt(first.deepcopy(), second.deepcopy());
    }
    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return second.typeCheck(first.typeCheck(typeEnv));
    }
}

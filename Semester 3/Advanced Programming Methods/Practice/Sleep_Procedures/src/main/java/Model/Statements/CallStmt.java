package Model.Statements;

import Model.ADTs.MyDictionary;
import Model.ADTs.MyIDictionary;
import Model.Expressions.Exp;
import Model.PrgState;
import Model.Values.Value;
import MyException.MyException;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;

public class CallStmt implements IStmt {
    private String procName;
    private List<Exp> expList;
    public CallStmt(String procName, List<Exp> expList) {
        this.procName = procName;
        this.expList = expList;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        Pair<List<String>, IStmt> procListBody = state.getProcTable().get(procName);
        ArrayList<String> variables = (ArrayList<String>)procListBody.getKey();
        IStmt procedureBody = procListBody.getValue();
        MyIDictionary<String, Value> newSymTable = new MyDictionary<>();
        for (int i = 0; i < variables.size(); i++)
            newSymTable.add(variables.get(i), expList.get(i).eval(state.getSymTable(), state.getHeap()));
        state.getSymTableStack().push(newSymTable);
        state.getStack().push(new ReturnStmt());
        state.getStack().push(procedureBody);
        return null;
    }
    @Override
    public String toString() {
        return "call " + procName + "(" + expList.toString() + ")";
    }
    @Override
    public IStmt deepcopy() {
        ArrayList<Exp> newExpList = new ArrayList<>();
        for (Exp exp : expList)
            newExpList.add(exp.deepcopy());
        return new CallStmt(procName, newExpList);
    }
    @Override
    public MyIDictionary<String, Model.Types.Type> typeCheck(MyIDictionary<String, Model.Types.Type> typeEnv) throws MyException {
        return typeEnv;
    }
}

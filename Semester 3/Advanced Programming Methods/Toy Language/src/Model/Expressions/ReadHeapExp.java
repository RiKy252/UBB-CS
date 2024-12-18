package Model.Expressions;


import Model.ADTs.IHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Value;
import MyException.MyException;

public class ReadHeapExp implements Exp {
    private Exp exp;
    public ReadHeapExp(Exp exp) {
        this.exp = exp;
    }
    public Exp getExp() {
        return exp;
    }
    @Override
    public String toString() {
        return "readHeap(" + exp.toString() + ")";
    }
    @Override
    public Value eval(MyIDictionary<String, Value> symTable, IHeap<Integer, Value> heap) throws MyException {
        Value val = exp.eval(symTable, heap);
        if (!(val instanceof RefValue)) {
            throw new MyException("Value is not a reference");
        }
        RefValue refVal = (RefValue) val;
        int addr = refVal.getAddress();
        if (!heap.isDefined(addr)) {
            throw new MyException("Address " + addr + " is not defined in the heap");
        }
        Value heapValue = heap.read(addr);
        return heapValue;
    }
    @Override
    public Exp deepcopy() {
        return new ReadHeapExp(exp.deepcopy());
    }
    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ = exp.typeCheck(typeEnv);
        if (typ instanceof RefType) {
            RefType refTyp = (RefType) typ;
            return refTyp.getInner();
        }
        else {
            throw new MyException("The readHeap argument is not a Ref Type");
        }
    }
}

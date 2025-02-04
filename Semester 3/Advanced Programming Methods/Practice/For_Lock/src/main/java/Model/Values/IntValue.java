package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

public class IntValue implements Value {
    private int val;
    public IntValue(int v) {
        val = v;
    }
    public IntValue() { val = 0; }
    @Override
    public Type getType() {
        return new IntType();
    }
    @Override
    public String toString() {
        return "" + val;
    }
    @Override
    public boolean equals(Value v) {
        if (!v.getType().equals(new IntType()))
            return false;
        return ((IntValue)v).getVal() == this.val;
    }
    public int getVal() {
        return val;
    }
    @Override
    public Value deepcopy() {
        return new IntValue(val);
    }
}
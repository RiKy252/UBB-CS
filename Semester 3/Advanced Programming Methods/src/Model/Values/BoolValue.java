package Model.Values;

import Model.Types.BoolType;
import Model.Types.Type;

public class BoolValue implements Value{
    private boolean val;
    public BoolValue(boolean b) {
        val = b;
    }
    public BoolValue() { val = false; }
    @Override
    public Type getType() {
        return new BoolType();
    }
    @Override
    public String toString() {
        return "" + val;
    }
    @Override
    public boolean equals(Value b) {
        if (!b.getType().equals(new BoolType()))
            return false;
        return ((BoolValue)b).getVal() == this.val;
    }
    public boolean getVal() {
        return val;
    }
    @Override
    public Value deepcopy() {
        return new BoolValue(val);
    }
}

package Model.Types;

import Model.Values.IntValue;
import Model.Values.Value;

public class IntType implements Type {
    @Override
    public boolean equals(Object another) {
        return another instanceof IntType;
    }
    @Override
    public String toString() {
        return "int";
    }
    @Override
    public Type deepcopy() {
        return new IntType();
    }
    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }
}

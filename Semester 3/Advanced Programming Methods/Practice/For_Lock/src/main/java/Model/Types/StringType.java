package Model.Types;

import Model.Values.StringValue;
import Model.Values.Value;

public class StringType implements Type {
    @Override
    public boolean equals(Object another) { return another instanceof StringType; }
    @Override
    public String toString() {
        return "string";
    }
    @Override
    public Type deepcopy() {
        return new StringType();
    }
    @Override
    public Value defaultValue() {
        return new StringValue("");
    }
}

package Model.Values;

import Model.Types.StringType;
import Model.Types.Type;

public class StringValue implements Value {
    private String val;
    public StringValue(String s) {
        this.val = s;
    }
    public StringValue() {
        this.val = "";
    }
    @Override
    public Type getType() {
        return new StringType();
    }
    @Override
    public String toString() {
        return "\"" + val + "\"";
    }
    public String getVal() {
        return val;
    }
    @Override
    public boolean equals(Value s) {
        if (!s.getType().equals(new StringType()))
            return false;
        return ((StringValue)s).getVal().equals(this.val);
    }
    @Override
    public Value deepcopy() {
        return new StringValue(val);
    }
}

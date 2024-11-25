package Model.Values;

import Model.Types.IntType;
import Model.Types.RefType;
import Model.Types.Type;

public class RefValue implements Value {
    private int address;
    private Type locationType;
    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }
    public int getAddress() {
        return address;
    }
    public Type getLocationType() { return locationType; }
    @Override
    public Type getType() {
        return new RefType(locationType);
    }
    @Override
    public boolean equals(Value v) {
        if (!v.getType().equals(new RefType(locationType)))
            return false;
        return ((RefValue) v).getAddress() == this.address;
    }
    @Override
    public String toString() {
        return "(" + address + ", " + locationType.toString() + ")";
    }
    @Override
    public Value deepcopy() {
        return new RefValue(address, locationType);
    }
}

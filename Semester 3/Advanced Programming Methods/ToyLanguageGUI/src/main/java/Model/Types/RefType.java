package Model.Types;

import Model.Values.RefValue;
import Model.Values.Value;

public class RefType implements Type {
    private Type inner;
    public RefType(Type inner) {
        this.inner = inner;
    }
    public Type getInner() {
        return inner;
    }
    @Override
    public boolean equals(Object another) {
        if (another instanceof RefType)
            return inner.equals(((RefType) another).getInner());
        else
            return false;
    }
    @Override
    public String toString() {
        return "Ref (" + inner.toString() + ")";
    }
    @Override
    public Type deepcopy() {
        return new RefType(inner);
    }
    @Override
    public Value defaultValue() {
        return new RefValue(0, inner);
    }
}

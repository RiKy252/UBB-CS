package Model.Values;

import Model.Types.Type;

public interface Value {
    String toString();
    boolean equals(Value v);
    Type getType();
    Value deepcopy();
}

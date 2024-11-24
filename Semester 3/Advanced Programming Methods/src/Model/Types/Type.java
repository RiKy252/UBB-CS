package Model.Types;

import Model.Values.Value;

public interface Type {
    boolean equals(Object another);
    String toString();
    Type deepcopy();
    Value defaultValue();
}

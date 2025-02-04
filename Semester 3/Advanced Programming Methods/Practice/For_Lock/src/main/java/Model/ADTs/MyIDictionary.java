package Model.ADTs;

import MyException.MyException;

import java.util.List;
import java.util.Map;

public interface MyIDictionary<TKey, TValue> {
    boolean isDefined(TKey key);
    void update(TKey key, TValue val);
    TValue lookup(TKey key);
    void add(TKey key, TValue val);
    String toString();
    void remove(TKey key);
    List<TKey> getAllKeys();
    List<TValue> getValues();
    MyIDictionary<TKey, TValue> copy() throws MyException;
    Map<TKey, TValue> toMap();
}

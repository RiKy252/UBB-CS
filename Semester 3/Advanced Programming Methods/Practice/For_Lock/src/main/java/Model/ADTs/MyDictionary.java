package Model.ADTs;
import MyException.MyException;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class MyDictionary<TKey, TValue> implements MyIDictionary<TKey, TValue> {
    private Map<TKey, TValue> dict;
    public MyDictionary() {
        dict = new ConcurrentHashMap<>();
    }
    @Override
    public boolean isDefined(TKey key) {
        return dict.containsKey(key);
    }
    @Override
    public void update(TKey key, TValue val) {
        dict.put(key, val);
    }
    @Override
    public TValue lookup(TKey key) {
        return dict.get(key);
    }
    @Override
    public void add(TKey key, TValue val) {
        dict.put(key, val);
    }
    @Override
    public String toString() {
        StringBuilder buffer = new StringBuilder();
        for (TKey key : this.dict.keySet()) {
            buffer.append(key).append("->").append(this.dict.get(key)).append("\n");
        }
        return buffer.toString();
    }
    @Override
    public void remove(TKey key) {
        this.dict.remove(key);
    }
    @Override
    public List<TKey> getAllKeys() {
        return new ArrayList<>(this.dict.keySet());
    }
    @Override
    public List<TValue> getValues() {
        return new ArrayList<>(this.dict.values());
    }
    @Override
    public MyIDictionary<TKey, TValue> copy() throws MyException {
        MyIDictionary<TKey, TValue> newDict = new MyDictionary<>();
        for (TKey key : this.dict.keySet()) {
            newDict.add(key, this.dict.get(key));
        }
        return newDict;
    }
    @Override
    public Map<TKey, TValue> toMap() {
        return this.dict;
    }
}

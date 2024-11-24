package Model.ADTs;

import java.util.ArrayList;

public class MyList<T> implements MyIList<T> {
    private ArrayList<T> list;
    public MyList() {
        list = new ArrayList<T>();
    }
    @Override
    public void add(T val) {
        list.add(val);
    }
    @Override
    public T get(int index) {
        return list.get(index);
    }
    @Override
    public int size() {
        return list.size();
    }
    @Override
    public String toString() {
        StringBuilder buffer = new StringBuilder();
        for (T elem : list) {
            buffer.append(elem.toString()).append("\n");
        }
        return buffer.toString();
    }
}

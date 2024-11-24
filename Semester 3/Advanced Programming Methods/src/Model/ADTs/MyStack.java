package Model.ADTs;
import java.util.*;

public class MyStack<T> implements MyIStack<T> {
    private Stack<T> stack;
    public MyStack() {
        stack = new Stack<T>();
    }
    @Override
    public T pop() {
        return stack.pop();
    }
    @Override
    public void push(T val) {
        stack.push(val);
    }
    @Override
    public String toString() {
        StringBuilder buffer = new StringBuilder();
        for (int i = stack.size() - 1; i >= 0; i--) {
            buffer.append(stack.get(i).toString());
            if (i != 0)
                buffer.append("\n");
        }
        return buffer.toString();
    }
    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }
}

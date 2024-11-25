package Model.ADTs;

import Model.Expressions.Exp;
import Model.Values.Value;
import MyException.MyException;

import java.util.HashMap;

public class Heap<TKey, TValue> implements IHeap<TKey, TValue> {
    private HashMap<Integer, Value> heap;
    private Integer nextFreeAddr;
    public Heap() {
        heap = new HashMap<>();
        nextFreeAddr = 1;
    }
    public boolean isDefined(Integer addr) {
        return heap.containsKey(addr);
    }
    @Override
    public Integer allocate(Value val) {
        heap.put(nextFreeAddr, val);
        nextFreeAddr += 1;
        return nextFreeAddr - 1;
    }
    @Override
    public void deallocate(Integer address) throws MyException {
        if (heap.containsKey(address)) {
            heap.remove(address);
        } else {
            throw new MyException("Invalid heap address");
        }
    }
    @Override
    public void write(int addr, Value val) throws MyException {
        if (heap.containsKey(addr)) {
            heap.put(addr, val);
        } else {
            throw new MyException("Invalid heap address");
        }
    }
    @Override
    public Value read(Integer addr) throws MyException {
        if (heap.containsKey(addr)) {
            return heap.get(addr);
        } else {
            throw new MyException("Invalid heap address");
        }
    }
    @Override
    public String toString() {
        StringBuilder buffer = new StringBuilder();
        for (Integer key : this.heap.keySet()) {
            buffer.append(key).append("->").append(this.heap.get(key)).append("\n");
        }
        return buffer.toString();
    }
}

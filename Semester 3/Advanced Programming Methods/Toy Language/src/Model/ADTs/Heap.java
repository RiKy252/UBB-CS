package Model.ADTs;

import Model.Expressions.Exp;
import Model.Values.Value;
import MyException.MyException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Heap<TKey, TValue> implements IHeap<TKey, TValue> {
    private Map<Integer, Value> heap;
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
    @Override
    public Map<Integer, Value> safeGarbageCollector(List<Integer> addresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e -> addresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
    @Override
    public void setHeap(Map<Integer, Value> heap) {
        this.heap = heap;
    }
    @Override
    public Map<Integer, Value> getHeap() {
        return this.heap;
    }
}

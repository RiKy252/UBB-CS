package Model.ADTs;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LatchTable implements ILatchTable {
    private Map<Integer, Integer> latchTable;
    private int nextFreeAddress;
    private Lock lock;
    public LatchTable() {
        this.latchTable = new HashMap<>();
        this.nextFreeAddress = 1;
        this.lock = new ReentrantLock();
    }
    @Override
    public void put(int key, int value) {
        lock.lock();
        try {
            latchTable.put(key ,value);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public int get(int key) {
        lock.lock();
        try {
            return latchTable.get(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public boolean contains(int key) {
        lock.lock();
        try {
            return latchTable.containsKey(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public void remove(int key) {
        lock.lock();
        try {
            latchTable.remove(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public Integer allocate(Integer val) {
        lock.lock();
        try {
            latchTable.put(nextFreeAddress, val);
            nextFreeAddress++;
            return nextFreeAddress - 1;
        } finally {
            lock.unlock();
        }
    }
    @Override
    public String toString() {
        lock.lock();
        try {
            return latchTable.toString();
        } finally {
            lock.unlock();
        }
    }
    @Override
    public Map<Integer, Integer> getLatchTable() {
        lock.lock();
        try {
            return this.latchTable;
        } finally {
            lock.unlock();
        }
    }
}

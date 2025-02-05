package Model.ADTs;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LockTable implements ILockTable {
    private Map<Integer, Integer> lockTable;
    private int freeLocation;
    private Lock lock;
    public LockTable() {
        this.lockTable = new HashMap<>();
        this.freeLocation = 1;
        this.lock = new ReentrantLock();
    }
    @Override
    public void put(int key, int value) {
        lock.lock();
        try {
            this.lockTable.put(key, value);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public int allocate(Integer value) {
        lock.lock();
        try {
            this.lockTable.put(freeLocation, value);
            freeLocation++;
            return freeLocation - 1;
        } finally {
            lock.unlock();
        }
    }
    @Override
    public int get(int key) {
        lock.lock();
        try {
            return this.lockTable.get(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public boolean contains(int key) {
        lock.lock();
        try {
            return this.lockTable.containsKey(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public void remove(int key) {
        lock.lock();
        try {
            this.lockTable.remove(key);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public Map<Integer, Integer> getLockTable() {
        lock.lock();
        try {
            return this.lockTable;
        } finally {
            lock.unlock();
        }
    }
    @Override
    public String toString() {
        lock.lock();
        try {
            StringBuilder buffer = new StringBuilder();
            for (Integer key : this.lockTable.keySet()) {
                buffer.append(key).append("->").append(this.lockTable.get(key)).append("\n");
            }
            return buffer.toString();
        } finally {
            lock.unlock();
        }
    }
}

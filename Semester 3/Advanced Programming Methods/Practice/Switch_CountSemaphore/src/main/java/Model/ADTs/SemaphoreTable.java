package Model.ADTs;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SemaphoreTable implements ISemaphoreTable {
    private Map<Integer, Pair<Integer, List<Integer>>> semaphoreTable;
    private int nextFreeLocation;
    private Lock lock;
    public SemaphoreTable() {
        this.semaphoreTable = new HashMap<>();
        this.nextFreeLocation = 1;
        this.lock = new ReentrantLock();
    }
    @Override
    public void put(Integer address, Pair<Integer, List<Integer>> value) {
        lock.lock();
        try {
            semaphoreTable.put(address, value);
        }
        finally {
            lock.unlock();
        }
    }
    @Override
    public int allocate(Pair<Integer, List<Integer>> value) {
        try {
            lock.lock();
            semaphoreTable.put(nextFreeLocation, value);
            nextFreeLocation++;
            return nextFreeLocation - 1;
        }
        finally {
            lock.unlock();
        }
    }
    @Override
    public Pair<Integer, List<Integer>> get(Integer address) {
        lock.lock();
        try {
            return semaphoreTable.get(address);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public boolean containsKey(Integer address) {
        lock.lock();
        try {
            return semaphoreTable.containsKey(address);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public void remove(Integer address) {
        lock.lock();
        try {
            semaphoreTable.remove(address);
        } finally {
            lock.unlock();
        }
    }
    @Override
    public String toString() {
        lock.lock();
        try {
            return semaphoreTable.toString();
        } finally {
            lock.unlock();
        }
    }
    @Override
    public Map<Integer, Pair<Integer, List<Integer>>> getSemaphoreTable() {
        lock.lock();
        try {
            return semaphoreTable;
        } finally {
            lock.unlock();
        }
    }
}

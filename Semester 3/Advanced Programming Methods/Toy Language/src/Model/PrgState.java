package Model;

import Model.ADTs.*;
import Model.Statements.IStmt;
import Model.Values.RefValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class PrgState {
    private  MyIStack<IStmt> exeStack;
    private MyIDictionary<String, Value> symTable;
    private MyIList<Value> out;
    private MyIDictionary<String, BufferedReader> fileTable;
    private IHeap<Integer, Value> heap;
    IStmt originalProgram;

    public PrgState(MyIStack<IStmt> stack, MyIDictionary<String, Value> symbolicTable, MyIList<Value> output, MyIDictionary<String, BufferedReader> fileTable, IHeap<Integer, Value> heap, IStmt program) {
        exeStack = stack;
        symTable = symbolicTable;
        out = output;
        this.fileTable = fileTable;
        originalProgram = program.deepcopy();
        this.heap = heap;
        stack.push(program);
    }

    public void init() {
        this.exeStack = new MyStack<IStmt>();
        this.symTable = new MyDictionary<String, Value>();
        this.out = new MyList<Value>();
        exeStack.push(this.originalProgram);
        originalProgram = originalProgram.deepcopy();
    }

    public MyIStack<IStmt> getStack() {
        return exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public MyIList<Value> getOut() {
        return out;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
         return fileTable;
    }

    public IHeap<Integer, Value> getHeap() { return heap; }

    public List<Integer> getReachableAddresses() {
        List<Integer> addresses = new ArrayList<>();
        Map<Integer, Value> heapTable = this.heap.getHeap();
        for (Value val : this.symTable.getValues()) {
            if (val instanceof RefValue) {
                addresses.add(((RefValue) val).getAddress());
            }
        }
        // in addresses, we have all the addresses that are referenced by the symTable
        // we need to add the addresses that are referenced by the heap
        for (int i = 0; i < addresses.size(); i++) {
            Integer currentAddr = addresses.get(i);
            Value val = heapTable.get(currentAddr);
            if (val instanceof RefValue) {
                Integer nextAddr = ((RefValue) val).getAddress();
                if (!addresses.contains(nextAddr)) {
                    addresses.add(nextAddr);
                }
            }
        }
        return addresses;
    }

    public IStmt getStmt() {
        return originalProgram;
    }

    @Override
    public String toString() {
        return "Stack:\n" + this.exeStack.toString() + "\n" +
                "Symbolic table:\n" + this.symTable.toString() +
                "Out:\n" + this.out.toString() +
                "File table:\n" + this.fileTable.toString() +
                "Heap:\n" + this.heap.toString() + "\n";
    }
}
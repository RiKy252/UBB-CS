package Model;

import Model.ADTs.*;
import Model.Statements.IStmt;
import Model.Values.RefValue;
import Model.Values.Value;
import MyException.EmptyExecutionStackException;
import MyException.MyException;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class PrgState {
    private int id;
    private static int nextId = 1;
    private MyIStack<IStmt> exeStack;
    private MyIList<Value> out;
    private MyIDictionary<String, BufferedReader> fileTable;
    private IHeap<Integer, Value> heap;
    private MyIStack<MyIDictionary<String, Value>> symTableStack;
    private IProcTable procTable;
    IStmt originalProgram;

    public PrgState(MyIStack<IStmt> stack, MyIStack<MyIDictionary<String, Value>> symbolicTableStack, MyIList<Value> output, MyIDictionary<String, BufferedReader> fileTable, IHeap<Integer, Value> heap, IProcTable procTable, IStmt program) {
        synchronized (PrgState.class) {
            this.id = nextId;
            nextId++;
        }
        exeStack = stack;
        symTableStack = symbolicTableStack;
        if (symTableStack.isEmpty())
            symTableStack.push(new MyDictionary<>());
        out = output;
        this.fileTable = fileTable;
        originalProgram = program.deepcopy();
        this.heap = heap;
        this.procTable = procTable;
        stack.push(program);
    }

    public PrgState(IStmt program, IProcTable procTable) {
        this.exeStack = new MyStack<>();
        this.exeStack.push(program);
        this.symTableStack = new MyStack<>();
        symTableStack.push(new MyDictionary<>());
        this.out = new MyList<>();
        this.fileTable = new MyDictionary<>();
        this.heap = new Heap<>();
        this.procTable = procTable;
    }

    public void init() {
        this.exeStack = new MyStack<IStmt>();
        symTableStack.push(new MyDictionary<String, Value>());
        this.out = new MyList<Value>();
        exeStack.push(this.originalProgram);
        originalProgram = originalProgram.deepcopy();
    }

    public MyIStack<IStmt> getStack() {
        return exeStack;
    }

    public MyIList<Value> getOut() {
        return out;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
         return fileTable;
    }

    public MyIStack<MyIDictionary<String, Value>> getSymTableStack() { return symTableStack; }

    public IHeap<Integer, Value> getHeap() { return heap; }

    public IProcTable getProcTable() { return this.procTable; }

    public MyIDictionary<String, Value> getSymTable() {
        if (symTableStack.isEmpty())
            return new MyDictionary<>();
        return symTableStack.peek();
    }

    public List<Integer> getReachableAddresses() {
        List<Integer> addresses = new ArrayList<>();
        Map<Integer, Value> heapTable = this.heap.getHeap();
        MyIDictionary<String, Value> symTable = this.getSymTable();
        for (Value val : symTable.getValues()) {
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
        return "ID: " + this.id + "\n" +
                "Stack:\n" + this.exeStack.toString() + "\n" +
                "Symbolic table:\n" + this.symTableStack.toString() +
                "Out:\n" + this.out.toString() +
                "File table:\n" + this.fileTable.toString() +
                "Heap:\n" + this.heap.toString() + "\n";
    }

    public boolean isNotCompleted() {
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStepExec() throws EmptyExecutionStackException {
        if (exeStack.isEmpty())
            throw new EmptyExecutionStackException("Program state stack is empty");
        IStmt currentStatement = exeStack.pop();
        return currentStatement.execute(this);
    }

    public int getId() {
        return this.id;
    }

    public MyIStack<MyIDictionary<String, Value>> copySymTable() {
        MyStack<MyIDictionary<String, Value>> copySym = new MyStack<>();
        for(MyIDictionary<String, Value> s : symTableStack.toList()) {
            try {
                copySym.push(s.copy());  // Ensure deep copying
            } catch (MyException e) {
                throw new RuntimeException("Error copying symbol table: " + e.getMessage());
            }
        }
        return copySym;
    }


}

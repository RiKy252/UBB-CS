package Model;

import Model.ADTs.*;
import Model.Statements.IStmt;
import Model.Values.StringValue;
import Model.Values.Value;
import com.sun.jdi.IntegerValue;

import java.io.BufferedReader;

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

package Model.ADTs;

import Model.Statements.IStmt;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ProcTable implements IProcTable {
    private Map<String, Pair<List<String>, IStmt>> procTable;
    public ProcTable() {
        this.procTable = new ConcurrentHashMap<>();
    }
    @Override
    public Map<String, Pair<List<String>, IStmt>> getProcedureTable() {
        return this.procTable;
    }
    @Override
    public void put(String procName, Pair<List<String>, IStmt> value) {
        this.procTable.put(procName, value);
    }
    @Override
    public Pair<List<String>, IStmt> get(String procName) {
        return this.procTable.get(procName);
    }
}

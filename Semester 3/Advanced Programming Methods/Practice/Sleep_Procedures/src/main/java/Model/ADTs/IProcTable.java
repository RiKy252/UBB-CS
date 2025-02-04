package Model.ADTs;

import Model.Statements.IStmt;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface IProcTable {
    Map<String, Pair<List<String>, IStmt>> getProcedureTable();
    void put(String procName, Pair<List<String>, IStmt> value);
    Pair<List<String>, IStmt> get(String procName);
}

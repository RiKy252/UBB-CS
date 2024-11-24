package Model.ADTs;

import MyException.MyException;

import java.util.List;

public interface MyIFileTable {
    void openFile(String name) throws MyException;
    void closeFile(String name) throws MyException;
    int readFile(String name) throws MyException;
    String toString();
    List<String> getFiles();
}

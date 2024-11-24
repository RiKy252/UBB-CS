package Model.ADTs;

import Model.Values.StringValue;
import MyException.MyException;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public class MyFileTable implements MyIFileTable {
    MyIDictionary<String, BufferedReader> data;
    public MyFileTable() {
        this.data = new MyDictionary<>();
    }
    @Override
    public void openFile(String name) throws MyException {
        if (data.isDefined(name)) {
            throw new MyException("File already opened!");
        }
        try {
            BufferedReader reader = new BufferedReader(new FileReader(name));
            data.update(name, reader);
        } catch (Exception e) {
            throw new MyException("Error opening file!");
        }
    }
    @Override
    public void closeFile(String name) throws MyException {
        try {
            BufferedReader reader = this.data.lookup(name);
            reader.close();
            this.data.remove(name);
        } catch (IOException e) {
            throw new MyException("Error closing file!");
        } catch (MyException e) {
            throw new MyException("File could not be found!");
        }
    }
    @Override
    public int readFile(String name) throws MyException {
        BufferedReader reader = null;
        try {
            reader = data.lookup(name);
        } catch (MyException e) {
            throw new MyException("Cannot read file " + name);
        }
        String content;
        try {
            content = reader.readLine();
        } catch (IOException e) {
            throw new MyException("Invalid line in file!");
        }
        if (content == null) {
            content = "0";
        }
        int answer = 0;
        try {
            answer = Integer.parseInt(content);
        } catch (MyException e) {
            throw new MyException("Invalid line in file");
        }
        return answer;
    }
    @Override
    public String toString() {
        StringBuilder buffer = new StringBuilder();
        for (String name : this.data.getAllKeys()) {
            buffer.append(name).append("\n");
        }
        return buffer.toString();
    }
    @Override
    public List<String> getFiles() {
        return data.getAllKeys();
    }
}

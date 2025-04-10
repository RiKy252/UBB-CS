package com.toylang.toylanguagegui;

import Controller.Controller;
import Model.ADTs.IHeap;
import Model.ADTs.ILockTable;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIList;
import Model.PrgState;
import Model.Statements.IStmt;
import Model.Values.Value;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.stream.Collectors;

public class MainWindowController {
    Controller controller;
    IHeap<Integer, Value> heap;
    MyIList out;
    MyIDictionary fileTable;
    ILockTable lockTable;
    public MainWindowController(Controller controller) {
        this.controller = controller;
    }

    @FXML
    private Label programStatesLabel;

    @FXML
    private ListView<Integer> programStatesListView;

    @FXML
    private ListView<IStmt> executionStackListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<String> outListView;

    @FXML
    private TableView<Pair<Integer, Value>> heapTableTableView;

    @FXML
    private TableColumn<Pair<Integer, Value>, Integer> heapAddressesColumn;

    @FXML
    private TableColumn<Pair<Integer, Value>, String> heapValuesColumn;

    @FXML
    private TableView<Pair<String, Value>> symbolTableTableView;

    @FXML
    private TableColumn<Pair<String, Value>, String> symbolNameColumn;

    @FXML
    private TableColumn<Pair<String, Value>, String> symbolValueColumn;

    @FXML
    private TableView<Pair<Integer, Integer>> lockTableView;

    @FXML
    private TableColumn<Pair<Integer, Integer>, Integer> lockTableAddressColumn;

    @FXML
    private TableColumn<Pair<Integer, Integer>, Integer> lockTablePrgstateColumn;

    @FXML
    private Button oneStepButton;

    public void refresh() {
        // Integer selectedProgram = 0;
        programStatesListView.getItems().clear();
        heapTableTableView.getItems().clear();
        outListView.getItems().clear();
        fileTableListView.getItems().clear();
        executionStackListView.getItems().clear();
        symbolTableTableView.getItems().clear();
        lockTableView.getItems().clear();

        programStatesLabel.setText("Program States: " + controller.getPrograms().size());
        controller.getPrograms().forEach(p -> programStatesListView.getItems().add(p.getId()));

        if (controller.getPrograms().size() > 0) {
            heap = controller.getPrograms().getFirst().getHeap();
            out = controller.getPrograms().getFirst().getOut();
            fileTable = controller.getPrograms().getFirst().getFileTable();
            lockTable = controller.getPrograms().getFirst().getLockTable();
        }

        if (heap != null) {
            heap.getHeap().forEach((Integer, Value) -> heapTableTableView.getItems().add(new Pair<>(Integer, Value)));
        }

        if (lockTable != null) {
            lockTable.getLockTable().forEach((k, v) -> lockTableView.getItems().add(new Pair<>(k, v)));
        }

        if (out != null) {
            out.getOutAsList().forEach(v -> outListView.getItems().add(v.toString()));
        }
        if (fileTable != null) {
            fileTable.getAllKeys().forEach(k -> fileTableListView.getItems().add(k.toString()));
        }
        PrgState current;
        try {
            current = controller.getPrograms().getFirst();
            current.getSymTable().toMap().forEach((k, v) -> symbolTableTableView.getItems().add(new Pair<>(k, v)));
            List<IStmt> stmtList = current.getStack().toList();
            for (int i = stmtList.size() - 1; i >= 0; i--) {
                executionStackListView.getItems().add(stmtList.get(i));
            }
            programStatesListView.onMouseClickedProperty().setValue(mouseEvent -> {
                int selectedProgram = programStatesListView.getSelectionModel().getSelectedItem();
                PrgState selectedState = controller.getPrograms().stream().filter(p -> p.getId() == selectedProgram).findFirst().get();
                symbolTableTableView.setItems(FXCollections.observableList(current.getSymTable().toMap().entrySet().stream()
                        .map(e -> new Pair<>(e.getKey(), e.getValue()))
                        .collect(Collectors.toList())));
                List<IStmt> selectedStmtList = selectedState.getStack().toList();
                executionStackListView.getItems().clear();
                for (int i = selectedStmtList.size() - 1; i >= 0; i--) {
                    executionStackListView.getItems().add(selectedStmtList.get(i));
                }
            });
        } catch (NoSuchElementException e) {
            return ;
        } finally {
            this.programStatesListView.refresh();
            this.heapTableTableView.refresh();
            this.outListView.refresh();
            this.fileTableListView.refresh();
            this.symbolTableTableView.refresh();
            this.executionStackListView.refresh();
            this.lockTableView.refresh();
        }
    }

    @FXML
    public void initialize() {
        this.heapAddressesColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        this.heapValuesColumn.setCellValueFactory(p -> new SimpleObjectProperty<>(  p.getValue().getValue().toString()));
        this.symbolNameColumn.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getKey()));
        this.symbolValueColumn.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getValue().toString()));
        this.lockTableAddressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        this.lockTablePrgstateColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getValue()).asObject());
        this.refresh();

        oneStepButton.setOnAction(actionEvent -> {
            try {
                controller.oneStep();
            } catch (Exception e) {
                Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage());
                alert.show();
            }
            this.refresh();
        });
    }

}
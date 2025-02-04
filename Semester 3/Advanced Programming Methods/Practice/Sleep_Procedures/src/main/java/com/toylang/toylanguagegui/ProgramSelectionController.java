package com.toylang.toylanguagegui;

import Controller.Controller;
import Model.ADTs.IProcTable;
import Model.ADTs.MyDictionary;
import Model.ADTs.ProcTable;
import Model.Statements.IStmt;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;

public class ProgramSelectionController {
    Controller controller;
    MainWindowController mainWindowController;
    IProcTable procTable = new ProcTable();

    @FXML
    private ListView<IStmt> availableProgramsListView;

    @FXML
    private Button selectProgramButton;

    public ProgramSelectionController(Controller c, MainWindowController mWC) {
        this.controller = c;
        this.mainWindowController = mWC;
    }

    @FXML
    public void initialize() {
        Controller.addProcedures(procTable);
        availableProgramsListView.setItems(FXCollections.observableList(controller.allExamples()));
        selectProgramButton.setOnAction(actionEvent -> {
            try {
                int index = availableProgramsListView.getSelectionModel().getSelectedIndex();
                if (index < 0) {
                    System.out.println("No program selected");
                } else if (index >= controller.allExamples().size()) {
                    System.out.println("Invalid program selected");
                } else {
                    controller.allExamples().get(index).typeCheck(new MyDictionary<>());
                    controller.setProgram(controller.allExamples().get(index), procTable);
                    mainWindowController.refresh();
                }
            } catch (Exception e) {
                Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage());
                alert.show();
            }
        });
        mainWindowController.refresh();
    }

}
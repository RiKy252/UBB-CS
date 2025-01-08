package com.toylang.toylanguagegui;

import Controller.Controller;
import Repository.Repo;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MainWindow extends Application {

    static Controller controller;

    public static void setController(Controller controller) {
        MainWindow.controller = controller;
    }

    public void run(String[] args){
        launch(args);
    }


    public static void main(String[] args) {
        MainWindow.setController(new Controller(new Repo("log.txt")));
        MainWindow view = new MainWindow();
        view.run(args);

    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        FXMLLoader mainWindowLoader = new FXMLLoader();
        mainWindowLoader.setLocation(getClass().getResource("MainWindow.fxml"));
        mainWindowLoader.setControllerFactory(c -> new MainWindowController(controller));

        Parent mainWindowRoot = mainWindowLoader.load();
        MainWindowController mainWindowController = mainWindowLoader.getController();

        primaryStage.setTitle("Toy Language");
        primaryStage.setScene(new Scene(mainWindowRoot));
        primaryStage.show();

        Stage secondaryStage = new Stage();
        FXMLLoader programSelectionLoader = new FXMLLoader();
        programSelectionLoader.setLocation(getClass().getResource("ProgramSelection.fxml"));
        programSelectionLoader.setControllerFactory(c -> new ProgramSelectionController(controller, mainWindowController));

        Parent programSelectionRoot = programSelectionLoader.load();
        ProgramSelectionController programSelectionController = programSelectionLoader.getController();

        secondaryStage.setTitle("Program Selection");
        secondaryStage.setScene(new Scene(programSelectionRoot));
        secondaryStage.show();
    }
}

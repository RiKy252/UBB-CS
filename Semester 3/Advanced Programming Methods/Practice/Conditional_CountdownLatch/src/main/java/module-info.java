module com.toylang.toylanguagegui {
    requires javafx.controls;
    requires javafx.fxml;
    requires jdk.jdi;
    requires java.desktop;

    opens com.toylang.toylanguagegui to javafx.fxml;
    exports com.toylang.toylanguagegui;
}
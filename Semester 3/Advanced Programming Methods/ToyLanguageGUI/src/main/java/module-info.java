module com.toylang.toylanguagegui {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.xml;
    requires jdk.jdi;

    opens com.toylang.toylanguagegui to javafx.fxml;
    exports com.toylang.toylanguagegui;
}
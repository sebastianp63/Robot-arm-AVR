package sample;

import javafx.application.Platform;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;

public class Controller {

    private final Serial serial= new Serial();
    private ChangeListener<String> listener;
    private final BooleanProperty connection=new SimpleBooleanProperty(false);
    boolean statusConnection = false;

    @FXML
    Button btnScan;
    @FXML
    Button btnConnect;
    @FXML
    ComboBox<String> portList = new ComboBox<>();
    @FXML
    Label status;
    @FXML
    Label receiveLabel;
    @FXML
    Label controlLabel;
    @FXML
    Button btn1;
    @FXML
    Button btn2;
    @FXML
    Button btn3;
    @FXML
    Button btn4;
    @FXML
    Button btn5;
    @FXML
    Button btn6;
    @FXML
    Button btn7;
    @FXML
    Button btn8;
    @FXML
    ToolBar toolBar;
    @FXML
    HBox hBox;
    @FXML
    AnchorPane anchorPane;
    @FXML
    BorderPane root;

    private final String STYLE_NORMAL = "-fx-background-color: transparent; -fx-padding: -5, -5, -5, -5;";
    private final String STYLE_PRESSED = "-fx-background-color: transparent; -fx-padding:  -2 -5 -2 -2;";

    private final String STYLE_NORMAL_ = "-fx-background-color: transparent; -fx-padding: -10, -10, -10, -10;";
    private final String STYLE_PRESSED_ = "-fx-background-color: transparent; -fx-padding:  -9 -10 -9 -9;";


    public void initialize() {
        controlLabel.setText("Conrtol: W S A D ARROW KEY");
        receiveLabel.setText("STATUS: STOP" );
        listener=(ov, t, t1) -> {
        Platform.runLater(() -> receiveLabel.setText("STATUS: " + serial.getLine())); };
        serial.getStringProperty().addListener(listener);

        btn1.setOnMousePressed( e-> {btn1.setStyle(STYLE_PRESSED_);  serial.sendCh('w');} );
        btn1.setOnMouseReleased(e-> {btn1.setStyle(STYLE_NORMAL_);   serial.sendCh('j');} );
        btn2.setOnMousePressed( e-> {btn2.setStyle(STYLE_PRESSED_);  serial.sendCh('z');} );
        btn2.setOnMouseReleased(e-> {btn2.setStyle(STYLE_NORMAL_);   serial.sendCh('h');} );
        btn3.setOnMousePressed( e-> {btn3.setStyle(STYLE_PRESSED_);  serial.sendCh('e');} );
        btn3.setOnMouseReleased(e-> {btn3.setStyle(STYLE_NORMAL_);   serial.sendCh('j');} );
        btn4.setOnMousePressed( e-> {btn4.setStyle(STYLE_PRESSED_);  serial.sendCh('x');} );
        btn4.setOnMouseReleased(e-> {btn4.setStyle(STYLE_NORMAL_);   serial.sendCh('h');} );
        btn5.setOnMousePressed( e-> {btn5.setStyle(STYLE_PRESSED);   serial.sendCh('a');} );
        btn5.setOnMouseReleased(e-> {btn5.setStyle(STYLE_NORMAL);    serial.sendCh('g');} );
        btn6.setOnMousePressed( e-> {btn6.setStyle(STYLE_PRESSED);   serial.sendCh('l');} );
        btn6.setOnMouseReleased(e-> {btn6.setStyle(STYLE_NORMAL);    serial.sendCh('l');} );
        btn7.setOnMousePressed( e-> {btn7.setStyle(STYLE_PRESSED);   serial.sendCh('s');} );
        btn7.setOnMouseReleased(e-> {btn7.setStyle(STYLE_NORMAL);    serial.sendCh('g');} );
        btn8.setOnMousePressed( e-> {btn8.setStyle(STYLE_PRESSED);   serial.sendCh('p');} );
        btn8.setOnMouseReleased(e-> {btn8.setStyle(STYLE_NORMAL);    serial.sendCh('p');} );

        status.setText("Not connected");
        ObservableList<String> port =  serial.getAvailablePorts();
        System.out.println(port);
        portList.setItems(port);

        btnScan.setOnAction(e->{
            ObservableList<String> ports =  serial.getAvailablePorts();
            System.out.println(ports);
            portList.setItems(ports);
        });

        btnConnect.setOnAction(e -> {
                    if (!statusConnection) {
                        String chosenPort = portList.getSelectionModel().getSelectedItem();
                        startSerial(chosenPort);
                        if (serial.getSerialPort().isOpened()) {
                            statusConnection = true;
                            btnConnect.setText("DISCONNECT");
                            status.setText("Connected to: " + chosenPort.toString());
                        }
                    } else if (statusConnection) {
                        stopSerial();
                        statusConnection = !statusConnection;
                        btnConnect.setText("CONNECT");
                        status.setText("Not connected");
                    }
                });

            root.setOnKeyPressed(event -> {
                if (statusConnection) {
                    switch (event.getCode()) {
                        case W:
                            serial.sendCh('w');
                            break;
                        case S:
                          serial.sendCh('e');
                            break;
                        case A:
                             serial.sendCh('a');
                            break;
                        case D:
                            serial.sendCh('s');
                            break;
                        case UP:
                             serial.sendCh('z');
                            break;
                        case DOWN:
                             serial.sendCh('x');
                            break;
                        case LEFT:
                             serial.sendCh('l');
                            break;
                        case RIGHT:
                            serial.sendCh('p');
                            break;
                    }
                }
            });

            root.setOnKeyReleased(event -> {
                if (statusConnection) {
                    switch (event.getCode()) {
                        case W:
                        serial.sendCh('j');
                            break;
                        case S:
                          serial.sendCh('j');
                            break;
                        case A:
                             serial.sendCh('g');
                            break;
                        case D:
                            serial.sendCh('g');
                            break;
                        case UP:
                            serial.sendCh('h');
                            break;
                        case DOWN:
                            serial.sendCh('h');
                            break;

                    }
                }

        });

        btnScan.disableProperty().bind(connection);
        portList.disableProperty().bind(connection);

        toolBar.getStyleClass().add("toolBar");
        hBox.getStyleClass().add("hBox");
    }

    private void startSerial(String port){
        serial.connect(port);
        connection.set(!serial.getPortName().isEmpty());
    }

    private void stopSerial(){
        if(connection.get()){
            serial.disconnect();
            connection.set(false);
        }
    }
}











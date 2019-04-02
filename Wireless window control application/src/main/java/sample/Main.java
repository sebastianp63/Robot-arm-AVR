package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
    Serial serial = new Serial();

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("sample.fxml"));
        primaryStage.setTitle("Hello World");
        primaryStage.setResizable(false);
        Scene scene = new Scene(root, 790, 520);
        scene.getStylesheets().add("Style.css");
        primaryStage.setScene(scene);
        primaryStage.show();

    }

    @Override
    public void stop(){
        System.out.println("Closing port" );
        serial.disconnect();



    }
    public static void main(String[] args) {
        launch(args);
    }
}

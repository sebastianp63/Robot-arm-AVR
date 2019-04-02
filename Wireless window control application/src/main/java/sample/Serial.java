package sample;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortException;
import jssc.SerialPortList;
import java.util.logging.Level;
import java.util.logging.Logger;

import static jssc.SerialPort.MASK_RXCHAR;

/**
 * Created by Sebastian on 01.05.2017.
 */
public class Serial {

    private static SerialPort serialPort;
    private final  StringProperty line=new SimpleStringProperty("");
    private StringBuilder sb= new StringBuilder();

    public String getLine() {return line.get();}
    public StringProperty getStringProperty(){return line;}

    public void setSerialPort(SerialPort serialPort) {
        this.serialPort = serialPort;
    }
    public String getPortName(){
        return serialPort!=null?serialPort.getPortName():"";
    }
    public SerialPort getSerialPort() {
        return serialPort;
    }

    public ObservableList<String> getAvailablePorts(){
        ObservableList<String> list = FXCollections.observableArrayList();
        String[] portsName = SerialPortList.getPortNames();
        for(String s: portsName){list.add(s);}
        return list;
    }

    public boolean connect(String port){

        boolean success = false;
          SerialPort serialPort = new SerialPort(port);
        try {
            System.out.println("Connecting to: " + serialPort.getPortName());
            serialPort.openPort();
            serialPort.setParams(
                    SerialPort.BAUDRATE_9600,

                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
            serialPort.setEventsMask(MASK_RXCHAR);

            serialPort.addEventListener((SerialPortEvent serialPortEvent) -> {
                if(serialPortEvent.isRXCHAR()){
                    try {
                        sb.append(serialPort.readString(serialPortEvent.getEventValue()));
                         String st = sb.toString();
                        if(st.endsWith("\r\n")){
                            line.set(st.substring(0,st.indexOf("\r\n")));

                          sb = new StringBuilder();
                        }
                    } catch (SerialPortException ex) {
                       Logger.getLogger(getClass().getName())
                            .log(Level.SEVERE, null, ex);
                    }
                }
            });
            this.serialPort = serialPort;
            success = true;
        } catch (SerialPortException ex) {
            Logger.getLogger(getClass().getName())
                    .log(Level.SEVERE, null, ex);
            System.out.println("SerialPortException: " + ex.toString());
        }
        return success;
    }

    public void sendS(String text){
        try{
            serialPort.writeBytes(text.getBytes());
        } catch(SerialPortException e){
            System.out.println("ERROR: " + text + ": " + e.toString());
        }
    }

    public void sendCh(char c){
        try{
            serialPort.writeByte((byte)c);
        } catch(SerialPortException e){
            System.out.println("ERROR: " + c + ": " + e.toString());
        } catch(NullPointerException e){
            System.out.println("ERROR: You have to connect with device ");
        }
    }

    public void disconnect(){
        if(serialPort!=null){
            try{
                serialPort.removeEventListener();
                if(serialPort.isOpened()){
                    serialPort.closePort();
                }
            } catch (SerialPortException e){
                System.out.println("ERROR closing port: " + e.toString());
            }
            System.out.println("Disconnected");
        }
    }
}





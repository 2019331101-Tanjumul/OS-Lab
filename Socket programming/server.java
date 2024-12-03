
import java.io.*;
import java.net.*;
import java.util.*;

import javax.print.attribute.standard.Severity;

public class server{
    public static void main(String[] args) throws IOException{
        ServerSocket serverSocket = new ServerSocket(22221);
        System.out.println("Server Started");

        while(true){
            Socket socket = serverSocket.accept();
            System.out.println("Client connected");

            //new server thread start
            new ServerThread(socket);

            
        }
    }
}

class ServerThread implements Runnable {

    Socket clientSocket;
    Thread t;

    ServerThread(Socket clientSocket){
        this.clientSocket = clientSocket;
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run(){

        try{
            ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
            ObjectOutputStream oss = new ObjectOutputStream(clientSocket.getOutputStream());

            while(true){
                try{
                    Object cMsg = ois.readObject();
                    if(cMsg == null)break;
                    System.out.println("From Client: "+(String)cMsg);
    
                    String serverMsg = (String)cMsg;
                    serverMsg = serverMsg.toUpperCase();
    
                    oss.writeObject(serverMsg);
                }catch(ClassNotFoundException e){
                    e.printStackTrace();
                }
            }
        }catch(IOException e){
            e.printStackTrace();
        }
        try {
            clientSocket.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

}
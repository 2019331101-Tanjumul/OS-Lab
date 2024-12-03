
import java.io.*;
import java.net.*;
import java.util.*;
public class client{
    public static void main(String[] args) throws IOException{
        System.out.println("Client Started");
        Socket socket = new Socket("192.168.0.243",22221);
        System.out.println("Client Connected");

        
        ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());

        while(true){
            Scanner sc = new Scanner(System.in);
            
            String message = sc.nextLine();
            System.out.println(message);
            if(message.equals("Exit")){
                break;
            }

            oos.writeObject(message);
            try{
                Object fromServer = ois.readObject();
                System.out.println("From Server: " + (String)fromServer);
            }catch(ClassNotFoundException e){
                e.printStackTrace();
            }
        }
        
        socket.close();
    }
}
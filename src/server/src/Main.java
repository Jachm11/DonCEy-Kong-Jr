import java.net.*;
import java.io.*;
  

public class Main {

    private static final int PORT = 1108;

    public static void main(String[] args) {
 
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
 
            System.out.println("Server is listening on port " + PORT);
 
            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("New client connected");
 
                new ServerThread(socket).start();
            }
 
        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
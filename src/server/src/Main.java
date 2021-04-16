import java.net.*;
import java.io.*;
  

public class Main {

    private static final int PORT = 1108;
 
    public static void main(String[] args) throws IOException {
        ServerSocket listener = new ServerSocket(PORT);

        System.out.println("{Server} Waiting for a connection");
        Socket client = listener.accept();
        System.out.println("{Server} Connected to client!");

        PrintWriter out = new PrintWriter(client.getOutputStream(),true);
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));

        try{
            while(true){
                String request = in.readLine();
                System.out.println("{Server} client says: "+request)
            }
        }finally{
            out.close();
            in.close();
        }
      
    }
}
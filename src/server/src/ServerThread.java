import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * This thread is responsible to handle client connection.
 *
 * @author www.codejava.net
 */
public class ServerThread extends Thread {
    private Socket socket;
 
    public ServerThread(Socket socket) {
        this.socket = socket;
    }

    public boolean testImput(String input){
        if (input == null){
            System.out.println("Null");
            return true;
        }
        else{
            if (input.equals("bye")){
                return false;
            }
        }
        //System.out.println("Not null,not bye");
        return true;

    }
 
    public void run() {
        try {
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
 
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);
 
            String text;
 
            do {
                text = reader.readLine();

                writer.println("LIVES:2;POINTS:120;70,570;1,200,400:2,800,380;580,490");
 
            } while (testImput(text));
            socket.close();

        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
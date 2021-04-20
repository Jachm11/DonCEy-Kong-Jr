package ServerApp;

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
            return false;
        }
        else{
            if (input.equals("bye")){
                return false;
            }
        }
        return true;

    }
 
    public void run() {
        try {
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
 
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);
            int i =0;
            String text;
 
            do {
                text = reader.readLine();
                System.out.println(text);
                if(text.equals("Tecla"))
                {
                    writer.println(App.juego.game_str()); 

                }
                else if(text.equals("Tecla w"))
                {
                    App.juego.move_player("w");
                    writer.println(App.juego.game_str());

                }
                else if(text.equals("Tecla a"))
                {
                    App.juego.move_player("a");
                    writer.println(App.juego.game_str());

                }
                else if(text.equals("Tecla s"))
                {
                    App.juego.move_player("s");
                    writer.println(App.juego.game_str());

                }
                else if(text.equals("Tecla d"))
                {
                    App.juego.move_player("d");
                    writer.println(App.juego.game_str());

                }
                else{
                    writer.println(App.juego.game_str());
                }
                
            } while (testImput(text));
            socket.close();

        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
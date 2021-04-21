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
    private ServerHandler myHandler;
    private Boolean imPlayer;
 
    public ServerThread(Socket socket,ServerHandler myHandler) {
        this.socket = socket;
        this.myHandler = myHandler;
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
            String text;
 
            do {
                text = reader.readLine();
                System.out.println(text);
                if(text.equals("Tecla"))
                {
                    writer.println(myHandler.miJuego.game_str()); 

                }
                else if(text.equals("Tecla w"))
                {
                    myHandler.miJuego.move_player("w");
                    writer.println(myHandler.miJuego.game_str());

                }
                else if(text.equals("Tecla a"))
                {
                    myHandler.miJuego.move_player("a");
                    writer.println(myHandler.miJuego.game_str());

                }
                else if(text.equals("Tecla s"))
                {
                    myHandler.miJuego.move_player("s");
                    writer.println(myHandler.miJuego.game_str());

                }
                else if(text.equals("Tecla d"))
                {
                    myHandler.miJuego.move_player("d");
                    writer.println(myHandler.miJuego.game_str());
                }
                else if(text.equals("player"))
                {
                    if (myHandler.player == true){
                        writer.println("pdenied");
                        myHandler.count = myHandler.count - 1;
                    }else{
                        myHandler.player = true;
                        imPlayer = true;
                        writer.println(myHandler.miJuego.game_str());
                    }
                    
                }
                else if(text.equals("spectator"))
                {
                    if(myHandler.count == 2 && myHandler.player == false){
                        writer.println("sdenied");
                        myHandler.count = 2;
                    }else{
                        writer.println(myHandler.miJuego.game_str());
                    }
                }

            } while (testImput(text));
            myHandler.count = myHandler.count - 1;
            if(imPlayer){
                myHandler.player = false;
            }
            socket.close();

        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
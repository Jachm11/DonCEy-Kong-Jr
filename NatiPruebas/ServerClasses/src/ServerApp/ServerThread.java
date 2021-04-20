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
            int i =0;
            String text;
 
            do {
                text = reader.readLine();
                System.out.println(text);
                if(text.equals("Tecla"))
                {
                    writer.println(App.juego.game_str()); 

                }
                if(text.equals("Tecla w"))
                {
                    App.juego.move_player("w");
                    writer.println(App.juego.game_str());

                }
                if(text.equals("Tecla a"))
                {
                    App.juego.move_player("a");
                    writer.println(App.juego.game_str());

                }
                if(text.equals("Tecla s"))
                {
                    App.juego.move_player("s");
                    writer.println(App.juego.game_str());

                }
                if(text.equals("Tecla d"))
                {
                    App.juego.move_player("d");
                    writer.println(App.juego.game_str());

                }
                else{
                    writer.println(App.juego.game_str());
                }
                /*if (i == 0 ){
                    writer.println("LIVES:2;POINTS:120;70,570;1,200,400:2,800,380;580,490");
                    i = i + 1 ;
                }
                else if (i == 1){
                    writer.println("LIVES:2;POINTS:125;70,580;1,200,410:2,800,370;580,490");
                    i = i + 1 ;
                }
                else if (i == 2){
                    writer.println("LIVES:1;POINTS:130;70,590;1,200,420:2,800,360;580,490");
                    i = i + 1 ;
                }
                else if (i == 3){
                    writer.println("LIVES:2;POINTS:120;70,600;1,200,430:2,800,350;580,490");
                    i = i + 1 ;
                }
                else if (i == 4){
                    writer.println("LIVES:2;POINTS:120;70,620;1,200,440:2,800,340;580,490");
                    i = i + 1 ;
                }
                else if (i == 5){
                    writer.println("LIVES:2;POINTS:120;700,350;2,800,380;580,490");
                    i = i + 1 ;
                }
                else if (i == 6){
                    writer.println("LIVES:1;POINTS:120;70,570;1,200,450:2,800,330;580,490:280,490:1000,290");
                    i = i + 1 ;
                }
                else if (i == 7){
                    writer.println("LIVES:0;POINTS:120;70,570;1,200,400:2,800,320;580,490");
                    i = 0;
                }*/
                
 
            } while (testImput(text));
            socket.close();

        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
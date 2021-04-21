
package ServerApp;
import java.awt.event.*;
import javax.swing.*;
public class App extends JFrame implements ActionListener
{

    //private static final int PORT = 1108;
    // JTextField
    static JTextField t;
 
    // JFrame
    static JFrame f;
 
    // JButton
    static JButton b;
    static JButton b2;
 
    // label to display text
    static JLabel l;

    static Juego juego;
    static Juego juego2;

    static ServerHandler server1;
    static ServerHandler server2;
    // default constructor
    App()
    {
        juego = new Juego();
        juego2 = new Juego();
    }
    public static void main(String[] args)
    {  
        App te = new App();
        f = new JFrame("textfield");
        l = new JLabel("nothing entered");
        b = new JButton("submit");
        b2 = new JButton("go");
        
        b.addActionListener(te);
        b2.addActionListener(te);
        t = new JTextField(16);
        JPanel p = new JPanel();
        p.add(t);
        p.add(b);
        p.add(b2);
        p.add(l);
        f.add(p);
        f.setSize(300, 300);
 
        f.show();

        server1 = new ServerHandler(1108,juego);
        server2 = new ServerHandler(802,juego2);

        server1.start();
        server2.start();


    }
    @Override
    public void actionPerformed(ActionEvent e) {
        
        String s = e.getActionCommand();
        if (s.equals("submit")) 
        {
            // set the text of the label to the text of the field
            
            String accion = t.getText();
            System.out.println(accion);
            if (accion.equals("w"))
            {
                System.out.println("W");
                juego.move_player("w");
                

            }
            if (accion.equals("a"))
            {
                System.out.println("A");
                juego.move_player("a");

            }
            if (accion.equals("s"))
            {
                System.out.println("S");
                juego.move_player("s");

            }
            if (accion.equals("d"))
            {
                System.out.println("D");
                juego.move_player("d");

            }
            if(accion.split(",")[0].equals("Cenemigo"))
            {
                System.out.println("creando enemigo");
                String tipo = accion.split(",")[1];
                Integer liana = Integer.parseInt(accion.split(",")[2]);
                Integer porcentaje = Integer.parseInt(accion.split(",")[3]);
                juego.crear_cocodrilo(tipo, liana, porcentaje);
            }
            if(accion.split(",")[0].equals("Cfruta"))
            {
                System.out.println("creando fruta");
                Integer liana = Integer.parseInt(accion.split(",")[1]);
                Integer porcentaje = Integer.parseInt(accion.split(",")[2]);
                juego.crear_fruta(liana, porcentaje);
            }
            if(accion.split(",")[0].equals("Eenemigo"))
            {
                System.out.println("eliminando enemigo");
                String tipo = accion.split(",")[1];
                Integer liana = Integer.parseInt(accion.split(",")[2]);
                juego.eliminar_cocodrilo(tipo, liana);
            }
            if(accion.split(",")[0].equals("Efruta"))
            {
                System.out.println("eliminando fruta");
                Integer liana = Integer.parseInt(accion.split(",")[1]);
                Integer porcentaje = Integer.parseInt(accion.split(",")[2]);
                juego.eliminar_fruta(liana, porcentaje);
            }
            // set the text of field to blank
            t.setText("");
        }
        if (s.equals("go")) 
        {
            
            String game =juego.game_str();
            l.setText(game);
            System.out.println(game);
        }
        
    }  
    
}
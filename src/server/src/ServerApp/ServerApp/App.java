
package ServerApp;
import java.awt.*;
import java.awt.BorderLayout;
import java.io.*;
import javax.imageio.ImageIO;
import java.awt.event.*;
import java.awt.image.BufferedImage;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
public class App extends JFrame implements ActionListener
{

    //private static final int PORT = 1108;
    // JTextField
    static ImageIcon icon;
    static String gameObj[] = {"enemigo azul", "enemigo rojo", "fruta"};
    static String gameOpt[] = {"Crear", "Eliminar"};
    static Integer gameLiana[] = {1,2,3,4,5,6,7,8,9,10};
    static JTextField textJ1;
    static JTextField textJ2;
    
    static JComboBox c;
    // JFrame
    static JFrame frame;
 
    // JButton
    static JButton buttonJ1;
    static JButton buttonJ2;

    static JSlider sliderJ1;
    static JSlider sliderJ2;

    static JSpinner objJ1, optJ1, liaJ1;
    static JSpinner objJ2, optJ2, liaJ2;
 
    // label to display text
    static JLabel labelJ1;
    static JLabel labelJ2;

    static Juego juego1;
    static Juego juego2;

    static ServerHandler server1;
    static ServerHandler server2;
    // default constructor
    App()
    {
        juego1 = new Juego();
        juego2 = new Juego();
    }
    public static void main(String[] args)
    {  
        App app = new App();
        
        frame = new JFrame("textfield");
        JLabel label = new JLabel("en liana");
        labelJ1 = new JLabel("nothing entered");
        buttonJ1 = new JButton("submit");

        labelJ2 = new JLabel("nothing entered");
        buttonJ2 = new JButton("submit2");

        buttonJ1.addActionListener(app);
        buttonJ2.addActionListener(app);

        textJ1 = new JTextField(16);
        textJ2 = new JTextField(16);

        sliderJ1 = new JSlider(JSlider.VERTICAL);
        sliderJ1.setMinorTickSpacing(10);
        sliderJ1.setPaintTicks(true);
        sliderJ1.setPaintLabels(true);
        sliderJ1.setSnapToTicks(true);
        sliderJ1.setInverted(true);
        sliderJ1.setLabelTable(sliderJ1.createStandardLabels(10));

        sliderJ2 = new JSlider(JSlider.VERTICAL);
        sliderJ2.setMinorTickSpacing(10);
        sliderJ2.setPaintTicks(true);
        sliderJ2.setPaintLabels(true);
        sliderJ2.setSnapToTicks(true);
        sliderJ2.setInverted(true);
        sliderJ2.setLabelTable(sliderJ2.createStandardLabels(10));
        
        
        objJ1 = new JSpinner(new SpinnerListModel (gameObj));
        optJ1 = new JSpinner(new SpinnerListModel (gameOpt));
        liaJ1 = new JSpinner(new SpinnerNumberModel(1, 1, 10, 1));

        objJ2 = new JSpinner(new SpinnerListModel (gameObj));
        optJ2 = new JSpinner(new SpinnerListModel (gameOpt));
        liaJ2 = new JSpinner(new SpinnerNumberModel(1, 1, 10, 1));

        JPanel panelJ1 = new JPanel();
        panelJ1.add(optJ1);
        panelJ1.add(objJ1);
        panelJ1.add(label);
        panelJ1.add(liaJ1);
        panelJ1.add(sliderJ1);
        panelJ1.add(buttonJ1);
        panelJ1.add(labelJ1);

        JPanel panelJ2 = new JPanel();
        panelJ2.add(optJ2);
        panelJ2.add(objJ2);
        panelJ2.add(label);
        panelJ2.add(liaJ2);
        panelJ2.add(sliderJ2);
        panelJ2.add(buttonJ2);
        panelJ2.add(labelJ2);


        frame.add(panelJ1, BorderLayout.PAGE_START);
        frame.add(panelJ2, BorderLayout.PAGE_END);
        frame.setSize(1000, 600);
        frame.pack();
        frame.setVisible(true);

        server1 = new ServerHandler(1108,juego1);
        server2 = new ServerHandler(802,juego2);

        server1.start();
        server2.start();


    }
    public void stateChanged(ChangeEvent e){}
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        Integer x_liana = 0;
        Integer y_percentage = 0;
        String opcion = "";
        String objeto = "";
        String action = "";
        String s = e.getActionCommand();
        Juego juego = new Juego();
        if (s.equals("submit")) 
        {
            x_liana = (Integer)liaJ1.getValue();
            y_percentage = sliderJ1.getValue();
            opcion = (String)optJ1.getValue();
            objeto = (String)objJ1.getValue();
            action =  opcion  + "," + objeto + "," + x_liana + "," + y_percentage; 
            labelJ1.setText(action);
            juego = juego1;
        }
        if (s.equals("submit2")) 
        {
            x_liana = (Integer)liaJ2.getValue();
            y_percentage = sliderJ2.getValue();
            opcion = (String)optJ2.getValue();
            objeto = (String)objJ2.getValue();
            action =  opcion  + "," + objeto + "," + x_liana + "," + y_percentage; 
            labelJ2.setText(action);
            juego = juego2;
        }
            
            if (opcion.equals("Crear"))
            {
                if(objeto.equals("enemigo rojo"))
                {
                    System.out.println("creando enemigo rojo");
                    juego.crear_cocodrilo("1", x_liana, y_percentage);
                    

                }
                if(objeto.equals("enemigo azul"))
                {
                    System.out.println("creando enemigo azul");
                    juego.crear_cocodrilo("2", x_liana, y_percentage);
                    
                }
                if(objeto.equals("fruta"))
                {
                    System.out.println("creando fruta");
                    juego.crear_fruta(x_liana, y_percentage);
                    
                }
            }
            if (opcion.equals("Eliminar"))
            {
                if(objeto.equals("enemigo rojo"))
                {
                    System.out.println("eliminando enemigo rojo");
                    juego.eliminar_cocodrilo("1", x_liana);

                }
                if(objeto.equals("enemigo azul"))
                {
                    System.out.println("eliminando enemigo azul");
                    juego.eliminar_cocodrilo("2", x_liana);
                }
                if(objeto.equals("fruta"))
                {
                    juego.eliminar_fruta(x_liana, y_percentage);
                }
            }
        
        System.out.println("juego1: ");
        System.out.println(juego1.game_str());
        System.out.println("juego2: ");
        System.out.println(juego2.game_str());

        
        
    }
      
    
}
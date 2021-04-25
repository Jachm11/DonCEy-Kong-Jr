package ServerApp;

import java.net.MalformedURLException;
import java.net.URL;
import java.awt.*;
import java.awt.BorderLayout;
import java.io.*;
import javax.imageio.ImageIO;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import Game.*;
public class App extends Canvas implements ActionListener
{

    
    // JTextField
    private static App singleApp;

    private static Font f;
    static ImageIcon icon;
    static String gameObj[] = {"enemigo azul", "enemigo rojo", "fruta"};
    static String gameOpt[] = {"Crear", "Eliminar"};
    static Integer gameLiana[] = {1,2,3,4,5,6,7,8,9,10};
    static JTextField textJ1;
    static JTextField textJ2;
    static JFrame frame;
    static JButton buttonJ1;
    static JButton buttonJ2;
    static JSlider sliderJ1;
    static JSlider sliderJ2;
    static JSpinner objJ1, optJ1, liaJ1;
    static JSpinner objJ2, optJ2, liaJ2;
    static JLabel labelJ1;
    static JLabel labelJ2;
    static Juego juego1;
    static Juego juego2;

    static ServerHandler server1;
    static ServerHandler server2;

    App()
    {
        juego1 = new Juego();
        juego2 = new Juego();
        f = new Font("Impact", Font.PLAIN, 16);
    }

    public static App getInstance()
    {
        if(singleApp == null)
        {
            singleApp = new App();
        }
        return singleApp;
    }

    public static void main(String[] args) throws MalformedURLException, IOException
    {  
       
        App app = App.getInstance();
        ImageIcon icon = new ImageIcon("img/ico.png");
        frame = new JFrame("DonCEy Kong Jr. Server");
        frame.setIconImage(icon.getImage());
        JLabel label = new JLabel("en liana");
        label.setFont(f);
        label.setForeground(new Color(179,207,221));

        JLabel label2 = new JLabel("en liana");
        label2.setFont(f);
        label2.setForeground(new Color(179,207,221));

        buttonJ1 = new JButton("Enviar a J1");
        buttonJ1.setBackground(new Color(179,207,221));
        buttonJ1.setForeground(Color.BLACK);

        buttonJ2 = new JButton("Enviar a J2");
        buttonJ2.setBackground(new Color(179,207,221));
        buttonJ2.setForeground(Color.BLACK);

        buttonJ1.addActionListener(app);
        buttonJ2.addActionListener(app);

        

        sliderJ1 = new JSlider(JSlider.VERTICAL);
        sliderJ1.setBackground(Color.BLACK);
        sliderJ1.setForeground(new Color(179,207,221));
        sliderJ1.setMinorTickSpacing(10);
        sliderJ1.setPaintLabels(true);
        sliderJ1.setSnapToTicks(true);
        sliderJ1.setInverted(true);
        sliderJ1.setLabelTable(sliderJ1.createStandardLabels(10));
        sliderJ1.setFont(f);

        sliderJ2 = new JSlider(JSlider.VERTICAL);
        sliderJ2.setBackground(Color.BLACK);
        sliderJ2.setForeground(new Color(179,207,221));
        sliderJ2.setMinorTickSpacing(10);
        sliderJ2.setPaintLabels(true);
        sliderJ2.setSnapToTicks(true);
        sliderJ2.setInverted(true);
        sliderJ2.setLabelTable(sliderJ2.createStandardLabels(10));
        sliderJ2.setFont(f);
        
        
        objJ1 = new JSpinner(new SpinnerListModel (gameObj));
        setSpinnerProperties(objJ1, 8);

        optJ1 = new JSpinner(new SpinnerListModel (gameOpt));
        setSpinnerProperties(optJ1, 5);

        liaJ1 = new JSpinner(new SpinnerNumberModel(1, 1, 10, 1));
        setSpinnerProperties(liaJ1 , 3);

        objJ2 = new JSpinner(new SpinnerListModel (gameObj));
        setSpinnerProperties(objJ2, 8);

        optJ2 = new JSpinner(new SpinnerListModel (gameOpt));
        setSpinnerProperties(optJ2, 5);

        liaJ2 = new JSpinner(new SpinnerNumberModel(1, 1, 10, 1));
        setSpinnerProperties(liaJ2, 3);

        
        
        //JPanel panelJ1 = new JPanel();
        ImagePanel panelJ1 = new ImagePanel(
            new ImageIcon("img/fondo.jpg").getImage());
        panelJ1.setPreferredSize(new Dimension(1000, 350));
        panelJ1.setBorder(BorderFactory.createEmptyBorder(40,40,40,40));
        panelJ1.add(optJ1);
        panelJ1.add(objJ1);
        panelJ1.add(label);
        panelJ1.add(liaJ1);
        panelJ1.add(sliderJ1);
        panelJ1.add(buttonJ1);

        ImagePanel panelJ2 = new ImagePanel(
            new ImageIcon("img/fondo2.jpg").getImage());
        panelJ2.setPreferredSize(new Dimension(1000, 350));
        panelJ2.setBorder(BorderFactory.createEmptyBorder(40,40,40,40));
        panelJ2.add(optJ2);
        panelJ2.add(objJ2);
        panelJ2.add(label2);
        panelJ2.add(liaJ2);
        panelJ2.add(sliderJ2);
        panelJ2.add(buttonJ2);

        
        
        
        
        frame.add(panelJ1, BorderLayout.NORTH);
        frame.add(panelJ2, BorderLayout.CENTER);
        frame.setPreferredSize(new Dimension(1000, 700));
        frame.pack();
        frame.setVisible(true);

        server1 = new ServerHandler(1108,juego1);
        server2 = new ServerHandler(802,juego2);

        server1.start();
        server2.start();


    }
    public static void setSpinnerProperties(JSpinner spinner, Integer width)
    {
        spinner.setFont(f);
        ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().setColumns(width);
        ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().setEditable(false);;
        spinner.getEditor().getComponent(0).setBackground(Color.BLACK);
        spinner.getEditor().getComponent(0).setForeground(new Color(179,207,221));
    }
    public void stateChanged(ChangeEvent e){}
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        Integer x_liana = 0;
        Integer y_percentage = 0;
        String opcion = "";
        String objeto = "";
        String s = e.getActionCommand();
        Juego juego = new Juego();
        if (s.equals("Enviar a J1")) 
        {
            x_liana = (Integer)liaJ1.getValue();
            y_percentage = sliderJ1.getValue();
            opcion = (String)optJ1.getValue();
            objeto = (String)objJ1.getValue();
            juego = juego1;
        }
        if (s.equals("Enviar a J2")) 
        {
            x_liana = (Integer)liaJ2.getValue();
            y_percentage = sliderJ2.getValue();
            opcion = (String)optJ2.getValue();
            objeto = (String)objJ2.getValue();
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

class ImagePanel extends JPanel
{
private static final long serialVersionUID = 1L;
private Image image = null;
private int iWidth2;
private int iHeight2;

public ImagePanel(Image image)
{
    this.image = image;
    this.iWidth2 = image.getWidth(this)/2;
    this.iHeight2 = image.getHeight(this)/2;
}


public void paintComponent(Graphics g)
{
    super.paintComponent(g);
    if (image != null)
    {
        g.drawImage(image, 0, 0, null);
    }
}
}
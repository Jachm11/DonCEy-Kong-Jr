package Game;

import java.util.LinkedList;
import java.lang.Integer;

public class Juego 
{
    public Jugador jugador;
    Integer puntos;
    Integer vel;
    LinkedList<Cocodrilo> cocodrilos;
    LinkedList<Fruta> frutas;
    LinkedList<Liana> lianas ;

    public Juego()
    {
        puntos = 0;
        vel = 5;
        jugador = new Jugador();
        lianas =  new LinkedList<Liana>();
        cocodrilos =  new LinkedList<Cocodrilo>();
        frutas =  new LinkedList<Fruta>();
        crear_lianas();
    }
    public void move_player(String command)
    {
        Liana liana_actual = getLiana(jugador.liana);
        if(command == "w")//up
        {
            if(jugador.y >= liana_actual.getPosicion()[1])
            {
                jugador.move_up();
            }           

        }
        else if(command == "s")//down
        {
            if(jugador.y <= liana_actual.getPosicion()[2])
            {
                jugador.move_down();
            }
            
        }
        else if(command == "a")//left
        {
            Liana temp = getLiana(jugador.liana-1);
            if(((liana_actual.getId()>1) && (jugador.getY()>= temp.getPosicion()[1]) 
                                        && (jugador.getY()< temp.getPosicion()[2]))
                                        || (jugador.getY()<=145))
            {
                jugador.move_sideways(temp.getPosicion()[0], temp.getId());

            }

            
        }
        else if(command == "d")//right
        {
            Liana temp = getLiana(jugador.liana+1);
            if((liana_actual.getId()<10) && (jugador.getY()>= temp.getPosicion()[1]) 
                                         && (jugador.getY()< temp.getPosicion()[2]))
                                         
            {
                jugador.move_sideways(temp.getPosicion()[0], temp.getId());

            }
            
        }
    }
    public void crear_fruta(Integer liana, Integer y)
    {
        Liana temp= getLiana(liana);
        Integer y_inicial = temp.getPosicion()[1];
        Integer y_final = temp.getPosicion()[2];
        Integer newY =  y_inicial + ((y*(y_final - y_inicial))/100);
        Integer pos_y = (newY/10)*10;
        Fruta fruta = new Fruta(temp.getPosicion()[0],pos_y);
        frutas.add(fruta);
    }
    public void crear_cocodrilo(String tipo, Integer liana, Integer y)
    {
        if(tipo.equals("1"))
        {
            crear_rojo(liana, y);
            System.out.println("Creando cocodrilo rojo");
        }
        if(tipo.equals("2"))
        {
            crear_azul(liana, y);
            System.out.println("Creando cocodrilo azul");
        }
    }
    public void crear_rojo(Integer liana, Integer y)
    {
        Liana temp= getLiana(liana);
        Integer y_inicial = temp.getPosicion()[1];
        Integer y_final = temp.getPosicion()[2];
        Integer newY =  y_inicial + ((y*(y_final - y_inicial))/100);
        Integer pos_y = (newY/10)*10;
        
        Rojo rojo = new Rojo(temp.getPosicion()[0],pos_y,temp.getPosicion());
        rojo.setVelocidad(vel);
        cocodrilos.add(rojo);

       
    }
    public void crear_azul(Integer liana, Integer y)
    {
        Liana temp= getLiana(liana);
        Integer y_inicial = temp.getPosicion()[1];
        Integer y_final = temp.getPosicion()[2];
        Integer newY =  y_inicial + ((y*(y_final - y_inicial))/100);
        Integer pos_y = (newY/10)*10;

        Azul azul = new Azul(temp.getPosicion()[0],pos_y,temp.getPosicion());
        azul.setVelocidad(vel);
        cocodrilos.add(azul);
    }

    public void eliminar_cocodrilo(String tipo, Integer liana)
    {
        
        Liana temp= getLiana(liana);
        String posicion = tipo + "," + temp.getPosicion()[0];
        for(int i = 0; i< cocodrilos.size();i++)
        {
            String id = cocodrilos.get(i).getPosicion();
            String newID = id.split(",")[0] + "," + id.split(",")[1];
           
            if(newID.equals(posicion))
            {
                cocodrilos.remove(i);
                System.out.println("coco eliminado");
                break;
            }
            
        }

    }
    public void eliminar_fruta(Integer liana, Integer y)
    {
        
        Liana temp= getLiana(liana);
        Integer y_inicial = temp.getPosicion()[1];
        Integer y_final = temp.getPosicion()[2];
        Integer newY = y_inicial + ((y*(y_final - y_inicial))/100);
        Integer pos_y = (newY/10)*10;
        String posicion = temp.getPosicion()[0] + "," + pos_y;
        for(int i = 0; i< frutas.size();i++)
        {
            String id = frutas.get(i).getPosicion();
            
            if(id.equals(posicion))
            {
                frutas.remove(i);
                System.out.println("fruta eliminado");
                break;
            }
            
        }

    }

    public void crear_lianas()
    {
        
        Liana liana1 = new Liana(1, 85, 230, 585);
        Liana liana2 = new Liana(2, 205, 230, 585);
        Liana liana3 = new Liana(3, 325, 360, 600);
        Liana liana4 = new Liana(4, 461, 230, 490);
        Liana liana5 = new Liana(5, 575, 230, 525);
        Liana liana6 = new Liana(6, 690, 230, 420);
        Liana liana7 = new Liana(7, 813, 255, 510);
        Liana liana8 = new Liana(8, 935, 255, 465);
        Liana liana9 = new Liana(9, 1055, 140, 510);
        Liana liana10 = new Liana(10, 1178, 140, 510);

        this.lianas.add(liana1);
        this.lianas.add(liana2);
        this.lianas.add(liana3);
        this.lianas.add(liana4);
        this.lianas.add(liana5);
        this.lianas.add(liana6);
        this.lianas.add(liana7);
        this.lianas.add(liana8);
        this.lianas.add(liana9);
        this.lianas.add(liana10);
    }

    public Liana getLiana(Integer ID)
    {
        Liana temporal = null;
        for(int i = 0; i< lianas.size();i++)
        {
            if(lianas.get(i).getId()==ID)
            {
                temporal=lianas.get(i);
            }
            else
            {
                //System.out.println(lianas.get(i).getId());
            }
        }
        //System.out.println(temporal.getId());
        return temporal;
    }
    private void won()
    {
        if(jugador.x<610 && jugador.y<=160)
        {
            System.out.println("Won!");
            jugador.won();
            puntos = puntos + 1000;
            //for(int i = 0; i< cocodrilos.size();i++)
            //{
            if (cocodrilos.isEmpty())
            {
            }
            else
            {
                cocodrilos.get(0).addVelocidad();
                vel = cocodrilos.get(0).getVelocidad();
            }
                
            //}

        }
    }
    public String game_str()
    {
        String vidas_str = "LIVES:" + jugador.getVidas();
        String puntos_str = "POINTS:" + puntos;
        won();
        String jugador_str = jugador.getPosition();
        
        return vidas_str + ";"+ puntos_str + ";" + jugador_str + ";" + cocodrilos_str() + ";" + frutas_str();
    }

    public String frutas_str()
    {
        if(frutas.isEmpty())
        {
            return "0,0";
        }
        else
        {
            String finalStr ="";
            for(int i = 0; i< frutas.size();i++)
            {
                
                //colision con jugador
                //if(frutas.get(i).getPosicion().equals(jugador.getPosition()))
                if(frutas.get(i).colision(jugador.getX(), jugador.getY()))
                {
                    System.out.println("fruta eliminada");
                    puntos = puntos + frutas.get(i).getPuntos();
                    String pos = frutas.get(i).getPosicion() + ":";
                    finalStr = finalStr + pos;
                    frutas.remove(i);

                }
                else
                {
                    
                    String pos = frutas.get(i).getPosicion() + ":";
                    finalStr = finalStr + pos;  
                }
                

            }
            return finalStr.substring(0,finalStr.length()-1);


        }


    }
    public String cocodrilos_str()
    {
        if(cocodrilos.isEmpty())
        {
            return "0,0,0";
        }
        else
        {
            String finalStr ="";
            for(int i = 0; i< cocodrilos.size();i++)
            {
                //colision con jugador
                //String id = cocodrilos.get(i).getPosicion();
                //String newPos = id.split(",")[1] + "," + id.split(",")[2];
                //if(newPos.equals(jugador.getPosition()))
                if(cocodrilos.get(i).colision(jugador.getX(), jugador.getY()))
                {
                    jugador.hit();
                }

                //se slane de la pantalla
                if(cocodrilos.get(i).y>720)
                {
                    
                    
                    System.out.println("coco murio");
                    
                    String pos = cocodrilos.get(i).getPosicion() + ":";
                    finalStr = finalStr + pos;
                    cocodrilos.get(i).move();
                    cocodrilos.remove(i);
                }
                else
                {
                    
                    String pos = cocodrilos.get(i).getPosicion() + ":";
                    finalStr = finalStr + pos;
                    cocodrilos.get(i).move();

                }
                
                    
                
            }
            return finalStr.substring(0,finalStr.length()-1);

            }
        
    }

    
}

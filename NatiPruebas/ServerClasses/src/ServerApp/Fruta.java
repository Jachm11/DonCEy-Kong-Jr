package ServerApp;

public class Fruta 
{
    private String posicion;
    private Integer x;
    private Integer y;
    private Integer puntos;


    public Fruta(Integer x_position, Integer y_position)
    {
        this.puntos = 100;
        this.x = x_position;
        this.y = y_position;
        this.posicion = x_position + "," + y_position;

    }

    public Boolean colision(Integer player_x, Integer player_y)
    {
        if((player_x == this.x) && (player_y == this.y))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    public String getPosicion()
    {
        return posicion;
    }
    
    public Integer getPuntos()
    {
        return puntos;
    }


    
}

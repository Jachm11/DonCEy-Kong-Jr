package ServerApp;

public class Jugador 
{
    private Integer vidas;
    private String posicion;
    public Integer liana;
    public Integer x;
    public Integer y;

    public Jugador()
    {
        liana = 1;
        vidas = 3;
        x = 85;
        y = 585;
        posicion = x + "," + y;

    }
    public void move_up()
    {
        change_position(x, y-20);

    }
    
    public void move_down()
    {
        change_position(x, y+20);

    }
    public void move_sideways(Integer X, Integer liana_nueva)
    {
        liana = liana_nueva;
        change_position(X, y);
    }
    
    public Boolean colision(Integer object_x, Integer object_y)
    {
        if((object_x == this.x) && (object_y == this.y))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    public void hit()
    {
        change_position(85, 385);
        vidas--;
    }
    public void change_position(Integer X, Integer Y)
    {
        this.x = X;
        this.y = Y;
        this.posicion = x + "," + y;

    }
    public String getPosition()
    {
        return this.posicion;

    }
    public Integer getVidas()
    {
        return this.vidas;
    }
    
}

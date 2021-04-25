package Game;

public class Cocodrilo 
{
    static protected Integer velocidad;
    protected Integer[] liana;
    protected String posicion;
    protected Integer x;
    protected Integer y;

    public Boolean colision(Integer player_x, Integer player_y)
    {
        if((player_x == this.x) && (((this.y +20)> player_y) && ((this.y -20)< player_y)))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    public void move(){}
    public void setVelocidad(Integer speed)
    {
        velocidad = speed;
    }
    public void addVelocidad()
    {
        velocidad = velocidad + 5;
    }
    public Integer getVelocidad()
    {
        return velocidad;
    }
    public String getPosicion()
    {
        return posicion;
    }
}

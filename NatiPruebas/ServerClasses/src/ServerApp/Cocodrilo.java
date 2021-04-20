package ServerApp;


public class Cocodrilo 
{
    protected Integer velocidad;
    protected Integer[] liana;
    protected String posicion;
    protected Integer x;
    protected Integer y;

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
    public void move(){}
    public void resetVelocidad()
    {
        velocidad = 5;
    }
    public void addVelocidad()
    {
        velocidad = velocidad + 3;
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

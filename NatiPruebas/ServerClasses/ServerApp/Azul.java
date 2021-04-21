package ServerApp;

public class Azul extends Cocodrilo
{
    public Azul(Integer x_position, Integer y_position, Integer[] liana_position)
    {
        this.velocidad = 5;
        this.liana = liana_position;
        this.x = x_position;
        this.y = y_position;
        this.posicion = "2," + x_position + "," + y_position;

    }
    public void move()
    {
        this.y = this.y + this.velocidad;
        this.posicion = "2," + this.x + "," + this.y;
    }
    

}

package ServerApp;

public class Rojo extends Cocodrilo {
    private Boolean down;

    public Rojo(Integer x_position, Integer y_position, Integer[] liana_position)
    {
        
        this.down = true;
        this.liana = liana_position;
        this.x = x_position;
        this.y = y_position;
        this.posicion = "1," + x_position + "," + y_position;

    }

    public void move()
    {
        if(y<=(liana[1] + 20))
        {
            down = true;
        }
        if(y>=(liana[2] - 20))
        {
            down = false;
        }
        if(down)
        {
            move_down();
        }
        else
        {
            move_up();
        }
        
    }
    private void move_down()
    {
        this.y = this.y + velocidad;
        this.posicion = "1," + this.x + "," + this.y;
    }
    private void move_up()
    {
        this.y = this.y - velocidad;
        this.posicion = "1," + this.x + "," + this.y;
    }
}

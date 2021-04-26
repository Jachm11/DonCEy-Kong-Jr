package Game;
/**
Clase hija de cocodrilo para crear enemigos rojos
*/
public class Rojo extends Cocodrilo {
    private Boolean down;
    /**
    * Constructor de rojo
    * @param x_position posicion en x
    * @param y_position posicion en y
    * @param liana_position datos de la liana
    */
    public Rojo(Integer x_position, Integer y_position, Integer[] liana_position)
    {
        
        this.down = true;
        this.liana = liana_position;
        this.x = x_position;
        this.y = y_position;
        this.posicion = "1," + x_position + "," + y_position;

    }
    /*
    * Función para mover a un enemigo rojo a lo largo de la liana
    */
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
    /*
    * Función para mover a un enemigo rojo hacia arriba
    */
    private void move_down()
    {
        this.y = this.y + velocidad;
        this.posicion = "1," + this.x + "," + this.y;
    }
    /*
    * Función para mover a un enemigo rojo hacia abajo
    */
    private void move_up()
    {
        this.y = this.y - velocidad;
        this.posicion = "1," + this.x + "," + this.y;
    }
}

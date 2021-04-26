package Game;
/*
* Clase padre Cocodrilo para crear enemigos a partir de las clases hijas Azul y Rojo
*/
public class Cocodrilo 
{
    static protected Integer velocidad;
    protected Integer[] liana;
    protected String posicion;
    protected Integer x;
    protected Integer y;
    /**
    * Función para detectar una colision entre el jugador y el enemigo
    * @param player_x posicion en x del jugador
    * @param player_y posicion en y del jugador
    * @return true si colisiona, false de lo contrario
    */
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
    /**
    * Función para cambiar el valor de velocidad
    * @param speed la velocidad a la que se quiere cambiar
    */
    public void setVelocidad(Integer speed)
    {
        velocidad = speed;
    }
     /**
    * Función para aumentar el valor de velocidad en un valor de 5
    */
    public void addVelocidad()
    {
        velocidad = velocidad + 5;
    }
     /**
    * Función para obtener el valor de velocidad
    * @return velocidad
    */
    public Integer getVelocidad()
    {
        return velocidad;
    }
    /**
    * Función para obtener el valor de la posicion del enemigo
    * @return posicion
    */
    public String getPosicion()
    {
        return posicion;
    }
}

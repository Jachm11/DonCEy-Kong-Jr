package Game;
/*
* Clase para crear un Jugador
*/
public class Jugador 
{
    private Integer vidas;
    private String posicion;
    public Integer liana;
    public Integer x;
    public Integer y;
    /**
	* Constructor de Jugador
	*/
    public Jugador()
    {
        liana = 1;
        vidas = 3;
        x = 85;
        y = 585;
        posicion = x + "," + y;

    }
    /**
	* Función para mover al jugador hacia arriba
	*/
    public void move_up()
    {
        change_position(x, y-20);

    }
    /**
	* Funcion para mover al jugador hacia abajo
	*/
    public void move_down()
    {
        change_position(x, y+20);

    }
    /**
	* Función para mover el jugador hacia los lados
	* @param X, posicion en x a la que se quiere mover
	* @param liana_nueva liana en la que está el jugador despues de moverse
	*/
    public void move_sideways(Integer X, Integer liana_nueva)
    {
        liana = liana_nueva;
        change_position(X, y);
    }
    /**
	* Función para detectar una colision entre el jugador y una objeto
	* @param player_x posicion en x del objeto
	* @param player_y posicion en y del objeto
	* @return true si detecta una colision, false de lo contrario
	*/
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
    /**
    * Función en caso de que haya una colision con un enemigo, devuelv al jugador a la posicion inicial y le resta una vida
    */
    public void hit()
    {
        change_position(85, 585);
        liana = 1;
        vidas--;
    }
    /**
    * Función para devolver al jugador a la posicion inicial
    */
    public void won()
    {
        change_position(85, 585);
        liana = 1;

    }
    /**
	* Funcion para cambiar la posicion del jugador
	* @param X posicion en x
	* @param Y posicion en Y
	*/
    private void change_position(Integer X, Integer Y)
    {
        this.x = X;
        this.y = Y;
        this.posicion = x + "," + y;

    }
    /**
    * Función para obtener el valor de la posicion del jugador
    * @return posicion
    */
    public String getPosition()
    {
        return this.posicion;

    }
    /**
    * Función para obtener las viddas del jugador
    * @return vidas
    */
    public Integer getVidas()
    {
        return this.vidas;
    }
    /**
    * Función para obtener el valor de la posicion de X
    * @return x
    */
    public Integer getX()
    {
        return this.x;
    }
    /**
    * Función para obtener el valor de la posicion de y
    * @return y
    */
    public Integer getY()
    {
        return this.y;
    }
}

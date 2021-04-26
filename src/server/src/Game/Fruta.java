package Game;
/*
* Clase para crear nuevas frutas en el juego
*/
public class Fruta 
{
    private String posicion;
    private Integer x;
    private Integer y;
    private Integer puntos;

    /**
    * Constructor de Fruta
    * @param x_position la posición en x
    * @param y_position la posicion en y
    */
    public Fruta(Integer x_position, Integer y_position)
    {
        this.puntos = 100;
        this.x = x_position;
        this.y = y_position;
        this.posicion = x_position + "," + y_position;

    }
	/**
	* Función para detectar una colision entre el jugador y una fruta
	* @param player_x posicion en x del jugador
	* @param player_y posicion en y del jugador
	* @return true si detecta una colision, false de lo contrario
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
    /**
    * Función para obtener el valor de la posicion del enemigo
    * @return posicion
    */
    public String getPosicion()
    {
        return posicion;
    }
    /**
    * Función para obtener el valor de los puntos de la fruta
    * @return puntos
    */
    public Integer getPuntos()
    {
        return puntos;
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

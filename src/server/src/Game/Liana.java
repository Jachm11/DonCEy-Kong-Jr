package Game;
/*
* Clase para crear una Liana
*/
public class Liana 
{
    private Integer id;
    private Integer x;
    private Integer y_inicio;
    private Integer y_fin;
    /**
    * Constructor de Liana
    * @param ID id de la liana
    * @param X posición en x de la liana
    * @param y_inicio inicio de la liana en y
    * @param y_Fin final de la liana en y
    */
    public Liana(Integer ID, Integer X, Integer y_Inicio, Integer y_Fin )
    {
        
        this.x = X;
        this. y_inicio = y_Inicio;
        this. y_fin = y_Fin;

        this.id = ID;
    }
    /**
    * Función para obtener el ID de la liana
    * @return id
    */
    public Integer getId()
    {
        return id;
    }
    /**
    * Función para obtener el valor de la posicion de la liana
    * @return posicion [x, y_inicio, y_fin]
    */
    public Integer[] getPosicion()
    {
        Integer posicion[] = new Integer[3];
        posicion[0] = this.x;
        posicion[1] = this.y_inicio;
        posicion[2] = this.y_fin;
        return posicion;
    }

    
}

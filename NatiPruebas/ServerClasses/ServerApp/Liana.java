package ServerApp;

public class Liana 
{
    private Integer id;
    private Integer x;
    private Integer y_inicio;
    private Integer y_fin;

    public Liana(Integer ID, Integer X, Integer y_Inicio, Integer y_Fin )
    {
        
        this.x = X;
        this. y_inicio = y_Inicio;
        this. y_fin = y_Fin;

        this.id = ID;
    }
    public Integer getId()
    {
        return id;
    }

    public Integer[] getPosicion()
    {
        Integer posicion[] = new Integer[3];
        posicion[0] = this.x;
        posicion[1] = this.y_inicio;
        posicion[2] = this.y_fin;
        return posicion;
    }

    
}

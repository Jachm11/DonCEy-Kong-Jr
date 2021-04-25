//Socket
#define PORT1                1108
#define PORT2                802
#define DEFAULT_BUFLEN       512

//GUI
#define CONNECT_AS_PLAYER    11
#define CONNECT_AS_SPECTATOR 10
#define CONNECT_TO_1         12
#define CONNECT_TO_2         21
#define CLOSE_APP            100
#define VK_W                 0x57
#define VK_A                 0x41
#define VK_S                 0x53
#define VK_D                 0x44
#define ID_TIMER             1
#define MAX_ELEM             40
#define IDI_ICON1            101
/**
 * @brief Loop default de win32
 * 
 * @return LRESULT 
 */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM , LPARAM);
/**
 * @brief Agrega todos los concontroles a la interfaz grafica en la ventana HWND
 * 
 */
void addControls(HWND);
/**
 * @brief Carga todas las imagenes de la interfaz grafica
 * 
 */
void loadImages();
/**
 * @brief Funcion que se encarga de generar y enviar los mensajes al servidor
 * @param int codigo del mensaje a enviar
 */
void sendToServer(int);
/**
 * @brief Funcion que se encarga de leer los mensajes del servidor y cargalos al buffer (recvbuff)
 *
 */
void readFromServer();
/**
 * @brief Inicializa un socket para un puerto espacifico determinado por el usuario al escoger un servidor
 * @param int puerto donde incializar el socket
 * 
 */
void initializeSocket(int);
/**
 * @brief Funcion que se ejecuta cada vez que termina el timer. Elimina todas las imagenes cargadas en la iteracion pasada y carga las 
 * nuevas imagenes segun lo especificado por el servidor
 * 
 */
void update(HWND);
/**
 * @brief Funcion que esconde los botones de la pantalla de titulo y muestra el fondo y los botones de la seleccion de servidor
 * 
 */
void serverSelect();
/**
 * @brief Funcion que esconde los botones de la pantalla de seleccion de servidor y muestra el fondo y los textos de juego
 * 
 */
void gameStart(HWND);
/**
 * @brief Funcion que muestra una imagen determinada por el codigo de imagen y posiciones X y Y en Hwnd
 * @param int posicion en x
 * @param int posicion en y
 * @param int codigo de la imagen
 * 
 */
void windowSetNewImg(int, int, int,HWND);
/**
 * @brief Parser del mensaje del servidor. Extrae todos los detalles que deben ser mostrados durante el ciclo de update
 * @param char* token con la informacio del objeto de juego
 * @param int id del objeto de juego
 * 
 */
void setPositions(char*, int , HWND);
/**
 * @brief Muestra la pantalla de derrota
 * 
 */

/**
 * @brief Estructura que controla todos los flags del juego
 * 
 */
struct gameState {

    bool playing;
    bool connected;
    bool ready;
    bool sent;
    bool right;
    bool up;
    bool moving;
    int onScreenElem;
    int onScreenPastElem;
    bool clean;
    bool lost;
    int lastX;
    int animCount;

};
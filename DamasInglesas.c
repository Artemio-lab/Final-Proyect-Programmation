#include <stdio.h>
#include <string.h>
#define ROJO 0
#define AZUL 1
#define MORADO 2
#define BLANCO 3

void Juego();
void Creditos();
void HistorialV();
void iniciar_tablero(int tablero[8][8]);
int verificacion_casilla_negra(int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY);
int movimiento(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int movimiento_peon(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int movimiento_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
void crear_dama(int tablero[8][8]);
void imprimir_tablero(int tablero[8][8]);
void imprimir_linea();
void cambiar_color(int color);
void kernel_capturas(int x, int y, int kernel[3][3], int tablero[8][8], int turno);
void imprimir_kernel(int kernel[3][3]);
void capturar_ficha(int x, int y, int dx, int dy, int tablero[8][8]);

int main() {
  int opcion;

  do{
    printf("\n===== Damas Inglesas =====\n");
    printf("\n1. Jugar");
    printf("\n2. Creditos");
    printf("\n3. Historial de Victorias");
    printf("\n4. Salir\n");
    scanf("%d", &opcion);
    while(getchar()!='\n');

    switch (opcion){
      case 1:
        Juego();
      break;

      case 2:
        Creditos();
      break;

      case 3:
        HistorialV();
      break;

      case 4:
        printf("\nFin del programa!!");
      break;

      default:
        printf("\nOpcion invalida\n");
  }

  }while(opcion!=4);
}

void Juego(){
  printf("\nJugar\n");
  int turno=1, resultado=0, bandera, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero[8][8]={0};
  char jugador1[250], jugador2[250];
  printf("Ingrese el nombre del jugador 1: ");
  scanf(" %[^\n]", jugador1);
  printf("Ingrese el nombre del jugador 2: ");
  scanf(" %[^\n]", jugador2);

  iniciar_tablero(tablero);
  do{
    do{
        bandera=0;
    if((turno%2)!=0){
        printf("Turno de %s\n", jugador1);
    }else{
        printf("Turno de %s\n", jugador2);
    }
        imprimir_tablero(tablero);
        for(int i=0;i<8;i++){
        for(int l=0;l<8;l++){
            printf("%d  ", tablero[i][l]);
        }
        printf("\n");
    }
        do{
            printf("Coordenada ficha 1: ");
            scanf("%d", &coordenadas_fichaX);
            printf("Coordenada ficha 2: ");
            scanf("%d", &coordenadas_fichaY);
            // Aqui se crea un kernel el cual servira para las capturas más tarde
            int kernel[3][3];
            kernel_capturas(coordenadas_fichaX, coordenadas_fichaY, kernel, tablero, turno);
            imprimir_kernel(kernel);
            // Verificamos posibles movimientos válidos o capturas
            int movimientos_validos = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    // checamos si se encuentra una ficha rival
                    if (kernel[i + 1][j + 1] == 1) { // 1 = ficha rival, 2 = ficha aliada, X = invalido, 0 = no hay nada
                        int dy = i * 2; // Movimiento en X para capturar
                        int dx = j * 2; // Movimiento en Y para capturar
                        int posy = coordenadas_fichaX + dy; // posición en Y tras la captura
                        int posx = coordenadas_fichaY + dx; // Posición en X tras capturar

                        // Validar que la posición resultante esté dentro del tablero y sea válida
                        if (posy >= 0 && posy < 8 && posx >= 0 && posx < 8 && tablero[posy][posx] == 0) {
                            printf("Captura disponible en (%d, %d).\n", posy, posx);
                        }
                    }
                }
            }
            printf("Cordenada mover 1: ");
            scanf("%d", &coordenadas_moverX);
            printf("Cordenada mover 1: ");
            scanf("%d", &coordenadas_moverY);
            bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
        }while(bandera==0);
        bandera=movimiento(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        if(bandera==0){
            printf("No es una de tus fichas o la casilla destino esta ocupada\n");
        }
    }while(bandera==0);
    turno++;
    crear_dama(tablero);
  }while(resultado ==0);
}
void iniciar_tablero(int tablero[8][8]){
    int bandera1=1, bandera2=1;
    for(int i=0;i<8;i++){
        for(int l=0;l<8;l++){
            if((bandera1%2)==0 && i <3){
                tablero[i][l]=20;
            }
            if((bandera2%2)==0 && i>4){
                tablero[i][l]=10;
            }
            bandera2++;
            bandera1++;
        }
        bandera2++;
        bandera1++;
    }
}
int verificacion_casilla_negra(int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY){
    if((coordenadas_fichaX%2)==0 && (coordenadas_fichaY%2)==0 || (coordenadas_moverX%2)==0 && (coordenadas_moverY%2)==0){
        printf("No se puden casillas blancas\n");
        return 0;
    }else{
        return 1;
    }
}
int movimiento(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    int bandera=0,bandera2=0;
    if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10){
        if((coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY || (coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY){
            bandera= movimiento_peon(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        }
    }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20){
        if((coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY){
            bandera= movimiento_peon(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        }
    }else{
        if((coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY || (coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY){
        bandera2= movimiento_dama(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        }
    }
    if(bandera==1 || bandera2==1){
        return 1;
    }else{
        return 0;
    }
}
int movimiento_peon(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    if((turno%2) !=0){
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && tablero[coordenadas_moverX][coordenadas_moverY] !=10){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=10;
            return 1;
        }else{
            return 0;
        }
    }else{
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && tablero[coordenadas_moverX][coordenadas_moverY] !=20){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=20;
            return 1;
        }else{
            return 0;
        }
    }
}
int movimiento_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    if((turno%2) !=0){
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && tablero[coordenadas_moverX][coordenadas_moverY] !=11){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=11;
            return 1;
        }else{
            return 0;
        }
    }else{
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && tablero[coordenadas_moverX][coordenadas_moverY] !=21){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=21;
            return 1;
        }else{
            return 0;
        }
    }
}
void crear_dama(int tablero[8][8]){
    for(int i=0;i<8;i++){
        if(tablero[0][i]==10){
            tablero[0][i]=11;
        }
        if(tablero[7][i]==20){
            tablero[7][i]=21;
        }
    }
}

void Creditos(){
  printf("\nCreditos\n");
  printf("\nMelissa Rico Aguilar");
  printf("\nArtemio Hernandez Villalobos");
  printf("\nDerek Ramón Garzón Vizcarra\n");
}

void HistorialV(){
  printf("\nHistorial de Victorias\n");
}

/////////////////////////Imprimir tablero/////////////////////////////////////////
void imprimir_tablero(int tablero[8][8]){
    for(int l = 0; l <= 7; l++){
        printf("\033[0;37m");
        printf("     %d   ", l);
    }
    printf("\n");
    for(int i=0;i<8;i++){
        for(int l=0;l<8;l++){
    if((i%2)==0 ){
                if((l%2)!=0){
                    cambiar_color(MORADO);
                    imprimir_linea();
                }else{
                    cambiar_color(BLANCO);
                    imprimir_linea();
                }
            }else{
                if((l%2)==0){
                    cambiar_color(MORADO);
                    imprimir_linea();
                }else{
                    cambiar_color(BLANCO);
                    imprimir_linea();
                }
            }
        }
        printf("\n");
        cambiar_color(BLANCO);
        printf("%d ", i);
        for(int l=0;l<8;l++){
    if((i%2)==0 ){
        if((l%2)!=0){
            cambiar_color(BLANCO);
            cambiar_color(MORADO);                    
            if(tablero[i][l]== 10 || tablero[i][l] == 20){
                printf(" | ");
                if(tablero[i][l]==10){
                    cambiar_color(ROJO); 
                    printf("P");  
                    cambiar_color(MORADO);
                    printf(" |   ");                        
                    }else if(tablero[i][l]==20){
                        cambiar_color(AZUL);
                        printf("P");
                        cambiar_color(MORADO);
                        printf(" |   ");
                    }                    
            }else if(tablero[i][l]== 11 || tablero[i][l] == 21){
                printf("   | ");
                if(tablero[i][l]==11){
                    cambiar_color(ROJO);
                    printf("D");
                    cambiar_color(MORADO); 
                    printf(" |   ");                          
                }else if(tablero[i][l]==21){
                    cambiar_color(AZUL);
                    printf("D");
                    cambiar_color(MORADO);
                    printf(" |   ");
                    }
                }else{
                    cambiar_color(MORADO);
                    printf(" |   |   ");
                }
        }else{
                cambiar_color(BLANCO);
                printf(" |   |   ");
        }
    }else{
        if((l%2)==0){
            cambiar_color(BLANCO);
            cambiar_color(MORADO);                    
            if(tablero[i][l]== 10 || tablero[i][l] == 20){
                printf(" | ");
                if(tablero[i][l]==10){
                    cambiar_color(ROJO); 
                    printf("P");  
                    cambiar_color(MORADO);
                    printf(" |   ");                        
                    }else if(tablero[i][l]==20){
                        cambiar_color(AZUL);
                        printf("P");
                        cambiar_color(MORADO);
                        printf(" |   ");
                    }                    
            }else if(tablero[i][l]== 11 || tablero[i][l] == 21){
                printf("   | ");
                if(tablero[i][l]==11){
                    cambiar_color(ROJO);
                    printf("D");
                    cambiar_color(MORADO); 
                    printf(" |   ");                          
                }else if(tablero[i][l]==21){
                    cambiar_color(AZUL);
                    printf("D");
                    cambiar_color(MORADO);
                    printf(" |   ");
                    }
                }else{
                    cambiar_color(MORADO);
                    printf(" |   |   ");
                }
        }else{
                cambiar_color(BLANCO);
                printf(" |   |   ");
        }
    }
    }
    printf("\n");
        for(int l=0;l<8;l++){
    if((i%2)==0 ){
                if((l%2)!=0){
                    cambiar_color(MORADO);
                    imprimir_linea();
                }else{
                    cambiar_color(BLANCO);
                    imprimir_linea();
                }
            }else{
                if((l%2)==0){
                    cambiar_color(MORADO);
                    imprimir_linea();
                }else{
                    cambiar_color(BLANCO);
                    imprimir_linea();
                }
            }
        }
    printf("\n");
    }      
    printf("\033[0;37m");
}

void imprimir_linea(){
    printf("    ---  ");
}

void cambiar_color(int color){
    switch (color) {
  case ROJO:
    printf("\033[0;31m");
    break;
  case AZUL:
    printf("\033[0;34m");
    break;
  case MORADO:
    printf("\033[0;35m");
    break;
  case BLANCO:
    printf("\033[0;37m");
    break;
}
}


void kernel_capturas(int x, int y, int kernel[3][3], int tablero[8][8], int turno) {
    int rival;
    int aliado;
    if (turno % 2 != 0) {
        rival = 20;
        aliado = 10;
    } else {
        rival = 10;
        aliado = 20;
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                if (tablero[nx][ny] == 0) {
                    kernel[i + 1][j + 1] = 0; // Espacio vacío
                } else if (tablero[nx][ny] == rival) {
                    kernel[i + 1][j + 1] = 1; // Ficha rival
                } else if (tablero[nx][ny] == aliado) {
                    kernel[i + 1][j + 1] = 2; // Ficha aliada
                }
            } else {
                kernel[i + 1][j + 1] = -1; // Fuera de límites
            }
        }
    }
}
void imprimir_kernel(int kernel[3][3]){
    printf("\nKernel 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (kernel[i][j] == -1) {
                printf(" X "); // Fuera de límites
            } else {
                printf(" %d ", kernel[i][j]);
            }
        }
        printf("\n");
    }
}
void capturar_ficha(int x, int y, int dx, int dy, int tablero[8][8]) {
    int rivalX = x + dx / 2; // Coordenada de la ficha rival (mitad del salto)
    int rivalY = y + dy / 2;
    int destinoX = x + dx; // Coordenada final después del salto
    int destinoY = y + dy;

    // Verificar que el destino esté dentro de los límites
    if (destinoX >= 0 && destinoX < 8 && destinoY >= 0 && destinoY < 8) {
        // Mover la ficha del jugador al destino
        tablero[destinoX][destinoY] = tablero[x][y];
        tablero[x][y] = 0; // Vaciar la casilla original
        tablero[rivalX][rivalY] = 0; // Eliminar la ficha rival

        printf("Captura realizada: (%d, %d) -> (%d, %d)\n", x, y, destinoX, destinoY);
    } else {
        printf("Movimiento fuera de los límites. Captura no válida.\n");
    }
}

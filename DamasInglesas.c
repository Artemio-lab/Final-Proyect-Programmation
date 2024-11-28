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
            printf("Cordenada mover 1: ");
            scanf("%d", &coordenadas_moverX);
            printf("Cordenada mover 1: ");
            scanf("%d", &coordenadas_moverY);
            bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
        }while(bandera==0);
        bandera=movimiento(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        if(bandera==0){
            printf("Posibles faltas: No es una de tus fichas, la casilla destino esta ocupada o esta muy lejos la casilla\n");
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
    if((coordenadas_fichaX%2)==0 && (coordenadas_fichaY%2)==0 || (coordenadas_moverX%2)==0 && (coordenadas_moverY%2)==0 || (coordenadas_fichaX%2)!=0 && (coordenadas_fichaY%2)!=0 || (coordenadas_moverX%2)!=0 && (coordenadas_moverY%2)!=0){
        printf("No se pueden casillas blancas\n");
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
                printf(" | "); 
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
                printf(" | "); 
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
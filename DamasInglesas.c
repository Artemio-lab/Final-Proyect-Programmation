#include <stdio.h>
#include <string.h>
#define ROJO 0
#define AZUL 1
#define MORADO 2
#define BLANCO 3
#define SIZE 8

//Estructura para los ganadores
typedef struct resumen{
    char nombre[50];
    int fichasRestantes;
    char colorFicha[50];
} resumen_juego_t;

void Juego();
void Creditos();
void Historial();
void iniciar_tablero(int tablero[8][8]);
int verificacion_casilla_negra(int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY);
int movimiento(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int movimiento_peon(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int movimiento_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int funcion_comer_peon(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int funcion_comer_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int concatenar(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
int verificacion_movimiento_concatenar(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]);
void crear_dama(int tablero[8][8]);
void imprimir_tablero(int tablero[8][8]);
void imprimir_linea();
void cambiar_color(int color);
int cadenaEsLetraSIoNO(char nombre[]);
int verificar_ganador(int tablero[8][8]);

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
        Historial();
      break;
    
      case 4:
        printf("\nFin del programa!!\n");
      break;
    
      default:
        printf("\nOpcion invalida\n");
  }
    
  }while(opcion!=4);
}

void Juego(){
  printf("\nJugar\n");
  int turno=1, resultado=0, bandera, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero[8][8]={0}, bandera2;
  int contadorFichasX=12, contadorFichasY=12;;
  char jugador1[250], jugador2[250];
  resumen_juego_t ganadores;
  
  do{
      printf("Ingrese el nombre del jugador 1: ");
      scanf(" %[^\n]", jugador1);
      
      if(cadenaEsLetraSIoNO(jugador1)==0){
          printf("\nNOMBRE INVALIDO, vuelvelo a intentar\n");
      }
  }while(cadenaEsLetraSIoNO(jugador1)==0);

  do{
      printf("Ingrese el nombre del jugador 2: ");
      scanf(" %[^\n]", jugador2);
      
      if(cadenaEsLetraSIoNO(jugador2)==0){
          printf("\nNOMBRE INVALIDO, vuelvelo a intentar\n");
      }
  }while(cadenaEsLetraSIoNO(jugador2)==0);

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
        //for(int i=0;i<8;i++){
        //for(int l=0;l<8;l++){
        //    printf("%d  ", tablero[i][l]);
        //}
        //printf("\n");
        //}
        do{
            int coordenada_validaX, coordenada_validaY, coordenada_mover_validaX, coordenada_mover_validaY;
            do{
                do{
                    coordenada_validaX=-1;
                    printf("\nIngresa la coordenada 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaX);
                    while (getchar() != '\n');
                    if(coordenada_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaX<0);
                
                coordenadas_fichaX=coordenada_validaX;
                
                if(coordenadas_fichaX <  0 || coordenadas_fichaX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }    
            }while(coordenadas_fichaX < 0 || coordenadas_fichaX > 7);

            do{
                do{
                    coordenada_validaY=-1;
                    printf("\nIngresa la coordenada 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaY);
                    while (getchar() != '\n');
                    
                    if(coordenada_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaY<0);
                
                coordenadas_fichaY=coordenada_validaY;
                
                if(coordenadas_fichaY < 0 || coordenadas_fichaY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_fichaY < 0 || coordenadas_fichaY > 7);
            
            //fichas mover
            do{
                do{
                    coordenada_mover_validaX=-1;
                    printf("\nIngresa la coordenada a mover 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_mover_validaX);
                    while (getchar() != '\n'); 
                    
                    if(coordenada_mover_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_mover_validaX<0);
                
                coordenadas_moverX=coordenada_mover_validaX;
                
                if(coordenadas_moverX < 0 || coordenadas_moverX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_moverX < 0 || coordenadas_moverX > 7);
            
            do{
                do{
                    coordenada_mover_validaY=-1;
                    printf("\nIngresa la coordenada a mover 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_mover_validaY);
                    while (getchar() != '\n'); 
                    
                    if(coordenada_mover_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_mover_validaY<0);
                
                coordenadas_moverY=coordenada_mover_validaY;
                
                if(coordenadas_moverY < 0 || coordenadas_moverY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_moverY < 0 || coordenadas_moverY > 7);
            
            bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
        }while(bandera==0);
        bandera=movimiento(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
        if(bandera==0){
            printf("Posibles faltas: No es una de tus fichas, la casilla destino esta ocupada o esta muy lejos la casilla\n");
        }
    }while(bandera==0);
    turno++;
    crear_dama(tablero);
    bandera2=verificar_ganador(tablero);
  }while(bandera2==0);


  //CONTAR FICHAS
  int fichas_p1 = 0, fichas_p2 = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tablero[i][j] == 10 || tablero[i][j]==11){
                fichas_p1++;
            }
            if (tablero[i][j] == 20 || tablero[i][j]==21){
                fichas_p2++;
            }
        }
    }
  
  int ganador = verificar_ganador(tablero);
  FILE *archivo;
  archivo = fopen("historial.bin", "ab");
  
  if(ganador == 1){
    printf("\n¡Felicidades %s! Ganaste con fichas rojas!!\n", jugador1);
    strcpy(ganadores.nombre,jugador1);
    strcpy(ganadores.colorFicha,"Rojo");
    ganadores.fichasRestantes = fichas_p1;

    fwrite(&ganadores, sizeof(resumen_juego_t), 1, archivo);
    fclose(archivo);
  }else if(ganador==2){
    printf("\n¡Felicidades %s! Ganaste con fichas azules!!\n", jugador2);
    strcpy(ganadores.nombre,jugador2);
    strcpy(ganadores.colorFicha,"Azul");
    ganadores.fichasRestantes = fichas_p2;

    fwrite(&ganadores, sizeof(resumen_juego_t), 1, archivo);
    fclose(archivo);
  }
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
    int bandera, bandera2;
    if((turno%2) !=0){
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && tablero[coordenadas_moverX][coordenadas_moverY] ==0){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=10;
            return 1;
        }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && tablero[coordenadas_moverX][coordenadas_moverY] ==20 || tablero[coordenadas_moverX][coordenadas_moverY]==21){
            bandera=funcion_comer_peon(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
            if(bandera==1){            
                do{
                    imprimir_tablero(tablero);
                    do{                      
            int coordenada_validaX, coordenada_validaY, coordenada_mover_validaX, coordenada_mover_validaY;

                        do{
                do{
                    coordenada_validaX=-1;
                    printf("\nIngresa la coordenada 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaX);
                    while (getchar() != '\n');
                    if(coordenada_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaX<0);
                
                coordenadas_fichaX=coordenada_validaX;
                
                if(coordenadas_fichaX <  0 || coordenadas_fichaX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }    
            }while(coordenadas_fichaX < 0 || coordenadas_fichaX > 7);

            do{
                do{
                    coordenada_validaY=-1;
                    printf("\nIngresa la coordenada 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaY);
                    while (getchar() != '\n');
                    
                    if(coordenada_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaY<0);
                
                coordenadas_fichaY=coordenada_validaY;
                
                if(coordenadas_fichaY < 0 || coordenadas_fichaY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_fichaY < 0 || coordenadas_fichaY > 7);
                        //fichas mover
                        do{
                            do{
                                coordenada_mover_validaX=-1;
                                printf("\nIngresa la coordenada a mover 1 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaX);
                                while (getchar() != '\n'); 
                                if(coordenada_mover_validaX==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaX<0);
                            
                            coordenadas_moverX=coordenada_mover_validaX;
                            
                            if(coordenadas_moverX < 0 || coordenadas_moverX > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverX < 0 || coordenadas_moverX > 7);
                        
                        do{
                            do{
                                coordenada_mover_validaY=-1;
                                printf("\nIngresa la coordenada a mover 2 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaY);
                                while (getchar() != '\n'); 
                                
                                if(coordenada_mover_validaY==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaY<0);
                            
                            coordenadas_moverY=coordenada_mover_validaY;
                            
                            if(coordenadas_moverY < 0 || coordenadas_moverY > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverY < 0 || coordenadas_moverY > 7);

                        bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
                        bandera2=verificacion_movimiento_concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                    }while(bandera==0 || bandera2 ==0);
                    bandera2=concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                }while(bandera2==1);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && tablero[coordenadas_moverX][coordenadas_moverY] ==0){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=20;
            return 1;
        }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && tablero[coordenadas_moverX][coordenadas_moverY] ==10 || tablero[coordenadas_moverX][coordenadas_moverY]==11){
            bandera=funcion_comer_peon(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);    
            if(bandera==1){
                do{
                    imprimir_tablero(tablero);
                    do{  
                        int coordenada_validaX, coordenada_validaY, coordenada_mover_validaX, coordenada_mover_validaY;
                       do{
                do{
                    coordenada_validaX=-1;
                    printf("\nIngresa la coordenada 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaX);
                    while (getchar() != '\n');
                    if(coordenada_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaX<0);
                
                coordenadas_fichaX=coordenada_validaX;
                
                if(coordenadas_fichaX <  0 || coordenadas_fichaX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }    
            }while(coordenadas_fichaX < 0 || coordenadas_fichaX > 7);

            do{
                do{
                    coordenada_validaY=-1;
                    printf("\nIngresa la coordenada 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaY);
                    while (getchar() != '\n');
                    
                    if(coordenada_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaY<0);
                
                coordenadas_fichaY=coordenada_validaY;
                
                if(coordenadas_fichaY < 0 || coordenadas_fichaY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_fichaY < 0 || coordenadas_fichaY > 7);

                        //fichas mover
                        do{
                            do{
                                coordenada_mover_validaX=-1;
                                printf("\nIngresa la coordenada a mover 1 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaX);
                                while (getchar() != '\n'); 
                                if(coordenada_mover_validaX==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaX<0);
                            
                            coordenadas_moverX=coordenada_mover_validaX;
                            
                            if(coordenadas_moverX < 0 || coordenadas_moverX > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverX < 0 || coordenadas_moverX > 7);
                        
                        do{
                            do{
                                coordenada_mover_validaY=-1;
                                printf("\nIngresa la coordenada a mover 2 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaY);
                                while (getchar() != '\n'); 
                                
                                if(coordenada_mover_validaY==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaY<0);
                            
                            coordenadas_moverY=coordenada_mover_validaY;
                            
                            if(coordenadas_moverY < 0 || coordenadas_moverY > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverY < 0 || coordenadas_moverY > 7);

                        bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
                        bandera2=verificacion_movimiento_concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                    }while(bandera==0 || bandera2 ==0);
                    bandera2=concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                }while(bandera2==1);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }
}

int funcion_comer_peon(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    if((turno%2)!=0){
        if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY-1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY-1]=10;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY+1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY+1]=10;
                return 1;
            }else{
                return 0;
            }
        }
    }else{
        if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY-1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY-1]=20;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY+1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY+1]=20;
                return 1;
            }else{
                return 0;
            }
        }
    }
    return 0;
}

int funcion_comer_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    if((turno%2)!=0){
        if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY-1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY-1]=11;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY+1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY+1]=11;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY-1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY-1]=11;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY+1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY+1]=11;
                return 1;
            }else{
                return 0;
            }
        }
    }else{
        if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY-1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY-1]=21;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY+1]==0 && (coordenadas_moverX-1)>=0 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX-1][coordenadas_moverY+1]=21;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY-1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY-1)>=0){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY-1]=21;
                return 1;
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY+1]==0 && (coordenadas_moverX+1)<=7 && (coordenadas_moverY+1)<=7){
                tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                tablero[coordenadas_moverX][coordenadas_moverY]=0;
                tablero[coordenadas_moverX+1][coordenadas_moverY+1]=21;
                return 1;
            }else{
                return 0;
            }
        }
    }
    return 0;
}

int verificacion_movimiento_concatenar(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    if((turno%2)!=0){
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 || tablero[coordenadas_fichaX][coordenadas_fichaY]==11 &&(coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY || (coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY){
            return 1;
        }else{
            return 0;
        }
    }else{
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 || tablero[coordenadas_fichaX][coordenadas_fichaY]==21 &&(coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY || (coordenadas_fichaX -1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY+1)==coordenadas_moverY || (coordenadas_fichaX +1)==coordenadas_moverX && (coordenadas_fichaY-1)==coordenadas_moverY){
            return 1;
        }else{
            return 0;
        }
    }
}

int concatenar(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    int bandera;
    if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY-1]==0 && ((coordenadas_moverX-1)>=0 && (coordenadas_moverY-1)>=0) && tablero[coordenadas_moverX][coordenadas_moverY]!=0){
                if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX-1][coordenadas_moverY-1]=10;                    
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX-1][coordenadas_moverY-1]=11;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX-1][coordenadas_moverY-1]=20;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && (turno%2)==0){
                    tablero[coordenadas_moverX-1][coordenadas_moverY-1]=21;
                    bandera=1;
                }else{
                    return 0;
                }
                if(bandera ==1){
                    tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                    tablero[coordenadas_moverX][coordenadas_moverY]=0;
                return 1;
                }                
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX-1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX-1][coordenadas_moverY+1]==0 && ((coordenadas_moverX-1)>=0 && (coordenadas_moverY+1)<=7) && tablero[coordenadas_moverX][coordenadas_moverY]!=0){
                if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX-1][coordenadas_moverY+1]=10;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX-1][coordenadas_moverY+1]=11;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX-1][coordenadas_moverY+1]=20;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX-1][coordenadas_moverY+1]=21;
                    bandera=1;
                }else{
                    return 0;
                }
                if(bandera ==1){
                    tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                    tablero[coordenadas_moverX][coordenadas_moverY]=0;
                return 1;
                }
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY -1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY-1]==0 && ((coordenadas_moverX+1)<=7 && (coordenadas_moverY-1)>=0) && tablero[coordenadas_moverX][coordenadas_moverY]!=0){
                if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX+1][coordenadas_moverY-1]=10;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX+1][coordenadas_moverY-1]=11;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX+1][coordenadas_moverY-1]=20;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX+1][coordenadas_moverY-1]=21;
                    bandera=1;
                }else{
                    return 0;
                }
                if(bandera ==1){
                    tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                    tablero[coordenadas_moverX][coordenadas_moverY]=0;
                return 1;
                }
            }else{
                return 0;
            }
        }else if((coordenadas_fichaX+1) == coordenadas_moverX && (coordenadas_fichaY +1)==coordenadas_moverY){
            if(tablero[coordenadas_moverX+1][coordenadas_moverY+1]==0 && ((coordenadas_moverX+1)<=7 && (coordenadas_moverY+1)<=7) && tablero[coordenadas_moverX][coordenadas_moverY]!=0){
                if(tablero[coordenadas_fichaX][coordenadas_fichaY]==10 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX+1][coordenadas_moverY+1]=10;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && (turno%2)!=0 && tablero[coordenadas_moverX][coordenadas_moverY]!=11 && tablero[coordenadas_moverX][coordenadas_moverY]!=10){
                    tablero[coordenadas_moverX+1][coordenadas_moverY+1]=11;
                    bandera=1;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==20 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX+1][coordenadas_moverY+1]=20;
                }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && (turno%2)==0 && tablero[coordenadas_moverX][coordenadas_moverY]!=21 && tablero[coordenadas_moverX][coordenadas_moverY]!=20){
                    tablero[coordenadas_moverX+1][coordenadas_moverY+1]=21;
                    bandera=1;
                }else{
                    return 0;
                }
                if(bandera ==1){
                    tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
                    tablero[coordenadas_moverX][coordenadas_moverY]=0;
                return 1;
                }             
            }else{
                return 0;
            }
        }
    return 0;
}

int movimiento_dama(int turno, int coordenadas_fichaX, int coordenadas_fichaY, int coordenadas_moverX, int coordenadas_moverY, int tablero[8][8]){
    int bandera, bandera2;
    if((turno%2) !=0){
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && tablero[coordenadas_moverX][coordenadas_moverY] ==0){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=11;
            return 1;
        }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==11 && tablero[coordenadas_moverX][coordenadas_moverY] ==20 || tablero[coordenadas_moverX][coordenadas_moverY]==21){
            bandera=funcion_comer_dama(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
            
            int coordenada_validaX, coordenada_validaY, coordenada_mover_validaX, coordenada_mover_validaY;
            
            if(bandera==1){
                do{
                    imprimir_tablero(tablero);
                    do{                  
                        printf("\n");  

            do{
                do{
                    coordenada_validaX=-1;
                    printf("\nIngresa la coordenada 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaX);
                    while (getchar() != '\n');
                    if(coordenada_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaX<0);
                
                coordenadas_fichaX=coordenada_validaX;
                
                if(coordenadas_fichaX <  0 || coordenadas_fichaX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }    
            }while(coordenadas_fichaX < 0 || coordenadas_fichaX > 7);

            do{
                do{
                    coordenada_validaY=-1;
                    printf("\nIngresa la coordenada 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaY);
                    while (getchar() != '\n');
                    
                    if(coordenada_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaY<0);
                
                coordenadas_fichaY=coordenada_validaY;
                
                if(coordenadas_fichaY < 0 || coordenadas_fichaY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_fichaY < 0 || coordenadas_fichaY > 7);

                         //fichas mover

                    do{
                            do{
                                coordenada_mover_validaX=-1;
                                printf("\nIngresa la coordenada a mover 1 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaX);
                                while (getchar() != '\n'); 
                                if(coordenada_mover_validaX==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaX<0);
                            
                            coordenadas_moverX=coordenada_mover_validaX;
                            
                            if(coordenadas_moverX < 0 || coordenadas_moverX > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverX < 0 || coordenadas_moverX > 7);
                        
                        do{
                            do{
                                coordenada_mover_validaY=-1;
                                printf("\nIngresa la coordenada a mover 2 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaY);
                                while (getchar() != '\n'); 
                                
                                if(coordenada_mover_validaY==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaY<0);
                            
                            coordenadas_moverY=coordenada_mover_validaY;
                            
                            if(coordenadas_moverY < 0 || coordenadas_moverY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_moverY < 0 || coordenadas_moverY > 7);
                        
                            

                        bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
                        bandera2=verificacion_movimiento_concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                    }while(bandera==0 || bandera2 ==0);
                    bandera2=concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                }while(bandera2==1);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && tablero[coordenadas_moverX][coordenadas_moverY] ==0){
            tablero[coordenadas_fichaX][coordenadas_fichaY]=0;
            tablero[coordenadas_moverX][coordenadas_moverY]=21;
            return 1;
        }else if(tablero[coordenadas_fichaX][coordenadas_fichaY]==21 && tablero[coordenadas_moverX][coordenadas_moverY] ==10 || tablero[coordenadas_moverX][coordenadas_moverY]==11){
            bandera=funcion_comer_dama(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
            if(bandera==1){
                do{
                    int coordenada_validaX, coordenada_validaY, coordenada_mover_validaX, coordenada_mover_validaY;
                    imprimir_tablero(tablero);
                    do{     
                        do{
                do{
                    coordenada_validaX=-1;
                    printf("\nIngresa la coordenada 1 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaX);
                    while (getchar() != '\n');
                    if(coordenada_validaX==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaX<0);
                
                coordenadas_fichaX=coordenada_validaX;
                
                if(coordenadas_fichaX <  0 || coordenadas_fichaX > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }    
            }while(coordenadas_fichaX < 0 || coordenadas_fichaX > 7);

            do{
                do{
                    coordenada_validaY=-1;
                    printf("\nIngresa la coordenada 2 [DE 0 A 7]: ");
                    scanf("%d",&coordenada_validaY);
                    while (getchar() != '\n');
                    
                    if(coordenada_validaY==-1){
                        printf("\nCLAVE INVALIDA!!\n");
                    }
                }while(coordenada_validaY<0);
                
                coordenadas_fichaY=coordenada_validaY;
                
                if(coordenadas_fichaY < 0 || coordenadas_fichaY > 7){
                    printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                }
            }while(coordenadas_fichaY < 0 || coordenadas_fichaY > 7);

                        //fichas mover
                        do{
                            do{
                                coordenada_mover_validaX=-1;
                                printf("\nIngresa la coordenada a mover 1 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaX);
                                while (getchar() != '\n'); 
                                if(coordenada_mover_validaX==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaX<0);
                            
                            coordenadas_moverX=coordenada_mover_validaX;
                            
                            if(coordenadas_moverX < 0 || coordenadas_moverX > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverX < 0 || coordenadas_moverX > 7);
                        
                        do{
                            do{
                                coordenada_mover_validaY=-1;
                                printf("\nIngresa la coordenada a mover 2 [DE 0 A 7]: ");
                                scanf("%d",&coordenada_mover_validaY);
                                while (getchar() != '\n'); 
                                
                                if(coordenada_mover_validaY==-1){
                                    printf("\nCLAVE INVALIDA!!\n");
                                }
                            }while(coordenada_mover_validaY<0);
                            
                            coordenadas_moverY=coordenada_mover_validaY;
                            
                            if(coordenadas_moverY < 0 || coordenadas_moverY > 7){
                                printf("\nOPCION INVALIDA! Vuelvelo a intentar\n");
                            }
                        }while(coordenadas_moverY < 0 || coordenadas_moverY > 7);

                        bandera=verificacion_casilla_negra(coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY);
                        bandera2=verificacion_movimiento_concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                    }while(bandera==0 || bandera2 ==0);
                    bandera2=concatenar(turno, coordenadas_fichaX, coordenadas_fichaY, coordenadas_moverX, coordenadas_moverY, tablero);
                }while(bandera2==1);
                return 1;
            }else{
                return 0;
            }
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

void Historial(){
  printf("\nHistorial de Victorias\n");
    
  FILE *archivo = fopen("historial.bin", "rb");
    
  if (!archivo) {
    printf("PRIMERO JUEGA!!\n");
        return;
  }
    
  resumen_juego_t ganadores;
  while (fread(&ganadores, sizeof(resumen_juego_t), 1, archivo)){
    printf("Ganador: %s | Fichas restantes: %d | Color: %s\n", ganadores.nombre, ganadores.fichasRestantes, ganadores.colorFicha);
  }
  
  fclose(archivo);
}

////////////////Imprimir tablero///////////////////
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
    switch (color){
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

int cadenaEsLetraSIoNO(char nombre[]){
    int i = 0;
    
    //Verifica que cada caracter sea una letra o un espacio
    while (nombre[i] != '\0' && nombre[i] != '\n'){
        if (!((nombre[i] >= 'A' && nombre[i] <= 'Z') || (nombre[i] >= 'a' && nombre[i] <= 'z') || nombre[i] == ' ')) {
            return 0;//Retorna 0 si encuentra un caracter que no es letra ni espacio
        }
        i++;
    }
    //Elimina espacios al final de la cadena

    i--;
    
    while (i >= 0 && nombre[i] == ' ') {
        nombre[i] = '\0';
        i--;
    }   

    // Elimina espacios al inicio de la cadena, desplazando el contenido
    int j = 0;

    while (nombre[j] == ' ') {
        j++;
    }
    
    if (j > 0) {
        int k = 0;
        while (nombre[j] != '\0') {
            nombre[k++] = nombre[j++];
        }
        
        nombre[k] = '\0'; //Termina la cadena correctamente
    }

    return 1; //Retorna 1 si todos los caracteres son letras o espacios
}

int verificar_ganador(int tablero[8][8]) {
    int fichas_p1 = 0, fichas_p2 = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(tablero[i][j]==10 || tablero[i][j]==11){
                fichas_p1++;
            }else if(tablero[i][j]==20 || tablero[i][j]==21){
                fichas_p2++;
            }
        }
    }
    if(fichas_p1 == 0){
        return 1; //2 Gano el jugador 2 porque el jugador 1 no tiene fichas
    }else if(fichas_p2 == 0){
        return 2; //1 Gano el jugador 1 porque el jugador 2 no tiene fichas
    }else{
        return 0;
    }
}

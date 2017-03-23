#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct casilla{
        /*Definición del tipo de dato mina que servira para realizar las funciones desed el comienzo 
        hasta el final, definiendola con una parte entera que nos define o el numero de minas alrededor
        de cada casilla o si es una mina; y otra parte definida por un caracter que sirve como interfaz 
        de usuario al ser impresa para mostrar el tablero*/
        int v;
        int g;
    };
    typedef struct casilla mina;
mina ** llenarc(mina **s,int r,int c,int cm,int *k){
    /*Funcion que ademas de inicializar la matriz,llenara la matriz de minas recibiendo como parametros 
    matriz de tipo de dato mina **, su numero de filas(r), la cantidad de minas que tendra la matriz(cm) 
    y el numero de banderas que se tendran para poner. rama2 es el numero maximo de minas permitido por 
    fila, f e i al ser indices se utilizar para recorrer la matriz y ademas de inicializarla ver si n el
    cual es un numero al azar entre 0 y 3, es 1, lo que implica que en el la posicion que darian los 
    indices ya descritos iria una mina, dandole el valor de 9 en su parte entera e igual asignando 'X' a su 
    representacion grafica*/
    srand(time(NULL)); 
    int i,f,n,m=0,mf,rama2=3;
    if(r>16){
        rama2=4;
    }
    mina**p=s;
    p=(mina**)malloc(r*sizeof(mina*));
    for(i=0;i<r;i++){
        p[i]=(mina *)malloc(c*sizeof(mina));
        for(mf=0,f=0;f<c;f++){
            n=rand()%3;
            if(n==1&& m<cm&&mf<rama2){
                p[i][f].v=9;
                m+=1;
                mf+=1;
                *k+=1;
            }else{
            	p[i][f].v=1;
			}
            p[i][f].g='X';
        }
    }
    return p;
}
mina ** llenarn(mina **s,int r,int col,int *h){
    /*Funcion que llenara los numeros una vez que ya se han colocado las minas, 
    se recorren una por una las casillas de la matriz y se verifica cada parte entera de los datos en busca de uno diferente de nueve,
    pues esto implica que es una mina, empieza el proceso de verificar cuantas minas hay a su alrededor apartir de condicionales que revisan el octante 
    externo a la casilla a la que se esta verificando, haciendo que un contador de minas(c) con cada mina que se encuentres en las posiciones de su octante,
    al final al valor entero de esta casilla en cuestion se le agragara este contador que sera ahora el numero de minas cerca a esa casilla y se aumentara un 
    entero recibido por referencia que sera la cantidad de numeros que se tienen en el tablero, la verificacion de minas se aplica para 3 casos distintos, la 
    fila superior, inferior y el resto comprendidas entre estas, definiendo que para las dos primeras se hace una verificacion de 5 posiciones alrededor y el
    resto 8, al final se reinicia el proceso igualando c a 0 para que no se acumulen minas cuando se realice el proceso en otra casilla y se agrega la 
    representacion grafica de 'X' para su impresion.*/
    int i,f,c=0,n;
    mina**p=s;
    for(i=0;i<r;i++){
        for(f=0;f<col;f++){
            if(i>0&&i<r-1&&p[i][f].v!=9){
                if(p[i][f-1].v==9){
                    c+=1;                
                }
                if(p[i][f+1].v==9){
                    c+=1;                
                }
                if(p[i-1][f].v==9){
                    c+=1;                
                }
                if(p[i-1][f+1].v==9){
                    c+=1;                
                }
                if(p[i-1][f-1].v==9){
                    c+=1;                
                }
                if(p[i+1][f-1].v==9){
                    c+=1;                
                }
                if(p[i+1][f].v==9){
                    c+=1;                
                }
                if(p[i+1][f+1].v==9){
                    c+=1;                
                }
				p[i][f].v=c;
                p[i][f].g='X';
			*h+=1;
    			c=0;	                
            }else{
            	if(i==0&&p[i][f].v!=9){

            		if(p[i][f-1].v==9){
	                    c+=1;                
	                }
	                if(p[i][f+1].v==9){
	                    c+=1;                
	                }
	                if(p[i+1][f-1].v==9){
	                    c+=1;                
	                }
	                if(p[i+1][f].v==9){
	                    c+=1;                
	                }
	                if(p[i+1][f+1].v==9){
	                    c+=1;                
	                }
					p[i][f].v=c;
                    p[i][f].g='X';
				*h+=1;
	    			c=0;
				}
				if(i==r-1&&p[i][f].v!=9){
            		if(p[i][f-1].v==9){
	                    c+=1;                
	                }
	                if(p[i][f+1].v==9){
	                    c+=1;                
	                }
	                if(p[i-1][f-1].v==9){
	                    c+=1;                
	                }
	                if(p[i-1][f].v==9){
	                    c+=1;                
	                }
	                if(p[i-1][f+1].v==9){
	                    c+=1;                
	                }
					p[i][f].v=c;
                    p[i][f].g='X';
				*h+=1;
	    			c=0;
				}
			}
        }
    }
    return p;
}
void dibujar(mina**s,int r,int c,int *p,int *q){
    /*Funcion que imprime las casillas una por una en pantalla se accede al apuntador s y se recorre todo 
    Se imprime la el caracter que se ha dispuesto para esta casilla, q sera el mismo h anterior que aumentaba de acuerdo a la cantidad de minas
    y p la cantidad de banderas disponibles.*/
    int i,f;
    for(i=0;i<r;i++){
        for(f=0;f<c;f++){
            printf("   %c",s[i][f].g);
        }
        printf("\n");
    }
	printf("\t%d minas\t%d banderas para poner\n",*q,*p);
}
mina **ceros(mina **s, int f,int c,int *h,int r){
    /*funcion que en caso de que el valor entero de la casilla detapada sea 0, destapa su octante exterior, berificando que si ya han sido
    destapadas no se le reste 1 a la cantidad de numeros destapados(h), en el caso de que no, le reste 1 y cambie su valor imprimible de 
    caracter a su valor entero mas 48, pues este es la representacion ASCII para el numero que se dispone.la funcion se aplica para 3 casos distintos,
    la fila superior, inferior y el resto comprendidas entre estas, definiendo que para las dos primeras se hace una verificacion de 5 
    posiciones alrededor y el resto 8*/
    if(s[f][c].g=='X'){
        *h-=1;
    }
    s[f][c].g=s[f][c].v+48;
    if(f>0&&f<r-1){
        if(s[f][c-1].v!=9){
            if(s[f][c-1].g=='X'){
                *h-=1;
            }
            s[f][c-1].g=s[f][c-1].v+48;
        }
        if(s[f][c+1].v!=9){
            if(s[f][c+1].g=='X'){
                *h-=1;
            }
            s[f][c+1].g=s[f][c+1].v+48;                
        }
        if(s[f-1][c].v!=9){
            if(s[f-1][c].g=='X'){
                *h-=1;
            }
            s[f-1][c].g=s[f-1][c].v+48;       
        }
        if(s[f-1][c+1].v!=9){
            if(s[f-1][c+1].g=='X'){
                *h-=1;
            }
            s[f-1][c+1].g=s[f-1][c+1].v+48;              
        }
        if(s[f-1][c-1].v!=9){
            if(s[f-1][c-1].g=='X'){
                *h-=1;
            }
            s[f-1][c-1].g=s[f-1][c-1].v+48;              
        }
        if(s[f+1][c-1].v!=9){
            if(s[f+1][c-1].g=='X'){
                *h-=1;
            }
            s[f+1][c-1].g=s[f+1][c-1].v+48;      
        }
        if(s[f+1][c].v!=9){
            if(s[f+1][c].g=='X'){
                *h-=1;
            }
            s[f+1][c].g=s[f+1][c].v+48;                
        }
        if(s[f+1][c+1].v!=9){
            if(s[f+1][c+1].g=='X'){
                *h-=1;
            }
            s[f+1][c+1].g=s[f+1][c+1].v+48;   
        }
    }
    if(f==0){
        if(s[f][c-1].v!=9){
            if(s[f][c-1].g=='X'){
                *h-=1;
            }
            s[f][c-1].g=s[f][c-1].v+48;
        }
        if(s[f][c+1].v!=9){
            if(s[f][c+1].g=='X'){
                *h-=1;
            }
            s[f][c+1].g=s[f][c+1].v+48;                
        }
        if(s[f+1][c-1].v!=9){
            if(s[f+1][c-1].g=='X'){
                *h-=1;
            }
            s[f+1][c-1].g=s[f+1][c-1].v+48;      
        }
        if(s[f+1][c].v!=9){
            if(s[f+1][c].g=='X'){
                *h-=1;
            }
            s[f+1][c].g=s[f+1][c].v+48;                
        }
        if(s[f+1][c+1].v!=9){
            if(s[f+1][c+1].g=='X'){
                *h-=1;
            }
            s[f+1][c+1].g=s[f+1][c+1].v+48;   
        }
    }
    if(f==r-1){
        if(s[f][c-1].v!=9){
            if(s[f][c-1].g=='X'){
                *h-=1;
            }
            s[f][c-1].g=s[f][c-1].v+48;
        }
        if(s[f][c+1].v!=9){
            if(s[f][c+1].g=='X'){
                *h-=1;
            }
            s[f][c+1].g=s[f][c+1].v+48;                
        }
        if(s[f-1][c].v!=9){
            if(s[f-1][c].g=='X'){
                *h-=1;
            }
            s[f-1][c].g=s[f-1][c].v+48;       
        }
        if(s[f-1][c+1].v!=9){
            if(s[f-1][c+1].g=='X'){
                *h-=1;
            }
            s[f-1][c+1].g=s[f-1][c+1].v+48;              
        }
        if(s[f-1][c-1].v!=9){
            if(s[f-1][c-1].g=='X'){
                *h-=1;
            }
            s[f-1][c-1].g=s[f-1][c-1].v+48;              
        }
    }

return s;
}
mina ** jugar(mina **s,int o, int f,int c,int *p,int *q,int *h){
    /*funcion que recibe como parametros una matriz tipo mina(s), una opcion a realizar(o),
    una coordenada dada por filas(f) y columnas(c) y por referencia, numero de banderas disponibles(q),
    cantidad de numeros destapados(p) y un estado(s) que indica si ha destapado o no una mina, despues de 
    determinar si la opcion indica el poner una bandera, verifica que haya una cantidad mayor a 0 de banderas,
    antes de cambiar la representacion grafica de la casilla dada por las coordenadas en matriz por 'F', en tal caso 
    de que ya su representacion grafica ya sea 'F', la devuelve a 'X' y aumenta la cantidad de banderas para poner en uno,
    si la opcion implica el destapar una casilla, verifica que el valor entero de esta, no sea nueve, lo que indica que es una mina y modificaria p
    a 0, dando por terminado el juego, por el contrario, decreceria la cantidad de numeros por destapar para ganar el juego y cambiaria la representacion
    grafica de la casilla, a su valor entero mas 48, pues este es la representacion ASCII para el numero que se dispone.*/ 
    if (o==1){
    	if(s[f][c].g=='F'){
    		s[f][c].g='X';
    		*q+=1;
    	}else{
    		if(*q>0){
    			s[f][c].g='F';
    			*q-=1;
    		}else{
    			printf(" No hay mas banderas para poner.\n");
    		}
    	}
        return s;
    }else{
        if(s[f][c].v==9){
            *p=0;
        }else{
            if(s[f][c].g=='X'){
                *h-=1;
            }
            s[f][c].g=s[f][c].v+48;
        }
        return s;
    }
}
void main(int argc, char * argv[]){
    /*
    Esta funcion recibe como parametros por linea de comando el nivel al cual se quiere accerder,
    apartir de esto se define el numero de filas(r), columnas(col) y minas que se tendran, para
    realizar el tablero, tambien ejecutara un ciclo que se realizara con la condicion de que la 
    cantidad de numeros que se hayan destapados sea cero y no haya destapado una mina, 
    significando que ha ganado o perdido respectivamente; en este ciclo, con cada iteracion se
    dibujara el tablero con las minas destapadas, banderas puestas o cualquier cambio que tambien se realiza
    apartir del menu que aparece en este ciclo, donde se pedira ingresar el numero de la fila(f) y columna(c)
    que se desea destapar, poner bandera en o quitar bandera de.
    */
    int r=atoi(argv[1]);
    int s=1,o,f,c,cm=0,cn,cf,col;
    mina** matrix;
    switch(r){
        case 1:
                r=8;
                col=8;
                cf=10;
                break;
        case 2:
                r=16;
                col=16;
                cf=40;
                break;
        case 3:
                r=32;
                col=16;
                cf=99;
                break;
        case 4:
                printf( "Ingrese la cantidad de filas que tendra su juego\n");
                scanf("%d",&r);
                printf( "Ingrese la cantidad de columnas que tendra su juego\n");
                scanf("%d",&col);
                printf( "Ingrese la cantidad de minas que tendra su juego\n");
                scanf("%d",&cf);
                break;
        default:
                printf("Nivel no encontrado");
                break;
    }
    if(atoi(argv[1])<=4&&atoi(argv[1])>=1){
        cn=0;
        matrix=llenarc(matrix,r,col,cf,&cm);
        matrix=llenarn(matrix,r,col,&cn);
        while (s!=0&&cn!=0){
            dibujar(matrix,r,col,&cm,&cf);
            printf( "\n 1: Poner/quitar una bandera \n 2: Destapar una casilla\n 3: Salir\n");
            scanf("%d",&o);
            if(o==1||o==2){
                printf("\n Fila:");
                scanf("%d",&f);
                printf("\n Columna:");
                scanf("%d",&c);
                if (f<=r&&f>0&&c<=col&&c>0){
                    if(matrix[f-1][c-1].v==0){
                        matrix=ceros(matrix,f-1,c-1,&cn,r);
                    }else{
                        matrix=jugar(matrix,o,f-1,c-1,&s,&cm,&cn);
                    }
                }
            }else{
                if(o==3){
                    break;
                }else{
                    printf(" Opcion incorrecta\n");
                }  
            }
        }
    }
    if(cn==0){
        printf(" Ha ganado, felicidades\n");
    }
    if(s==0){
        printf(" Ha perdido, intentalo de nuevo\n");
    }
}
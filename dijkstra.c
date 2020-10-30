#include<stdio.h>
 
#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL -1
 
void buscarCamino(int routOrigen, int routDestino);
void Dijkstra( int routOrigen);
int min_temp( );
void dibujarGrafo();
 
int n;    // Número de routers
int matriz[MAX][MAX]; //Matriz de Adyacencia donde se guardan los costos
int predecessor[MAX];   /*predecessor of each vertex in shortest path*/
int pathLength[MAX];
int status[MAX];
 
int main()
{
        int routOrigen,routDestino;
 
        dibujarGrafo();
 
        printf("\nIngrece el router de origen: ");
        scanf("%d",&routOrigen);
 
        Dijkstra(routOrigen);
 
        while(1)
        {
                printf("\nIngrese el router de destino: ");
                scanf("%d",&routDestino);
                if(routDestino == -1)
                        break;
                if(routDestino < 0 || routDestino >= n )
                        printf("\nEl router no existe\n");
                else if(routDestino == routOrigen)
                        printf("\nRouter de origen y destino son iguales\n");
                else if( pathLength[routDestino] == infinity )
            printf("\nNo hay camino para este destino\n");
                else
                        buscarCamino(routOrigen,routDestino);
        }
 
        return 0;
}
 
void Dijkstra( int routOrigen)
{
        int i,current;
 
        /* Make all vertices temporary */
        for(i=0; i<n; i++)
        {
                predecessor[i] =  NIL;
                pathLength[i] = infinity;
                status[i] = TEMP; //0 si aun no pasa
        }
        /* Make pathLength of source vertex equal to 0 */
        pathLength[routOrigen] = 0;
 
        while(1)
        {
                /*Search for temporary vertex with minimum pathLength
                and make it current vertex*/
                current = min_temp( );
 
                if( current == NIL )
                        return;
 
                status[current] = PERM; //1 ya paso
 
                for(i=0; i<n; i++)
                {
                        /*Checks for adjacent temporary vertices */
                        if ( matriz[current][i] !=0 && status[i] == TEMP )
                                if( pathLength[current] + matriz[current][i] < pathLength[i] )
                                {
                                        predecessor[i] = current;  /*Relabel*/
                                        pathLength[i] = pathLength[current] + matriz[current][i];
                                }
                }
        }
}
 
/*Returns the temporary vertex with minimum value of pathLength
  Returns NIL if no temporary vertex left or
  all temporary vertices left have pathLength infinity*/
int min_temp( )
{
        int i;
        int min = infinity;
        int k = NIL;
        for(i=0;i<n;i++)
        {
                if(status[i] == TEMP && pathLength[i] < min)
                {
                        min = pathLength[i];
                        k = i;
                }
        }
        return k;
}
 
 
void buscarCamino(int routOrigen, int routDestino)
{
        int i,u;
        int camino[MAX];          /*se almacenan los nodos del camino mas corto*/
        int shortdist = 0;      /*length of shortest path (costo)*/
        int contador = 0;          /*number of vertices in the shortest path*/
 
        /*Store the full path in the array path*/
        while( routDestino != routOrigen ) //bucle de atras hacia adelante 
        {
                contador++;
                camino[contador] = routDestino;
                u = predecessor[routDestino];
                shortdist += matriz[u][routDestino];
                routDestino = u;
        }
        contador++;
        camino[contador]=routOrigen;
 
        printf("\nEl camino mas corto es: ");
        for(i=contador; i>=1; i--)
                printf("%d  ",camino[i]);
        printf("\nLa distancia mas corta es: %d\n", shortdist);
}
 
void dibujarGrafo()
{
        int i,max_edges,origin,destin, wt;
 
        printf("\nIngrese el número de routers: ");
        scanf("%d",&n);
        max_edges = n*(n-1);
        
        int router = 0;
 		int c=1;
 	
	printf("\nAhora ingresara las aristas y los pesos de los routers");
        printf("\nLas aristas deben ser ingresadas con espacios (por ejemplo: 0 1 representa la arista del router 0 al 1)\n");
	
        for(i=1;i<=max_edges;i++)
        {
     
                printf("\nIngrese los lados del router %d: ",router);
                scanf("%d %d",&origin,&destin);
                if(c==n-1){
                	c=1;
                	router=router+1;
				}else{
					c=c+1;
				}
                
 
                if( (origin == -1) && (destin == -1) )
                        break;
 
                printf("\nIngrese el peso de la arista: ");
                scanf("%d",&wt);
 
                if( origin >= n || destin >= n || origin<0 || destin<0)
                {
                        printf("\nArista Invalida!\n");
                        i--;
                }
                else
                        matriz[origin][destin] = wt;
        }
}

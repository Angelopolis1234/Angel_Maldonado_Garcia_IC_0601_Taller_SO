//LIBRERIA SIMBOLOS ESTANDAR
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//LIBRERIAS PARA LOS SOCKETS
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define TAM 300
#define TAM2 925

//VARIABLES GLOBALES
int SERVER_PORT=0;

int main(int argc, char *argv[]){ //obtendremos el servidor
  system("clear");
  if(argc < 2){
    printf("[SERVER]::Falata el puerto, ingrese ahora:");
    char Puerto[4];
    gets(Puerto);
    SERVER_PORT = atoi(Puerto);
  }else{
    SERVER_PORT = atoi(argv[1]);
  }
  //printf("Puerto: %d\n",SERVER_PORT);
  system("clear");
  int FD,FD2,LEN_CLIENT;
  int SERVER_SOCKET;

  struct sockaddr_in SERVER;
  struct sockaddr_in CLIENT;

  //CONFIGURAMOS EL SERVIDOR
  SERVER.sin_family = AF_INET; //DECLARAMOS LA NATURALEZA DEL SOCKET ( TCP/IP )
  SERVER.sin_port = htons(SERVER_PORT); //DECLARAMOS EL PUERTO DEL SERVIDOR 
  SERVER.sin_addr.s_addr = INADDR_ANY; //CUALQUIER CLIENTE PUDE CONECTARSE
  bzero(&(SERVER.sin_zero),8); //RELLENAMOS CON CEROS
  
  SERVER_SOCKET = socket(AF_INET, SOCK_STREAM,0);
  FD = SERVER_SOCKET;
  if(SERVER_SOCKET < 0){
    perror("[SERVER]::Error al abrir el socket");
    return -1;
  }else{
    perror("[SERVER]::Exito al abrir el socket");
  }
  //CREAMOS EL SERVIDOR CON BIND
  if(bind(SERVER_SOCKET,(struct sockaddr*)&SERVER, sizeof(struct sockaddr)) == -1){
    perror("[SERVER]::Error con el BIND");
    return -1;
  }else{
    printf("[SERVER]::Bind asignado\n");
  }
  if(listen(SERVER_SOCKET,5) == -1){
    perror("[SERVER]::Error en escucha");
    return -1;
  }
  //aceptamos conexiones
  printf("[SERVER]::En escucha...\n");
  while(1){
    LEN_CLIENT = sizeof(struct sockaddr_in);
    if((FD2 = accept(SERVER_SOCKET,(struct sockaddr*)&CLIENT,&LEN_CLIENT)) == -1){
      perror("[SERVER]::Error en las conexiones");
      return -1;
    }
    //puts("[SERVER]::En espera...");
    send(FD2,"BIENVENIDO AL SERVIDOR CALCULADORA\n",TAM2,0);
    char NUM1[TAM],NUM2[TAM];
    int Bytes=0;
    Bytes = recv(FD2,NUM1,TAM2,0);
    NUM1[Bytes] = '\0';
    send(FD2,NUM1,TAM,0);
    Bytes = recv(FD2,NUM2,TAM2,0);
    NUM2[Bytes] = '\0';
    send(FD2,NUM2,TAM2,0);

    char aa[202],bb[202];
    int a[202],b[202],c[203];
    int i,j,k,ki;
    strcpy(aa,NUM1);
    strcpy(bb,NUM2);
    int m,n,len;
    m=strlen(aa);
    n=strlen(bb);
    len = ( m > n)? m:n ;
    for ( i=0; i<m; i++)
      a[i]=aa[i]-'0'; //i=m;
    for ( j=0; j<n; j++)
      b[j]=bb[j]-'0'; //j=n;
    for( i=m-1,j=n-1,k=len-1; i>=0 && j>=0; i--,j--,k--){
      c[k] = a[i] + b[j];
    }
    for( ;i>=0; i--,k--)
      c[k] = a[i];
    for( ;j>=0; j--,k--)
      c [k] = b [j]; // Alto guardado
         // Cada décimo
    for( k=len-1; k>0; k--){
      if( c[k] >9 ){
	c[k] = c[k]%10;
        c[k-1] += 1;
      }
    }
    char res[TAM];
    for( k=0; k<len; k++)
      sprintf(&res[strlen(res)],"%d",c[k]);
    send(FD2,res,TAM2,0);


    close(FD2);
  }
  close(SERVER_SOCKET);
  
  
  return 0;
} 


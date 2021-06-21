#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//LIBRERIAS PARA LOS SOCKETS
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define TAM 300
#define TAM2 925

int main(int argc, char *argv[]){
  int PORT;
  char *IP;
  system("clear");
  if(argc < 3){
    printf("[CLIENT]::Error, parametro del ip/puerto vacio. \n\t\tIngresa la ip: ");
    char portc[4];
    gets(portc);
    PORT = atoi(portc);
    printf("\t\tIngresa el puerto: ");
    gets(IP);//LA ESTRUCTURA ES LA SIGUIENTE: 255.255.255.255 EJ: 192.168.1.1
  }else{
    IP = argv[1];
    PORT = atoi(argv[2]);
  }

  //DECLARAMOS LAS VARIABLES LOCALES
  int FD, nBytes;
  char BUF[TAM];

  struct hostent *HOST; //ENTIDAD QUE RECIBIRA INFORMACION DEL HOST
  struct sockaddr_in SERVER; //INFORMACION SOBRE LA DIRECCION DEL SERVIDOR

  if((HOST=gethostbyname(IP)) == NULL){ //LLAMAMOS AL HOST Y COMPARAMOS LA SALIDA PARA DETECTAR ERRORES
    perror("[CLIENT]::Error de gethostname().");
    return -1;
  }
  if((FD = socket(AF_INET, SOCK_STREAM, 0)) == -1){//CREAMOS EL SOCKET Y DETECTAMOS ERRORES
    perror("[CLIENT]::Error en la creacion del socket.");
    return -1;
  }
  //ASIGNAMOS LOS DATOS AL SERVIDOR
  SERVER.sin_family = AF_INET;
  SERVER.sin_port = htons(PORT);
  SERVER.sin_addr = *((struct in_addr *)HOST->h_addr);
  bzero(&(SERVER.sin_zero),8);

  //NOS CONECTAMOS AL SERVIDOR
  if(connect(FD, (struct sockaddr *)&SERVER, sizeof(struct sockaddr)) == -1){
    perror("[CLIENT]::Error al conectarse con el servidor.");
    return -1;
  }
  //LLAMAMOS A RECV 
  nBytes = recv(FD,BUF,TAM2,0);
  BUF[nBytes] = '\0';
  printf("Mensaje: [SERVER]::%s\n",BUF);
  char num1[TAM], num2[TAM], *num = (char *)malloc(TAM);
  printf("[CLIENT]::Envia primer numero:");
  scanf("%s",num);
  strcpy(num1,num);
  send(FD,num1,TAM2,0);
  nBytes = recv(FD,BUF,TAM2,0);
  BUF[nBytes] = '\0';
  printf("[SERVER]::Recibio: %s\n",BUF);
  printf("[CLIENT]::Envia segundo numero:");
  scanf("%s",num);
  strcpy(num2,num);
  send(FD,num2,TAM2,0);
  nBytes = recv(FD,BUF,TAM2,0);
  BUF[nBytes] = '\0';
  printf("[SERVER]::Recibio: %s\n",BUF);
  nBytes = recv(FD,BUF,TAM2,0);
  BUF[nBytes] = '\0';
  printf("\n[SERVER]::RESULTADO DE LA SUMA: %s\n",BUF);
  close(FD);
}

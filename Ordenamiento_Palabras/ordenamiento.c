#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMP 40
#define TAM 1000

//--------------------------------------------------------------------------------------------------------------------DECLARACION DE ESTRUCTURAS

typedef struct nodo{
  char palabra[TAMP];
  struct nodo *subDer;
  struct nodo *subIzq;
}hoja;

typedef struct{
  char palabra[TAMP];
}Diccionario;

hoja *arbol = NULL;

//--------------------------------------------------------------------------------------------------------------------DECLARACION DE FUNCIONES

void insertarElemento(char *palabra);//Funcion para agragar y ligar elementos
void inOrden(hoja *raiz);//Funcion de busqueda basada en un arbol binario
void insertarEnDiccionario(Diccionario *diccionario, char *palabra);
void escribirArrayInOrden(hoja *raiz);

//--------------------------------------------------------------------------------------------------------------------FUNCION MAIN
int cont=0;
char word[TAMP];
FILE *fichero_Salida;
int main(int argc, char *argv[]){
  system("clear");
  Diccionario diccionario[TAM];
  FILE *fichero_Entrada;
  fichero_Entrada = fopen(argv[1],"r");
  char palabra[TAMP];
  int i=0, j=0;
  if(fichero_Entrada == NULL){
    printf("\t**El fichero no se ha podido abrir o el fichero no existe\n\n");
  }else{
    printf("\n\n--Leyendo\n\n");
    while(!feof(fichero_Entrada)){
      //fflus(stdin);
      fscanf(fichero_Entrada,"%s",palabra);
      if(strcmp(palabra,"") != 0){
	insertarElemento(palabra);
	insertarEnDiccionario(&diccionario[i],palabra);
	i++;
      }
      memset(palabra,0,TAMP);
    }
  }
  printf("\n\t----------------Palabras del archivo:\n\n");
  while(j<i){
    printf("Obtenido y procesado -> [ %s ]\n",diccionario[j].palabra);
    j++;
  }
  printf("\n\n\tOrdenamiento por arbol binario:\n\n");
  inOrden(arbol);
  fclose(fichero_Entrada);
  printf("\n\t---->Creando el archivo [ %s ]\n\n",argv[2]);
  fichero_Salida = fopen(argv[2],"w");
  printf("\n\n------->Archivo listo\n\nEscribiendo en el...\n\n");
  escribirArrayInOrden(arbol);
  fclose(fichero_Salida);
  printf("\n\n\t------->Fichero escrito\n\n\t\t----------------->Contenido:\n\n");
  char cat[TAMP] = "cat ";
  strcat(cat,argv[2]);
  system(cat);
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------DESARROLLO DE FUNCIONES

void insertarElemento(char *palabra){
  //printf("Funcion Insertar Elemento\n");
  if(arbol == NULL){
    //printf("Arbol NULL\n");
    arbol = (hoja*)malloc(sizeof(hoja));
    if(arbol != NULL){
      //printf("Arbol no NULL\n");
      strcpy(arbol->palabra,palabra);
      arbol->subDer = NULL;
      arbol->subIzq = NULL;
    }
  }else{
    //printf("Paso al else\n");
    hoja *copia, *aux;
    bool igual=false;
    copia = arbol;
    aux = NULL;
    while(copia != NULL && igual==false){
      if(strcmp(palabra,copia->palabra) > 0){
	aux = copia;
	copia = copia->subDer;
      }else if(strcmp(palabra,copia->palabra) < 0){
	aux = copia;
	copia = copia->subIzq;
      }else{
	igual = true;
      }
    }
    if(igual==false){
      //printf("Informacion: [ %s ]\n",aux->palabra);
      hoja *nuevaHoja;
      nuevaHoja = (hoja*)malloc(sizeof(hoja));
      if(nuevaHoja != NULL){
	nuevaHoja=(hoja*)malloc(sizeof(hoja));
	strcpy(nuevaHoja->palabra,palabra);
	nuevaHoja->subDer = NULL;
	nuevaHoja->subIzq = NULL;
	if(strcmp(palabra,aux->palabra) < 0){
	  aux->subIzq = nuevaHoja;
	  //printf("Agregado[ %s ]\n",nuevaHoja->palabra);
	}else{
	  aux->subDer = nuevaHoja;
	  //printf("Agregado[ %s ]\n",nuevaHoja->palabra);
	}
      }
    }
  }
};
void inOrden(hoja *raiz){
  if(raiz != NULL){
    inOrden(raiz->subIzq);
    printf("Informacion [ %s ]\n",raiz->palabra);
    inOrden(raiz->subDer);
  }
};

void insertarEnDiccionario(Diccionario *diccionario, char *palabra){
  strcpy(diccionario->palabra,palabra);
};
void escribirArrayInOrden(hoja *raiz){
  if(raiz != NULL){
    escribirArrayInOrden(raiz->subIzq);
    strcpy(word,raiz->palabra);
    fprintf(fichero_Salida,"%s\n",word);
    escribirArrayInOrden(raiz->subDer);
  }
};

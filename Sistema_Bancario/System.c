/*
CODIGO REALIZADO POR ANGEL MALDONADO GARCÍA IC-0601 ING. SISTEMAS COMPUTACIONALES
*/

//DECLARAMOS LAS CABECERAS------------------------------------------------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//DEFINIMOS LAS CONSTANTES-------------------------------------------------------------------------------------------------------------------------------------------

#define MOSTRAR_MENU_PRIN 0
#define LIMITE_PAISES 5
#define LIMITE_CLIENTES 10
#define ALTA 1
#define BAJA 2
#define MOSTRAR_TODO 3
#define MOSTRAR_ESPECIFICO 4
#define MOSTRAR_OCUPADOS 5
#define ABONAR 6
#define RETIRAR 7
#define BUSCAR_ID_VACIO_ESTRUCTURA 8
#define ESTA_LLENA_ESTRUCTURA 9
#define ESTA_VACIA_ESTRUCTURA 10
#define IMPRIMIR_NOM_PAISES 11
#define MOSTRAR_LONGITUDES 12
#define ACTUALIZAR 13
#define SALIR 14
#define ACTUALIZAR_MOSTRAR_MENU 0
#define ACTUALIZAR_NOMBRE 1
#define ACTUALIZAR_SEXO 2
#define SALIR_ACTUALIZAR 3
#define TAM 100

//DEFINIMOS LAS ESTRUCTURAS------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{
    char nombre[20];
    char sexo;
    double saldo;
    int ocupado; //Ocuparemos 0 para false y 1 para true
}Cliente;

typedef struct{
    char nombrePais[10];
    int aOcupar;
    Cliente clientes[TAM];
}Banco;

typedef struct{
    int pais;
    int cliente;
}Indices;

//DEFINIMOS LAS VARIABLES GENRALES---------------------------------------------------------------------------------------------------------------------------------

//DEFINIMOS LAS FUNCIONES------------------------------------------------------------------------------------------------------------------------------------------

//Funciones de los datos----------------------------------------------------------------<
int Entero(char mensaje[]);
char* Cadena(char mensaje[]);
double Double(char mensaje[]);

//Funciones del Cliente ----------------------------------------------------------------<
void setTodosDatosF(Cliente *cliente);
void setTodosDatos(char *nombre, char sexo, double saldo, Cliente *cliente);
void validarSexo(char sexo, Cliente *cliente);
void validarSaldo(float saldo, Cliente *cliente);
int tieneSaldo(Cliente *cliente); //Retornaremos un 1 si es True o un 0 si es False
int tieneDatos(Cliente *cliente); //Retornaremos un 1 si es True o un 0 si es False
void setOcupado(Cliente *cliente);
char* getNombre(Cliente *cliente);
char getSexo(Cliente *cliente);
double getSaldo(Cliente *cliente);
int isOcupado(Cliente *cliente); //Retornaremos un 1 si es True o un 0 si es False
void eliminar(Cliente *cliente);
void cambiarNombre(char *nuevoNombre, Cliente *cliente);
void cambiarSexo(char sexo, Cliente *cliente);
void abonarSaldo(double cuanto, Cliente *cliente);
void retirarSaldo(double cuanto, Cliente *cliente);
void imprimirCliente(Cliente *cliente);
Cliente getTodosDatos(Cliente *cliente);

//Funciones del Banco-----------------------------------------------------------------<
int getTotalClientes(Banco *banco);
int isTodoOcupado(Banco *banco);//Retornaremos un 1 si es True o un 0 si es False
int isTodoVacio(Banco *banco);//Retornaremos un 1 si es True o un 0 si es False
int existeEspacioVacio(Banco *banco);//Retornaremos un 1 si es True o un 0 si es False
int existeEspacioOcupado(Banco *banco);//Retornaremos un 1 si es True o un 0 si es False
int indiceVacio(Banco *banco);
int printSoloOcupados(Banco *banco);//Retornaremos un 1 si es True o un 0 si es False
void printTodosClientes(Banco *banco);
void printEspecifico(Banco *banco, int cliente);
char* getNombrePais(Banco *banco);
void setNombrePais(Banco *banco, char *nombre);
Cliente getEspecificoCliente(Banco *banco, int index);
char* getNombreCliente(Banco *banco, int index);
char getSexoCliente(Banco *banco, int index);
double getSaldoCliente(Banco *banco, int index);
int getIsOcupadoCliente(Banco *banco, int index);//Retornaremos un 1 si es True o un 0 si es False
void eliminarCliente(Banco *banco, int index);
void cambiarNombreCliente(Banco *banco, char *nuevoNombre, int index);
void cambiarSexoCliente(Banco *banco, char nuevoSexo, int index);
void abonarSaldoCliente(Banco *banco, double cuanto, int index);
void retirarSaldoCliente(Banco *banco, double cuanto, int index);
void printCliente(Banco *banco, int index);
int getaOcupar(Banco *banco);

//Funciones propias del main--------------------------------------------------------------<
void mostrarLongitudes(Banco banco[],int tope);
void imprimirTodo(Banco banco[], int tope);
void imprimirSoloOcupados(Banco banco[],int tope);
void introducirPaises(Banco banco[],int tope);
int validarRango(int inicio, int fin, char mensaje[]);
int hayEspacioVacioTodaEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
Indices indiceVcioTodaEstructura(Banco banco[]);
int estaTodoLlenoEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
int estaTodoVacioEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
int indiceVacioPaisEspecifico(int pais, Banco banco[]);
char* pedirNombrePais3(int inicio, char *mensaje, Banco banco[]);
int estaNombreRepetido(int inicio, char *nombrePais, Banco banco[]);
int getIndicePais(char *nombrePais, Banco banco[]);
int seEncuentraNombre(char *nombrePais, Banco Banco[]);//Retornaremos un 1 si es True o un 0 si es False
char* pedirNombrePais2(char mensaje[], Banco banco[]);
void instrucciones();
void instruccionesActualizar();
void imprimirPaises(Banco banco[]);
void saltoLinea();

//FUNCION MAIN---------------------------------------------------------------------------------------------------------------------------------------------------



//DESARROLLO DE FUNCIONES----------------------------------------------------------------------------------------------------------------------------------------

//Funciones de Datos------------------------------------------------------------------<
int Entero(char mensaje[]){
    int longitud = strlen(mensaje);// Quitar espacios, saltos de línea, etcétera
    while (longitud > 0 && isspace(mensaje[longitud - 1]))
        longitud--;
    if (longitud <= 0) return 0;
    for (int i = 0; i < longitud; ++i) {// En caso de que sea un guión, y que no esté al inicio, no es válido
        if (mensaje[i] == '-' && i > 0) {
            return 0;
        } // Si no es dígito, tampoco es válido
        if (!isdigit(mensaje[i]) && mensaje[i] != '-') {
            return 0;
        }
    }
    int digito=atoi(mensaje);
    return digito;
};
char* Cadena(char mensaje[]){
  return mensaje;  
};
double Double(char mensaje[]){
int longitud = strlen(mensaje);// Quitar espacios, saltos de línea, etcétera
    while (longitud > 0 && isspace(mensaje[longitud - 1]))
        longitud--;
    if (longitud <= 0) return 0;
    int i;
    int haEncontradoElPunto = 0;
    for (i = 0; i < longitud; ++i) {// En caso de que sea un guión, y que no esté al inicio, no es válido
        if (mensaje[i] == '-' && i > 0) {
            return 0;
        }// El punto solo puede aparecer una vez
        if (mensaje[i] == '.') {// Si ya lo ha encontrado antes, entonces no es válido
            if (haEncontradoElPunto) {
                return 0;
            } else {

                haEncontradoElPunto = 1;
            }
        }// Si no es dígito, tampoco es válido
        if (!isdigit(mensaje[i]) && mensaje[i] != '-' && mensaje[i] != '.') {
            return 0;
        }
    }
    double doble=0.0;
    doble=atof(mensaje);
    return doble;
};

//Funciones del cliente---------------------------------------------------------------<
void setTodosDatosF(Cliente *cliente){
    strcpy(cliente->nombre," ");
    cliente->ocupado = 0;//false
    cliente->saldo = 0.0;
    cliente->sexo = " ";
};
void setTodosDatos(char *nombre, char sexo, double saldo, Cliente *cliente){
    strcpy(cliente->nombre,nombre);
    cliente->sexo=sexo;
    cliente->saldo=saldo;
    cliente->ocupado=1;//true
};
void validarSexo(char sexo, Cliente *cliente){
    if(sexo != "M" && sexo != "F"){
        sexo=" ";
    }
    cliente->sexo=sexo;
};
void validarSaldo(float saldo, Cliente *cliente){
    if(saldo<=0){
        saldo=0.0;
    }
    cliente->saldo=saldo;
};
int tieneSaldo(Cliente *cliente){//Retornaremos un 1 si es True o un 0 si es False
    if(cliente->saldo > 0.0){
        return 1;
    }else{
        return 0;
    }
}; 
int tieneDatos(Cliente *cliente){//Retornaremos un 1 si es True o un 0 si es False
    if(cliente->ocupado==1){
        return 1;//esta ocupado
    }else{
        return 0;//no esta ocupado
    }
}; 
void setOcupado(Cliente *cliente){
    cliente->ocupado==1;
};
char* getNombre(Cliente *cliente){
    return cliente->nombre;
};
char getSexo(Cliente *cliente){
    return cliente->sexo;
};
double getSaldo(Cliente *cliente){
    return cliente->saldo;
};
int isOcupado(Cliente *cliente){//Retornaremos un 1 si es True o un 0 si es False
    return cliente->ocupado;
}; 
void eliminar(Cliente *cliente){
    setTodosDatosF(cliente);
};
void cambiarNombre(char *nuevoNombre, Cliente *cliente){
    strcpy(cliente->nombre,nuevoNombre);
};
void cambiarSexo(char sexo, Cliente *cliente){
    cliente->sexo=sexo;
};
void abonarSaldo(double cuanto, Cliente *cliente){
    if(cliente->ocupado==1){
        if(cuanto > 0.0){
            cliente->saldo += cuanto;
        }else{
            printf("Imposible, no puedes abonar saldos negativos o nada.");
        }
    }
};
void retirarSaldo(double cuanto, Cliente *cliente){
    if(cliente->ocupado==1){
        if(cuanto > 0.0){
            if(tieneSaldo(cliente)==1){
                if(cliente->saldo >= cuanto){
                    cliente->saldo -= cuanto;
                }else{
                    printf("Imposible, no hay saldo suficiente.");
                }
            }else{
                printf("Imposible, no tienes saldo.");
            }
        }else{
            printf("Imposible, no puedes retirar saldos negativos o nada.");
        }
    }
};
void imprimirCliente(Cliente *cliente){
    printf(" Nombre: %s",cliente->nombre);
    printf("   Sexo: %c",cliente->sexo);
    printf("  Saldo: %f",cliente->saldo);
    if(cliente->ocupado==1){
        printf("Ocupado: True");
    }else{
        printf("Ocupado: False");
    }
};
Cliente getTodosDatos(Cliente *cliente){
    Cliente *temporal = cliente;
    strcpy(temporal->nombre,getNombre(cliente));
    temporal->sexo = getSexo(cliente);
    temporal->saldo = getSaldo(cliente);
    temporal->ocupado = isOcupado(cliente);
    return *temporal;
};

//Funciones de Banco--------------------------------------------------------------<
int getTotalClientes(Banco *banco){
    return banco->aOcupar;
}
int isTodoOcupado(Banco *banco){//Retornaremos un 1 si es True o un 0 si es False
    int todo_ocupado = 0; //False
    int contador = 0;
    for(int i=0 ; i<getTotalClientes(banco) ; i++){
        if(getIsOcupadoCliente(banco,i)==1){
            contador++;
        }
    }
    if(contador == getTotalClientes(banco)){
        todo_ocupado = 1; //True
    }
    return todo_ocupado;
};
int isTodoVacio(Banco *banco){//Retornaremos un 1 si es True o un 0 si es False
    int todo_vacio = 0; //False
    int contador = 0;
    for(int i=0; i<getTotalClientes(banco); i++){
        if(getIsOcupadoCliente(banco,i)==0){
            contador++;
        }
    }
    if(contador == getTotalClientes(banco)){
        todo_vacio = 1;//True
    }
    return todo_vacio;
};
int existeEspacioVacio(Banco *banco){//Retornaremos un 1 si es True o un 0 si es False
    int existeVacio = 0;//False
    for(int i=0; i<getTotalClientes(banco); i++){
        if(getIsOcupadoCliente(banco,i) == 0){
            existeVacio = 1;//True
            break;
        }
    }
    return existeVacio;
};
int existeEspacioOcupado(Banco *banco){//Retornaremos un 1 si es True o un 0 si es False
    int existeOcupado = 0;//False
    for(int i=0; i<getTotalClientes(banco); i++){
        if(getIsOcupadoCliente(banco,i) == 1){
            existeOcupado = 1;//True
            break;
        }
    }
    return existeOcupado;
};
int indiceVacio(Banco *banco){
    int indexVacio = -1;
    for(int i=0; i<getTotalClientes(banco); i++){
        if(getIsOcupadoCliente(banco,i) == 1){
            indexVacio = i;
            break;
        }
    }
    return indexVacio;
};
int printSoloOcupados(Banco *banco){//Retornaremos un 1 si es True o un 0 si es False
    int imprimio = 0;//False
    if(existeEspacioOcupado(banco) == 1){
        imprimio = 1;//True
        printf("-----------------------------------------------------------------------\n");
        printf("Del pais [ %s ] los clienes disponibles son: \n",getNombrePais(banco));
        for(int i=0; i<getTotalClientes(banco); i++){
            printf("El cliente %i es:\n",i);
            printCliente(banco,i);
        }
        printf("-----------------------------------------------------------------------\n");
    }
    return imprimio;
};
void printTodosClientes(Banco *banco){
    printf("-----------------------------------------------------------------------\n");
    printf("Del pais [ %s ] los clienes disponibles son: \n",getNombrePais(banco));
    for(int i=0; i<getTotalClientes(banco); i++){
        printf("El cliente %i es:\n",i);
        printCliente(banco,i);
    }
    printf("-----------------------------------------------------------------------\n");
};
void printEspecifico(Banco *banco, int cliente){
    printf("-----------------------------------------------------------------------\n");
    printf("Del pais [ %s ] los clienes disponibles son: \n",getNombrePais(banco));
    printCliente(banco, cliente);
};
char* getNombrePais(Banco *banco){
    return banco->nombrePais;
};
void setNombrePais(Banco *banco, char *nombrePais){
    strcpy(banco->nombrePais,nombrePais);
};
Cliente getEspecificoCliente(Banco *banco, int index){
    Cliente auxiliar= banco->clientes[index];
    return auxiliar;
};
char* getNombreCliente(Banco *banco, int index){
    return getNombre(&banco->clientes[index]);
};
char getSexoCliente(Banco *banco, int index){
    return getSexo(&banco->clientes[index]);
};
double getSaldoCliente(Banco *banco, int index){
    return getSaldo(&banco->clientes[index]);
};
int getIsOcupadoCliente(Banco *banco, int index){//Retornaremos un 1 si es True o un 0 si es False
    return isOcupado(&banco->clientes[index]);
};
void eliminarCliente(Banco *banco, int index){
    eliminar(&banco->clientes[index]);
};
void cambiarNombreCliente(Banco *banco, char *nuevoNombre, int index){
    cambiarNombre(nuevoNombre,&banco->clientes[index]);
};
void cambiarSexoCliente(Banco *banco, char nuevoSexo, int index){
    cambiarSexo(nuevoSexo,&banco->clientes[index]);
};
void abonarSaldoCliente(Banco *banco, double cuanto, int index){
    abonarSaldo(cuanto,&banco->clientes[index]);
};
void retirarSaldoCliente(Banco *banco, double cuanto, int index){
    retirarSaldo(cuanto,&banco->clientes[index]);
};
void printCliente(Banco *banco, int index){
    imprimirCliente(&banco->clientes[index]);
};
int getaOcupar(Banco *banco){
    return banco->aOcupar;
};

//Funciones propias del main--------------------------------------------------------------<
void mostrarLongitudes(Banco banco[],int tope){//La variable tope nos ayuda a saber cuantos paises son(cuantos bancos)
    for(int i=0; i<tope; i++){
        printf("\n-->Del pais %s, existen %i clientes.", getNombrePais(&banco[i]), getTotalClientes(&banco[i]));
    }
}
void imprimirTodo(Banco banco[],int tope){
    for(int i=0; i<tope; i++){
        printf("-----------------------------------------------------------------------------------------------------------\n");
        printTodosClientes(&banco[i]);
    }
};
void imprimirSoloOcupados(Banco banco[],int tope){
    int contador=0;
    for(int i=0; i<tope; i++){
        if(printSoloOcupados(banco[i])==1){
            contador++;
        }
    }
    if(contador == 0){
        printf("\n-->No existen clientes que mostrar\n")
    }
};
void introducirPaises(Banco banco[],int tope){
    char mensaje[TAM];
    for(int i=0; i<tope; i++){
        printf("Introduce el nombre del pais %i: ",i);
        gets(mensaje);
        fflush(stdin);
        pedirNombrePais3(i,&mensaje,banco);
    }
};
int validarRango(int inicio, int fin, char mensaje[]);
int hayEspacioVacioTodaEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
Indices indiceVcioTodaEstructura(Banco banco[]);
int estaTodoLlenoEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
int estaTodoVacioEstructura(Banco banco[]);//Retornaremos un 1 si es True o un 0 si es False
int indiceVacioPaisEspecifico(int pais, Banco banco[]);
char* pedirNombrePais3(int inicio, char *mensaje, Banco banco[]);
int estaNombreRepetido(int inicio, char *nombrePais, Banco banco[]);
int getIndicePais(char *nombrePais, Banco banco[]);
int seEncuentraNombre(char *nombrePais, Banco Banco[]);//Retornaremos un 1 si es True o un 0 si es False
char* pedirNombrePais2(char mensaje[], Banco banco[]);
void instrucciones();
void instruccionesActualizar();
void imprimirPaises(Banco banco[]);
void saltoLinea();
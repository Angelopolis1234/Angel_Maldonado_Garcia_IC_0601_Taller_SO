#include <stdio.h>

void ejercicioUno();
void ejercicioDos();

int main(){
	//Ejercicio uno
	printf("\n\n---------------------->Ejercicio 1\n\n");
	ejercicioUno();
	//Ejercicio dos
	printf("\n\n---------------------->Ejercicio 2\n\n");
	ejercicioDos();
	return 0;
}

void ejercicioUno(){
	int x, y, *p, *puntero;
	x = 10;
	p = &x;
	printf("Puntero p[1]: %p\n", p);
	*p++;
	printf("Puntero p[2]: %p\n", p);
	*p += 2;
	printf("Puntero p[3]: %p\n", p);
	y=20;
	puntero = &y;
	printf("Puntero puntero: %p\n", puntero);
};

void ejercicioDos(){
	int arrayInt[5];
	for(int i=0; i<5; i++){
		arrayInt[i]=i;
	}
	int *punteroInt;
	punteroInt = &arrayInt;
	int *punteroIntDos;
	punteroIntDos = &arrayInt[0];
	printf("Contenido primer elemento arrayInt[0]: %i\n", arrayInt[0]);
	printf("Contenido del primer elemento del puntero punteroInt: %i\n", punteroInt[0]);
	printf("Contenido del primer elemento del puntero punteroIntDos: %p\n", punteroIntDos);
	printf("Contenido del quinto elemento del array arrayInt[4]: %i\n", arrayInt[4]);
	printf("Contenido del quinto elemento del puntero punteroInt: %i\n", punteroInt[4]);
	printf("Contenido del quinto elemento del puntero punteroInt con aritmetica de punteros: %i\n", punteroInt+4);
	printf("Contenido del quinto elemento del puntero punteroIntDos con aritmetica de punteros: %i\n", punteroIntDos+4);
	for(int i=0; i<2; i++){
		for(int j=0; j<5; j++){
			printf("Contenido [%i] de punteroIntDos (Aritmetica de Punteros): %p\n",j , punteroIntDos+j);
		}
		if(i==0){printf("------------------->Segunda Vuelta\n\n");}
	}
};

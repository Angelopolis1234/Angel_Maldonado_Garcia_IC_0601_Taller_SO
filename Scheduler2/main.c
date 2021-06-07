#include "scheduler.h"

void *accion_1(void *argv){
	printf("->Reproduciendo musica\n");
}
void *accion_2(void *argv){
	printf("->Usando Youtube\n");
}
void *accion_3(void *argv){
	printf("->Escribiendo texto en Word\n");
}
void *accion_4(void *argv){
	printf("->Descargando archivo\n");
}
void *accion_5(void *argv){
	printf("->Subiendo archivo\n");
}
void *accion_6(void *argv){
	printf("->Compilando programa\n");
}
void *accion_7(void *argv){
	printf("->Ejecutando programa\n");
}
void *accion_8(void *argv){
	printf("->Usando terminal\n");
}

void hilo_reproducir_musica(void){
    pthread_t hilo_proceso_1;
    pthread_create(&hilo_proceso_1,NULL,accion_1,NULL);
    pthread_join(hilo_proceso_1,NULL);
}
void hilo_abrir_youtube(void){
    pthread_t hilo_proceso_2;
    pthread_create(&hilo_proceso_2,NULL,accion_2,NULL);
    pthread_join(hilo_proceso_2,NULL);
}
void hilo_escribir_texto_word(void){
    pthread_t hilo_proceso_3;
    pthread_create(&hilo_proceso_3,NULL,accion_3,NULL);
    pthread_join(hilo_proceso_3,NULL);
    
}
void hilo_descargar_archivo(void){
     pthread_t hilo_proceso_4;
    pthread_create(&hilo_proceso_4,NULL,accion_4,NULL);
    pthread_join(hilo_proceso_4,NULL);
}
void hilo_subiendo_archivo(void){
    pthread_t hilo_proceso_5;
    pthread_create(&hilo_proceso_5,NULL,accion_5,NULL);
    pthread_join(hilo_proceso_5,NULL);
}
void hilo_compilando_programa(void){
    pthread_t hilo_proceso_6;
    pthread_create(&hilo_proceso_6,NULL,accion_6,NULL);
    pthread_join(hilo_proceso_6,NULL);
}
void hilo_ejecutando_programa(void){
    pthread_t hilo_proceso_7;
    pthread_create(&hilo_proceso_7,NULL,accion_7,NULL);
    pthread_join(hilo_proceso_7,NULL);
}
void hilo_usando_terminal(void){
    pthread_t hilo_proceso_8;
    pthread_create(&hilo_proceso_8,NULL,accion_8,NULL);
    pthread_join(hilo_proceso_8,NULL);
}


int main(int argc, char const *argv[]){
    printf("----------------Creando de procesos----------------\n\n");
	process *p1 = crear_Proceso(1, UN_SEGUNDO, "->Proceso_1", hilo_reproducir_musica, ACTIVO); 		//<--
	process *p2 = crear_Proceso(1, DOS_SEGUNDOS, "->Proceso_1", hilo_abrir_youtube, NO_ACTIVO);
	process *p3 = crear_Proceso(3, TRES_SEGUNDOS, "->Proceso_2", hilo_escribir_texto_word, ACTIVO); 	//<--
	process *p4 = crear_Proceso(4, TRES_SEGUNDOS, "->Proceso_3", hilo_descargar_archivo, ACTIVO);   	//<--
	process *p5 = crear_Proceso(3, TRES_SEGUNDOS, "->Proceso_4", hilo_subiendo_archivo, ACTIVO);		
	process *p6 = crear_Proceso(4, TRES_SEGUNDOS, "->Proceso_5", hilo_compilando_programa, NO_ACTIVO);
	process *p7 = crear_Proceso(0, TRES_SEGUNDOS, "->Proceso_6", hilo_ejecutando_programa, ACTIVO);	//<--	
	process *p8 = crear_Proceso(2, CUATRO_SEGUNDOS, "->Proceso_7", hilo_usando_terminal, ACTIVO);		//<--
	process *p9 = crear_Proceso(5, CUATRO_SEGUNDOS, "->Proceso_8", hilo_usando_terminal, NO_ACTIVO);	//<--

    printf("----------------Agregando procesos----------------\n\n");
	array_procesos *array = crear_ArrayProcesos();

	agregar_Proceso(array, *p1);
	agregar_Proceso(array, *p2);
	agregar_Proceso(array, *p3);
	agregar_Proceso(array, *p4);
	agregar_Proceso(array, *p5);
	agregar_Proceso(array, *p6);
	agregar_Proceso(array, *p7);
	agregar_Proceso(array, *p8);
	agregar_Proceso(array, *p9);

    printf("\n----------------Ejecutando procesos----------------\n\n");
	ejecutar_Procesos(array);

	free(array);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(p8);
	free(p9);

	return 0;
}

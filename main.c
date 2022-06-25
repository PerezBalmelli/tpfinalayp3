#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestionAlumnos.h"


// - - - FUNCIONES PARA LOG - - -

/*
 * Obtiene la hora actual.
 * fID: 98
 */
char * ahora() {
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    return asctime (timeinfo);
}

/*
 * Loguea en un archivo la ejecucion de las funciones en el programa.
 * fID: 99
 */
void ftlog(int idFuncion, double tiempoTranscurrido) {
    FILE * log;
    log = fopen("../flog/ftlog.log", "a");
    if(log)
    {
        fprintf(log,"--fID %d in %f on -%s", idFuncion, tiempoTranscurrido, ahora());
        fclose(log);
    }
    else
    {
        printf("\nlog error on %s",ahora());
    }
}

/*
 * --OBLIGATORIO TODO: Lista enlazada de numeros para guardar los IDs de las materias de cada alumno [X]
 * --OBLIGATORIO TODO: Implementar una resolucion de nombre-ID para las materias aprobadas y en curso por cada alumno [X]
 * TODO: Agregar try-catch y logueo de errores [O]
 * TODO: Lectura y guardado de datos (csv) [O]
 * TODO: Backups del log y del archivo principal [O]
 * TODO: Shrink de log [O]
 * TODO: Archivo de configuraciones (Elegir si loguear, auto-shrink, compresion, etc) [O]
 * TODO: Funcion de impresion de arbol de correlatividades [O]
 * --OBLIGATORIO TODO: Interfaz para usuario [O]
 * --OBLIGATORIO TODO: Pruebas y limitaciones temporales y espaciales [O]
 * TODO: Programa en PY para estadisticas (Pandas, Seaborn) [O]
 * --OBLIGATORIO TODO: Implementar arreglo de tamanio variable a materias (analizar alumnos) (No funciona implementacion como se espera) [X]
 * --OBLIGATORIO TODO: Implementar funcion para agregar materia en curso y materia aprobada a alumno. [O]
 * TODO: Modularizar codigo [O]
 */

// - - - Listado de materias- - -

typedef struct ListadoMaterias {
    int cantidadElementos;
    Materia * materias;
}ListadoMaterias;

ListadoMaterias * inicializarListadoMaterias() {

    //-- LOG --
//    clock_t start, end;
//    double cpu_time_used;
//    start = clock();

    ListadoMaterias * listado = (ListadoMaterias *)malloc(sizeof(ListadoMaterias *));
    listado->cantidadElementos = 0;
    Materia * materias = (Materia *)malloc(sizeof(Materia *));
    listado->materias = materias;

    //-- LOG --
//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//    ftlog(4,cpu_time_used);

    return listado;

}

void imprimirMaterias(ListadoMaterias * listado){

    int i;
    Materia * materia;
    for(i = 0; i<listado->cantidadElementos;i++){

        materia = & listado->materias[i];
        printf("@ %s\n", materia->nombre);
    }

}

void agregarMateria(ListadoMaterias * listado, Materia * materia){

    //LA POSICIONA EN EL ARREGLO
    //Se hace un realloc para reservar mas espacio que el que se le dio inicialmente con malloc
//    Materia * materiaTemp = (Materia *)realloc(listado->materias,sizeof(Materia *) * (listado->cantidadElementos+1));
//    if(materiaTemp != NULL){
//        listado->materias = materiaTemp;
//    }


    listado->materias[listado->cantidadElementos] = *materia;
    listado->cantidadElementos++;

}

void agregarNuevaMateria(ListadoMaterias * listado, char * nombre, ListadoMaterias * correlativas){

    //CREA LA MATERIA
    Materia * materia = (Materia *)malloc(sizeof(Materia *));
    materia->nombre = nombre;
    materia->correlativas = correlativas;
    materia->id = listado->cantidadElementos;

    //LA POSICIONA EN EL ARREGLO
    //Se hace un realloc para reservar mas espacio que el que se le dio inicialmente con malloc
    //listado->materias = (Materia *)realloc(listado->materias,sizeof(Materia *) * (listado->cantidadElementos+1));

    listado->materias[listado->cantidadElementos] = *materia;
    listado->cantidadElementos++;
}


// - - Listado de alumnos - -


typedef struct ListadoAlumnos {
    int cantidadElementos;
    Alumno * alumnos;
}ListadoAlumnos;

ListadoAlumnos * inicializarListadoAlumnos() {

    //-- LOG --
//    clock_t start, end;
//    double cpu_time_used;
//    start = clock();

    ListadoAlumnos * listado = (ListadoAlumnos *)malloc(sizeof(ListadoAlumnos));
    listado->cantidadElementos = 0;
    Alumno * alumnos = (Alumno *)malloc(sizeof(Alumno *));
    listado->alumnos = alumnos;

    //-- LOG --
//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//    ftlog(4,cpu_time_used);

    return listado;

}

void agregarNuevoAlumno(ListadoAlumnos * listado, char * nombre, int edad){

    //CREA EL ALUMNO
    Alumno * alumno = (Alumno *)malloc(sizeof(Alumno));
    alumno->id = listado->cantidadElementos;
    alumno->nombre = nombre;
    alumno->edad = edad;
    alumno->materiasEnCurso = inicializarListadoMaterias();
    alumno->materiasAprobadas = inicializarListadoMaterias();

    //LA POSICIONA EN EL ARREGLO
    //Se hace un realloc para reservar mas espacio que el que se le dio inicialmente con malloc
//    listado->alumnos = (Alumno *)realloc(listado->alumnos,sizeof(Alumno *) * (listado->cantidadElementos+1));

    listado->alumnos[listado->cantidadElementos] = *alumno;
    listado->cantidadElementos++;

}

void imprimirAlumnos(ListadoAlumnos * listado){

    int i;
    Alumno * alumno;
    for(i = 0; i<listado->cantidadElementos;i++){

        alumno = & listado->alumnos[i];
        printf("Nombre: %s\n", alumno->nombre);
        printf("Edad: %d\n", alumno->edad);
        printf("- - Materias en curso - -\n");
        imprimirMaterias(alumno->materiasEnCurso);
    }

}

// - - FUNCIONES PARA CURSAR Y APROBAR MATERIAS - -

void cursarMateria(ListadoMaterias * listadoMaterias, ListadoAlumnos * listadoAlumnos, int id_alumno, int id_materia){

    Materia * materia = &listadoMaterias->materias[id_materia];
    Alumno * alumno = &listadoAlumnos->alumnos[id_alumno];

    ListadoMaterias * enCurso = alumno->materiasEnCurso;
    agregarMateria(enCurso,materia);

}


// - - - MAIN - - -


int main() {

    ListadoMaterias * listadoMaterias = inicializarListadoMaterias();

    agregarNuevaMateria(listadoMaterias,"Analisis Matematico I", NULL);
    agregarNuevaMateria(listadoMaterias,"Algebra I",NULL);
    agregarNuevaMateria(listadoMaterias,"Sistemas de representacion",NULL);
    agregarNuevaMateria(listadoMaterias,"IPMC",NULL);
    agregarNuevaMateria(listadoMaterias,"puto",NULL);
    agregarNuevaMateria(listadoMaterias,"el",NULL);
//    agregarNuevaMateria(listadoMaterias,"que",NULL);
//    agregarNuevaMateria(listadoMaterias,"lee",NULL);
//    agregarNuevaMateria(listadoMaterias,"smateria5",NULL);
//    agregarNuevaMateria(listadoMaterias,"6materia",NULL);
//    agregarNuevaMateria(listadoMaterias,"7materia",NULL);
//    agregarNuevaMateria(listadoMaterias,"8materia",NULL);
//    agregarNuevaMateria(listadoMaterias,"9materia",NULL);
//    agregarNuevaMateria(listadoMaterias,"99materia",NULL);

    ListadoAlumnos * listadoAlumnos = inicializarListadoAlumnos();

    agregarNuevoAlumno(listadoAlumnos, "Tomas Saavedra", 20);

    cursarMateria(listadoMaterias,listadoAlumnos,0,0);
    cursarMateria(listadoMaterias,listadoAlumnos,0,1);
    cursarMateria(listadoMaterias,listadoAlumnos,0,2);
    cursarMateria(listadoMaterias,listadoAlumnos,0,3);
    cursarMateria(listadoMaterias,listadoAlumnos,0,4);
    cursarMateria(listadoMaterias,listadoAlumnos,0,5);
//    cursarMateria(listadoMaterias,listadoAlumnos,0,7);

    imprimirAlumnos(listadoAlumnos);

    return 0;
}
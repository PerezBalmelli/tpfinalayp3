
#ifndef TPLISTA_GESTIONALUMNOS_H
#define TPLISTA_GESTIONALUMNOS_H

typedef struct{
    int id;
    char * nombre;
    struct ListadoMaterias * correlativas;
}Materia;

typedef struct{
    int id;
    char * nombre;
    int edad;
    struct ListadoMaterias * materiasEnCurso;
    struct ListadoMaterias * materiasAprobadas;
}Alumno;
#endif //TPLISTA_GESTIONALUMNOS_H

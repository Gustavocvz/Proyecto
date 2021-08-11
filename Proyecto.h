#ifndef PROYECTO_H
#define PROYECTO_H

typedef int INFO;
typedef struct _nodo NODO;
struct _nodo{
    INFO info;
    NODO *siguiente;
};


struct _lista{
    NODO *head;
    NODO *tail;
    int num;
};

typedef struct _lista LISTA;


NODO* crear_nodo(INFO info);
LISTA* crear_lista();
bool insertar_inicio(LISTA* lista,INFO info);
bool insertar_final(LISTA* lista, INFO info);
bool insertar(LISTA* lista,INFO info,int pos); 
bool es_vacia(LISTA *lista);
bool vaciar(LISTA* lista);
void imprimir_lista(LISTA* lista);
void EliminarNodo(NODO* nodo);
void EliminarAlInicio(LISTA* lista);
void EliminarAlFinal(LISTA* lista);
void Eliminar(LISTA* lista,int posicion);
void Pop(LISTA* lista,int posicion,int *punt);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "PROYECTO.h"



int main(){
    
    Actividad1();

    system ("PAUSE");
    return 0;
    
}

void Actividad1(){
    LISTA *primerlista;
    primerlista= crear_lista();

    char *entrada;//Entrada: Una cadena en notación infija:s
    int variablepop, i=0, num_op=0, num=0;
    char salida[num];//Entrada: Una cadena en notación postfija:s´
    int prioridad[num_op];

    Leer_cadena("Ingresa operación: ",&entrada);  
    // 1 Obtener los caracteres de la expresion y repetir los pasos 2 y 4 

    //Damos prioridad de los operadores         
    
    while(entrada[i]!='\000'){ 
        
        num++;

        if((entrada[i])==('+')||(entrada[i])=='-'){
            prioridad[i]=1;
            num_op++;
        }
    
        if((entrada[i])==('(')||(entrada[i])==(')')){
            prioridad[i]=5;
            num_op++;
        }    

        if((entrada[i])==('*')||(entrada[i])==('/')){
            prioridad[i]=2; 
        }   

        if((entrada[i])=='^'){
            prioridad[i]=4;  
            num_op++;
        }

        else{
        prioridad[i]=prioridad[i+1];
        i=i+1;

        }

    }

    for(i=0; i<=num; i++){ //para cada caracter de la cadena s hacer
        if(entrada[i]>=97 && entrada[i]<=122)//2 Si es operando entonces
            printf("\nEntra en 's %c",entrada[i]);//Pasarlo a la expresión postfija
        
        else{ //si no
            if(entrada[i]=='+'||entrada[i]=='-'||entrada[i]=='*'||entrada[i]=='/'||entrada[i]==')'){ // 3 Si es operador
                if(es_vacia(primerlista)){//si la pila está vacía entonces 
                    insertar(primerlista,entrada[i],0);//Meter en la pila
                    printf("\n Ingreso a la pila");
                    imprimir_lista(primerlista);
                }
    
                else{// 3.2 Si la pila no esta vacia
                    if(prioridad[i]>prioridad[i-1]){ //3.2.1 Si la propiedade del operador es >prioridad cima entonces
                        insertar(primerlista,entrada[i],0);//Meterlo en la pila
                        printf("\n Ingreso a la pila");
                        imprimir_lista(primerlista);
                    } 

                    else//En otro caso 
                        if(prioridad[i]<=prioridad[i-1]){ //3.2.2 si la prioridad del operador es <= prioridad cima entonces
                            Pop(primerlista,0,variablepop);//Sacar de la pila y ponerlo en la expresión postfija, pasasr paso 3
                            printf("\nEntra en 's %c \n",entrada[i]);
                        } 
                }
            }  
            
            else
                if(entrada[i]=='(') // 4 Si es paréntesis derecho  
                    Pop(primerlista,0,variablepop);//Sacar de la pila y ponerlo en postfija
                //4.3??                
        }
    }

    while(es_vacia(primerlista))
        Pop(primerlista,0,variablepop);  
}

//Funciones

void Leer_cadena(char *d,char **f){
    
    printf("%s",d);
    for(int i =0;1;i++)
    {    
        if(i)//I.e if i!=0
            *f = (char*)realloc((*f),i+1);
        else
            *f = (char*)malloc(i+1);
        (*f)[i]=getchar();
        
        printf("%c \n",(*f)[i]);
        if((*f)[i] == '\n')
        {
            (*f)[i]= '\0';
            break;
        }
    }   
}

NODO* crear_nodo(INFO info){
    NODO* t = (NODO*) malloc(sizeof(NODO));
    t->siguiente = NULL;
    t->info = info;
    return t;
}

LISTA* crear_lista(){
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));
    l->head = l->tail = NULL;
    l->num = 0;
    return l;
}

bool insertar_inicio(LISTA* lista,INFO info){
    NODO* nuevo = crear_nodo(info); // Crear nodo
    if(lista->head==NULL && lista->tail==NULL){
        // Cuando la lista esta vacia
        lista->head = lista->tail = nuevo;
        lista->num++;
        return true;
    }else{
        // Cuando hay uno o mas nodos
        nuevo->siguiente = lista->head;
        lista->head = nuevo;
        lista->num++;
        return true;
    }
    return false;
}

bool insertar_final(LISTA* lista, INFO info){
    NODO* nuevo = crear_nodo(info); // Crear nodo
    if(lista->head==NULL && lista->tail==NULL){
        // Cuando la lista esta vacia
        lista->head = lista->tail = nuevo;
        return true;
    }else{
        lista->tail->siguiente = nuevo;
        lista->tail = nuevo;
        return true;
    }
    return false;
}
// Insertar en posicion p
bool insertar(LISTA* lista,INFO info,int pos){
    if(pos == 0) return insertar_inicio(lista,info);
    else if(pos==lista->num) return insertar_inicio(lista,info);
    else if(pos>0 && pos < lista->num){
        NODO* nuevo = crear_nodo(info);
        NODO* temporal = lista->head;
        int tpos;
        for(tpos = 0; tpos < tpos-1;tpos++){
            temporal = temporal->siguiente;
        }
        nuevo->siguiente = temporal->siguiente;
        temporal->siguiente = nuevo;
        lista->num++;
        return true;
    }
    return false;
}

bool es_vacia(LISTA *lista){
    if(lista->head == NULL && lista->tail == NULL) return true;
    return false;
}

bool vaciar(LISTA* lista){
    NODO* temporal = lista->head;
    while(temporal != NULL){
        lista->head = temporal->siguiente;
        free(temporal);
        temporal = lista->head;
    }
    lista->head = lista->tail = NULL;
    lista->num = 0;
    return 0;
}

void imprimir_lista(LISTA* lista){
    NODO* nodo;
    for(nodo = lista->head; nodo != NULL; nodo = nodo->siguiente){
        printf("%c ---> ",nodo->info);
    }
    printf("NULL\n");
}

void EliminarNodo(NODO* nodo){
    if(nodo->siguiente == NULL){
        free(nodo);
        printf(".");
    }else{
        printf("No se ha podido eliminar.\n");
    }
}

void EliminarAlInicio(LISTA* lista){
    NODO* temporal = lista->head;
    if(es_vacia(lista)) return;
    lista->head = lista->head->siguiente;
    temporal->siguiente=NULL;
    EliminarNodo(temporal);
    lista->num--;
    printf("\n Posicion:%d \n",lista->num);
}

void EliminarAlFinal(LISTA* lista){
    if(es_vacia(lista)) return;
    NODO* temporal =lista->head;
    if (temporal->siguiente!=lista->tail)
    {
        temporal= temporal->siguiente;
    }
    lista->tail=temporal;
    temporal= temporal->siguiente;
    lista->tail->siguiente= NULL;
    EliminarNodo(temporal);
    lista->num--;
    printf("\n Posicion:%d \n",lista->num);
    
}

void Eliminar(LISTA* lista,int posicion){
    if(posicion == 0){
        EliminarAlInicio(lista);
    }else if(posicion == lista->num-1){
        EliminarAlFinal(lista);
    }else if(posicion > 0 && posicion < lista->num-1){

        NODO* temporal = lista->head;
        NODO* temporaldos = lista->head;

        for(int postemporal = 1; postemporal < posicion; postemporal++){
            temporal = temporal->siguiente;
            temporaldos=temporaldos->siguiente;
        }

        temporaldos=temporaldos->siguiente;
        temporal->siguiente=temporal->siguiente->siguiente;
        temporaldos->siguiente=NULL;
        EliminarNodo(temporaldos);
        printf("\n Posicion:%d \n",lista->num);
        lista->num--;
    }
}

void Pop(LISTA* lista,int posicion,int *punt)
{
    int variable;
    NODO* pop = lista->head;
    for(int postemporal = 1; postemporal <= posicion; postemporal++){
        pop = pop->siguiente;
    }
    printf("\n Pop: %c ---> \n ",pop->info);


    
    //Eliminar
    if(posicion == 0)
        EliminarAlInicio(lista);
    else if(posicion == lista->num-1)
        EliminarAlFinal(lista);
    else if(posicion > 0 && posicion < lista->num-1){

        NODO* temporal = lista->head;
        NODO* temporaldos = lista->head;

        for(int postemporal = 1; postemporal < posicion; postemporal++){
            temporal = temporal->siguiente;
            temporaldos=temporaldos->siguiente;
        }

        temporaldos=temporaldos->siguiente;
        temporal->siguiente=temporal->siguiente->siguiente;
        temporaldos->siguiente=NULL;
        EliminarNodo(temporaldos);
        printf("\n Posicion:%d \n",lista->num);
        lista->num--;
    }
    return pop;
}

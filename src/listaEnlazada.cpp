#include "listaEnlazada.h"

NodoLista::NodoLista(string nombre){

    this->nombre = nombre;
    next = NULL;
    x = NULL;
}

listaEnlazada::listaEnlazada()
{
    head = NULL;
    tamano = 0;
}

bool listaEnlazada::esVacia(){
    return head==NULL;
}

int listaEnlazada::getSize(){
    return tamano;
}

void listaEnlazada::insertar(string nombre){
    NodoLista *nuevo = new NodoLista(nombre);

    if(esVacia()){
        head = nuevo;
        head->x = tamano;
        tamano++;
        return;
    }
    else{

        NodoLista *tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }

        tmp->next = nuevo;
        nuevo->x = tamano;
        tamano++;
    }

}

NodoLista *listaEnlazada::obtener(int pos){
    NodoLista *tmp = head;

    while (tmp != NULL){
        if(tmp->x == pos){
            return tmp;
        }
        tmp = tmp->next;
    }


}

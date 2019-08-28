#include "listaCircular.h"
#include <iostream>
NodoL::NodoL(int numero, string info){
    this->numero = numero;
    this->info = info;
    this->next = NULL;
    this->prev = NULL;
}


listaCircular::listaCircular()
{
    this->head = NULL;
    this->listSize = 0;
}
int listaCircular::getSize(){
    return listSize;
}

void listaCircular::insertar(int numero, string info){
    NodoL* nuevo = new NodoL(numero,info);

    if(listSize == 0){
        head = nuevo;
        head->next = nuevo;
        head->prev = nuevo;
        listSize++;
    }else{
        if(head->numero >= nuevo->numero){
            NodoL* last = head->prev;
            nuevo->next = head;
            nuevo->prev = last;
            last->next = nuevo;
            head->prev = nuevo;
            head = nuevo;
            listSize++;
        }else{
            NodoL* tmp = head->next;
            while(tmp != head){
                if(tmp->numero > nuevo->numero){ // 1 4 5 7 8 -9- 10
                    break;
                }
                tmp = tmp->next;
            }
            tmp->prev->next = nuevo;
            nuevo->prev = tmp->prev;
            nuevo->next = tmp;
            tmp->prev = nuevo;
            listSize++;

        }
    }
}

void listaCircular::imprimir(){
    NodoL* aux = head;
    while(aux->next != head){
        cout << aux->numero << " - " << aux->info << endl;
        aux = aux->next;
    }
    cout << aux->numero << " - " << aux->info << endl;
}





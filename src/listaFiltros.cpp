#include "listaFiltros.h"
#include <iostream>
nodoFiltro::nodoFiltro(string nombre, int width, int height, int pxwidth, int pxheight, cuboDisperso *imagen){
    this->nombre = nombre;
    imagenFiltro = imagen;
    this->width = width;
    this->height = height;
    this->pxwidth = pxwidth;
    this->pxheight = pxheight;
    prev = NULL;
    next = NULL;
}


listaFiltros::listaFiltros()
{
    head = NULL;
}

void listaFiltros::insertar(string nombre, int width, int height, int pxwidth, int pxheight, cuboDisperso *imagen){
    nodoFiltro *nuevo = new nodoFiltro(nombre, width, height, pxwidth, pxheight, imagen);
    if(head == NULL){
        head = nuevo;
        head->next = head;
        head->prev = head;

    }
    else{
        nodoFiltro *temp = head->next;
        while(temp->next != head){
            temp = temp->next;
        }
        temp->next = nuevo;
        nuevo->next = head;
        nuevo->prev = temp;
        head->prev = nuevo;
    }
}

nodoFiltro *listaFiltros::obtener(int x){
    x = x -1 ;
    if(x == 0){
        return head;
    }
    int aux = 1;
    bool flag = false;
    nodoFiltro *temp = head->next ;
    //cout << "x: " << x << endl;
   // cout << "aux :" << aux << endl;
    while(temp != head){ //0 1
            cout << "x: " << x << endl;
            cout << "aux :" << aux << endl;
        if(aux == x){
            flag = true;
            break;
        }
        temp = temp->next;
        aux++;
    }

    if(flag){
        return temp;
    }
    return NULL;
}

void listaFiltros::imprimir(){
   nodoFiltro *temp = head;
   cout << temp->nombre << endl;
   temp = head->next;
   while (temp != head){
        cout << temp->nombre << endl;
        temp = temp->next;
   }


}



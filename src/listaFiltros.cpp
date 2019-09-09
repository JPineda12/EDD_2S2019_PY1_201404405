#include "listaFiltros.h"
#include <iostream>
#include <fstream>
nodoFiltro::nodoFiltro(string nombre, int width, int height, int pxwidth, int pxheight, int repx, int repy, cuboDisperso *imagen){
    this->nombre = nombre;
    imagenFiltro = imagen;
    this->width = width;
    this->height = height;
    this->pxwidth = pxwidth;
    this->pxheight = pxheight;
    this->repx = repx;
    this->repy = repy;
    prev = NULL;
    next = NULL;
}


listaFiltros::listaFiltros()
{
    head = NULL;
    tamano = 0;
}
bool listaFiltros::esVacio(){
    return head == NULL;

}
int listaFiltros::getSize(){
    return tamano;
}
void listaFiltros::insertar(string nombre, int width, int height, int pxwidth, int pxheight, int repx, int repy, cuboDisperso *imagen){
    nodoFiltro *nuevo = new nodoFiltro(nombre, width, height, pxwidth, pxheight, repx, repy, imagen);
    if(head == NULL){
        head = nuevo;
        head->next = head;
        head->prev = head;
        tamano++;
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
        tamano++;
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

void listaFiltros::graficar(){
    ofstream archivo;

    archivo.open("Reports/AllFilters.dot");

    archivo << "digraph Circular{\n";
    archivo << "    node[shape=box, width = 1.7];\n";
    archivo << "    graph[nodesep=0.6];\n";
    archivo << "    edge[dir=both]\n";
    //NODE AND LINKS CREATION BEGIN.
    nodoFiltro *temp = head;
    int n = 0;
    //Writes head
    archivo << "    Filtro"+to_string(n)+"[label = \""+temp->nombre+"\"];\n";
    archivo << "    Filtro"+to_string(n)+"->Filtro"+to_string(n+1)+";\n";
    n++;
    temp = head->next;
    while(temp != head){
        archivo << "    Filtro"+to_string(n)+"[label = \""+temp->nombre+"\"];\n";
        if(temp->next == head){
            archivo << "    Filtro"+to_string(n)+"->Filtro0\n";
        }else{
            archivo << "    Filtro"+to_string(n)+"->Filtro"+to_string(n+1)+";\n";
        }
        n++;
        temp = temp->next;
    }

    //RAnks same for all the nodes
    temp = head;
    n=0;
    archivo << "    {rank=same; Filtro"+to_string(n)+"; ";
    temp = temp->next;
    n = 1;
    while(temp != head){
        archivo << "Filtro"+to_string(n)+"; ";
        temp = temp->next;
        n++;
    }
    archivo << "};\n";
    archivo << "}";
    archivo.close();
    //END OF THE FILE

    string comando2 = "dot Reports/AllFilters.dot -Tpng -o Reports/AllFilters.png";
    const char *cmd2 = comando2.c_str();
    system(cmd2);

    comando2 ="eog Reports/AllFilters.png";
    const char *cmd3 = comando2.c_str();
    system(cmd3);


}



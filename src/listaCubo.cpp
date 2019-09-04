#include "listaCubo.h"
#include <fstream>
NodoLineal::NodoLineal(string info, string coords){

    this->info = info;
    this->coords = coords;
    next = NULL;
}



listaCubo::listaCubo()
{
    inicio = NULL;
    tamano = 0;
}

int listaCubo::getSize(){
    return tamano;
}

NodoLineal *listaCubo::obtenerInicio(){
    return inicio;
}

void listaCubo::insertar(string info, string coords){
    NodoLineal *nuevo = new NodoLineal(info, coords);
    if(inicio == NULL){
        inicio = nuevo;
        tamano++;
        return;
    }else{

        NodoLineal *temp = inicio;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nuevo;
        tamano++;
    }
}

void listaCubo::graficar(string nombre){

    ofstream archivo;
    archivo.open("Reports/"+nombre+".dot");
    archivo << "digraph linearMatrix\n{\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [ shape = box]\n ";
    archivo << "    node [width = 1.5, height = 0.55];\n";
    archivo << "    //Nodes and links creation\n";
    //Ej: nodo[label="Mario"];
    int n = 0;
    NodoLineal *temp = inicio;
    while(temp != NULL){
        archivo << "    Nodo"+to_string(n)+"[label =";
        archivo << "\""+temp->info+"\\n"+temp->coords+"\"];\n";
        //Link to the next bro
        if(temp->next != NULL){
            archivo << "    Nodo"+to_string(n)+"->Nodo"+to_string(n+1);
            archivo << "\n";
        }
        n++;
        temp = temp->next;
    }

    archivo << "}";

        //ARCHIVO TERMINADO!
     archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png"
    string comando = "dot Reports/"+nombre+".dot -Tpng -o Reports/"+nombre+".png";
    const char *cmd = comando.c_str();
    system(cmd);


}

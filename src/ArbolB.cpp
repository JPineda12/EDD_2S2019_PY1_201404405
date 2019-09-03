#include "ArbolB.h"
#include <bits/stdc++.h>
#include <fstream>
NodoArbol::NodoArbol(string nombre, int width, int height, int pxWidth, int pxHeight, cuboDisperso *imagen){
    this->imagen = imagen;
    this->nombre = nombre;
    this->height = height;
    this->width = width;
    this->pxWidth = pxWidth;
    this->pxHeight = pxHeight;
    left = NULL;
    right = NULL;
}

ArbolB::ArbolB()
{
    raiz = NULL;
}

bool ArbolB::esVacio(){
    return raiz == NULL;
}

int ArbolB::comparar(string palabraNueva,string palabraArbol){
    //El primer parametro es la palabra de la imagen nueva a insertar
    //El segundo parametro es la palabra que ya existe en el arbol;
    //Retorna si es menor = true
    string smallest = palabraNueva;
    bool flag = false;
    bool iguales = false;
    if (palabraNueva.length() > palabraArbol.length()){
            smallest = palabraArbol;
            flag = true;
    }else if(palabraNueva.length() == palabraArbol.length()){
            iguales = true;
    }
    for(int i = 0; i < smallest.length(); i++){
        if(palabraNueva.at(i) < palabraArbol.at(i) ){
            //Si es menor
            return 1;
            break;
        }else if(palabraNueva.at(i) > palabraArbol.at(i)){
            return -1;
            break;
        }
    }
    if(iguales){
        return 0;
    }
    if(flag){
        return -1;
    }else{
        return 1;
    }
}

bool ArbolB::insertar(string nombre, int width, int height, int pxWidth, int pxHeight, cuboDisperso *imagen){
    NodoArbol *nuevo =new NodoArbol(nombre, width, height, pxWidth, pxHeight, imagen);
    if(raiz == NULL){
        raiz = nuevo;
    }else{
        bool success = insertar_recursivo(raiz, nuevo);
        return success;
    }
}

bool ArbolB::insertar_recursivo(NodoArbol *actual, NodoArbol *nuevo){
    string palabraNueva = nuevo->nombre;
    string palabraArbol = actual->nombre;
    int menor = comparar(palabraNueva, palabraArbol);
    if(menor == 1){ // Si es menor, insertar en la izquierda del arbol
        if(actual->left != NULL){ //Si ya existe un valor
            insertar_recursivo(actual->left ,nuevo);
        }else{ // insertar .
            actual->left = nuevo;
        }
    }else if(menor == -1){ // Si es mayor, insertar en la derecha
        if(actual->right != NULL){
            insertar_recursivo(actual->right, nuevo);
        }else{
            actual->right = nuevo;
        }


    }else if(menor == 0){
        //Si es igual.......
        cout << "Ya existe una imagen: \""<< nuevo->nombre <<  "\"" << endl;
        return false;
    }
    return true;
}

NodoArbol *ArbolB::obtener(string nombre){
    return obtener(raiz, nombre);
}

NodoArbol *ArbolB::obtener(NodoArbol *actual, string nombre){
    if(actual == NULL){
        return NULL;
    }
    string palabraNueva = nombre;
    string palabraArbol = actual->nombre;
    int menor = comparar(palabraNueva, palabraArbol);

    if(actual->nombre == nombre){
        return actual;
    }else if(menor == 1){
        return obtener(actual->left, nombre);
    }else if(menor == -1){
        return obtener(actual->right, nombre);
    }

    return NULL;
}

void ArbolB::inorder(NodoArbol *actual, int n){
        // LEFT - ROOT - RIGHT
        // left
        if(actual->left != NULL){
            inorder(actual->left,n);
        }
        // ROOT = PRINT
        cout << n << ".- " <<actual->nombre << endl;
        n++;

        // RIGHT
        if(actual->right != NULL){
            inorder(actual->right,n);
        }
}

void ArbolB::preorder(NodoArbol *actual, int n){
        // ROOT - LEFT - RIGHT
        // ROOT = PRINT
        cout << n << ".- " <<actual->nombre << endl;
        n++;
            // left
        if(actual->left != NULL){
            preorder(actual->left,n);
        }

        // RIGHT
        if(actual->right != NULL){
            preorder(actual->right,n);
        }
}

void ArbolB::posorder(NodoArbol *actual, int n){
        // left - right  - Rroot
            // left
        if(actual->left != NULL){
            posorder(actual->left,n);
        }
        // RIGHT
        if(actual->right != NULL){
            posorder(actual->right,n);
        }
         // ROOT = PRINT
        cout << n << ".- " <<actual->nombre << endl;
        n++;
}
void ArbolB::getinOrder(){
    int n = 1;
    inorder(raiz,n);
}

void ArbolB::getpreOrder(){
    int n = 1;
    preorder(raiz,n);
}

void ArbolB::getposOrder(){
    int n = 1;
    posorder(raiz,n);
}

string ArbolB::escribirArbol(NodoArbol *treenode){
        string archivo = "";
        // ROOT - LEFT - RIGHT
        // ROOT = Write the file
        archivo += "    nd"+treenode->nombre+"[label=\"<left> | "+treenode->nombre;
        archivo += " \\n"+to_string(treenode->width)+"x"
                    +to_string(treenode->height)+"\\n"+to_string(treenode->pxWidth)
                    +"x"+to_string(treenode->pxHeight)+" | <right>\"];\n";
        archivo += "    //Links nd"+treenode->nombre+"\n";
         //Si estos existen, enlaza con su nodo hijo izquierda o derecha.
        if(treenode->left != NULL){
            archivo += "    nd"+treenode->nombre+" : left->nd"+treenode->left->nombre;
            archivo += "\n";

        }
        if(treenode->right != NULL){
            archivo += "    nd"+treenode->nombre+" : right->nd"+treenode->right->nombre;
            archivo += "\n";
        }
            // left
        if(treenode->left != NULL){
            archivo += escribirArbol(treenode->left);
        }

        // RIGHT
        if(treenode->right != NULL){
            archivo += escribirArbol(treenode->right);
        }

        return archivo;
}

void ArbolB::graficar(){
    ofstream archivo;
    archivo.open("binaryTree.dot");
    archivo << "digraph arbolBinario\n{\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    graph [pad=\".25\", ranksep=\"1.0\", nodesep=\"1\"];\n";
    archivo << "    node [shape=record, style = rounded, color = forestgreen];\n";
    archivo << "    node [width = 2, height = 0.7, fixedsize=\"true\"];\n";
    //Empieza creacion de NODOS y sus ENLACES
    //ej: ndnombreimagen[label="<left> | Random\n16px16px\n30px| <right>"];
    archivo << "    //Nodes and links creation\n";
    //LLama al metodo escribir que se encarga de escribir los nodos y sus hijos
    // de manera recursiva.
    archivo << escribirArbol(raiz); //Empezando desde la raiz del arbol.
    archivo << "}";
    //ARCHIVO TERMINADO!
     archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png BinaryTree.dot"
    string comando = "dot binaryTree.dot -Tpng -o binaryTree.png";
    const char *cmd = comando.c_str();
    system(cmd);
}

listaEnlazada *ArbolB::escribirInorder(NodoArbol *treenode,listaEnlazada *ls){
        // LEFT - ROOT - RIGHT

            // left
        if(treenode->left != NULL){
            escribirInorder(treenode->left, ls);
        }

                //ROOT
         // ROOT = Write the file name into the list
         ls->insertar(treenode->nombre);


        // RIGHT
        if(treenode->right != NULL){
            escribirInorder(treenode->right, ls);
        }

        return ls;
}

listaEnlazada *ArbolB::escribirPreorder(NodoArbol *treenode, listaEnlazada *ls){
        // ROOT - LEFT - RIGHT

         //ROOT
         // ROOT = Write the file name into the list
         ls->insertar(treenode->nombre);

            // left
        if(treenode->left != NULL){
            escribirPreorder(treenode->left, ls);
        }



        // RIGHT
        if(treenode->right != NULL){
            escribirPreorder(treenode->right, ls);
        }

        return ls;
}


listaEnlazada *ArbolB::escribirPosorder(NodoArbol *treenode, listaEnlazada *ls){
        // LEFT - RIGHT - ROOT

            // left
        if(treenode->left != NULL){
            escribirPosorder(treenode->left, ls);
        }

        // RIGHT
        if(treenode->right != NULL){
            escribirPosorder(treenode->right, ls);
        }

         //ROOT
         // ROOT = Write the file name into the list
         ls->insertar(treenode->nombre);

        return ls;
}

void ArbolB::graficarInorder(){
    ofstream archivo;
    archivo.open("Reports/inorder_Tree.dot");
    archivo << "digraph arbol_inorder\n{\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [width = 1, height = 0.25];\n";
    //Empieza creacion de NODOS y sus ENLACES
    //ej: ndnombreImagen[label="Mario",]
    archivo << "    //Nodes and links creation\n";
    //LLama al metodo escribir que se encarga de escribir los nodos y sus hijos
    // de manera recursiva.
    listaEnlazada *ls= new listaEnlazada();
    ls = escribirInorder(raiz,ls); //Empezando desde la raiz del arbol.
    //Escribir los nodos y sus links a partir de la lista (recorriendola)
    for(int i=0; i<ls->getSize(); i++){
        //Ej: nodo[label="Mario"];
        archivo << "\nnd"+ls->obtener(i)->nombre+"[label=\""+ls->obtener(i)->nombre+"\"];\n";
        //Ahora escribir su link
        if(ls->obtener(i)->next != NULL){
            //ej: a->b
            archivo << "nd"+ls->obtener(i)->nombre+"->nd"+ls->obtener(i+1)->nombre;";\n";
        }
    }
    archivo << "}";
    //ARCHIVO TERMINADO!
     archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png BinaryTree.dot"
    string comando = "dot Reports/inorder_Tree.dot -Tpng -o Reports/inorder_Tree.png";
    const char *cmd = comando.c_str();
    system(cmd);


}

void ArbolB::graficarPosorder(){
    ofstream archivo;
    archivo.open("Reports/posorder_Tree.dot");
    archivo << "digraph arbol_inorder\n{\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [width = 1, height = 0.25];\n";
    //Empieza creacion de NODOS y sus ENLACES
    //ej: ndnombreImagen[label="Mario",]
    archivo << "    //Nodes and links creation\n";
    //LLama al metodo escribir que se encarga de escribir los nodos y sus hijos
    // de manera recursiva.
    listaEnlazada *ls= new listaEnlazada();
    ls = escribirPosorder(raiz,ls); //Empezando desde la raiz del arbol.
    //Escribir los nodos y sus links a partir de la lista (recorriendola)
    for(int i=0; i<ls->getSize(); i++){
        //Ej: nodo[label="Mario"];
        archivo << "\nnd"+ls->obtener(i)->nombre+"[label=\""+ls->obtener(i)->nombre+"\"];\n";
        //Ahora escribir su link
        if(ls->obtener(i)->next != NULL){
            //ej: a->b
            archivo << "nd"+ls->obtener(i)->nombre+"->nd"+ls->obtener(i+1)->nombre;"\n";
        }
    }
    archivo << "}";
    //ARCHIVO TERMINADO!
     archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png BinaryTree.dot"
    string comando = "dot Reports/posorder_Tree.dot -Tpng -o Reports/posorder_Tree.png";
    const char *cmd = comando.c_str();
    system(cmd);


}

void ArbolB::graficarPreorder(){
    ofstream archivo;
    archivo.open("Reports/preorder_Tree.dot");
    archivo << "digraph arbol_inorder\n{\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [width = 1, height = 0.25];\n";
    //Empieza creacion de NODOS y sus ENLACES
    //ej: ndnombreImagen[label="Mario",]
    archivo << "    //Nodes and links creation\n";
    //LLama al metodo escribir que se encarga de escribir los nodos y sus hijos
    // de manera recursiva.
    listaEnlazada *ls= new listaEnlazada();
    ls = escribirPreorder(raiz,ls); //Empezando desde la raiz del arbol.
    //Escribir los nodos y sus links a partir de la lista (recorriendola)
    for(int i=0; i<ls->getSize(); i++){
        //Ej: nodo[label="Mario"];
        archivo << "\nnd"+ls->obtener(i)->nombre+"[label=\""+ls->obtener(i)->nombre+"\"];\n";
        //Ahora escribir su link
        if(ls->obtener(i)->next != NULL){
            //ej: a->b
            archivo << "nd"+ls->obtener(i)->nombre+"->nd"+ls->obtener(i+1)->nombre;"\n";
        }
    }
    archivo << "}";
    //ARCHIVO TERMINADO!
     archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png BinaryTree.dot"
    string comando = "dot Reports/preorder_Tree.dot -Tpng -o Reports/preorder_Tree.png";
    const char *cmd = comando.c_str();
    system(cmd);
}





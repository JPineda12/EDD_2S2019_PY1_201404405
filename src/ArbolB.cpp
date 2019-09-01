#include "ArbolB.h"
#include <bits/stdc++.h>

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
    bool iguales = true;
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
        return false;
    }else{
        return true;
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


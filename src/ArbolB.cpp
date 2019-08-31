#include "ArbolB.h"
#include <bits/stdc++.h>
NodoArbol::NodoArbol(string nombre, cuboDisperso *imagen){
    this->imagen = imagen;
    this->nombre = nombre;
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

void ArbolB::insertar(string nombre,cuboDisperso *imagen){
    NodoArbol *nuevo =new NodoArbol(nombre, imagen);
    if(raiz == NULL){
        raiz = nuevo;
    }else{
        insertar_recursivo(raiz, nuevo);
    }
}

void ArbolB::insertar_recursivo(NodoArbol *actual, NodoArbol *nuevo){
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
    }
}
void ArbolB::inorder(NodoArbol *actual){
        // LEFT - ROOT - RIGHT
        // left
        if(actual->left != NULL){
            inorder(actual->left);
        }
        // ROOT = PRINT
        cout << actual->nombre;
        cout << "->";

        // RIGHT
        if(actual->right != NULL){
            inorder(actual->right);
        }
}

void ArbolB::preorder(NodoArbol *actual){
        // ROOT - LEFT - RIGHT
        // ROOT = PRINT
        cout << actual->nombre;
        cout << "->";

            // left
        if(actual->left != NULL){
            preorder(actual->left);
        }

        // RIGHT
        if(actual->right != NULL){
            preorder(actual->right);
        }
}

void ArbolB::posorder(NodoArbol *actual){
        // left - right  - Rroot
            // left
        if(actual->left != NULL){
            posorder(actual->left);
        }
        // RIGHT
        if(actual->right != NULL){
            posorder(actual->right);
        }
         // ROOT = PRINT
        cout << actual->nombre;
        cout << "->";
}



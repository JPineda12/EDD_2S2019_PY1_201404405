#ifndef ARBOLB_H
#define ARBOLB_H
#include "cuboDisperso.h"
struct NodoArbol{

    public:
         NodoArbol(string nombre, cuboDisperso *imagen);
         NodoArbol *left;
         NodoArbol *right;
         string nombre;
         cuboDisperso* imagen;


};

class ArbolB
{
    public:
        ArbolB();
        NodoArbol *raiz;
        bool esVacio();
        void insertar(string nombre,cuboDisperso* imagen);
        void insertar_recursivo(NodoArbol *actual, NodoArbol *imagen);
        int comparar(string palabraNueva, string palabraArbol);
        void inorder(NodoArbol *actual);
        void posorder(NodoArbol *actual);
        void preorder(NodoArbol *actual);

    protected:

    private:
};

#endif // ARBOLB_H

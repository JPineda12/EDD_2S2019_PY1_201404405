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
        bool insertar(string nombre,cuboDisperso* imagen);
        bool insertar_recursivo(NodoArbol *actual, NodoArbol *imagen);
        int comparar(string palabraNueva, string palabraArbol);
        void inorder(NodoArbol *actual, int n);
        void getinOrder();
        void getposOrder();
        void getpreOrder();
        void posorder(NodoArbol *actual, int n);
        void preorder(NodoArbol *actual, int n);

    protected:

    private:
};

#endif // ARBOLB_H

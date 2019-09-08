#ifndef ARBOLB_H
#define ARBOLB_H
#include "cuboDisperso.h"
#include "listaEnlazada.h"
struct NodoArbol{

    public:
         NodoArbol(string nombre, int width, int height, int pxWidth, int pxHeight, cuboDisperso *imagen);
         NodoArbol *left;
         NodoArbol *right;
         string nombre;
         int width;
         int height;
         int pxWidth;
         int pxHeight;
         cuboDisperso* imagen;

};

class ArbolB
{
    public:
        ArbolB();
        NodoArbol *raiz;
        bool esVacio();
        bool insertar(string nombre, int width, int height, int pxWidth,int pxHeigth, cuboDisperso* imagen);
        NodoArbol *obtener(string nombre);
        int comparar(string palabraNueva, string palabraArbol);
        void inorder(NodoArbol *actual);
        void getinOrder();
        void getposOrder();
        void getpreOrder();
        void posorder(NodoArbol *actual, int n);
        void preorder(NodoArbol *actual, int n);
        void graficar();
        void graficarInorder();
        void graficarPosorder();
        void graficarPreorder();


    protected:

    private:
        bool insertar_recursivo(NodoArbol *actual, NodoArbol *imagen);
        NodoArbol *obtener(NodoArbol *actual, string nombre);
        listaEnlazada *escribirInorder(NodoArbol *tree, listaEnlazada *ls);
        listaEnlazada *escribirPosorder(NodoArbol *tree, listaEnlazada *ls);
        listaEnlazada *escribirPreorder(NodoArbol *tree, listaEnlazada *ls);
        string escribirArbol(NodoArbol *treenode);
};

#endif // ARBOLB_H

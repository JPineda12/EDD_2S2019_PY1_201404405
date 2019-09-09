#ifndef LISTAFILTROS_H
#define LISTAFILTROS_H
#include "cuboDisperso.h"
struct nodoFiltro{

    public:
        nodoFiltro(string nombre, int width, int height, int pxwidth, int pxheight, int repx, int repy, cuboDisperso *imagenFiltro);
        string nombre;
        int width,height, pxwidth, pxheight,repx,repy;
        cuboDisperso *imagenFiltro;
        nodoFiltro *next;
        nodoFiltro *prev;

};

class listaFiltros
{
    public:
        nodoFiltro *head;
        int tamano;
        bool esVacio();
        listaFiltros();
        void insertar(string nombre, int width, int height, int pxwidth, int pxheight, int repx, int repy, cuboDisperso *imagenFiltro);
        void imprimir();
        int getSize();
        nodoFiltro *obtener(int x);
        void graficar();

    protected:

    private:
};

#endif // LISTAFILTROS_H

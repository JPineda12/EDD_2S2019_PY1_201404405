#ifndef LISTAFILTROS_H
#define LISTAFILTROS_H
#include "cuboDisperso.h"
struct nodoFiltro{

    public:
        nodoFiltro(string nombre, int width, int height, int pxwidth, int pxheight, cuboDisperso *imagenFiltro);
        string nombre;
        int width,height, pxwidth, pxheight;
        cuboDisperso *imagenFiltro;
        nodoFiltro *next;
        nodoFiltro *prev;

};

class listaFiltros
{
    public:
        nodoFiltro *head;
        listaFiltros();
        void insertar(string nombre, int width, int height, int pxwidth, int pxheight, cuboDisperso *imagenFiltro);
        void imprimir();
        nodoFiltro *obtener(int x);

    protected:

    private:
};

#endif // LISTAFILTROS_H

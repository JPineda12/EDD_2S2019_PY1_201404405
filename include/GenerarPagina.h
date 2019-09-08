#ifndef GENERARPAGINA_H
#define GENERARPAGINA_H
#include <string>
#include "listaCubo.h"
#include "ArbolB.h"
using namespace std;

class GenerarPagina
{
    public:
        GenerarPagina(string nombreImagen);
        void crearHTMl(listaCubo *lsPixeles, NodoArbol *imagen);
        void crearCSS(listaCubo *lsPixeles, NodoArbol *imagen, int pagew, int pageh);
        string createHexa(int r, int g, int b);
        string convertRGB(NodoLineal *pixel);


    protected:

    private:
        string nombreImagen;
};

#endif // GENERARPAGINA_H

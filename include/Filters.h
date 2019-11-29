#ifndef FILTERS_H
#define FILTERS_H
#include "cuboDisperso.h"
#include "BinarySearchTree.h"
class Filters
{
    public:
        Filters();
        cuboDisperso *negativeAll(cuboDisperso *imagen);
        cuboDisperso *grayscaleAll(cuboDisperso *imagen);
        cuboDisperso *mirrorAll(cuboDisperso *imagen, int tipo, NodoArbol *hoja);
        cuboDisperso *collage(cuboDisperso *imagen, int x, int y, NodoArbol *hoja);
        cuboDisperso *mosaic(cuboDisperso *imagen);
        cuboDisperso *rep_x(cuboDisperso *imagen, int x, NodoArbol *hoja);
        cuboDisperso *rep_y(cuboDisperso *imagen, int y, NodoArbol *hoja);



    protected:

    private:
};

#endif // FILTERS_H

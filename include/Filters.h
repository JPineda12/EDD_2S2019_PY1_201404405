#ifndef FILTERS_H
#define FILTERS_H
#include "cuboDisperso.h"
#include "ArbolB.h"
class Filters
{
    public:
        Filters();
        cuboDisperso *negativeAll(cuboDisperso *imagen);
        cuboDisperso *grayscaleAll(cuboDisperso *imagen);
        cuboDisperso *mirrorAll(cuboDisperso *imagen, int tipo, NodoArbol *hoja);
        cuboDisperso *collage(cuboDisperso *imagen);
        cuboDisperso *mosaic(cuboDisperso *imagen);



    protected:

    private:
};

#endif // FILTERS_H

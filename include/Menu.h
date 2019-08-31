#ifndef MENU_H
#define MENU_H
#include "listaCircular.h"
#include "ArbolB.h"
#include "cuboDisperso.h"
class Menu
{
    public:
        Menu();
        listaCircular lista;
    protected:

    private:
        void insertImage(ArbolB *tree);
        cuboDisperso* selectImage(ArbolB *tree);
        listaCircular* filters(cuboDisperso *selectedimage);
        void manualEdit(cuboDisperso *selectedimage, listaCircular *filtros);
        void imageExport(cuboDisperso *selectedimage, listaCircular *filtros);
        void *reports(ArbolB *tree, listaCircular *filtros);
        cuboDisperso *createImage(string nombreCarpeta, listaCircular *listaCsv);

};

#endif // MENU_H

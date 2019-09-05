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
        void printImageMenu(ArbolB *tree);
        listaCircular* filters(cuboDisperso *selectedimage);
        void manualEdit(cuboDisperso *selectedimage, listaCircular *filtros);
        void imageExport(cuboDisperso *selectedimage, listaCircular *filtros, ArbolB *arbolImagenes);
        void reports(ArbolB *arbolImagenes, listaCircular *filtros);
        void repImageLayer(ArbolB *arbolImagenes);
        void repTrasversal(ArbolB *arbolImagenes);
        void repLinearMatrix(ArbolB *arbolImagenes);
        cuboDisperso *createImage(string nombreCarpeta, listaCircular *listaCsv);

};

#endif // MENU_H

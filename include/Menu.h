#ifndef MENU_H
#define MENU_H
#include "listaFiltros.h"
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
        cuboDisperso* selectImage(ArbolB *tree, listaFiltros *filtros);
        void printImageMenu(ArbolB *tree);
        listaFiltros* filters(cuboDisperso *selectedimage, ArbolB *arbolImagenes, listaFiltros *filtros);
        void manualEdit(cuboDisperso *selectedimage, listaFiltros *filtros);
        void imageExport(cuboDisperso *selectedimage, listaFiltros *filtros, ArbolB *arbolImagenes);
        void reports(ArbolB *arbolImagenes, listaFiltros *filtros);
        void repImageLayer(ArbolB *arbolImagenes);
        void repTrasversal(ArbolB *arbolImagenes);
        void repLinearMatrix(ArbolB *arbolImagenes);
        cuboDisperso *createImage(string nombreCarpeta, listaCircular *listaCsv);
        void exportarSelected(cuboDisperso *selectedImage, ArbolB *arbolImagenes);
        void exportarFiltro(listaFiltros *filtros, ArbolB *arbolImagenes, string nombreImagen);

};

#endif // MENU_H

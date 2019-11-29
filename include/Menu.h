#ifndef MENU_H
#define MENU_H
#include "listaFiltros.h"
#include "BinarySearchTree.h"
#include "cuboDisperso.h"
class Menu
{
    public:
        Menu();
        listaCircular lista;
    protected:

    private:
        void insertImage(BinarySearchTree *tree);
        cuboDisperso* selectImage(BinarySearchTree *tree, listaFiltros *filtros);
        void printImageMenu(BinarySearchTree *tree);
        listaFiltros *filters(cuboDisperso *selectedimage, BinarySearchTree *arbolImagenes, listaFiltros *filtros);
        listaFiltros *manualEdit(cuboDisperso *selectedimage, listaFiltros *filtros, BinarySearchTree *arbolImagenes);
        listaFiltros *editSelected(cuboDisperso *selectedImage, listaFiltros *filtros, BinarySearchTree *arbolImagenes);
        listaFiltros *editFilter(listaFiltros *filtros);
        void imageExport(cuboDisperso *selectedimage, listaFiltros *filtros, BinarySearchTree *arbolImagenes);
        void reports(BinarySearchTree *arbolImagenes, listaFiltros *filtros);
        void repImageLayer(BinarySearchTree *arbolImagenes);
        void repTrasversal(BinarySearchTree *arbolImagenes);
        void repLinearMatrix(BinarySearchTree *arbolImagenes);
        void repFilters(listaFiltros *filters);
        void repFIndiv(listaFiltros *filters);
        cuboDisperso *createImage(string nombreCarpeta, listaCircular *listaCsv);
        void exportarSelected(cuboDisperso *selectedImage, BinarySearchTree *arbolImagenes);
        void exportarFiltro(listaFiltros *filtros, BinarySearchTree *arbolImagenes, string nombreImagen);

};

#endif // MENU_H

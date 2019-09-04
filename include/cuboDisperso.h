#ifndef CUBODISPERSO_H
#define CUBODISPERSO_H
#include <string>
#include "listaCircular.h"
#include "listaCubo.h"
using namespace std;

struct NodoCubo{
         string info;
         string layerName;
         int x;
         int y;
         int z;
         NodoCubo* prev;
         NodoCubo* next;
         NodoCubo* up;
         NodoCubo* down;
         NodoCubo* lower;
         NodoCubo* upper;
    public:
         NodoCubo(string info, string layerName, int x, int y, int z);

};

class cuboDisperso
{
    public:
        int layerCount;
        NodoCubo *root;
        cuboDisperso();
        void insert_element(string info, string layerName, int x, int y, int z);
        NodoCubo *insert_sorted_col(NodoCubo* new_node, NodoCubo* head_col);
        NodoCubo *insert_sorted_row(NodoCubo* new_node, NodoCubo* head_row);
        NodoCubo *insert_sorted_layer(NodoCubo* new_node, NodoCubo* head_layer);
        NodoCubo *create_row(int y, NodoCubo* layer);
        NodoCubo *create_column(int x, NodoCubo* layer);
        NodoCubo *create_layer(int z, string layerName);
        NodoCubo *findRow(int y, int z);
        NodoCubo *findColumn(int x, int z);
        NodoCubo *findLayer(int z);
        NodoCubo *obtener(int x, int y, int z);
        int layerSize();
        void graficarMatriz(string nombreCapa, int z);
        void imprimir(int z);
        listaCubo *linearMap_byRow(int capa);
        listaCubo *linearMap_byCol(int capa);

    protected:

    private:
};

#endif // CUBODISPERSO_H

#ifndef CUBODISPERSO_H
#define CUBODISPERSO_H
#include <string>
using namespace std;

struct Nodo{
    public:
         string info;
         int x;
         int y;
         Nodo* prev;
         Nodo* next;
         Nodo* up;
         Nodo* down;
         Nodo(string info,int x, int y);

};

class cuboDisperso
{
    public:
        int tamano;
        Nodo *root;
        cuboDisperso();
        void insert_element(string info, int x, int y);
        Nodo *insert_sorted_col(Nodo* new_node, Nodo* head_col);
        Nodo *insert_sorted_row(Nodo* new_node, Nodo* head_row);
        Nodo *create_row(int y);
        Nodo *create_column(int x);
        Nodo *findRow(int y);
        Nodo *findColumn(int x);
        void graficarMatriz();


    protected:

    private:
};

#endif // CUBODISPERSO_H

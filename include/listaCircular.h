#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <string>
using namespace std;
struct NodoL{
    string info;
    int numero;
    NodoL *next;
    NodoL *prev;

    public:
        NodoL(int numero, string info);

};


class listaCircular
{
    public:
        listaCircular();
        int listSize;
        void insertar(int numero, string info);
        int getSize();
        void imprimir();
        NodoL *head;


    protected:

    private:
};

#endif // LISTACIRCULAR_H

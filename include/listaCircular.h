#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <string>
using namespace std;
struct Nodo{
    string info;
    int numero;
    Nodo *next;
    Nodo *prev;

    public:
        Nodo(int numero, string info);

};


class listaCircular
{
    public:
        listaCircular();
        int listSize;
        void insertar(int numero, string info);
        int getSize();
        void imprimir();
        Nodo *head;


    protected:

    private:
};

#endif // LISTACIRCULAR_H

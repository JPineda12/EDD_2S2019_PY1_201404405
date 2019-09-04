#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>
using namespace std;


struct NodoLista{
    public:
        NodoLista* next;
        NodoLista(string nombre);
        string nombre;
        int x;

};


class listaEnlazada
{
    public:
        NodoLista* head;
        listaEnlazada();
        void insertar(string nombre);
        bool esVacia();
        int getSize();
        NodoLista *obtener(int pos);
    protected:

    private:
        int tamano;
};

#endif // LISTAENLAZADA_H

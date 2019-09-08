#ifndef LISTACUBO_H
#define LISTACUBO_H
#include <string>
using namespace std;
struct NodoLineal{

    public:
        NodoLineal(string info, string coords);
        NodoLineal* next;
        string info;
        string coords;
};


class listaCubo
{
    public:
        NodoLineal *inicio;
        listaCubo();
        void insertar(string info, string coords);
        int getSize();
        void graficar(string nombre, string carpeta);
        NodoLineal *obtenerInicio();
    protected:

    private:
        int tamano;

};

#endif // LISTACUBO_H

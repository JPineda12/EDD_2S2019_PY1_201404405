#ifndef NODO_H
#define NODO_H
#include <string>
using namespace std;

struct nodo{
        int numero;
        string info;
    };

class Nodo
{

    public:
        Nodo(struct nodo nuevo);
        Nodo *sig;
        Nodo *prev;
        struct nodo nove;

        struct nodo getNumero();
        struct nodo getInfo();

    protected:

    private:
};

#endif // NODO_H

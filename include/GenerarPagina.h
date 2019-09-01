#ifndef GENERARPAGINA_H
#define GENERARPAGINA_H
#include <string>
using namespace std;

class GenerarPagina
{
    public:
        GenerarPagina(string nombreImagen);
        void crearHTMl();
        void crearCSS();

    protected:

    private:
        string nombreImagen;
};

#endif // GENERARPAGINA_H

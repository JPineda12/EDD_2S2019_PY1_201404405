#include "GenerarPagina.h"
#include <fstream>
GenerarPagina::GenerarPagina(string nombreImagen)
{
    this->nombreImagen = nombreImagen;
}

void GenerarPagina::crearHTMl(){
    ofstream pagina;
    pagina.open("Exports/"+nombreImagen+"/Sass/"+nombreImagen+".html");



}

void GenerarPagina::crearCSS(){
    ofstream style;
    style.open("Exports/"+nombreImagen+"/Sass"+nombreImagen+".scss");
}

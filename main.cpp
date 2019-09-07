#include "Menu.h"
#include "listaCircular.h"
#include <iostream>
#include "cuboDisperso.h"
#include <string>
#include "listaFiltros.h"
using namespace std;



int main()
{


    Menu *m = new Menu();

    //cb->imprimir(0);
    /*cuboDisperso *cb = new cuboDisperso();
    ArbolB *tree = new ArbolB();
    tree->insertar("Mario1",0,0,0,0, cb);
    tree->insertar("Pickachu",0,0,0,0,cb);
    tree->insertar("Boo",0,0,0,0,cb);
    tree->insertar("Geoff",0,0,0,0,cb);
    tree->insertar("Mario2",0,0,0,0,cb);
    tree->insertar("Mushroom",0,0,0,0,cb);
    //tree->insertar("Geoff", cb);
    tree->inorder(tree->raiz,0);
    cout << endl;
    tree->preorder(tree->raiz,0);
    cout << endl;
    tree->posorder(tree->raiz,0);
    cout << endl;

    tree->graficarInorder();
    tree->graficarPosorder();
    tree->graficarPreorder();
    //cuboDisperso *matriz = new cuboDisperso();
    /*matriz->insert_element("roaatt",3,3,1);
    matriz->insert_element("el10",0,1,1);
    matriz->insert_element("what",1,2,2);
    matriz->insert_element("xd",10,1,4);
    matriz->insert_element("qwewqe",2,2,10);
    matriz->insert_element("weee",2,2,11);
    matriz->insert_element("wutjeje",2,13,3);
    cout << "Layer Count: " << matriz->layerSize() << endl;
    //matriz->imprimir(1);


    matriz->graficarMatriz("Layer10", 10);*/
    return 0;

}

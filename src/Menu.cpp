#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <listaCircular.h>
#include <cuboDisperso.h>;
using namespace std;

void Menu::insertImage(){ //Metodo para obtener los archivos config y capas.
    cout << "----------- Insert Image -----------  " << endl;
    cout << "Nombre del archivo: ";
    string nombreArchivo;
    cin >> nombreArchivo;
    listaCircular* archivos = new listaCircular();
    ifstream infile(nombreArchivo);
    if(infile){                     //Checks if the file exists
        string line = "";
        int n = 0;
        int y = 0;
        while(getline(infile,line)){
            stringstream strstr(line);
            string word = "";
            int numero = 0;
            string info = "";
            while (getline(strstr,word,',')){
                if(n == 0 && y > 0){
                    numero = stoi(word);
                    n =  1;
                }else if(n == 1 && y > 0){
                    info = word;
                    n = 0;
                    archivos->insertar(numero, info);

                }
            }
            y++;

        }
    }else{
        cout << "Enter a valid File or path\n" << endl;
        insertImage();
    }
    //Crea el Cubo con las capas y nodos
    cuboDisperso *imagen = new cuboDisperso();
    NodoL *layercsv = archivos->head->next; //Obtiene el nombre del primer csv
    int x = 0;
    int y = 0;
    int z = 0; //Coordenadas para los nodos del cubo
    int layercount = 0;
    while(layercsv != archivos->head){
        ifstream capa(nombreArchivo.substr(0,nombreArchivo.length()-4)+"/"+layercsv->info);
        if(capa){                     //Checks if the file exists
            string line = "";
            //El numero de layercsv corresponde a la capa donde se insertara x,y.
            z = layercsv->numero;
            while(getline(capa,line)){
                stringstream strstr(line);
                string word = "";
                int numero = 0;
                string info = "";
                x = 0;
                while (getline(strstr,word,',')){
                    if(word != "x"){
                        imagen->insert_element(word,x,y,z);
                    }
                    x++;
                }
                y++;
            }
            layercount++;
        }else{
            cout << " Archivo de capa" << layercsv->info << "inexistente\n";
        }
        layercsv = layercsv->next;
    }
    cout << layercount << " capas ingresadas con exito!" << endl;
    NodoCubo* test = imagen->root->upper;
    int nambar = 0;
    string salida;
    while(true){
        while(test != NULL){
            cout << test->z << ". "<< test->info << endl;
            test = test->upper;
        }
        cout << "\n Graficar capa: ";
        cin >> nambar;
        salida = nombreArchivo.substr(0,nombreArchivo.length()-4)+"Layer"+to_string(nambar);
        if(nambar != 0){
            imagen->graficarMatriz(salida,nambar);
        }else{
            break;
        }
    }

    //system("clear"); //Cleans Console.
    //Menu();

}

Menu::Menu()
{
    int opcion;
    cout << "---------------- MENU ----------------" << endl;
    cout << "1 - Insert Image." << endl;
    cout << "2 - Select Image." << endl;
    cout << "3 - Apply Filters." << endl;
    cout << "4 - Manual Editing." << endl;
    cout << "5 - Export Image." << endl;
    cout << "6 - Reports." << endl;
    cout << "7 - Exit." << endl;
    cin >> opcion;
    switch(opcion){
    case 1:
        system("clear");
        insertImage();
        break;
    case 2:
        cout << "2" << endl;
        break;
    case 3:
        cout << "Apply Filters" << endl;
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    default:
        cout << "Opcion invalida!" << endl;
        Menu();
    }



}

#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <listaCircular.h>
using namespace std;

void Menu::insertImage(){ //Metodo para obtener los archivos config y capas.
    cout << "----------- Insert Image -----------  " << endl;
    cout << "Nombre del archivo: ";
    string archivo;
    cin >> archivo;
    listaCircular* archivos = new listaCircular();
    ifstream infile(archivo);
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
       cout << "Tamaño: " << archivos->getSize() << endl;
       archivos->imprimir();

    }else{
        cout << "Enter a valid File or path\n" << endl;
        insertImage();
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

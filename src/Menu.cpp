#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <listaCircular.h>
#include <cuboDisperso.h>;
#include "Filters.h"
using namespace std;

cuboDisperso* Menu::createImage(string nombreCarpeta,listaCircular *listaCSV){
//Crea el Cubo con las capas y nodos
    cuboDisperso *imagen = new cuboDisperso();
    NodoL *layercsv = listaCSV->head->next; //Obtiene el nombre del primer csv
    int x = 0;
    int y = 0;
    int z = 0; //Coordenadas para los nodos del cubo
    int layercount = 0;
    while(layercsv != listaCSV->head){
        ifstream capa(nombreCarpeta+"/"+layercsv->info);
        string layerName = layercsv->info.substr(0,layercsv->info.length()-4);
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
                        imagen->insert_element(word, layerName, x,y,z);
                    }
                    x++;
                }
                y++;
            }
            layercount++;
        }else{
            cout << " Archivo de capa " << layercsv->info << " inexistente\n";
            return NULL;
        }
        layercsv = layercsv->next;
    }
    cout << layercount << " capas ingresadas a un cubo con exito!" << endl;
    return imagen;

}

void Menu::insertImage(ArbolB *arbolImagenes){ //Metodo para obtener los archivos config y capas.
    cout << "----------- Insert Image -----------  " << endl;
    cout << "Nombre del archivo: ";
    string nombreArchivo;
    cin >> nombreArchivo;
    listaCircular* archivos = new listaCircular();
    string carpeta = nombreArchivo.substr(0,nombreArchivo.length()-4);
    ifstream infile(carpeta+"/"+nombreArchivo);
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
        insertImage(arbolImagenes);
        return;
    }
    //Nombre de la imagen y de la carpeta donde estan los csv.
    int pxWidth = 0;
    int pxHeight = 0;
    int imageWidth = 0;
    int imageHeight = 0;
    string config = carpeta+"/"+archivos->head->info;
    ifstream file(config);
    if(file){                     //Checks if the file exists
        string line = "";
        int n = -1;
        int y = 0;
        while(getline(file,line)){
            stringstream strstr(line);
            string word = "";
            while (getline(strstr,word,',')){
                if(n == 0){
                    imageHeight = stoi(word);
                    n = -1;
                }else if(n == 1){
                    imageWidth = stoi(word);
                    n = -1;
                }else if(n == 2){
                    pxWidth = stoi(word);
                    n = -1;
                }else if(n == 3){
                    pxHeight = stoi(word);
                    n = -1;
                }
                if(word == "image_width"){
                    n = 0;
                }else if(word ==  "image_height"){
                    n = 1;
                }else if(word == "pixel_width"){
                    n = 2;
                }else if(word == "pixel_height"){
                    n = 3;
                }
            }
            y++;
        }
    }else{
        cout << "Enter a valid File or path\n" << endl;
        insertImage(arbolImagenes);
        return;
    }
    //Crea la matriz con la imagen por capas
    cuboDisperso* imagen = createImage(carpeta, archivos);
    //Inserta la imagen en el arbol Binario de imagenes
    if(imagen != NULL){
        bool success = arbolImagenes->insertar(carpeta, imageWidth, imageHeight, pxWidth, pxHeight, imagen);
        if(success){
            cout << "La imagen  \"" << carpeta << "\" fue insertada al arbol!" << endl;
            cout << "\nPresiona cualquiera tecla para volver...." << endl;
        }else{
            cout << "La insercion al arbol fue  C A N C E L A D A......" << endl;
        }
        cin.ignore();
        cin.ignore();
        return;
    }
    cout << "Check CSV's files." << endl;
    cin.ignore();
    cin.ignore();
    insertImage(arbolImagenes);

}
void Menu::printImageMenu(ArbolB *arbolImagenes){
    cout << "----------- Select Image -----------  " << endl;
    arbolImagenes->getinOrder();
}

cuboDisperso* Menu::selectImage(ArbolB *arbolImagenes){
    string nombre = "";
    printImageMenu(arbolImagenes);
    cout << "Escriba el nombre de imagen a seleccionar: ";
    cin >> nombre;
    NodoArbol *imagenSeleccionada = arbolImagenes->obtener(nombre);
    if (imagenSeleccionada != NULL){
        cout << "Imagen "+nombre << " seleccionada!\n\n";
        cin.ignore();
        cin.ignore();
        return imagenSeleccionada->imagen;

    }
    cout << "Nombre incorrecto!\n" << endl;
    selectImage(arbolImagenes);
}

listaCircular* Menu::filters(cuboDisperso* selectedImage){
    cuboDisperso *imagenFiltro = selectedImage;
    Filters *filter = new Filters();
    int opcion = 0;
    while(opcion != 6){
        system("clear");
        cout << "1. Negative" << endl;
        cout << "2. Grayscale" << endl;
        cout << "3. Mirror" << endl;
        cout << "4. Collage" << endl;
        cout << "5. Mosaic" << endl;
        cout << "6. Volver" << endl;
        cin >> opcion;
        switch(opcion){
            case 1:
                filter->negativeAll(imagenFiltro);
                break;
            case 2:
                filter->grayscaleAll(imagenFiltro);
                break;
            case 3:
                filter->mirrorAll(imagenFiltro, 0);
                break;
            case 4:
                filter->collage(imagenFiltro);
                break;
            case 5:
                filter->mosaic(imagenFiltro);
                break;
            case 6:
                break;
            default:
                cout << "Opcion Invalida" << endl;
                cin.ignore();
                cin.ignore();
        }
    }


}
void Menu::repImageLayer(ArbolB *arbolImagenes){
    printImageMenu(arbolImagenes);
    string nombre = "";
    cout << "Escriba el nombre de la imagen a seleccionar: ";
    cin >> nombre;
    NodoArbol *hoja = arbolImagenes->obtener(nombre);
    if(hoja){
        system("clear");
        cout << "------ " << hoja->nombre << " ------" << endl;
        cout << "Numero      Capa" << endl;
        NodoCubo *temp = hoja->imagen->root->upper;
        while (temp != NULL){
            cout << "  " << temp->z << "    " << temp->layerName << endl;
            temp = temp->upper;
        }
        cout << "\nNumero de capa a reportar: ";
        string capa = "";
        cin >> capa;
        string salida = nombre+"Layer"+capa;
        hoja->imagen->graficarMatriz(salida,stoi(capa));
        //Abrir grafica.
        string comando = "eog Matrix_"+salida+".png";
        const char *cmd2 = comando.c_str();
        system(cmd2);
        cout << "\n¿Desea Graficar otra imagen? (y/n): ";
        cin >> capa;
        if(capa == "y"){
            repImageLayer(arbolImagenes);

        }
    }else{
        cout << "Seleccione una imagen valida" << endl;
        cin.ignore();
        cin.ignore();
        repImageLayer(arbolImagenes);
        }

}

void Menu::reports(ArbolB *arbolImagenes, listaCircular *filtros){
    int opcion = 0;
    string st = "";
    string comando;
    while(opcion != 6){
        system("clear");
        cout << "1. Imported Images Report" << endl;
        cout << "2. Image Layer Report" << endl;
        cout << "3. Linear Matrix Report" << endl;
        cout << "4. Traversal Report" << endl;
        cout << "5. Filters Report" << endl;
        cout << "6. Volver" << endl;
        cin >> opcion;
        switch(opcion){

            case 1:
                arbolImagenes->graficar();
                cout << "¿Desea abrir la grafica? (y/n): ";
                cin >> st;
                if(st == "y"){
                    //Abrir grafica.
                    comando = "eog binaryTree.png";
                    const char *cmd2 = comando.c_str();
                    system(cmd2);
                }
                break;
            case 2:
                repImageLayer(arbolImagenes);
                break;

            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "Opcion Invalida" << endl;
                cin.ignore();
                cin.ignore();
        }
    }
}

Menu::Menu()
{
    ArbolB *arbolImagenes = new ArbolB();
    cuboDisperso *selectedImage = new cuboDisperso();
    listaCircular *filtros = new listaCircular();

    int opcion = 0;
    while(opcion != 7){
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
            insertImage(arbolImagenes);
            //system("clear");
            break;
        case 2:
            system("clear");
            if(arbolImagenes->esVacio()){
                cout << "\nInserte Imagenes primero\n" << endl;
            }else{
                selectedImage = selectImage(arbolImagenes);
            }
            break;
        case 3:
            if(selectedImage->layerSize() > 0){
                filtros = filters(selectedImage);
            }else{
                cout << "No hay imagen seleccionada!" << endl;;
            }
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            if(arbolImagenes->esVacio()){
                cout << "Inserte Imagenes primero!" << endl;
            }else{
                reports(arbolImagenes, filtros);
            }
            break;
        case 7:
            break;
        default:
            cout << "Opcion invalida!" << endl;
        }
    }
}

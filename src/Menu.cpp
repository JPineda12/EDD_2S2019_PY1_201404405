#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <listaCircular.h>
#include <cuboDisperso.h>;
#include "Filters.h"
#include <GenerarPagina.h>
using namespace std;

cuboDisperso* Menu::createImage(string nombreCarpeta,listaCircular *listaCSV){
//Crea el Cubo con las capas y nodos
    cuboDisperso *imagen = new cuboDisperso(nombreCarpeta);
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
            y = 0;
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
                    imageWidth = stoi(word);
                    n = -1;
                }else if(n == 1){
                    imageHeight = stoi(word);
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
        if(success == true){
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

cuboDisperso* Menu::selectImage(ArbolB *arbolImagenes, listaFiltros *filtros){
    string nombre = "";
    printImageMenu(arbolImagenes);
    cout << "Escriba el nombre de imagen a seleccionar: ";
    cin >> nombre;
    NodoArbol *imagenSeleccionada = arbolImagenes->obtener(nombre);
    if (imagenSeleccionada != NULL){
        cout << "Imagen "+nombre << " seleccionada!\n\n";
        cin.ignore();
        cin.ignore();
        filtros = new listaFiltros();
        return imagenSeleccionada->imagen;

    }
    cout << "Nombre incorrecto!\n" << endl;
    return selectImage(arbolImagenes, filtros);
}

listaFiltros* Menu::filters(cuboDisperso* selectedImage, ArbolB *arbolImagenes, listaFiltros *filtros){
    int opcion = 0;
    int x, y;
    while(opcion != 6){
    cuboDisperso *imagenFiltro = new cuboDisperso(selectedImage->root->info);
    NodoCubo *auxz = selectedImage->root;
    NodoCubo *auxy;
    NodoCubo *auxx;
    while (auxz != NULL){
        auxy = auxz->down;
        while(auxy != NULL){
            auxx = auxy->next;
            while(auxx != NULL){
                imagenFiltro->insert_element(auxx->info,auxx->layerName,auxx->x,auxx->y,auxx->z);
                auxx = auxx->next;
            }
            auxy = auxy->down;
        }
        auxz = auxz->upper;
    }
        NodoArbol *hoja = arbolImagenes->obtener(imagenFiltro->root->info);
        Filters *filter = new Filters();
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
                imagenFiltro = filter->negativeAll(imagenFiltro);
                //cout << hoja << endl;
                //cout << imagenFiltro << endl;
                //cin.ignore();
                //cin.ignore();
                filtros->insertar("Negative", hoja->width, hoja->height, hoja->pxWidth, hoja->pxHeight, 1, 1, imagenFiltro);
                cout << "Negative Filter applied" << endl;
                cin.ignore();
                cin.ignore();
                break;
            case 2:
                imagenFiltro = filter->grayscaleAll(imagenFiltro);
                filtros->insertar("Grayscale", hoja->width, hoja->height, hoja->pxWidth, hoja->pxHeight, 1, 1, imagenFiltro);
                cout << "Grayscale Filter applied" << endl;
                cin.ignore();
                cin.ignore();
                break;
            case 3:
                system("clear");
                cout << "----- Mirror Filter -----" << endl;
                cout << "1. X-Mirror" << endl;
                cout << "2. Y-Mirror" << endl;
                cout << "3. Double Mirror" << endl;
                cin >> opcion;
                if(opcion == 1){
                 imagenFiltro = filter->mirrorAll(imagenFiltro, 0,hoja);
                 filtros->insertar("Mirror-X", hoja->width, hoja->height, hoja->pxWidth, hoja->pxHeight, 1, 1, imagenFiltro);
                 cout << "X-Mirror Filter applied" << endl;
                }else if(opcion == 2){
                     imagenFiltro = filter->mirrorAll(imagenFiltro, 1,hoja);
                     filtros->insertar("Mirror-Y", hoja->width, hoja->height, hoja->pxWidth, hoja->pxHeight, 1, 1, imagenFiltro);
                    cout << "Y-Mirror Filter applied" << endl;
                }else if(opcion == 3){
                    imagenFiltro = filter->mirrorAll(imagenFiltro, 2,hoja);
                    filtros->insertar("Double_Mirror", hoja->width, hoja->height, hoja->pxWidth, hoja->pxHeight, 1, 1, imagenFiltro);
                    cout << "Double-Mirror Filter applied" << endl;
                }else{
                    cout << "Opcion Invalida!" << endl;
                }
                cin.ignore();
                cin.ignore();
                break;
            case 4:
                system("clear");
                cout << "----- Collage Filter -----" << endl;
                cout << "Repeticiones en el eje x: ";
                cin >> x;
                cout << "\nRepeticiones en el eje y: ";
                cin >> y;
                imagenFiltro = filter->collage(imagenFiltro, x, y, hoja);
                filtros->insertar("Collage-"+to_string(x)+"x"+to_string(y), hoja->width*x, hoja->height*y, hoja->pxWidth, hoja->pxHeight, x, y, imagenFiltro);
                cout << "Collage Filter applied" << endl;
                cin.ignore();
                cin.ignore();
                break;
            case 5:
                imagenFiltro = filter->mosaic(imagenFiltro);
                break;
            case 6:
                break;
            default:
                cout << "Opcion Invalida" << endl;
                cin.ignore();
                cin.ignore();
        }
    }
    return filtros;

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
        int x = 1;
        while (temp != NULL){
            cout << "  " << temp->z << "    " << temp->layerName << endl;
            x = temp->z;
            temp = temp->upper;
        }
        x++;
        cout << "  " << to_string(x) << "    Graficar TODAS" << endl;
        cout << "\nNumero de capa a reportar: ";
        string capa = "";
        cin >> capa;
        string salida = "";
        if(stoi(capa) == x){
            temp = hoja->imagen->root->upper;
            while( temp != NULL){
                salida = nombre+"Layer"+to_string(temp->z);
                hoja->imagen->graficarMatriz(salida,temp->z,nombre);
                temp = temp->upper;
            }
        }else{
            salida = nombre+"Layer"+capa;
            hoja->imagen->graficarMatriz(salida,stoi(capa),nombre);
        }
        system("clear");
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

void Menu::repTrasversal(ArbolB *arbolImagenes){
    int opcion = 0;
    string st = "";
    string comando;
    while(opcion != 4){
        system("clear");
        cout << "1. Inorder Traversal" << endl;
        cout << "2. Postorder Traversal" << endl;
        cout << "3. Preorder Traversal" << endl;
        cout << "4. Volver" << endl;
        cin >> opcion;
        system("clear");
        switch(opcion){
            case 1:
                cout << "Generating inorder report!" << endl;
                arbolImagenes->graficarInorder();
                cout << "Generated!";
                cin.ignore();
                cin.ignore();
                system("clear");
                break;
            case 2:
                cout << "Generating posorder report!" << endl;
                arbolImagenes->graficarPosorder();
                cout << "Generated!";
                cin.ignore();
                cin.ignore();
                system("clear");
                break;
            case 3:
                cout << "Generating preorder report!" << endl;
                arbolImagenes->graficarPreorder();
                cout << "Generated!";
                cin.ignore();
                cin.ignore();
                system("clear");
                break;
            case 4:
                break;
            default:
                cout << "Opcion Invalida!\n";
                break;
        }
    }
}

void Menu::repLinearMatrix(ArbolB *arbolImagenes){
    printImageMenu(arbolImagenes);
    string nombre = "";
    cout << "Escriba el nombre de imagen a seleccionar: ";
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
        system("clear");
        listaCubo *linealizado = new listaCubo();
        int op = 0;
        string comando;
        const char *cmd2;
        while(op != 3){
            cout << "Linear Report para la capa no."+capa << endl;
            cout << "1. Linealizacion por Columnas\n";
            cout << "2. Linealizacion por filas\n";
            cout << "3. Volver" << endl;
            cin >> op;

            switch(op){
            case 1:
                cout << "\nGenerating linear map by Column\n";
                linealizado = hoja->imagen->linearMap_byCol(stoi(capa));
                linealizado->graficar("LinearMatrix_bycol", nombre);
                comando = "eog Reports/"+nombre+"/LinearMatrix_bycol.png";
                cmd2 = comando.c_str();
                system(cmd2);
                system("clear");
                cout << "Generated!\n";
                cin.ignore();
                cin.ignore();
                break;
            case 2:
                cout << "\nGenerating linear map by row\n";
                //hoja->imagen->linearMap_byRow(1);
                linealizado = hoja->imagen->linearMap_byRow(stoi(capa));
                linealizado->graficar("LinearMatrix_byrow",nombre);
                comando = "eog Reports/"+nombre+"/LinearMatrix_byrow.png";
                cmd2 = comando.c_str();
                system(cmd2);
                system("clear");
                cout << "Generated!\n";
                cin.ignore();
                cin.ignore();
                break;
            default:
                cout << "Opcion invalida!\n\n";
            //    cin.ignore();
            }
        }
    }

}

void Menu::repFIndiv(listaFiltros *filtros){
    int opcion = 0;
    int sub = 0;
    int exit = filtros->getSize()+1;
    int n;
    nodoFiltro *temp;
    while(opcion != exit){
        system("clear");
        n = 1;
        temp = filtros->head;
        cout << to_string(n) << ". " << temp->nombre << endl;
        temp = temp->next;
        n++;
        while(temp != filtros->head){
            cout << to_string(n) << ". " << temp->nombre << endl;
            temp = temp->next;
            n++;
        }
        cout << to_string(exit) << ". Volver " << endl;
        cin >> opcion;
        if(opcion == exit){
            break;
        }else if(opcion > exit){
            cout << "Opcion invalida" << endl;
        }else{
            nodoFiltro *f = filtros->obtener(opcion);
            cout << "---- Reporte De: " << f->nombre << " ----"<< endl;
            cout << "Numero      Capa" << endl;
            NodoCubo *capa = f->imagenFiltro->root->upper;
            int x = 0;
            while(capa != NULL){
                cout << "  " << to_string(capa->z) << "     " << capa->layerName << endl;
                x = capa->z;
                capa = capa->upper;
            }
            x++;
            cout << "  " << to_string(x) << "    Graficar TODAS" << endl;
            cin >> sub;
            string carpeta = f->imagenFiltro->root->info+"/Filters";
            string nombreF = f->nombre;
            if(sub == x){
                capa = f->imagenFiltro->root->upper;
                while(capa != NULL){
                    f->imagenFiltro->graficarMatriz(nombreF+"_"+capa->layerName,capa->z,carpeta);
                    capa = capa->upper;
                }
            }else if (sub <= x){
                capa = f->imagenFiltro->root->upper;
                while(capa != NULL){
                    if(sub == capa->z){
                        break;
                    }
                    capa = capa->upper;
                }
                f->imagenFiltro->graficarMatriz(nombreF+"_"+capa->layerName,capa->z,carpeta);
            }

        }

    }
}

void Menu::repFilters(listaFiltros *filtros){
    int opcion = 0;
    while (opcion != 3){
        system("clear");
        cout << "1. All filters Report" << endl;
        cout << "2. Individual filter Report" << endl;
        cout << "3. Volver" << endl;
        cin >> opcion;
        switch(opcion){
            case 1:
                filtros->graficar();
                cout << "Reporte Generado" << endl;
                cin.ignore();
                cin.ignore();
                break;
            case 2:
                repFIndiv(filtros);
                break;
            case 3:
                break;
            default:
                cout << "Opcion invalida!" << endl;
                break;
        }
    }
}

void Menu::reports(ArbolB *arbolImagenes, listaFiltros *filtros){
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
                    comando = "eog Reports/binaryTree.png";
                    const char *cmd2 = comando.c_str();
                    system(cmd2);
                }
                break;
            case 2:
                repImageLayer(arbolImagenes);
                break;

            case 3:
                repLinearMatrix(arbolImagenes);
                break;
            case 4:
                repTrasversal(arbolImagenes);
                break;
            case 5:
                if(filtros->esVacio()){
                    cout << "No existen filtros aplicados aun!" << endl;
                    cin.ignore();
                    cin.ignore();
                }else{
                    repFilters(filtros);
                }
                system("clear");
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

void Menu::exportarSelected(cuboDisperso *selectedImage, ArbolB *arbolImagenes){
    listaCubo *ls = new listaCubo();
    listaCubo *aux = new listaCubo();
    NodoArbol *hoja = arbolImagenes->obtener(selectedImage->root->info);
    NodoLineal *l;
    int layers = hoja->imagen->layerCount;
    for(int i = 1; i <= layers ; i++){
        aux = selectedImage->linearMap_byCol(i);
        l = aux->inicio;
        while( l != NULL){
            ls->insertar(l->info,l->coords);
            l = l->next;
        }
    }
    GenerarPagina *pagina = new GenerarPagina(selectedImage->root->info);
    pagina->crearCSS(ls,hoja, 1, 1);
    pagina->crearHTMl(ls,hoja);
    cout << "Imagen "+selectedImage->root->info+" exportada!";
    cin.ignore();
    cin.ignore();

}
void Menu::exportarFiltro(listaFiltros *filtros, ArbolB *arbolImagenes, string nombreImagen){
    cout << "\n\nLista de filtros aplicados" << endl;
    int n = 1;
    int opcion = 0;
    nodoFiltro *fil = filtros->head;
    cout << to_string(n)+". "+fil->nombre << endl;;
    fil = fil->next;
    n++;
    while (fil != filtros->head){
       cout << to_string(n)+". "+fil->nombre << endl;
       fil = fil->next;
       n++;
    }
    cout << "Escoja que filtro aplicado sobre "+nombreImagen+" quiere exportar:" << endl;
    cin >> opcion;
    nodoFiltro *f = filtros->obtener(opcion);
    if(f != NULL){
        cuboDisperso *exportar = f->imagenFiltro;
        NodoCubo *aux = exportar->root->upper;
        listaCubo *ls = new listaCubo();
        NodoLineal *l;
        listaCubo *temp = new listaCubo();
        while(aux != NULL){
            temp = exportar->linearMap_byCol(aux->z);
            l = temp->inicio;
            while(l != NULL){
                ls->insertar(l->info,l->coords);
                l = l->next;
            }
            aux = aux->upper;
        }
        NodoArbol *hoja = new NodoArbol(nombreImagen,f->width,f->height,f->pxwidth,f->pxheight,f->imagenFiltro);
        GenerarPagina *pagina = new GenerarPagina(nombreImagen+"_"+f->nombre);
        pagina->crearCSS(ls,hoja,f->repx,f->repy);
        pagina->crearHTMl(ls,hoja);
        cout << "Imagen con filtro exportada..." << endl;
        cin.ignore();
        cin.ignore();
    }else{
        cout << "Opcion Invalida" << endl;
        exportarFiltro(filtros, arbolImagenes, nombreImagen);
    }
}

void Menu::imageExport(cuboDisperso *selectedImage, listaFiltros *filtros, ArbolB *arbolImagenes){
    int opcion = 0;
    while(opcion != 3){
        system("clear");
        cout << "-----Image Export-----" << endl;
        cout << "1. Imagen original" << endl;
        cout << "2. Filtros aplicados" << endl;
        cout << "3. Volver" << endl;
        cout << "Que imagen desea exportar: ";
        string op = "";
        cin >> opcion;
        switch(opcion){
            case 1:
                cout << "Exportar "+selectedImage->root->info+" (y/n): ";
                cin >> op;
                if(op == "y"){
                    exportarSelected(selectedImage, arbolImagenes);
                }else{
                    system("clear");
                    break;
                }
                break;
            case 2:
                if(filtros->head != NULL){
                    exportarFiltro(filtros, arbolImagenes, selectedImage->root->info);
                }else{
                    system("clear");
                    cout << "Aplique algun filtro a la imagen en el menu de filtros primero!" << endl;
                }
                break;
            case 3:
                break;
            default:
                system("clear");
                cout << "Opcion Invalida!" << endl;
                break;
        }
    }
}
listaFiltros *Menu::editSelected(cuboDisperso *selectedImage, listaFiltros *filtros){
    system("clear");
    cout << "---- MANUAL EDIT - OG Image ----" << endl;
    NodoCubo *capa = selectedImage->root->upper;
    int opcion = 0;
    cout << "Numero      Capa" << endl;
    while(capa != NULL){
        cout << "  " << capa->z << "     "<< capa->layerName << endl;
        capa = capa->upper;
    }
    cout << "Escoja el NUMERO de capa: ";
    cin >> opcion;
    capa = selectedImage->root->upper;
    bool flag = false;
    while(capa != NULL){
        if(opcion == capa->z){
            flag = true;
            break;
        }
        capa = capa->upper;
    }
    if(flag){
        int x,y;
        cout << "---- LAYER: " << capa->layerName << " ----" << endl;
        cout << "Coordenada X: ";
        cin >> x;
        cout << "Coordenada Y: ";
        cin >> y;
        NodoCubo *fila = capa->down;
        NodoCubo *columna;
        bool foundcoords = false;
        system("clear");
        while(fila != NULL){
            if(fila->y == y){
                columna = fila->next;
                while(columna != NULL){
                    if(columna->x == x){
                        cout << "----------- (" << columna->x << "," << columna->y << ")" << " ----------- "<<endl;
                        cout << "R-G-B Actual: " << columna->info << endl;
                        cout << "-------------------------------" << endl;
                        foundcoords = true;
                        int r,g,b;
                        cout << "New R: ";
                        cin >> r;
                        cout << "New G: ";
                        cin >> g;
                        cout << "New B: ";
                        cin >> b;
                        string rgb = to_string(r)+"-"+to_string(g)+"-"+to_string(b);
                        columna->info = rgb;
                        cout << "Successfully edited!" << endl;
                        cin.ignore();
                        cin.ignore();
                        break;
                    }
                    columna = columna->next;
                }
                break;
            }
            fila = fila->down;
        }
        if(foundcoords == false){
            cout << "----------- (" << x << "," << y << ")" << " ----------- "<<endl;
            cout << "R-G-B Actual: sin color" << endl;
            cout << "-------------------------------" << endl;
            int r,g,b;
            cout << "New R: ";
            cin >> r;
            cout << "New G: ";
            cin >> g;
            cout << "New B: ";
            cin >> b;
            string rgb = to_string(r)+"-"+to_string(g)+"-"+to_string(b);
            selectedImage->insert_element(rgb,capa->layerName,x,y,capa->z);
            cout << "New color Successfully added!" << endl;
            cin.ignore();
            cin.ignore();
        }
    }else{
        cout << "Capa inexistente" << endl;
        return editSelected(selectedImage, filtros);
    }


    return filtros;


}

listaFiltros *Menu::editFilter(listaFiltros *filtros){


}

listaFiltros *Menu::manualEdit(cuboDisperso *selectedImage, listaFiltros *filtros){
    system("clear");
    cout << "-------- MANUAL EDITING --------" << endl;
    int opcion = 0;
    while(opcion != 3){
        cout << "1. Original Image" << endl;
        cout << "2. Filters" << endl;
        cout << "3. Volver" << endl;
        cin >> opcion;
        switch(opcion){
            case 1:
                editSelected(selectedImage, filtros);
                break;
            case 2:
                if(filtros->esVacio()){
                    system("clear");
                    cout << "No hay filtros aplicados!"<< endl;
                }else{
                    editFilter(filtros);
                    system("clear");
                }
                break;
            case 3:
                break;
            default:
                system("clear");
                cout << "Opcion Invalida!" << endl;
                break;
        }
    }

}

Menu::Menu()
{
    ArbolB *arbolImagenes = new ArbolB();
    cuboDisperso *selectedImage = new cuboDisperso("select");
    listaFiltros *filtros = new listaFiltros();

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
                selectedImage = selectImage(arbolImagenes, filtros);
                filtros = new listaFiltros();
            }
            break;
        case 3:
            if(selectedImage->layerSize() > 0){
                filtros = filters(selectedImage, arbolImagenes, filtros);
            }else{
                cout << "No hay imagen seleccionada!" << endl;
            }
            break;
        case 4:
            if(selectedImage->layerSize() > 0){
                filtros = manualEdit(selectedImage, filtros);
            }else{
                cout << "No hay imagen seleccionada!" << endl;
            }
            break;
        case 5:
            if(selectedImage->layerSize() > 0){
                imageExport(selectedImage, filtros,arbolImagenes);
            }else{
                cout << "No hay imagen seleccionada!" << endl;
            }
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

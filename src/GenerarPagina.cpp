#include "GenerarPagina.h"
#include <fstream>
#include <iostream>

GenerarPagina::GenerarPagina(string nombreImagen)
{
    this->nombreImagen = nombreImagen;
    string comando = "mkdir Exports/"+nombreImagen;
    const char *cmd = comando.c_str();
    system(cmd);
}

void GenerarPagina::crearHTMl(listaCubo *lsPixeles, NodoArbol *imagen){
    ofstream archivo;
    archivo.open("Exports/"+nombreImagen+"/"+nombreImagen+".html");
    int alto = imagen->height;
    int ancho = imagen->width;

    archivo << "<!DOCTYPE html>\n";
    archivo << "<html>";
    archivo << "<head>";
    archivo << "<link rel=\"stylesheet\" href=\""+nombreImagen+".scss\">\n";
    archivo << "</head>\n";
    archivo << "<body>\n";
    archivo << "<div class=\"canvas\">\n";
    int repetir = alto * ancho;
    for(int i = 0; i < repetir; i++){
        archivo << "    <div class=\"pixel\"></div>\n";
    }

    archivo << "</div>\n";
    archivo << "\n<body>\n";
    archivo << "<\html>";
    archivo.close();


}

string GenerarPagina::createHexa(int r, int g, int b){
    string hex = to_string((r<<16) | (g<<8) | b);
    return hex;

}

string GenerarPagina::convertRGB(NodoLineal *pixel){

    string sR = pixel->info;
    string sG = pixel->info;
    string sB = pixel->info;
    int foundR = sR.find("-");
    sR = sR.substr(0,foundR);
    int foundG = sG.find("-", foundR+1);
    sG = sG.substr(foundR+1,foundG-foundR+1);
    sB = sB.substr(foundG+1,3);
    int R = stoi(sR);
    int G = stoi(sG);
    int B = stoi(sB);
    //string hexa  = createHexa(stoi(R), stoi(G), stoi(B) );*/
    char Rhex_string[20];
    char Ghex_string[20];
    char Bhex_string[20];
    sprintf(Rhex_string,"%X", R);
    sprintf(Ghex_string, "%X", G);
    sprintf(Bhex_string, "%X",B);
    string hexr = Rhex_string;
    string hexg = Ghex_string;
    string hexb = Bhex_string;
    if(hexb == "0"){
        hexb = "00";
    }
    if(hexr == "0"){
        hexr = "00";
    }
    if(hexg == "0"){
        hexg = "00";
    }
    string hexa = hexr + hexg + hexb;

    return hexa;
}

void GenerarPagina::crearCSS(listaCubo *lsPixeles, NodoArbol *imagen, int pagew, int pageh){

    ofstream style;
    style.open("Exports/"+nombreImagen+"/"+nombreImagen+".scss");
    pageh = pageh * 100;
    style << "body {\n";
    style << "  background: #333333;\n ";
    style << "  height: "+to_string(pageh)+"vh;\n";
    if(pagew > 1){
    pagew = pagew * 100;
    style << "  width: "+to_string(pagew)+"vh;\n";
    }
    style << "  display: flex;\n";
    style << "  justify-content: center;\n";
    style << "  align-items: center;\n";
    style << "}\n";

    style << "\n.canvas {\n";
    int cWidth = imagen->width * imagen->pxWidth; //Size of the canvas
    int cHeight = imagen->height * imagen->pxHeight; //Size of the canvas

    style << "  width: "+to_string(cWidth)+"px;\n";
    style << "  height: "+to_string(cHeight)+"px;\n";
    style << "}\n";

    //Size of the pixel
    style << ".pixel {\n";
    style << "  width: "+to_string(imagen->pxWidth)+"px;\n";
    style << "  height: "+to_string(imagen->pxHeight)+"px;\n";
    style << "  float: left;\n";
    //style << "   box-shadow: 0px 0px 1px #fff;\n";
    style << "}";
    NodoLineal *pixel = lsPixeles->inicio; //Pixel con el color RGB
    int IR; //Indice real de la coordenada x,y del pixel
    string hexa; //Hexadecimal para pintar en el CSS
    int coordx;
    int coordy;
    string aux;
    int found;
    int found2;
    while(pixel != NULL){
        found = pixel->coords.find(",");
        aux = pixel->coords.substr(1,found-1);
        coordx = stoi(aux);

        found2 = pixel->coords.find(")");
        aux = pixel->coords.substr(found+1,found2-found-1);
        coordy = stoi(aux);
        IR = imagen->imagen->indiceReal(coordx, coordy, imagen->width);
        hexa = convertRGB(pixel);
        style << ".pixel:nth-child("+to_string(IR+1)+"){\n";
        style << "  background: #"+hexa+";\n";
        style << "}\n";
        pixel = pixel->next;
    }

    style.close();

}

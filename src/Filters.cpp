#include "Filters.h"
#include <iostream>;
Filters::Filters()
{
}

cuboDisperso *Filters::negativeAll(cuboDisperso *imagen){
    NodoCubo* tempz = imagen->root;
    NodoCubo* tempx;
    NodoCubo* tempy;
    string R = "";
    string G = "";
    string B = "";
    int new_R, new_G,new_B;
    string newRGB;
    int foundR = 0;
    int foundG = 0;
    int foundB = 0;
    while(tempz != NULL){
        tempy = tempz->down;
        while(tempy != NULL){
            tempx = tempy->next;
            while(tempx != NULL){
                //get R , G and B individually ej. 255-212-0
                R = tempx->info;
                G = tempx->info;
                B = tempx->info;
                foundR = R.find("-");
                R = R.substr(0,3);
                foundG = G.find("-",foundR+1);
                G = G.substr(foundR+1,3);
                B = B.substr(foundG+1,3);
                //Change the values with negative rgb colors. (255 - value)
                new_R = 255-stoi(R);
                new_G = 255-stoi(G);
                new_B = 255-stoi(B);
                //Change these values from the existing node.
                newRGB = to_string(new_R)+"-"+to_string(new_G)+"-"+to_string(new_B);
                tempx->info = newRGB;
                tempx = tempx->next;
            }
            tempy = tempy->down;
        }
        tempz = tempz->upper;
    }
    return imagen;
}

cuboDisperso *Filters::grayscaleAll(cuboDisperso *imagen){
    NodoCubo* tempz = imagen->root;
    NodoCubo* tempx;
    NodoCubo* tempy;

    string R = "";
    string G = "";
    string B = "";
    int new_R, new_G,new_B;
    string newRGB;
    int foundR = 0;
    int foundG = 0;
    int foundB = 0;
    int avg;
    while(tempz != NULL){
        tempy = tempz->down;
        while(tempy != NULL){
            tempx = tempy->next;
            while(tempx != NULL){
                //get R , G and B individually ej. 255-212-0
                R = tempx->info;
                G = tempx->info;
                B = tempx->info;
                foundR = R.find("-");
                R = R.substr(0,3);
                foundG = G.find("-",foundR+1);
                G = G.substr(foundR+1,3);
                B = B.substr(foundG+1,3);
                //Change the values with negative rgb colors. (255 - value)
                avg = (stoi(R)+stoi(G)+stoi(B))/3;
                new_R = avg;
                new_G = avg;
                new_B = avg;
                //Change these values from the existing node.
                newRGB = to_string(new_R)+"-"+to_string(new_G)+"-"+to_string(new_B);
                tempx->info = newRGB;
                cout << "New values: "+tempx->info << endl;
                cin.ignore();
                cin.ignore();
                tempx = tempx->next;
            }
            tempy = tempy->down;
        }
        tempz = tempz->upper;
    }
    return imagen;
}

cuboDisperso *Filters::mirrorAll(cuboDisperso *imagen, int tipo){
    return imagen;
}
cuboDisperso *Filters::mosaic(cuboDisperso *imagen){
    return imagen;
}
cuboDisperso *Filters::collage(cuboDisperso *imagen){
    return imagen;
}


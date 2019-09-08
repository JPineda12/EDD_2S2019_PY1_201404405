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
                tempx = tempx->next;
            }
            tempy = tempy->down;
        }
        tempz = tempz->upper;
    }
    return imagen;
}

cuboDisperso *Filters::mirrorAll(cuboDisperso *imagen, int tipo, NodoArbol *hoja){
    NodoCubo* tempz = imagen->root;
    NodoCubo* tempx;
    NodoCubo* tempy;
    int newx = 0;
    int newy = 0;
    int width = hoja->width-1;
    int height = hoja->height-1;
    cuboDisperso *aux = new cuboDisperso(imagen->root->info);
    while(tempz != NULL){
        tempy = tempz->down;
        while(tempy != NULL){
            tempx = tempy->next;
            while(tempx != NULL){
                if(tipo == 0){
                    //Apply only X-Mirror
                    newx = width - tempx->x;
                    newy = tempx->y;
                }else if(tipo == 1){
                    //Apply only Y-Mirror
                    newx =tempx->x;
                    newy = height - tempx->y;
                }else if(tipo == 2){
                    //Apply both mirrors
                    newx = width - tempx->x;
                    newy = height -tempx->y;
                }
                aux->insert_element(tempx->info,tempx->layerName,newx,newy,tempx->z);
                tempx = tempx->next;
            }
            tempy = tempy->down;
        }
        tempz = tempz->upper;
    }

    return aux;
}
cuboDisperso *Filters::mosaic(cuboDisperso *imagen){
    return imagen;
}

cuboDisperso *Filters::rep_x(cuboDisperso *imagen, int repeticiones_x, NodoArbol *hoja){
    NodoCubo* tempz;
    NodoCubo* tempx;
    NodoCubo* tempy;
    int width = hoja->width;
    int increment_width = hoja->width;
    int newx = 0;
    cuboDisperso *aux = new cuboDisperso(imagen->root->info);
    for(int i = 0; i<repeticiones_x; i++){
        tempz = imagen->root->upper;
        while (tempz != NULL){
            tempy = tempz->down;
            while(tempy != NULL){
                tempx = tempy->next;
                while(tempx != NULL){
                    aux->insert_element(tempx->info,tempx->layerName,tempx->x,tempx->y,tempx->z);
                    if(tempx->next == NULL){
                        tempx = tempy->next;
                        while(tempx != NULL){
                            newx = width + tempx->x;
                            aux->insert_element(tempx->info,tempx->layerName,newx,tempx->y,tempx->z);
                            tempx = tempx->next;
                        }
                    }else{
                        tempx = tempx->next;
                    }
                }
                tempy = tempy->down;
            }
            tempz = tempz->upper;
        }
        width = width + increment_width;
    }
    return aux;
}

cuboDisperso *Filters::rep_y(cuboDisperso *img, int repeticiones_y, NodoArbol *hoja){
    NodoCubo* tempz;
    NodoCubo* tempx;
    NodoCubo* tempy;
    int height = hoja->height;
    int increment_height = hoja->height;
    int newy = 0;
    cuboDisperso *aux = new cuboDisperso(img->root->info);

    for(int i = 0; i<repeticiones_y; i++){
        tempz = img->root->upper;
        while (tempz != NULL){
            tempx = tempz->next;
            while(tempx != NULL){
                tempy = tempx->down;
                while(tempy != NULL){
                    aux->insert_element(tempy->info,tempy->layerName,tempy->x,tempy->y,tempy->z);
                    if(tempy->down == NULL){
                        tempy = tempx->down;
                        while(tempy != NULL){
                        newy = height + tempy->y;
                        aux->insert_element(tempy->info,tempy->layerName,tempy->x,newy,tempy->z);
                        tempy = tempy->down;
                        }
                    }else{
                        tempy = tempy->down;
                    }
                }
                tempx = tempx->next;
            }
            tempz = tempz->upper;
        }
        height = height + increment_height;
    }
    return aux;

}

cuboDisperso *Filters::collage(cuboDisperso *imagen, int repeticiones_x, int repeticiones_y, NodoArbol *hoja){
    cuboDisperso *aux = new cuboDisperso(imagen->root->info);
    aux = rep_y(imagen, repeticiones_y, hoja);
    aux = rep_x(aux, repeticiones_x, hoja);
    return aux;
}


#include "cuboDisperso.h"
#include <fstream>
#include <iostream>
#include "listaCubo.h";
NodoCubo::NodoCubo(string info, string layerName, int x, int y, int z){
    this->info = info;
    this->layerName = layerName;
    this->x = x;
    this->y = y;
    this->z = z;
    next = NULL;
    prev = NULL;
    up = NULL;
    down = NULL;
    upper = NULL;
    lower = NULL;
}

cuboDisperso::cuboDisperso(string nombreImagen)
{
    this->root = new NodoCubo(nombreImagen, "Layer0", -1, -1,0);
    layerCount = 0;
}

NodoCubo* cuboDisperso::findRow(int y, int z){ //Method to look for a row.
    NodoCubo* temp = root;
    while(temp!= NULL){
        if(temp->z == z){
            while(temp->down != NULL){
                if(temp->y == y){
                    return temp;
                }
                temp = temp->down; //Moves down from root until it finds the specific row
            }
        }
        temp = temp->upper;
    }
    return NULL;
}

NodoCubo* cuboDisperso::findColumn(int x, int z){ //Method to look for a column.
    NodoCubo* temp = root; //2 , 4 ,10
    while(temp != NULL){
        if(temp->z == z){
            while(temp->next != NULL){
                if(temp->x == x){
                    return temp;
                }
                temp = temp->next; //Moves down from root until it finds the specific row
            }
        }
        temp = temp->upper;
    }
    return NULL;
}

NodoCubo* cuboDisperso::findLayer(int z){
    NodoCubo* temp = root; // 2 4 7 10 11  --4
    while(temp != NULL){
        if(temp->z == z){
            return temp;
        }
        temp = temp->upper;
    }
    return NULL;
}

NodoCubo* cuboDisperso::insert_sorted_col(NodoCubo* new_node, NodoCubo* head_col){
    NodoCubo* temp = head_col;
    bool flag = false;
        while(true){
            if(temp->x == new_node->x){
                //If pos x is the same, overwrites and existing node.
                temp->y = new_node->y;
                temp->info = new_node->info;
                return temp;
            }else if(temp->x > new_node->x){
                //If temp pos x is bigger, inserts just before that existing node.
                flag = true;
                break;
            }
            if(temp->next != NULL){
                //Moves to the next node to compare in the next iteration.
                temp = temp->next;
            }else{
                //If the next node is NULL, the new node should be inserted
                //  in the last position.
                break;
            }
        }

    if (flag){
        //Insert before temporal.
        new_node->next = temp;
        temp->prev->next = new_node;
        new_node->prev = temp->prev;
        temp->prev = new_node;
    }else{
        //inserts at the end.
        temp->next = new_node;
        new_node->prev = temp;
    }
        new_node->lower = temp->lower;
        new_node->upper = temp->upper;
    return new_node;
}
NodoCubo *cuboDisperso::insert_sorted_row(NodoCubo* new_node, NodoCubo* head_row){
    NodoCubo* temp = head_row;
    bool flag = false;
        while(true){
            if(temp->y == new_node->y){
                //If pos y is the same, overwrites and existing node.
                temp->x = new_node->x;
                temp->info = new_node->info;
                return temp;
            }else if(temp->y > new_node->y){
                //If temp pos y is greated, inserts just before that existing node.
                flag = true;
                break;
            }
            if(temp->down != NULL){
                //Moves to the node below to compare in the next iteration.
                temp = temp->down;
            }else{
                //If the node below is NULL, the new node should be inserted
                //  in the last position.
                break;
            }
        }

    if (flag){
        //Insert before temporal.
        new_node->down = temp;
        temp->up->down = new_node;
        new_node->up = temp->up;
        temp->up = new_node;
    }else{
        //inserts at the end.
        temp->down = new_node;
        new_node->up = temp;
    }
    //Links with the upper and lower root.
    new_node->lower = temp->lower;
    new_node->upper = temp->upper;
    return new_node;
}

NodoCubo* cuboDisperso::insert_sorted_layer(NodoCubo* new_node, NodoCubo* head_layer){
    NodoCubo* temp = head_layer;
    bool flag = false;

    while(true){
        if(temp->z == new_node->z){ //0 1  4 10  --3 -
        //I'm not gonna insert anything if this is the case.
            return temp;
        }else if(temp->z > new_node->z){
            flag = true;
            break;
        }
        if(temp->upper != NULL){
            temp = temp->upper;
        }else{
            break;
        }
    }

    if(flag){
        new_node->lower = temp->lower;
        new_node->upper = temp;
        temp->lower->upper = new_node;
        temp->lower = new_node;
    }else{ //Insert the layer at the top.
        new_node->lower = temp;
        temp->upper = new_node;
    }
    return new_node;
}

NodoCubo* cuboDisperso::create_layer(int z, string layerName){
    NodoCubo *head_layer = root;
    string name = "Layer"+to_string(z);
    NodoCubo *layer = new NodoCubo(name, layerName, -1,-1,z);
    layer = insert_sorted_layer(layer, head_layer);
    layerCount++;
    return layer;
}

NodoCubo* cuboDisperso::create_column(int x, NodoCubo* layer){
    NodoCubo *head_column = layer;
    string name = "Columna"+to_string(x); //Name of the column
    NodoCubo *column = new NodoCubo(name, "-",x,-1, layer->z);
    column = insert_sorted_col(column, layer);
    return column;
}

NodoCubo* cuboDisperso::create_row(int y, NodoCubo* layer){
    NodoCubo* head_row = layer;
    string name = "Fila"+to_string(y); //Name of the row
    NodoCubo *row = new NodoCubo(name,"-", -1,y, layer->z);
    row = insert_sorted_row(row, layer);
    return row;
}
int cuboDisperso::layerSize(){
    return layerCount;
}

void cuboDisperso::insert_element(string info, string layerName, int x, int y, int z){
    NodoCubo* new_node = new NodoCubo(info, layerName, x, y, z);
    //Look for the row & column where the element is gonna be inserted.
    NodoCubo* layerNode = findLayer(z);
    NodoCubo* rowNode = findRow(y, z);
    NodoCubo* columnNode = findColumn(x, z);
    if(layerNode == NULL){
        layerNode = create_layer(z, layerName);
    }
    //Case row & column does NOT exist
    if(columnNode == NULL && rowNode == NULL){
        //Step 1: Create column header
            NodoCubo* column = create_column(x, layerNode);
        //Step 2: Create row header
            NodoCubo* row = create_row(y, layerNode);
            //cout << "Row: " << rowNode << endl;
        //Step 3: Look for & insert the node in the new row
            new_node = insert_sorted_row(new_node,column);
        //Step 4: Look for & insert the node in the new column
           new_node = insert_sorted_col(new_node,row);

    }
    //Case row exists & column doesn't
    else if(rowNode != NULL && columnNode == NULL){
        //Step 1: Create Column Header
            NodoCubo* column = create_column(x, layerNode);
        //Step 2: insert the node in the existing row
            new_node = insert_sorted_row(new_node, column);
        //Step 3: Insert the node in the new column
            new_node = insert_sorted_col(new_node, rowNode);
    }

    //Case row does NOT exist & column does exists.
    else if(rowNode == NULL && columnNode != NULL){
        //Step 1: Create the row header
            NodoCubo* row = create_row(y, layerNode);
        //Step 2: Insert the node in the new row
            new_node = insert_sorted_row(new_node, columnNode);
        //Step 3: Insert the node in the existing column
            new_node = insert_sorted_col(new_node, row);
    }
    //Case row and column both exist
    else if(rowNode != NULL && columnNode != NULL){
        //Step 1: Insert the new node in the existing row
            new_node = insert_sorted_row(new_node, columnNode);
        //Step 2: Insert the new node in the existing column
            new_node = insert_sorted_col(new_node, rowNode);
    }
}

NodoCubo *cuboDisperso::obtener(int x, int y, int z){
    NodoCubo* tempz = root;
    NodoCubo* tempx = root;
    NodoCubo* tempy = root;
    while(tempz != NULL){
        if(tempz->z == z){
            tempy = tempz->down;
            while(tempy != NULL){
                if(tempy->y == y){
                    tempx = tempy->next;
                    while(tempx != NULL){
                        if(tempx->x == x){
                            return tempx;
                        }
                        tempx = tempx->next;
                    }
                }
                tempy = tempy->down;
            }
        }
        tempz = tempz->upper;
    }
    return NULL;
}

void cuboDisperso::imprimir(int z){
    NodoCubo* tempz = root;
    NodoCubo* tempx = root;
    NodoCubo* tempy = root;
    while(tempz != NULL){
            tempy = tempz->down;
        cout << "-------- C A P A  " << tempz->z <<"--------" << endl;
        while(tempy != NULL){
            tempx = tempy->next;
            while(tempx != NULL){
                cout << "(" << tempx->x << "," << tempx->y << "," << tempx->z << ") - "  << tempx->info << endl;
                tempx = tempx->next;
            }
            cout << endl;
            tempy = tempy->down;
        }
        tempz = tempz->upper;
    }

}

void cuboDisperso::graficarMatriz(string nombreCapa, int numeroCapa, string carpeta){
    // WRITING THE .DOT FILE
    NodoCubo* layer = root;
    while(layer != NULL){ //Find the layer to graph 1 2 3 4 5 6
        if(layer->z == numeroCapa){
            break;
        }
        layer = layer->upper;
    }
    string comando = "mkdir Reports/"+carpeta;
    const char *cmd = comando.c_str();
    system(cmd);
    ofstream archivo;
    //nombreCapa = to_string(numeroCapa);
    archivo.open("Reports/"+carpeta+"/Matrix_"+nombreCapa+".dot");
    archivo << "digraph Sparse_Matrix{\n";
    archivo << "node [shape=box]\n";
    archivo << "graph [ranksep=\"0.5\", nodesep=\"0.6\"];\n";
    archivo << "/* Group 0 para alinear verticalmente RAIZ*/ \n";
    archivo << layer->info+"[ label = \""+layer->info+"\", width = 1.5," +
                " style = filled, fillcolor = coral, group = 0 ];\n\n";

    //EMPIEZA CREACION DE NODOS FILAS
    archivo << "// Filas \n";
    NodoCubo* fila = layer->down;
    while (fila != NULL){
            //Escribir ej: Hora2[label = "Miercoles" width = 1.5 style = filled, fillcolor = bisque1, group = 1 ];
            archivo << "Fila"+to_string(fila->y)+" [label = \""+fila->info+"\" width = 1.5";
            archivo << " style = filled, fillcolor = bisque1, group = 0 ];\n";
            fila = fila->down;
    }

    //EMPIEZA CREACION DE ENLACES DE FILAS
    archivo << "\n //Enlaces de Filas\n";
    fila = layer->down;
    while (fila != NULL){
        //Escribir ej: Hora0->Hora1[dir = both];
        if(fila->down != NULL){
            archivo << "Fila"+to_string(fila->y)+"->Fila"+to_string(fila->down->y)+" [dir = both];\n";
        }
        fila = fila->down;
    }

    //EMPIEZA CREACION DE COLUMNAS
    archivo << "\n //Columnas\n";
    archivo <<"//Cada una con diferente group para alinear verticalmente con los nodos\n";
    NodoCubo* col = layer->next;
    while (col != NULL){
        //Escribir ej: Dia0[label = "Dia 0" width = 1.5 style = filled, fillcolor = pink2, group = 2 ];
        archivo << "Column"+to_string(col->x)+"[label = \""+col->info+"\" width = 1.5";
        archivo << " style = filled, fillcolor = pink2, group = "+to_string(col->x+1)+"];\n";
        col = col->next;
    }
    //EMPIEZA CREACION DE ENLACES DE COLUMNAS

    archivo << "\n //Enlaces de Columnas\n";
    col = layer->next;
    while(col != NULL){
        if(col->next != NULL){
            archivo << "Column"+to_string(col->x)+"->Column"+to_string(col->next->x)+" [dir = both];\n";
        }
        col = col->next;
    }
    //Alineacion Horizontal de Raiz con columnas
    col = layer->next;
    archivo << "\n // Alinear Raiz con Columnas\n";
    archivo << "{rank = same; "+layer->info+";";
    while(col != NULL){
        archivo << " Column"+to_string(col->x)+"; ";
        col = col->next;
    }
    archivo << "};\n";
    archivo << "\n // Enlaces Raiz con primera fila y columna\n";
    archivo << layer->info+"->Column"+to_string(layer->next->x)+";\n";
    archivo << layer->info+"->Fila"+to_string(layer->down->y)+";\n";

    //Empieza Creacion de Nodos
    archivo << "\n //Creacion de nodos\n";
    fila = layer->down;
    string group= "";
    while(fila != NULL){
        archivo << "//(^<---------------------- F I L A   "+to_string(fila->y)+"---------------------->\n";
        col = fila->next;
        while(col != NULL){
        //Escribir ej: A0_F0 [label = "153-204-255" width = 1.5, group = 2 style = filled, fillcolor = lavenderblush1];
        group = to_string(col->x+1); //El group siempre es la coordenada X osea, la columna.
        archivo << "N"+to_string(col->x)+"_F"+to_string(fila->y)+" [label = ";
        archivo << "\""+col->info+"\" width = 1.5 group = "+group+" style = filled, fillcolor = lavenderblush1];\n";
        col = col->next;
        }
        fila = fila->down;
        archivo << "\n";
    }

    //EMPIEZA CREACION DE ENLACES DE NODOS
    archivo << "\n //Creacion de enlaces de nodos\n";
    fila = layer->down;
    while (fila != NULL){
        archivo << "//E N L A C E S  F I L A   "+to_string(fila->y)+"\n";
        col = fila->next;
        while(col != NULL){
            //escribir ej: fila0->A0_F0[dir = both];
            if(fila->up == layer){ //Si es la primera fila
                //El nodo de arriba es un HEADER de columna, se enlaza.
                archivo << "Column"+to_string(col->x)+"->N"+to_string(col->x)+"_F"+to_string(fila->y);
                archivo << " [dir = both];\n";
            }else{
                //Enlaza con el Nodo de arriba
                if(col->up->y == -1){
                    archivo << "Column"+to_string(col->x)+"->N"+to_string(col->x)+"_F"+to_string(fila->y);
                    archivo << " [dir = both];\n";
                }else{
                    archivo << "N"+to_string(col->x)+"_F"+to_string(fila->y)+
                        "->N"+to_string(col->up->x)+"_F"+to_string(col->up->y);
                    archivo << " [dir = both];\n";
                }
            }
            if(col->prev == fila){ //Si es el primer nodo
                //Enlazar con cabecera de fila
                //escribir ej: Hora6->A0_F6[dir = both];
                archivo << "Fila"+to_string(fila->y)+"->N"+to_string(col->x)+"_F"+to_string(fila->y);
                archivo << " [dir = both];\n";
            }
            if(col->next != NULL){
                //Si existe un nodo a la derecha, Enlazarlo con el actual.
                //escribir ej: N1_L0->N2_L0[dir = both]; //Derecha
                archivo << "N"+to_string(col->x)+"_F"+to_string(fila->y)+
                        "->N"+to_string(col->next->x)+"_F"+to_string(fila->y);
                archivo << " [dir = both];\n";
            }
            col = col->next;
        }
        archivo << "//Alineacion vertical de nodos con la fila\n";
        col = fila->next;
        archivo << "{rank = same; Fila"+to_string(fila->y)+"; ";
        while(col != NULL){
            archivo << "N"+to_string(col->x)+"_F"+to_string(fila->y)+"; ";
            col = col->next;
        }
        archivo << " };\n\n";
        fila = fila->down;
    }

    archivo << "}\n";

    archivo.close();

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png SparseMatrix_"+nombreCapa+".dot"
    string comando2 = "dot Reports/"+carpeta+"/Matrix_"+nombreCapa+".dot -Tpng -o Reports/"+carpeta+"/Matrix_"+nombreCapa+".png";
    const char *cmd2 = comando2.c_str();
    system(cmd2);


}

listaCubo* cuboDisperso::linearMap_byRow(int z){
    //SUPONIENDO QUE LA MATRIZ DE COLORES RGB ESTA LLENA
    //FORMULA (ixn)+j;
    listaCubo *linealizado = new listaCubo();

    NodoCubo *tempz = root;
    NodoCubo *tempy = root;
    NodoCubo *tempx = root;
    while( tempz != NULL){
        if(tempz->z == z){
            break;
        }
        tempz = tempz->upper;
    }
    tempy = tempz->down;
    tempx;
    string coords = "";
    while(tempy != NULL){
        tempx = tempy->next;
        while(tempx != NULL){
            coords = "("+to_string(tempx->x)+","+to_string(tempx->y)+")";
                linealizado->insertar(tempx->info,coords);
            tempx = tempx->next;
        }
        tempy = tempy->down;

    }
    return linealizado;
}

listaCubo* cuboDisperso::linearMap_byCol(int z){
    //SUPONIENDO QUE LA MATRIZ DE COLORES RGB ESTA LLENA
    //FORMULA (jxn)+i;
    listaCubo *linealizado = new listaCubo();

    NodoCubo *tempz = root;
    NodoCubo *tempy = root;
    NodoCubo *tempx = root;
    while( tempz != NULL){
        if(tempz->z == z){
            break;
        }
        tempz = tempz->upper;
    }
    tempy;
    tempx = tempz->next;
    string coords = "";
    while(tempx != NULL){
        tempy = tempx->down;
        while(tempy != NULL){
            coords = "("+to_string(tempy->x)+","+to_string(tempy->y)+")";
                linealizado->insertar(tempy->info,coords);
            tempy = tempy->down;
        }
        tempx = tempx->next;

    }
    return linealizado;
}

int cuboDisperso::indiceReal(int x, int y, int width){
    //SUPONIENDO QUE LA MATRIZ DE COLORES RGB ESTA LLENA
    //FORMULA (ixn)+j;

    return (y*width)+x;


}





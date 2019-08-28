#include "cuboDisperso.h"
#include <fstream>
#include <iostream>
NodoCubo::NodoCubo(string info, int x, int y){
    this->info = info;
    this->x = x;
    this->y = y;
    next = NULL;
    prev = NULL;
    up = NULL;
    down = NULL;
}

cuboDisperso::cuboDisperso()
{
    this->root = new NodoCubo("Matrix", -1, -1);
}

NodoCubo* cuboDisperso::findRow(int y){ //Method to look for a row.
    NodoCubo* temp = root;
    while(temp->down != NULL){
        if(temp->y == y){
            return temp;
        }
        temp = temp->down; //Moves down from root until it finds the specific row
    }
    return NULL;
}

NodoCubo* cuboDisperso::findColumn(int x){ //Method to look for a column.
    NodoCubo* temp = root;
    while(temp->next != NULL){
        if(temp->x == x){
            return temp;
        }
        temp = temp->next; //Moves down from root until it finds the specific row
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
    return new_node;
}

NodoCubo* cuboDisperso::create_column(int x){
    NodoCubo *head_column = root;
    string name = "Columna"+to_string(x); //Name of the column
    NodoCubo *column = new NodoCubo(name,x,-1);
    column = insert_sorted_col(column, head_column);
    return column;
}

NodoCubo* cuboDisperso::create_row(int y){
    NodoCubo* head_row = root;
    string name = "Fila"+to_string(y); //Name of the row
    NodoCubo *row = new NodoCubo(name,-1,y);
    row = insert_sorted_row(row, head_row);
    return row;
}

void cuboDisperso::insert_element(string info, int x, int y){
    NodoCubo* new_node = new NodoCubo(info, x, y);
    //Look for the row & column where the element is gonna be inserted.
    NodoCubo* rowNode = findRow(y);
    NodoCubo* columnNode = findColumn(x);
    //Case row & column does NOT exist
    if(columnNode == NULL && rowNode == NULL){
        //Step 1: Create column header
            NodoCubo* column = create_column(x);
        //Step 2: Create row header
            NodoCubo* row = create_row(y);
        //Step 3: Look for & insert the node in the new row
            new_node = insert_sorted_row(new_node,column);
        //Step 4: Look for & insert the node in the new column
            new_node = insert_sorted_col(new_node,row);
    }
    //Case row exists & column doesn't
    else if(rowNode != NULL && columnNode == NULL){
        //Step 1: Create Column Header
            NodoCubo* column = create_column(x);
        //Step 2: insert the node in the existing row
            new_node = insert_sorted_row(new_node, column);
        //Step 3: Insert the node in the new column
            new_node = insert_sorted_col(new_node, rowNode);
    }

    //Case row does NOT exist & column does exists.
    else if(rowNode == NULL && columnNode != NULL){
        //Step 1: Create the row header
            NodoCubo* row = create_row(y);
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
void cuboDisperso::graficarMatriz(string nombreCapa){
    // WRITING THE .DOT FILE
    ofstream archivo;
    archivo.open("SparseMatrix_"+nombreCapa+".dot");
    archivo << "digraph Sparse_Matrix {\n";
    archivo << "node [shape=box]\n";
    archivo << "graph [ranksep=\"0.55\", nodesep=\"0.6\"];\n";
    archivo << "//Vertical Alignment for the ROOT - Group 0\n";
    archivo << root->info+"[ label = \""+root->info+"\", width = 1.5, style = filled, fillcolor = coral, group = 0 ];\n";
    archivo << "/* Filas Nodes HEADERS */\n";
    archivo << "// Filas with GROUP = 0 thus they are aligned with the ROOT Header\n";
    //ESCRITURA DE LAS FILAS DESDE LA PRIMERA DESPUES DE LA RAIZ HASTA QUE YA NO HAYAN FILAS (NULL)
    NodoCubo* fila = root->down;
    while(fila != NULL){
        //Escribir: Fila2 [label = "Fila 2"    width = 1.5 style = filled, fillcolor = bisque1, group = 1 ];
        archivo << fila->info+"[label = \""+fila->info+"\"" +
        " width = 1.5 style = filled, fillcolor = bisque1, group = 0 ];\n";
        fila = fila->down;
    }
    //ESCRITURA DE LOS ENLACES PARA CADA CABECERA DE LAS FILAS
    fila = root->down;
    archivo << "//ROWS LINKS\n";
    while(fila != NULL){
        //Escribir: Fila0->Fila1[dir = both];
        if(fila->down != NULL){
            //Si existe una fila abajo, enlazarla con fila actual.
            string valor = to_string(fila->down->y);
            archivo << fila->info+"->Fila"+valor+" [dir = both];\n";
        }
        fila = fila->down;
    }

    //ESCRITURA DE LA CREACION DE LOS NODOS DE LAS CABECERAS DE LAS COLUMNAS
    NodoCubo *columna = root->next;
    int group = 0;
    string valorgroup = "";
    archivo << "//Columns Nodes HEADERS\n";
    archivo << "//Each Column with diferent GROUP = n to align the nodes with these headers\n";
    while(columna != NULL){
        //Escribir: A0 [label = "Columna 1"   width = 1.5 style = filled, fillcolor = pink2, group = 2 ];
        group = columna->x+1; //Sums 1 to the x value so group = 1 belongs to column0;
        valorgroup = to_string(group);
        archivo << columna->info+"[label = \""+columna->info+"\"  width = 1.5"
                    +" style = filled, fillcolor = pink2, group = "+valorgroup+"];\n";
        columna = columna->next;
    }

    //ESCRITURA DE LOS ENLACES PARA CADA CABECERA DE LAS COLUMNAS
    columna = root->next;
    archivo << "//COLUMNS LINKS\n";
    while(columna != NULL){
        //Escribir: A0->A1[dir = both];
        if(columna->next != NULL){
            //Si existe una columna a la derecha, enlazarla la actual columna con esa
            archivo << columna->info+"->"+columna->next->info+" [dir = both];\n";
        }
        columna = columna->next;
    }

    archivo << "// \"rank = same\" so the columns are alligned with the ROOT header\n";
    columna = root;
    archivo << "{rank = same; ";
    while(columna != NULL){
        //Escribir: {rank = same ; Mt; A0; A1; A2; A3; A4};
        archivo << columna->info+"; ";
        columna = columna->next;
    }
    archivo << "};\n";

    //ENLACES DE LA RAIZ CON LA PRIMER COLUMNA Y PRIMERA FILA
    archivo <<"// ROOT links with the first column and row header\n";
    //Escribir     matrix->Fila0;    \n      Matrix->Column0;
    archivo <<root->info+"->"+root->down->info+";\n"+root->info+"->"+root->next->info;

    //EMPIEZA CREACION DE NODOS
    archivo <<"//NODES CREATION \n";
    int level = 0;
    NodoCubo* filaActual = root->down; //Level 0 belongs to the first row (the one linked to the root)
    NodoCubo* celdaActual;
    while(filaActual != NULL){
    archivo <<"//.....................L E V E L "+to_string(level)+" \n";
    //Now i'm gonna move actual to the right to create the nodes
    celdaActual = filaActual->next;
        while(celdaActual != NULL){
        //Escribir: C0_L0 [label = "153-204-255" width = 1.5, group = 2 style = filled, fillcolor = lavenderblush1];
            valorgroup = to_string(celdaActual->up->x+1); //Group equivale a la x+1 del nodo de arriba.
            archivo << "C"+to_string(celdaActual->x)+"_L"+to_string(level)
                    +" [label = \""+celdaActual->info+"\" width = 1.5, "
                    +"group = "+valorgroup+" style = filled, fillcolor = lavenderblush1];\n";
            celdaActual = celdaActual->next;
        }
        filaActual = filaActual->down;
        level++;
        archivo << "\n";
    }

    //EMPIEZA ESCRITURA DE LOS ENLACES DE LAS CELDAS
    archivo << "\n";
    filaActual = root->down;
    level = 0;
    while(filaActual != NULL){
    archivo << "//............... LINKS LEVEL "+to_string(level)+"\n";
    celdaActual = filaActual->next;
        while(celdaActual != NULL){
            if(level == 0){
                if(celdaActual == filaActual->next){
                //Si es el primer Nodo, Enlazar con CABECERA de fila
                    //Escribir: Fila2->C0_L0[dir = both];//Fila->Derecha
                    archivo << filaActual->info+"->C"+to_string(celdaActual->x)+"_L"+to_string(level)+
                                " [dir = both];\n";
                }
                //Enlazar con su nodo de arriba (Cabecera columna)
                archivo << celdaActual->up->info+"->C"+to_string(celdaActual->x)+"_L"+to_string(level)
                                +" [dir = both];\n";
                if(celdaActual->next != NULL){
                    //Si la celda actual tiene uno a la derecha enlazarlo
                    archivo << "C"+to_string(celdaActual->x)+"_L"+to_string(level)+"->C"
                            +to_string(celdaActual->next->x)+"_L"+to_string(level)+"[dir = both];\n";
                }
            }else{
            //A partir de LEVEL 1 >
                if(celdaActual == filaActual->next){
                //Si es el primer Nodo, Enlazar con CABECERA de fila
                    //Escribir: Fila2->C0_L0[dir = both];//Fila->Derecha
                    archivo << filaActual->info+"->C"+to_string(celdaActual->x)+"_L"+to_string(level)
                                +" [dir = both];\n";

                }
                if(celdaActual->up->y == -1 ) //Si la y de arriba es -1 entonces es una CABECERA de COLUMNA
                {
                    //Enlazar con la cabecera de arriba de columna.
                    archivo << celdaActual->up->info+"->C"
                            +to_string(celdaActual->x)+"_L"+to_string(level)+"[dir = both];\n";
                }else{
                    //Enlazar con su nodo de arriba (Celda arriba del LEVEL anterior)
                    archivo << "C"+to_string(celdaActual->x)+"_L"+to_string(level)+"->C"
                            +to_string(celdaActual->up->x)+"_L"+to_string(level-1)+"[dir = both];\n";
                }
                if(celdaActual->next != NULL){
                //Enlazar con su nodo de la derecha.
                    archivo << "C"+to_string(celdaActual->x)+"_L"+to_string(level)+"->C"
                            +to_string(celdaActual->next->x)+"_L"+to_string(level)+"[dir = both];\n";
                }
            }
            celdaActual = celdaActual->next;
        }

        //iterar para escribir el RANK = SAME
        celdaActual = filaActual->next;
        archivo << "{rank = same; "+filaActual->info+";";
        while(celdaActual != NULL){
            archivo << " C"+to_string(celdaActual->x)+"_L"+to_string(level)+";";
            celdaActual = celdaActual->next;
        }
        filaActual = filaActual->down;
        level++;
        archivo << "};\n\n";
        }
    archivo << "//END OF THE FILE! :')";
    archivo <<"\n}";
    archivo.close();
    //ARCHIVO TERMINADO.

    //ESCRIBIR EN TERMINAL PARA GENERAR EL .png SparseMatrix_"+nombreCapa+".dot"
    string comando = "dot SparseMatrix_"+nombreCapa+".dot -Tpng -o Matriz_"+nombreCapa+".png";
    const char *cmd = comando.c_str();
    system(cmd);
    //Abrir grafica.
    comando = "eog Matriz_"+nombreCapa+".png";
    const char *cmd2 = comando.c_str();
    system(cmd2);

}






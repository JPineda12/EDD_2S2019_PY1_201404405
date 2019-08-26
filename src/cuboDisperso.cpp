#include "cuboDisperso.h"

Nodo::Nodo(string info, int x, int y){
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
    tamano = 0;
    *root = Nodo("Root", 0, 0);
}

Nodo* cuboDisperso::findRow(int y){ //Method to look for a row.
    Nodo* temp = root;
    while(temp->next != root){
        if(temp->y == y){
            return temp;
        }
        temp = temp->down; //Moves down from root until it finds the specific row
    }
    return NULL;
}

Nodo* cuboDisperso::findColumn(int x){ //Method to look for a row.
    Nodo* temp = root;
    while(temp->next != root){
        if(temp->x == x){
            return temp;
        }
        temp = temp->next; //Moves down from root until it finds the specific row
    }
    return NULL;
}
Nodo* cuboDisperso::insert_sorted_col(Nodo* new_node, Nodo* head_col){
    Nodo* temp = head_col;
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
Nodo *cuboDisperso::insert_sorted_row(Nodo* new_node, Nodo* head_row){
    Nodo* temp = head_row;
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

Nodo* cuboDisperso::create_column(int x){
    Nodo *head_column = root;
    Nodo *column = new Nodo("COL",x,-1);
    column = insert_sorted_col(column, head_column);
    return column;
}

Nodo* cuboDisperso::create_row(int y){
    Nodo* head_row = root;
    Nodo *row = new Nodo("ROW",-1,y);
    row = insert_sorted_row(row, head_row);
    return row;
}

void cuboDisperso::insert_element(string info, int x, int y){
    Nodo* new_node = new Nodo(info, x, y);
    //Look for the row & column where the element is gonna be inserted.
    Nodo* columnNode = findColumn(x);
    Nodo* rowNode = findRow(y);

    //Case row & column does NOT exist
    if(columnNode == NULL && rowNode == NULL){
        //Step 1: Create column header
            Nodo* column = create_column(x);
        //Step 2: Create row header
            Nodo* row = create_row(y);
        //Step 3: Look for & insert the node in the new row
            new_node = insert_sorted_row(new_node,row);
        //Step 4: Look for & insert the node in the new column
            new_node = insert_sorted_col(new_node,row);
    }
    //Case row exists & column doesn't
    else if(rowNode != NULL && columnNode == NULL){
        //Step 1: Create Column Header
            Nodo* column = create_column(x);
        //Step 2: insert the node in the existing row
            new_node = insert_sorted_row(new_node, rowNode);
        //Step 3: Insert the node in the new column
            new_node = insert_sorted_col(new_node, column);
    }

    //Case row does NOT exist & column does exists.
    else if(rowNode == NULL && columnNode != NULL){
        //Step 1: Create the row header
            Nodo* row = create_row(y);
        //Step 2: Insert the node in the new row
            new_node = insert_sorted_row(new_node, row);
        //Step 3: Insert the node in the existing column
            new_node = insert_sorted_col(new_node, columnNode);
    }
    //Case row and column both exist
    else if(rowNode != NULL && columnNode != NULL){
        //Step 1: Insert the new node in the existing row
            new_node = insert_sorted_row(new_node, rowNode);
        //Step 2: Insert the new node in the existing column
            new_node = insert_sorted_col(new_node, columnNode);
    }
}






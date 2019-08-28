#ifndef CUBODISPERSO_H
#define CUBODISPERSO_H
#include <string>
using namespace std;

struct NodoCubo{
         string info;
         int x;
         int y;
         NodoCubo* prev;
         NodoCubo* next;
         NodoCubo* up;
         NodoCubo* down;
    public:
         NodoCubo(string info,int x, int y);

};

class cuboDisperso
{
    public:
        int tamano;
        NodoCubo *root;
        cuboDisperso();

        void insert_element(string info, int x, int y);
        NodoCubo *insert_sorted_col(NodoCubo* new_node, NodoCubo* head_col);
        NodoCubo *insert_sorted_row(NodoCubo* new_node, NodoCubo* head_row);
        NodoCubo *create_row(int y);
        NodoCubo *create_column(int x);
        NodoCubo *findRow(int y);
        NodoCubo *findColumn(int x);
        void graficarMatriz(string nombreCapa);


    protected:

    private:
};

#endif // CUBODISPERSO_H

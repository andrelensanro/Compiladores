#include<bits/stdc++.h>
using namespace std;

typedef struct nodo{
    string derecho; // simbolo
    bool terminal; // es un terminal?
    int wh_site; // en que numero de lista está?
}nodo;
typedef struct noTerminal{
    string izquierdo; // simbolo no terminal 
    bool terminal; // para estos tipos siempre estaran en false
    vector<nodo> regla; // la lista contendra los simbolos que representan la regla 
}noTerminal;
void initialize_nodo(nodo &nodito){
    nodito.derecho = "";
    nodito.terminal = true;
    nodito.wh_site = 0;
    return;
}

void initialize_noTerminal(noTerminal &noter){
    noter.izquierdo = "";
    noter.terminal = false;
    return;
}

void agregar_ladoDerecho(vector<noTerminal> &arrReglas, nodo &derecho){
    arrReglas[derecho.wh_site].regla.push_back(derecho);
    return;
}
void agregar_ladoIzquierdo(vector<noTerminal> &arrReglas, noTerminal &izquierdo){
    arrReglas.push_back(izquierdo);
    return;
}

void vernodo(nodo nodo){
    cout<<"simbolo del nodo: "<<nodo.derecho<<endl;
    cout<<"es terminal: "<<nodo.terminal<<endl;
    cout<<"a que numero de lista pertenezco: "<<nodo.wh_site<<endl;
}
void printArrayRules(vector<noTerminal> & arrReglas, string str){
    cout<<"-------------------------------------------- ";
    cout<<str<<endl;
    for( noTerminal &d: arrReglas ){
        cout<<d.izquierdo<<"->";
        for( nodo &n : d.regla ){
            cout<<n.derecho<<" ";
        }
        cout<<";"<<endl;
    }
    cout<<"--------------------------------------------\n";
}
int main(){
    vector<noTerminal> arrReglas;
    
    nodo derecho;
    initialize_nodo(derecho);
    derecho.derecho = "T";
    derecho.terminal = true;
    derecho.wh_site = arrReglas.size();
    vernodo(derecho);

    noTerminal izquierdo;
    initialize_noTerminal(izquierdo);
    izquierdo.izquierdo = "EP";
    izquierdo.terminal = false;
    
    agregar_ladoIzquierdo(arrReglas, izquierdo);
    agregar_ladoDerecho(arrReglas, derecho);
    printArrayRules(arrReglas, "resultado");

    return 0;
}
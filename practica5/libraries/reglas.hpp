#include<bits/stdc++.h>
using namespace std;
typedef struct nodo{
    string simb; // simbolo
    bool terminal; // es un terminal?
    int lugar; // en que numero de lista está?
}nodo;

typedef struct izquierdo{
    string simb; // simbolo no terminal 
    bool terminal; // para estos tipos siempre estaran en false
    vector<nodo> regla; // la lista contendra los simbolos que representan la regla 
}izquierdo;

void inicializar_derecho(nodo & nodito){
    nodito.simb = "";
    nodito.terminal = true;
    nodito.lugar = 0;
    return;
}

void inicializar_izquierdo(izquierdo & noterminal){
    noterminal.simb = "";
    noterminal.terminal = false;
    return;
}
void agregar_ladoDerecho(vector<izquierdo> &arrReglas, nodo &derecho){
    /*
    cout<<"GRAMATICA_________agregar_ladoDerecho\n";
    cout<<"GRAMATICA_________derecho.lugar = "<<derecho.lugar<<endl;
    cout<<"GRAMATICA_________tamaño de reglas = "<<arrReglas.size()<<endl;
    */
    arrReglas[derecho.lugar].regla.push_back(derecho);
    return;
}
void agregar_ladoIzquierdo(vector<izquierdo> &arrReglas, izquierdo &iz){
    //cout<<"GRAMATICA_________agregar_ladoIzquierdo\n";
    arrReglas.push_back(iz);
    return;
}
/*
int main(){
    nodo primerNodo;
    primerNodo.simb = "LadosDerechos";
    primerNodo.terminal = false;
    
    list<nodo> lista;
    noTerminal noTer;
    noTer.simbNoTerminal = "Regla";
    noTer.regla = &lista;

    list<nodo>::iterator miIt;
    miIt = lista.begin();
    lista.insert(miIt,primerNodo);
    noTer.terminal = false;

    //list<nodo>::iterator miIt;
    miIt = noTer.regla->begin();
    cout<<(*miIt).simb<<endl;
    while(miIt != noTer.regla->end()){
        cout<<(*miIt).simb<<endl;
        ++miIt;
    }
    return 0;
}
*/

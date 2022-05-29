#include<bits/stdc++.h>
using namespace std;
#include "libraries/reglas.hpp"
#include "libraries/analizadorLexicov2.hpp"
#define flecha 10
#define my_or 20
#define simbolo 30
#define puntocoma 40
#define espacio 50
void vertoken(int tok, string l){
    cout<<"token: "<<tok<<endl;
    cout<<"lexema: "<<l<<endl;
}
void vernodo(nodo *symbol){
    cout<<"simbolo del nodo: "<<symbol->simb<<endl;
    cout<<"es terminal: "<<symbol->terminal<<endl;
    cout<<"a que numero de lista pertenezco: "<<symbol->wh_site<<endl;
}
void printArrayRules(vector<noTerminal> & arrReglas, string str){
    cout<<"-------------------------------------------- ";
    cout<<str<<endl;
    for( noTerminal &d: arrReglas ){
        cout<<d.simbNoTerminal<<"->";
        for( nodo &n : d.regla ){
            cout<<n.simb<<" ";
        }
        cout<<";"<<endl;
    }
    cout<<"--------------------------------------------\n";
}
// ListaSimbolosP -> SIMBOLO ListaSimbolosP | epsilon (10)
bool ListaSimbolosP(vector<noTerminal> &arrReglas, nodo *symbol, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    nodo next_symbol;
    initialize_nodo(&next_symbol);
    next_symbol.wh_site = arrReglas.size();
    int tok;
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == simbolo){
        symbol->simb = lexema;
        if(ListaSimbolosP(arrReglas, &next_symbol, delta, a, lexema, symbolNotTerminal)){
            cout<<"aqui\n";
            vernodo(symbol);
            vernodo(&next_symbol);
            printArrayRules(arrReglas, "antes de que muera");
            arrReglas[arrReglas.size()].regla.push_back(next_symbol);
            cout<<"aqui ya no\n";
            printArrayRules(arrReglas, "Saliendo de ListaSimbolosP con modificacion");
            return true;
        }
        return false;
    }
    cout<<"llego hasta aca\n"<<endl;
    ctrlZ_analizadorLexico(tok,lexema);
    cout<<"llego hasta aca2\n"<<endl;
    return true;
}
// ListaSimbolos -> SIMBOLO ListaSimbolosP (9)
bool ListaSimbolos(vector<noTerminal> &arrReglas, nodo &symbol, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    nodo next_symbol;
    initialize_nodo(&next_symbol);
    next_symbol.wh_site = arrReglas.size();
    int tok;
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == simbolo){
        symbol.simb = lexema; // A
        if(ListaSimbolosP(arrReglas, &next_symbol, delta, a, lexema, symbolNotTerminal)){
            /*ligar symbol y next_symbol*/
            cout<<"regrese\n";
            printArrayRules(arrReglas, "Saliendo de ListaSimbolosP");
            arrReglas[symbol.wh_site].regla.push_back(next_symbol);
            return true;
        }
    }
    return false;
}
// LadoDerecho -> ListaSimbolos (8)
bool LadoDerecho(vector<noTerminal> &arrReglas, nodo &node, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    cout<<"entrando a lista de simbolos\n";
    if(ListaSimbolos(arrReglas, node, delta, a, lexema, symbolNotTerminal)){
        printArrayRules(arrReglas, "Saliendo de ListaSimbolos");
        return true;
    }
    return false;
}
// LadoSDerechoSP -> or LadoDerechoLadoSDerechoSP | epsilon (7)
bool LadoSDerechoSP(string lado_izquierdo, vector<noTerminal> &arrReglas, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    nodo symbol;
    initialize_nodo(&symbol);
    noTerminal noter;
    initialize_noTerminal(&noter);
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == my_or){
        if(LadoDerecho(arrReglas, symbol, delta, a, lexema, symbolNotTerminal)){
            symbol.wh_site = arrReglas.size();
            noter.simbNoTerminal = lado_izquierdo;
            noter.terminal = false;
            arrReglas.push_back(noter);
            arrReglas.end()->regla.push_back(symbol);
            printArrayRules(arrReglas, "Se acaba de modificar, asi que debe llevar algo-Saliendo de LadoDerecho");
            if(LadoSDerechoSP(lado_izquierdo, arrReglas, delta, a, lexema, symbolNotTerminal)){
                printArrayRules(arrReglas, "Saliendo de a ladosDerechosP");
                return true;
            }
        }
        return false;
    }
    ctrlZ_analizadorLexico(tok, lexema);
    return true;
}
// LadoSDerechoS -> LadoDerechoLadoSDerechoSP (6)
bool LadoSDerechoS(string &lado_izquierdo , vector<noTerminal> *arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    cout<<"lado_izquierdo: "<<lado_izquierdo<<endl;
    nodo lado_derecho;
    initialize_nodo(&lado_derecho);
    lado_derecho.wh_site = arrReglas->size();   /************************/
    noTerminal izquierdo; 
    initialize_noTerminal(&izquierdo);
    /*****/
    izquierdo.simbNoTerminal = lado_izquierdo;
    izquierdo.terminal = false;
    arrReglas->push_back(izquierdo);
    /********/
    printArrayRules(*arrReglas, "Entrando a ladosDerechos");
    if(LadoDerecho(*arrReglas, &lado_derecho, delta, a, lexema, symbolNotTerminal)){
        izquierdo.simbNoTerminal = lado_izquierdo;
        izquierdo.terminal = false;
        arrReglas->push_back(izquierdo);/************************/
        arrReglas->end()->regla.push_back(lado_derecho);/************************/
        //printArrayRules(arrReglas, "Se acaba de modificar, asi que debe llevar algo-Saliendo de ladoDerecho en LadosDerechos");
        if(LadoSDerechoSP(lado_izquierdo, arrReglas, delta, a, lexema, symbolNotTerminal)){
            //printArrayRules(arrReglas, "Saliendo de ladoDerecho en LadosDerechos");
            return true;
        }
    }
    return false;
}
// LadoIzq -> simbolo (5)
bool LadoIzq(string &simbolo_ladoIzquierdo, vector<noTerminal> *arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    tok = analizadorLexico(*delta, a, simbolo_ladoIzquierdo);
    cout<<"token del lado izquierdo: "<<tok<<endl;
    while(tok == espacio)
        tok = analizadorLexico(*delta, a, simbolo_ladoIzquierdo);
    //vertoken(tok, simbolo_ladoIzquierdo);
    //printArrayRules(arrReglas, "En ladoIzquierdo");
    if(tok == simbolo){
        return true;
    }
    return false;
}
// Regla -> LadoIzq -> LadoSDerechoS (4)
bool Regla(vector<noTerminal> *arrReglas, char **a, vector<reg> *delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    string simbolo_ladoIzquierdo;
    if(LadoIzq(simbolo_ladoIzquierdo, arrReglas, a, *delta, lexema, symbolNotTerminal)){// obtenermos la cadena del simbolo del lado izquierdo
        //printArrayRules(arrReglas, "Saliendo de lado izquierdo en Regla");
        tok = analizadorLexico(*delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(*delta, a, lexema);
        //vertoken(tok, lexema);
        if(tok == flecha){
            if(LadoSDerechoS(simbolo_ladoIzquierdo, arrReglas, a, *delta, lexema, symbolNotTerminal)){// pasamos la cadena del simbolo
                //printArrayRules(arrReglas, "Saliendo de ladosDerechos en Regla");
                return true;
            }
        }
    }
    return false;
}
// ReglasP -> Regla ; ReglasP | epsilon (3)
bool ReglasP(vector<noTerminal> &arrReglas, char **a, vector<reg> delta, string &lexema, vector<string> &symbolNotTerminal){
    /*guardar estado previo a llamar a regla*/
    //saveStateA = true;
    /*todo el estado de analizadorLexico*/
    int tok_antes_regla = analizadorLexico(delta, a, lexema);
    vertoken(tok_antes_regla, lexema);
    ctrlZ_analizadorLexico(tok_antes_regla, lexema);
    int tok;
    if(Regla(arrReglas, a, delta, lexema, symbolNotTerminal)){
        printArrayRules(arrReglas, "Saliendo de Regla en ReglasP");
        tok = analizadorLexico(delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(delta, a, lexema);
        vertoken(tok, lexema);
        if(tok == puntocoma){
            if(ReglasP(arrReglas, a, delta, lexema, symbolNotTerminal)){
                printArrayRules(arrReglas, "Saliendo de ReglasP en ReglasP");
                return true;
            }
        }
        return false;
    }
    /*regresar al estado previo de llamar a regla*/
    //restoreStateA = true;
    if(tok_antes_regla == 0)//fin de cadena ES AQUI DONDE TOMAMOS EN CUENTA A "EPSILON" 
        return true;
    return false;
    // si agarra epsilon, entonces, es muy probable de que detecte una gramatica que  no lo es como una que es correcta
}
// Reglas -> Regla ; ReglasP (2)
bool Reglas(vector<noTerminal> *arrReglas, char **a, vector<reg> *delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    if(Regla(arrReglas, a, delta, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de Regla en Reglas");
        tok = analizadorLexico(delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(delta, a, lexema);
        //vertoken(tok, lexema);
        if(tok == puntocoma){
            if(ReglasP(arrReglas, a, delta, lexema, symbolNotTerminal)){
                //printArrayRules(arrReglas, "Saliendo de ReglasP en Reglas");
                return true;
            }
        }
    }
    return false;
}
// G -> Reglas  (1)
bool G (vector<noTerminal> *arrReglas, char **a, vector<reg> *delta, string &lexema, vector<string> &symbolNotTerminal){
    //printArrayRules(arrReglas, "Entrando a G");
    if(Reglas(arrReglas, a, delta, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de Reglas en G");
        return true;
    }
    return false;
}
int main(){
    
    vector<noTerminal> arrReglas ;
    vector<reg> delta;
    vector<string> symbolNotTerminal;
    
    lecturaAFD(delta);

    ifstream f;
    f.open("./txt/inputs_GG/gramatica_ExpresionesRegulares.txt");
    if (f.is_open()){
        string lexema;
        string s="";
        char *a;
        while (!f.eof()){
            getline(f, s);
        }
        //s = "E->.T.Ep;Ep->.\\|.T.Ep|eps;T->.C.Tp;Tp->.\\!.C.Tp|eps;C->.F.Cp;Cp->\\+.Cp|\\*.Cp|\\?.Cp|eps;F->\\(.E.\\)|\\[.simb.\\-.simb.\\]|simb;";
        
        a = &s[0];
        G(&arrReglas, &a, &delta, lexema, symbolNotTerminal);
        cout<<"El arreglo de reglas queda de la siguiente forma:\n";
        for( noTerminal &d: arrReglas ){
            cout<<d.simbNoTerminal<<"->";
            for( nodo &n : d.regla ){
                cout<<n.simb<<" ";
            }
            cout<<";"<<endl;
        }
        printArrayRules(arrReglas, "main");
        f.close();
    }else{
        cout<<"el archivo especificado no se logro abrir\n";
    }
    return 0;
}
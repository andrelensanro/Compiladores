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
    cout<<"GRAMATICA_________vertoken\n";
    cout<<"GRAMATICA_________token: "<<tok<<endl;
    cout<<"GRAMATICA_________lexema: "<<l<<endl;
}
void vernodo(nodo &nodito){
    cout<<"GRAMATICA_________vernodo\n";
    cout<<"GRAMATICA_________simbolo del nodo: "<<nodito.simb<<endl;
    cout<<"GRAMATICA_________es terminal: "<<nodito.terminal<<endl;
    cout<<"GRAMATICA_________a que numero de lista pertenezco: "<<nodito.lugar<<endl;
}
void printArrayRules(vector<izquierdo> & arrReglas, string str){
    cout<<"-------------------------------------------- ";
    cout<<str<<endl;
    for( izquierdo &d: arrReglas ){
        cout<<d.simb<<"->";
        for( nodo &n : d.regla ){
            cout<<n.simb<<" ";
        }
        cout<<";"<<endl;
    }
    cout<<"--------------------------------------------\n";
}
void agregar_ladoDerecho(vector<izquierdo> &arrReglas, nodo &derecho){
    cout<<"GRAMATICA_________agregar_ladoDerecho\n";
    cout<<"GRAMATICA_________derecho.lugar = "<<derecho.lugar<<endl;
    cout<<"GRAMATICA_________tamaño de reglas = "<<arrReglas.size()<<endl;
    arrReglas[derecho.lugar].regla.push_back(derecho);
    return;
}
void agregar_ladoIzquierdo(vector<izquierdo> &arrReglas, izquierdo &iz){
    cout<<"GRAMATICA_________agregar_ladoIzquierdo\n";
    arrReglas.push_back(iz);
    return;
}
// ListaSimbolosP -> SIMBOLO ListaSimbolosP | epsilon (10)
//bool ListaSimbolosP(vector<izquierdo> &arrReglas, nodo &symbol, vector<reg> &delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
bool ListaSimbolosP(vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    nodo symbol;
    inicializar_derecho(symbol);
    //next_symbol.lugar = arrReglas.size();
    int tok;
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == simbolo){
        symbol.simb = lexema;
        symbol.terminal = false;
        symbol.lugar = arrReglas.size()-1;
        agregar_ladoDerecho(arrReglas, symbol);

        if(ListaSimbolosP(arrReglas, delta, a, lexema, symbolNotTerminal)){
            //cout<<"aqui\n";
            //vernodo(symbol);
            //vernodo(next_symbol);
            //printArrayRules(arrReglas, "antes de que muera");
            //agregar_ladoDerecho(arrReglas, next_symbol);
            //arrReglas[arrReglas.size()].regla.push_back(next_symbol);
            //cout<<"aqui ya no\n";
            //printArrayRules(arrReglas, "Saliendo de ListaSimbolosP con modificacion");
            return true;
        }
        return false;
    }
    //cout<<"llego hasta aca\n"<<endl;
    ctrlZ_analizadorLexico(tok,lexema);
    //cout<<"llego hasta aca2\n"<<endl;
    return true;
}
// ListaSimbolos -> SIMBOLO ListaSimbolosP (9)
//bool ListaSimbolos(vector<izquierdo> &arrReglas, nodo &symbol, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
bool ListaSimbolos(vector<izquierdo> &arrReglas, vector<reg> delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    nodo symbol;
    inicializar_derecho(symbol);
    int tok;
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == simbolo){

        symbol.simb = lexema; // A
        symbol.terminal = false;
        symbol.lugar = arrReglas.size()-1;
        agregar_ladoDerecho(arrReglas, symbol);

        if(ListaSimbolosP(arrReglas, delta, a, lexema, symbolNotTerminal)){
            /*ligar symbol y next_symbol*/
            //cout<<"regrese\n";
            //printArrayRules(arrReglas, "Saliendo de ListaSimbolosP");
            //arrReglas[symbol.lugar].regla.push_back(next_symbol);
            //agregar_ladoDerecho(arrReglas, next_symbol);
            
            //printArrayRules(arrReglas, "Saliendo de ListaSimbolosP");
            return true;
        }
    }
    return false;
}
// LadoDerecho -> ListaSimbolos (8)
bool LadoDerecho(vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    //cout<<"entrando a lista de simbolos\n";
    if(ListaSimbolos(arrReglas,delta, a, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de ListaSimbolos");
        return true;
    }
    return false;
}
// LadoSDerechoSP -> or LadoDerechoLadoSDerechoSP | epsilon (7)
bool LadoSDerechoSP(string &lado_izquierdo, vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    izquierdo noter;
    inicializar_izquierdo(noter);

    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    
    if(tok == my_or){
        cout<<"GRAMATICA_________agrego: "<<lado_izquierdo<<" como un nuevo lado izquierdo de arrReglas\n";
        noter.simb = lado_izquierdo;
        noter.terminal = false;
        agregar_ladoIzquierdo(arrReglas, noter);

        if(LadoDerecho(arrReglas, delta, a, lexema, symbolNotTerminal)){
            //symbol.lugar = arrReglas.size();
            /* // lo muevo para el lado izquierdo
            noter.simb = lado_izquierdo;
            noter.terminal = false;
            agregar_ladoIzquierdo(arrReglas, noter);
            */
            //arrReglas.push_back(noter);
            //agregar_ladoDerecho(arrReglas, symbol);
            //arrReglas.end()->regla.push_back(symbol);
            //printArrayRules(arrReglas, "Se acaba de modificar, asi que debe llevar algo-Saliendo de LadoDerecho");
            if(LadoSDerechoSP(lado_izquierdo, arrReglas, delta, a, lexema, symbolNotTerminal)){
                //printArrayRules(arrReglas, "Saliendo de a ladosDerechosP");
                return true;
            }
        }
        return false;
    }
    ctrlZ_analizadorLexico(tok, lexema);
    return true;
}
// LadoSDerechoS -> LadoDerechoLadoSDerechoSP (6)
bool LadoSDerechoS(string &lado_izquierdo , vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    //cout<<"lado_izquierdo: "<<lado_izquierdo<<endl;
    //nodo lado_derecho;
    //inicializar_derecho(lado_derecho);
    //lado_derecho.lugar = arrReglas->size();   /************************/
    //izquierdo iz; 
    //inicializar_izquierdo(iz);
    /*****/
    //iz.simb = lado_izquierdo;
    //iz.terminal = false;
    //arrReglas->push_back(iz);
    /********/
    //printArrayRules(arrReglas, "Entrando a ladosDerechos");
    if(LadoDerecho(arrReglas, delta, a, lexema, symbolNotTerminal)){
        //iz.simb = lado_izquierdo;
        //iz.terminal = false;
        //agregar_ladoIzquierdo(arrReglas, iz);
        //arrReglas->push_back(iz);/************************/
        //arrReglas->end()->regla.push_back(lado_derecho);/************************/
        //agregar_ladoDerecho(arrReglas, lado_derecho);
        //printArrayRules(arrReglas, "Se acaba de modificar, asi que debe llevar algo-Saliendo de ladoDerecho en LadosDerechos");
        if(LadoSDerechoSP(lado_izquierdo, arrReglas, delta, a, lexema, symbolNotTerminal)){
            //printArrayRules(arrReglas, "Saliendo de ladoDerecho en LadosDerechos");
            return true;
        }
    }
    return false;
}
// LadoIzq -> simbolo (5)
bool LadoIzq(string &simbolo_ladoIzquierdo, vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    tok = analizadorLexico(delta, a, simbolo_ladoIzquierdo);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, simbolo_ladoIzquierdo);
    cout<<"GRAMATICA_________lado_izquierdo"<<endl;
    vertoken(tok, simbolo_ladoIzquierdo);
    if(tok == simbolo){
        cout<<"GRAMATICA_________ladoIzquierdo encontrado: "<<simbolo_ladoIzquierdo<<endl;
        izquierdo noter;
        inicializar_izquierdo(noter);
        noter.simb = simbolo_ladoIzquierdo;
        noter.terminal = false;
        symbolNotTerminal.push_back(simbolo_ladoIzquierdo);
        agregar_ladoIzquierdo(arrReglas, noter);
        return true;
    }
    return false;
}
// Regla -> LadoIzq -> LadoSDerechoS (4)
bool Regla(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    string simbolo_ladoIzquierdo;
    if(LadoIzq(simbolo_ladoIzquierdo, arrReglas, a, delta, lexema, symbolNotTerminal)){// obtenermos la cadena del simbolo del lado izquierdo
        //printArrayRules(arrReglas, "Saliendo de lado izquierdo en Regla");
        tok = analizadorLexico(delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(delta, a, lexema);
        vertoken(tok, lexema);
        if(tok == flecha){
            if(LadoSDerechoS(simbolo_ladoIzquierdo, arrReglas, a, delta, lexema, symbolNotTerminal)){// pasamos la cadena del simbolo
                //printArrayRules(arrReglas, "Saliendo de ladosDerechos en Regla");
                return true;
            }
        }
    }
    return false;
}
// ReglasP -> Regla ; ReglasP | epsilon (3)
bool ReglasP(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    /*guardar estado previo a llamar a regla*/
    //saveStateA = true;
    /*todo el estado de analizadorLexico*/
    cout<<"GRAMATICA_________________________guardar estado previo\n";
    int tok_antes_regla = analizadorLexico(delta, a, lexema);
    vertoken(tok_antes_regla, lexema);
    ctrlZ_analizadorLexico(tok_antes_regla, lexema);

    int tok;
    if(Regla(arrReglas, a, delta, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de Regla en ReglasP");
        tok = analizadorLexico(delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(delta, a, lexema);
        vertoken(tok, lexema);
        if(tok == puntocoma){
            if(ReglasP(arrReglas, a, delta, lexema, symbolNotTerminal)){
                //printArrayRules(arrReglas, "Saliendo de ReglasP en ReglasP");
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
bool Reglas(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    int tok;
    if(Regla(arrReglas, a, delta, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de Regla en Reglas");
        tok = analizadorLexico(delta, a, lexema);
        while(tok == espacio)
            tok = analizadorLexico(delta, a, lexema);
        vertoken(tok, lexema);
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
bool G (vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, vector<string> &symbolNotTerminal){
    //printArrayRules(arrReglas, "Entrando a G");
    //int tok = analizadorLexico(delta, a, lexema);
    //cout<<"token en G: "<<tok;
    if(Reglas(arrReglas, a, delta, lexema, symbolNotTerminal)){
        printArrayRules(arrReglas, "Saliendo de Reglas en G");
        return true;
    }
    return false;
}
int main(){
    
    vector<izquierdo> arrReglas;
    vector<reg> delta;
    vector<string> symbolNotTerminal;
    
    lecturaAFD(delta);
    
    ifstream f;
    f.open("./txt/inputs_GG/gramatica_Gramaticas.txt");
    if (f.is_open()){
        string lexema;
        string s="";
        char *a;
        while (!f.eof()){
            getline(f, s);
        }
        //s = "E->.T.Ep;Ep->.\\+.T.Ep|\\-.T.Ep|epsilon;T->.P.Tp;Tp->.\\*.P.Tp|\\/.P.Tp|epsilon;P->.F.Pp;Pp->.\\^.F.Pp|epsilon;F->.\\(.E.\\)|sin.\\(.E.\\)|cos.\\(.E.\\)|tan.\\(.E.\\)|num;";
        a = &s[0];
        G(arrReglas, &a, delta, lexema, symbolNotTerminal);
        cout<<"GRAMATICA_________El arreglo de reglas queda de la siguiente forma:\n";
        for( izquierdo &d: arrReglas ){
            cout<<d.simb<<"->";
            for( nodo &n : d.regla ){
                cout<<n.simb<<" ";
            }
            cout<<";"<<endl;
        }
        printArrayRules(arrReglas, "main");
        f.close();
    }else{
        cout<<"GRAMATICA_________El archivo especificado no se logro abrir.\n";
    }
    return 0;
}
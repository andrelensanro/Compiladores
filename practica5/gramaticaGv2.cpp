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
// ListaSimbolosP -> SIMBOLO ListaSimbolosP | epsilon (10)
//bool ListaSimbolosP(vector<izquierdo> &arrReglas, nodo &symbol, vector<reg> &delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
bool ListaSimbolosP(vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
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
        symbol.terminal = true;
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
//bool ListaSimbolos(vector<izquierdo> &arrReglas, nodo &symbol, vector<reg> delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
bool ListaSimbolos(vector<izquierdo> &arrReglas, vector<reg> delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
    nodo symbol;
    inicializar_derecho(symbol);
    int tok;
    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    if(tok == simbolo){
        symbol.simb = lexema; // A
        symbol.terminal = true;
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
bool LadoDerecho(vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
    //cout<<"entrando a lista de simbolos\n";
    if(ListaSimbolos(arrReglas,delta, a, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de ListaSimbolos");
        return true;
    }
    return false;
}
// LadoSDerechoSP -> or LadoDerechoLadoSDerechoSP | epsilon (7)
bool LadoSDerechoSP(string &lado_izquierdo, vector<izquierdo> &arrReglas, vector<reg> &delta, char **a, string &lexema, map<string, int> &symbolNotTerminal){
    int tok;
    izquierdo noter;
    inicializar_izquierdo(noter);

    tok = analizadorLexico(delta, a, lexema);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, lexema);
    vertoken(tok, lexema);
    
    if(tok == my_or){
        //cout<<"GRAMATICA_________agrego: "<<lado_izquierdo<<" como un nuevo lado izquierdo de arrReglas\n";
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
bool LadoSDerechoS(string &lado_izquierdo , vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
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
bool LadoIzq(string &simbolo_ladoIzquierdo, vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
    int tok;
    tok = analizadorLexico(delta, a, simbolo_ladoIzquierdo);
    while(tok == espacio)
        tok = analizadorLexico(delta, a, simbolo_ladoIzquierdo);
    //cout<<"GRAMATICA_________lado_izquierdo"<<endl;
    vertoken(tok, simbolo_ladoIzquierdo);
    if(tok == simbolo){
        //cout<<"GRAMATICA_________ladoIzquierdo encontrado: "<<simbolo_ladoIzquierdo<<endl;
        izquierdo noter;
        inicializar_izquierdo(noter);
        noter.simb = simbolo_ladoIzquierdo;
        noter.terminal = false;
        //symbolNotTerminal.push_back(simbolo_ladoIzquierdo);
        symbolNotTerminal.insert(make_pair(simbolo_ladoIzquierdo, symbolNotTerminal.size()-1));
        agregar_ladoIzquierdo(arrReglas, noter);
        return true;
    }
    return false;
}
// Regla -> LadoIzq -> LadoSDerechoS (4)
bool Regla(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
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
bool ReglasP(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
    /*guardar estado previo a llamar a regla*/
    //saveStateA = true;
    /*todo el estado de analizadorLexico*/
    //cout<<"GRAMATICA_________________________guardar estado previo\n";
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
bool Reglas(vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
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
bool G (vector<izquierdo> &arrReglas, char **a, vector<reg> &delta, string &lexema, map<string, int> &symbolNotTerminal){
    //printArrayRules(arrReglas, "Entrando a G");
    //int tok = analizadorLexico(delta, a, lexema);
    //cout<<"token en G: "<<tok;
    if(Reglas(arrReglas, a, delta, lexema, symbolNotTerminal)){
        //printArrayRules(arrReglas, "Saliendo de Reglas en G");
        return true;
    }
    return false;
}
bool tieneEpsilon(set<string> &s){
    //cout<<"entras en tieneEpsilon\n";
    if(s.find("eps") == s.end() && s.find("epsilon") == s.end()){
        //cout<<"entras en tieneEpsilon\n";
        return false;
    }
    //cout<<"si tiene epsilon\n";
    return true;
}
void first(vector<nodo> &n, vector<izquierdo> &arrReglas, int &i, set<string> &r){// i se manda a llamar en 0
    //set<string> r = {};
    set<string> s = {};
    int j=0;
    set<string>::iterator it;
    /*for(izquierdo z: arrReglas){
        if(z.simb == n[i].simb){//0
            cout<<"z: "<<z.simb<<endl;
            for(nodo p : z.regla)
                cout<<p.simb<<"  ";
            cout<<endl;
            first(z.regla, arrReglas, i, s);
        }
    }*/
    if(n[i].terminal || n[i].simb == "epsilon" || n[i].simb == "eps"){
        //cout<<"Es terminal n["<<i<<"]: "<<n[i].simb<<endl;
        r.insert(n[i].simb);
    }
    if(!n[i].terminal){//i = 0 Ep
        for(izquierdo z: arrReglas){
            if(z.simb == n[i].simb){//0
                //cout<<"z: "<<z.simb<<endl;// Ep ->+ T Ep
                /*for(nodo p : z.regla)
                    cout<<p.simb<<"  ";
                cout<<endl;*/
                first(z.regla, arrReglas, j, s);
                if( tieneEpsilon(s) && i<n.size()-1){
                    it = s.find("epsilon");
                    s.erase(it);
                    //cout<<z.regla[i].simb<<endl;
                    i++;
                    //cout<<"incrementamos i: "<<i<<endl;
                    //cout<<" por lo que sacamos el first del siguiente termino: "<<z.regla[i].simb<<endl;
                    set<string> l;
                    first(n, arrReglas, i, l);
                    for(string str: l)
                        s.insert(str);
                }
            }
        }
        for(string str: s)
            r.insert(str);
    }
    //return r;
    return;
}
void follow(string simb, vector<izquierdo> &arrReglas, set<string> &r, map<string, int> &noterminales){
    if(simb == arrReglas[0].simb)
        r.insert("$");
    set<string> s;
    for(izquierdo ar : arrReglas){
        //for(nodo n: ar.regla){
        for(int i=0; i<ar.regla.size(); i++){
            if(ar.regla[i].simb == simb){
                //cout<<"buscando si eres ultimo"<<ar.regla[i].simb<<endl;
                if(i == ar.regla.size()-1){// eres ultimo
                    //cout<<"calcular follow de: "<<ar.simb<<endl;
                    if(ar.simb != simb){
                        follow(ar.simb, arrReglas, s, noterminales);
                        //cout<<"por lo que quedas con tamanio de: "<<s.size()<<endl;
                    }
                }else{
                    set<string> l;
                    set<string>::iterator it;
                    vector<nodo> v;
                    nodo nn;
                    inicializar_derecho(nn);
                    nn.lugar=0;//no me importa, solo es para llenar el campo
                    nn.simb = ar.regla[++i].simb;
                    for(auto str: noterminales){
                        if (str.first == nn.simb){ 
                            nn.terminal = false;
                            break;
                        }else
                            nn.terminal = true;
                    }      
                    v.push_back(nn);
                    int j = 0; 
                    first(v, arrReglas, j, l);

                    if(tieneEpsilon(l)){
                        it = l.find("epsilon");
                        l.erase(it);
                        for(string str: l)
                            s.insert(str);
                        set<string> p;
                        if(ar.simb != simb){
                            follow(ar.simb, arrReglas, p, noterminales);
                            for(string str: p)
                                s.insert(str);
                        }
                    }else{
                        for(string str: l)
                            s.insert(str);
                    }
                }
            }
        }
    }
    for(string str: s)
        r.insert(str);
}
string vector2string(vector<nodo> v){
    string resp;
    for(nodo n: v){
        resp.append(n.simb);
    }
    return resp;
}
void imprimirLL1(vector<vector<pair<string, int>>> tablaLL1){
    cout<<"Tabla LL1\n";
    char *a;
    cout<<"filas: "<<tablaLL1.size()<<endl;
    for(int i=0; i<tablaLL1.size(); i++){ 
        for(int j=0; j<tablaLL1[i].size(); j++){
            a = &tablaLL1[i][j].first[0];
            printf("%7s,%7d|", a, tablaLL1[i][j].second);
        }
        cout<<endl;
    }
    return;
}
/*bool verificarCadena(string str, vector<vector<pair<string, int>>> &tablall1){

}*/
void generartablaLL1(map<string, int> &noterminales, map<string, int> &terminales, vector<vector<pair<string, int>>> &tablall1, vector<izquierdo> &arrReglas){
    //llenar columnas
    for(auto p: terminales){
        tablall1[0][p.second] = p;
    }
    tablall1[0][terminales.size()+1] = make_pair("$", terminales.size()+ 1);
    //llenar filas
    for(auto p: noterminales)
        tablall1[p.second][0] = p;
    for(auto p: terminales)
        tablall1[p.second+noterminales.size()][0] = p;
    tablall1[terminales.size()+noterminales.size()+1][0] = make_pair("$", terminales.size()+noterminales.size()+1);
    /*Analisis de cada regla*/
    int i=0;
    int numRegla = 0;
    for(izquierdo iz: arrReglas){
        set<string> firstR ={};
        set<string> followR = {};
        set<string> ::iterator it;
        first(iz.regla, arrReglas, i, firstR);
        if(tieneEpsilon(firstR)){
            it = firstR.find("epsilon");
            firstR.erase(it);
            follow(iz.simb, arrReglas, followR, noterminales);
            for(string f: followR){
                firstR.insert(f);
            }
        }
        /*los busco en los terminales*/
        for(string str: firstR){
            string aux = vector2string(iz.regla);
            if(str == "$"){
                tablall1[noterminales[iz.simb]][terminales.size()+1] = make_pair("$", numRegla);
            }else{
                tablall1[noterminales[iz.simb]][terminales[str]] = make_pair(aux, numRegla); /*columna - fila*/
            }
            /*OJO.PUEDE SER UNA PAIR DE VECTOR, NUMERO DE REGLA y solo ya no utilizaria la funcion de convertir vector a string*/
        }
        numRegla++;
    }
    for(auto t: terminales)
        tablall1[t.second + noterminales.size()][t.second] = make_pair("pop", -1);
    tablall1[terminales.size()+noterminales.size()+1][terminales.size()+1] = make_pair("ac", -1);
}
int main(){
    vector<izquierdo> arrReglas;
    vector<reg> delta;
    map<string, int> symbolNotTerminal;
    map<string, int> terminales;
    lecturaAFD(delta);
    ifstream f;
    f.open("./txt/inputs_GG/gramatica_calculadora.txt");
    if (f.is_open()){
        string lexema;
        string s="";
        char *a;
        while (!f.eof()){
            getline(f, s);
        }
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
        f.close();
        
        //cout<<"Los simbolos no terminales son:"<<endl;
        int c=1;
        for(auto &str: symbolNotTerminal){
            str.second = c;
        //    cout<<str.first<<" "<<str.second<<endl;
            c++;
        }
        
        bool ter;
        map<string, int>:: iterator it;
        for( izquierdo &d: arrReglas ){
            for( nodo &n : d.regla ){
                ter = false;
                for(auto str: symbolNotTerminal){
                    if(n.simb == str.first ){
                        n.terminal = false;
                        ter = true;
                        break;
                    }
                }
                if(!ter){//no es terminal
                    if(!terminales.count(n.simb)){
                        cout<<"'"<<n.simb<<"'"<<endl;
                        terminales.insert(make_pair(n.simb, 1));
                        
                    }
                }
            }
        }
        if(terminales.count("epsilon")){
            it = terminales.find("epsilon");
            terminales.erase(it);
        }
        
        //cout<<"Los simbolos terminales son:"<<endl;
        c=1;
        for(auto &str: terminales){
            str.second = c;
            //cout<<str.first<<" "<<str.second<<endl;
            c++;
        }
        //cout<<endl;
        
        /*GENERAR TABLA LL1*/
        vector<vector<pair<string, int>>> tablaLL1(symbolNotTerminal.size()+terminales.size()+2, vector<pair<string, int>>(terminales.size()+2, make_pair("-",-1)));
        generartablaLL1(symbolNotTerminal, terminales, tablaLL1, arrReglas);
        imprimirLL1(tablaLL1);
        
    }else{
        cout<<"GRAMATICA_________El archivo especificado no se logro abrir.\n";
    }
    return 0;
}
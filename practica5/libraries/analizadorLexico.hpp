#include<bits/stdc++.h>
using namespace std;

typedef struct reg{
    int origen;
    char a;
    char b;
    int destino;
    int token;
}reg;
typedef struct stateLexico{
    stack<pair<int, string>> cp_tokens;
    int cp_estadoActualAFD;
    bool cp_ac;
    string cp_lexema;
    char * cp_finLexema;
    char * cp_inilexema;
    int cp_token;
    int cp_TOKEN;
    int cp_destino;
}stateLexico;

stack<pair<int, string>> tokens;
bool saveStateA;
bool restoreStateA;
stateLexico state; // tendra el estado del lexico, cuando se saveStateA = true

void ctrlZ_analizadorLexico(int &TOKEN, string lex){
    tokens.push(make_pair(TOKEN, lex));
}
int findTransition(vector<reg> d, int estadoActual, char a, int &ptoken, bool &ac){
    int destino;
    for(int i=0; i<d.size(); i++){
        if(estadoActual == d[i].origen && a >= d[i].a && a <= d[i].b){
            destino = d[i].destino;
            for(int j=0; j<d.size(); j++){
                if(destino == d[j].origen){
                    if(d[j].token!=0){
                        ac = true; // como no es 0, es estado de aceptacion
                        ptoken = d[j].token;
                    }else{
                        ac = false;
                        ptoken = d[j].token; 
                    }
                    break;
                }
            }
            return destino;
        }
    }
    ptoken = 0; 
    return -1;
}
int analizadorLexico(vector<reg> d, char **a, string &lexema){
    lexema = "";
    int estadoActualAFD = 0;
    bool ac = false;
    char * finLexema = nullptr;
    char * caracterActual = *a;
    char * inilexema = *a;
    int TOKEN = 0;
    int pToken;
   
    while(*caracterActual!='\0'){
        if(restoreStateA){
            ac = state.cp_ac;
            //destino = state.cp_destino;
            estadoActualAFD = state.cp_estadoActualAFD;
            finLexema = state.cp_finLexema;
            inilexema = state.cp_inilexema;
            lexema = state.cp_lexema;
            TOKEN = state.cp_TOKEN;
            pToken = state.cp_token;
            tokens = state.cp_tokens;
            restoreStateA = false;
        }
        if(tokens.size()){ // >0
            pair<int, string> tope_tokens = tokens.top();
            tokens.pop();
            return tope_tokens.first;
        }
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken, ac);
        //destino = state.cp_destino;
        if(destino==-1){
            if(!ac){
                inilexema++;
                *a = inilexema;
                return -1; // no hay estado de aceptacion y retorna eso
            }else{
                finLexema++;
                *a = finLexema;
                return TOKEN; // cuando ya hubo un estado de aceptacion retorna ese token
            }
        }else{
            estadoActualAFD = destino;
            if(pToken!=0){ // es un estado final
                TOKEN = pToken;
                finLexema = caracterActual;
                lexema.push_back(*caracterActual);
            }
            caracterActual++;
        }
        /*if(saveStateA){
            state.cp_ac = ac;
            state.cp_destino = destino;
            state.cp_estadoActualAFD = estadoActualAFD;
            state.cp_finLexema = finLexema;
            state.cp_inilexema = inilexema;
            state.cp_lexema = lexema;
            state.cp_TOKEN = TOKEN;
            state.cp_token = pToken;
            state.cp_tokens = tokens;
            saveStateA = false;
        }*/
    }
    *a = caracterActual;
    return TOKEN;
}
void lecturaAFD(vector<reg> &delta){
    char direccion[100];
    int origen=-1, destino=-1, token=-1;
    string rango="", s="";
    ifstream f;
    reg registro;
    f.open("./../txt/inputs_analizadorLexico/clasesLexicasGramatica.txt");
    if (f.is_open()){
        while (!f.eof()){
            f >> origen >> rango >> destino >> token;
            registro.origen = origen;
            registro.destino = destino;
            registro.a = rango[1];
            registro.b = rango[rango.size()-2];
            registro.token = token;
            delta.push_back(registro);
        }
    }
    f.close();
}
/*
int callLexic(string &s, int &token){
    vector<reg> delta;
    lecturaAFD(delta);
    char *a;
    a = &s[0];
    string lexema;
    //token =  analizadorLexico(delta, &a, lexema);
    /*
    while(1){
        int TOKEN = analizadorLexico(delta, &a, lexema);
        cout<<"\t\t\t\t\ttoken: "<<TOKEN<<" lexema: '"<<lexema<<"'\n";
        if(TOKEN == 0){
            cout<<"Fin de cadena\n";
            break;
        }
    }
    
}
*/
/*
int main(){
    string s = "[s-s]*|[t-t*";
    int token = 20;
    callLexic(s, token);
}
*/
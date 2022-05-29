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
        /*if(restoreStateA){
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
        }*/
        cout<<"LEXICO_________Estado actual: "<<estadoActualAFD<<endl;
        cout<<"LEXICO_________Caracter actual: "<<*caracterActual<<endl;
        cout<<"LEXICO_________Inilexema inicial: "<<*inilexema<<endl;
        //cout<<"Finlexema: "<<*finLexema<<endl;
        if(tokens.size()){ // >0
            pair<int, string> tope_tokens = tokens.top();
            tokens.pop();
            lexema = tope_tokens.second;
            return tope_tokens.first;
        }
        
        cout<<"LEXICO_________Buscamos transicion de : "<<estadoActualAFD<<" con "<<*caracterActual<<endl;
        cout<<"LEXICO_________Estado de aceptacion antes: "<<ac<<endl;
        
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken, ac);
        
        cout<<"LEXICO_________Destino: "<<destino<<endl;
        cout<<"LEXICO_________Estado de aceptacion despues: "<<ac<<endl;
        
        //destino = state.cp_destino;
        if(destino==-1){
            cout<<"LEXICO_________El destino es -1.\n";
            if(!ac){
                cout<<"LEXICO_________No hubo estado de aceptacion al buscar la transicion.\n";
                inilexema++;
                *a = inilexema;
                return -1; // no hay estado de aceptacion y retorna eso
            }else{
                cout<<"LEXICO_________Si hubo estado de aceptacion al buscar la transicion.\n";
                /*ADD*/

                //lexema = ""; // porque solo se agrego el ultimo, el que llego a estado final
                char *aux_i = inilexema;
                char *aux_f = finLexema;
                cout<<"LEXICO_________inilexema: "<<*aux_i<<endl;  

                while(aux_f!=aux_i){
                    lexema.push_back(*aux_i);
                    aux_i++;
                }
                lexema.push_back(*aux_i);
                
                cout<<"LEXICO_________Carcater actual cuando al encontrar la transicion me lleva a un estado de aceptacion: ";
                cout<<*caracterActual<<endl;
                /*ADD*/
                finLexema++;
                *a = finLexema;
                return TOKEN; // cuando ya hubo un estado de aceptacion retorna ese token
            }
        }else{
            //cout<<"si se encontro transicion\n";
            estadoActualAFD = destino;
            if(pToken!=0){ // es un estado final
                /*
               
                cout<<"carcater actual: "<<*caracterActual<<endl;
                */
                TOKEN = pToken;
                finLexema = caracterActual;
                //lexema.push_back(*caracterActual);
                //cout<<"lexema: ";
                //cout<<lexema<<endl;
            }
            caracterActual++;
            if(*caracterActual=='\0' && pToken!=0){ // solamente me importa lo que quedo en fin lexema e inilexema cuando hubo un estado de aceptacion 
                char *aux_i = inilexema;
                char *aux_f = finLexema;
                while(aux_f!=aux_i && *aux_i!='\0'){
                    lexema.push_back(*aux_i);
                    aux_i++;
                }
                lexema.push_back(*aux_i);
            }
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
        //cout<<"Finlexema: "<<*finLexema<<endl;
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
    f.open("./libraries/gramaticaGv2.txt");
    if (f.is_open()){
        //cout<<"se pudo abrir\n";
        while (!f.eof()){
            f >> origen >> rango >> destino >> token;
            registro.origen = origen;
            registro.destino = destino;
            registro.a = rango[1];
            registro.b = rango[rango.size()-2];
            registro.token = token;
            delta.push_back(registro);
        }
    }else{
        cout<<"LEXICO_________No se pudo abrir.\n";
    }
    f.close();
}

/*
int callLexic(string &s){
    vector<reg> delta;
    lecturaAFD(delta);
    cout<<"hicimos la lectura\n";
    char *a;
    a = &s[0];
    string lexema;
    //token =  analizadorLexico(delta, &a, lexema);
    
    while(1){
        int TOKEN = analizadorLexico(delta, &a, lexema);
        cout<<"\t\t\t\t\ttoken: "<<TOKEN<<" lexema: '"<<lexema<<"'\n";
        if(TOKEN == 0){
            cout<<"Fin de cadena\n";
            break;
        }
    }
    return 10; // no sé que tiene que regresar
}
int main(){
    string s = "E->.T.Ep;Ep->.\\|.T.Ep|eps;T->.C.Tp;Tp->.\\!.C.Tp|eps;C->.F.Cp;Cp->\\+.Cp|\\*.Cp|\\?.Cp|eps;F->\\(.E.\\)|\\[.simb.\\-.simb.\\]|simb;";
    callLexic(s);
}
*/

#include<bits/stdc++.h>
using namespace std;
typedef struct reg{
    int origen;
    char a;
    char b;
    int destino;
    int token;
}reg;
#define msj(v, s) cout<<v<<" "<<s<<endl;
int t;
void ctrlZ_analizadorLexico(int &TOKEN){
    t = TOKEN;
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
    int cont=0;
    while(*caracterActual!='\0'){
        cont++;
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken, ac);
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
            if(pToken!=0){
                TOKEN = pToken;
                finLexema = caracterActual;
                lexema.push_back(*caracterActual);
            }
            caracterActual++;
        }
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
    f.open("clases_lexicas_ER.txt");
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
int callLexic(string &s, int token){
    vector<reg> delta;
    lecturaAFD(delta);
    char *a;
    a = &s[0];
    string lexema;
    int token;
    return analizadorLexico(delta, &a, lexema);
    /*
    while(1){
        int TOKEN = analizadorLexico(delta, &a, lexema);
        cout<<"\t\t\t\t\ttoken: "<<TOKEN<<" lexema: '"<<lexema<<"'\n";
        if(TOKEN == 0){
            cout<<"Fin de cadena\n";
            break;
        }
    }
    */
}
/*
int main(){
    string s = "[s-s]*|[t-t*";
    int token = 20;
    callLexic(s, token);
}
*/
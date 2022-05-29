#include<bits/stdc++.h>
using namespace std;
typedef struct reg{
    int origen;
    char a;
    char b;
    int destino;
    int token;
}reg;

int t;
void ctrlZ_analizadorLexico(int &TOKEN){
    t = TOKEN;
}
int findTransition(vector<reg> d, int estadoActual, char a, int &ptoken){
    int destino;
    /*
    for(int i=0; i<d.delta.size(); i++){
        if(estadoActual == d.delta[i].v[0]&& a == d.delta[i].v[1]){
            destino = d.delta[i].v[2];
            for(int i=0; i<d.delta.size(); i++){
                if(destino == d.delta[i].v[0]){
                    ptoken = d.delta[i].v[3];
                    break;
                }
            }
            return destino;
        }
    }
    */
    for(int i=0; i<d.size(); i++){ // si a está en el rango 
        if(estadoActual == d[i].origen && a >= d[i].a && a <= d[i].b){
            destino = d[i].destino;
            for(int j=0; j<d.size(); j++){
                if(destino == d[j].destino){
                    ptoken = d[j].token;
                    break;
                }
            }
            return destino;
        }
    }
    ptoken = -1;
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
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken);
        if(destino==-1){
            if(!ac){
                inilexema++;
                *a = inilexema;
                return -1;
            }else{
                finLexema++;
                *a = finLexema;
                return TOKEN;
            }
        }else{
            estadoActualAFD = destino;
            if(pToken!=0){
                ac = true;
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
    string rango="";
    ifstream file("/.../txt/inputs/clases_lexicas_ER.txt");
    while (!file.eof()) {
        while(origen!=45); // "-"
        reg registro;
        cin >> origen >> rango >> destino >> token;
        registro.origen = origen;
        registro.destino = destino;
        bool flag = false; bool bb = false;
        for(char &c: rango){
            if(c == 91 || c == 45)//"[" "-" "]"
                continue;
            if(c == 92){//"\"
                flag = true;
                continue;
            }
            if(c == 93){//"-"
                bb = true;
                continue;
            }
            if(flag){// ascii number
                flag = false;
                registro.a = c;
            }
            if(bb)
                registro.b = c;
        }
        registro.token = token;
        delta.push_back(registro);
        cout << origen << rango << destino << token <<endl;
    }
    file.close();
    //return delta;
}
void callLexic(string s, int token){
    vector<reg> delta;
    lecturaAFD(delta);
    //string s = "DDM.L";
    char *a;
    a = &s[0];
    string lexema;
    analizadorLexico(delta, &a, lexema);
}

int main(){
    string s = "([s-s]*)|[t-t]*";
    int token = 20;
    callLexic(s, token);
    
    /*
    delta d;
    int edo_origen, destino, token;
    char tran;
    
    while(cin>>edo_origen>>tran>>destino>>token){
        cuarteta aux;
        aux.v.push_back(edo_origen);
        aux.v.push_back(tran);
        aux.v.push_back(destino);
        aux.v.push_back(token);
        d.delta.push_back(aux);
    }
    string s = "DDM.L";
    char *a;
    a = &s[0];
    string lexema;
    while(1){
        int TOKEN = analizadorLexico(d, s, &a, lexema);
        cout<<TOKEN<<" '"<<lexema<<"'\n";
        if(TOKEN == 0){
            cout<<"Fin de cadena\n";
            break;
        }
    }
    */
}

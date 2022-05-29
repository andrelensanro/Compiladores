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
            ptoken = d[i].token;
            for(int j=0; j<d.size(); j++){
                if(destino == d[j].destino){
                    ptoken = d[j].token;
                    break;
                }
            }
            msj("find_transition-----------> retornamos ", destino)
            return destino;
        }
    }
    ptoken = -1;
    msj("find_transition-----------> retornamos ", -1)
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
    /*
    
    [simb-simb]!(+ or * or ! or | or ?)?
    
    */
    while(*caracterActual!='\0'){
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken);
        msj("estado actual:", estadoActualAFD)
        msj("caracter actual:", *caracterActual)
        msj("destino", destino)
        /*
        unitarios ? * +
        en pares ! |
        */
        if(destino==-1){
            msj("no hay destino, por lo que tengo que ver si ya hubo un estado de acpetacion", "")
            if(!ac){
                msj("no hubo un estado de aceptacion", "")
                inilexema++;
                *a = inilexema;
                return -1; // no hay estado de aceptacion y retorna eso
            }else{
                msj("si hubo un estado de aceptacion", "")
                finLexema++;
                *a = finLexema;
                return TOKEN; // cuando ya hubo un estado de aceptacion retorna ese token
            }
        }else{
            estadoActualAFD = destino;
            if(pToken!=0){
                msj("formando el lexema y actualizando el token", "\t\t\t\tSe activo AC")
                //ac = true; // antes 
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
        cout<<"se pudo abrir"<<endl;
        while (!f.eof()){
            f >> origen >> rango >> destino >> token;
            cout << origen << " " << rango << " " << destino << " "  << token <<endl;
            registro.origen = origen;
            registro.destino = destino;
            // ignoro el primero y el ultimo y el del medio 
            registro.a = rango[1];
            registro.b = rango[rango.size()-2];
            registro.token = token;
            delta.push_back(registro);
        }
    }
    f.close();
    //cout<<"viendo que tiene delta"<<endl;
    //for(auto d: delta){
    //    cout<<d.origen<<" "<<d.a<<" "<<d.b<<" "<<d.destino<<" "<<d.token<<endl;
    //}
    
}
void callLexic(string &s, int token){
    vector<reg> delta;
    lecturaAFD(delta);
    //string s = "DDM.L";
    char *a;
    a = &s[0];
    string lexema;
    while(1){
        int TOKEN = analizadorLexico(delta, &a, lexema);
        cout<<"\t\t\t\t\ttoken: "<<TOKEN<<" lexema: '"<<lexema<<"'\n";
        if(TOKEN == 0){
            cout<<"Fin de cadena\n";
            break;
        }
    }
    //analizadorLexico(delta, &a, lexema);
}

int main(){
    string s = "[s-s]*|[t-t]*";
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

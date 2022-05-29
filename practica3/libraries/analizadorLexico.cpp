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
    for(int i=0; i<d.size(); i++){
        /*
        Busco el estado actual y que sus caracteres de transicion coincidan con los
        parametros de esta funcion. 
        */
        if(estadoActual == d[i].origen && a >= d[i].a && a <= d[i].b){
            destino = d[i].destino;
            msj("find_transition----------->  destino: ", destino)
            for(int j=0; j<d.size(); j++){
                /*buscamos si destino es final*/
                if(destino == d[j].origen){
                    if(d[j].token!=0){
                        msj("find_transition----------->  es un estado de aceptacion      token =", d[j].token)
                        ac = true; // como no es 0, es estado de aceptacion
                        ptoken = d[j].token;
                    }else{
                        msj("find_transition----------->  NO es un estado de aceptacion      token =", d[j].token)
                        ac = false;
                        ptoken = d[j].token; 
                    }
                    break;
                }
            }
            msj("1. find_transition----------->  retornamos como destino:", destino)
            return destino;
        }
    }
    /*
    lo pongo en 0, ya que la transicion estado-caracter no existe, por lo tanto ptoken no importa si lo 
    pongo en 0 cuando no haya transicion.
    //************************************** (-1)
    */
    ptoken = 0; 
    msj("2. find_transition-----------> no hay transicion por lo que destino:", -1)
    msj("y token: ", ptoken)
    return -1;
}
int analizadorLexico(vector<reg> d, char **a, string &lexema){
    lexema = "";
    /*
    nuestro estado inicial siempre será el 0
    está previsto en la formacion del afd final en la practica 2 expresiones_AFD.cpp
    */
    int estadoActualAFD = 0;
    bool ac = false;
    char * finLexema = nullptr;
    char * caracterActual = *a;
    char * inilexema = *a;
    int TOKEN = 0;
    int pToken;
    /*auxiliar hay que borrarlo*/
    int cont=0;
    while(*caracterActual!='\0'){
        cont++;
        msj("VUELTA #", cont)
        msj("pregunto por la transicion que hay con el estado actual y el caracter actual:","")
        msj("estado actual:", estadoActualAFD)
        msj("caracter actual", *caracterActual)
        int destino = findTransition(d, estadoActualAFD, *caracterActual, pToken, ac);
        msj("destino", destino)
        msj("hubo estado de aceptacion: ", ac)
        /*
        unitarios ? * +
        en pares ! |
        */
        if(destino==-1){
            msj("no hay destino, por lo que tengo que ver si ya hubo un estado de acpetacion", "")
            if(!ac){
                msj("no hubo un estado de aceptacion, por lo que tengo que buscar un nuevo lexema", "")
                inilexema++;
                *a = inilexema;
                msj("como no hay destino y tampoco hubo estado de aceptacion y aun no es fin de cadena", "")
                msj("retorno como token: ", "-1")
                return -1; // no hay estado de aceptacion y retorna eso
            }else{
                msj("si hubo un estado de aceptacion", "")
                finLexema++;
                *a = finLexema;
                return TOKEN; // cuando ya hubo un estado de aceptacion retorna ese token
            }
        }else{
            // ptoken viene de la funcion find_transition
            estadoActualAFD = destino;
            msj("si hubo estado de transicion", "")
            if(pToken!=0){
                msj("Es estado final, formando el lexema y actualizando el token", "\t\t\t\tSe activo AC")
                //ac = true; // antes 
                TOKEN = pToken;
                finLexema = caracterActual;
                lexema.push_back(*caracterActual);
            }else
                msj("no es estado final, pero si hubo transicion", "")
            caracterActual++;
        }
    }
    msj("ya es el fin de cadena", "")
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
        //cout<<"se pudo abrir"<<endl;
        while (!f.eof()){
            f >> origen >> rango >> destino >> token;
            //cout << origen << " " << rango << " " << destino << " "  << token <<endl;
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
    string s = "[s-s]*|[t-t*";
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

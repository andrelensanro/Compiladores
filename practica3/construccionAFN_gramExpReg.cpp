#include<bits/stdc++.h>
using namespace std;
#include "libraries/analizadorLexicov2.hpp"
//los parametros van a ser automatas
#include "libraries/operacionAutomata.hpp"
//Esto se tiene que generalizar
#define union 1000
#define concatenacion 1010
#define transicion 1020
#define cerradura_K 1030
#define operador_opcional 1040
#define parentIzq 1050
#define parentDer 1060
#define corchIzq 1070
#define corchDer 1080
#define guion 1090
#define simb 1100

bool C(afn *f,  char **a, string &lexema, vector<reg> delta, int t_solve);
//Gramática regla 6 :  Cp -> + Cp | * Cp | ? Cp | epsilon
bool Cp(afn *f,  char **a, string &lexema, vector<reg> delta, int t_solve){ // cerraduras anidadas
    //msj("esto llega a Cp")
    //printMy_Afn(*f);
    int tok;
    /*solo es para recuperar el lexema*/
    pair<int, string> lex;
    bool there_isLex = false;
    if(tokens.size()){
        lex = tokens.top();
        mv("lexema: ", lex.second)
        there_isLex = true;
    }
    /*-------------------------------*/
    tok = analizadorLexico(delta, a, lexema);
    mv("token: ", tok)
    if(!there_isLex)
        mv("lexema: ", lexema)
    switch (tok){
        /*operan sobre un solo automata*/
        case transicion:{
            msj("operacion de transicion")
            afn solve;
            ini_afn(&solve);
            lockTransitive(f, &solve, "transition", t_solve);
            //printMy_Afn(solve);
            vaciarAFN(&solve, f);
            if(Cp(f, a, lexema, delta, t_solve))
                return true;
            return false;
        }
        case cerradura_K:{
            afn solve;
            msj("operacion de kleene")
            ini_afn(&solve);
            lockKleene(f, &solve, "kleene", t_solve);
            //printMy_Afn(solve);
            vaciarAFN(&solve, f);
            if(Cp(f, a, lexema, delta, t_solve))
                return true; 
            return false;
        }
        case operador_opcional:{
            msj("operacion opcional")
            afn solve;
            ini_afn(&solve);
            optional(f, &solve, "optional", t_solve);
            //printMy_Afn(solve);
            vaciarAFN(&solve, f);
            if(Cp(f, a, lexema, delta, t_solve))
                return true;
            return false;
        }
        default:
            msj("regresamos token")
            ctrlZ_analizadorLexico(tok, lexema);
            mv("ver que hay en el tope de pila: ", tokens.top().first)
            return true;
            
    }
    
    return true;  
}

//Gramática regla 4 :  Tp -> & C Tp
bool Tp(afn *f,  char **a, string &lexema, vector<reg> delta, int t_solve){
    //msj("esto llega a Tp")
    //printMy_Afn(*f);
    int tok;
    /*solo es para recuperar el lexema*/
    pair<int, string> lex;
    bool there_isLex = false;
    if(tokens.size()){
        lex = tokens.top();
        mv("lexema: ", lex.second)
        there_isLex = true;
    }
    /*-------------------------------*/
    tok = analizadorLexico(delta, a, lexema);
    mv("token: ", tok)
    if(!there_isLex)
        mv("lexema: ", lexema)
    if(tok == concatenacion){
        afn g;
        ini_afn(&g);
        if(C(&g, a, lexema, delta, t_solve)){
            /* lo mismo
            AQUI, va acción semántica correspondientes al OR, es decir, 
            se hara la unicon de los afns del parametro de Ep con lo que nos arroge la llamada de T*/
            msj("operacion concatenar")
            afn solve;
            ini_afn(&solve);
            concatenate(f, &g, &solve, "concatenacion", t_solve);
            //printMy_Afn(solve);
            vaciarAFN(&solve, f);
            if(Tp(f, a, lexema, delta, t_solve))
                return true;
        }
        return false; 
    }   
    ctrlZ_analizadorLexico(tok, lexema);
    return true;    
}

//Gramática regla 3 :  T -> C Tp
bool T(afn *f, char **a, string &lexema, vector<reg> delta, int t_solve){
    //msj("antes de entrar a C")
    //printMy_Afn(*f);
    if(C(f, a, lexema, delta, t_solve)){// el afn que sale de C entra a la funcion Tp
        //msj("el afn saliendo de C")
        //printMy_Afn(*f);
        if(Tp(f, a, lexema, delta, t_solve)){
            //msj("el afn saliendo de Tp")
            //printMy_Afn(*f);
            return true;
        }
    }
    return false;
}
//Gramática regla 2 : Ep  -> or T Ep
bool Ep(afn *f,  char **a, string &lexema, vector<reg> delta, int t_solve){
    int tok; 
    //msj("esto llega a Ep")
    //printMy_Afn(*f);
    /*solo es para recuperar el lexema*/
    pair<int, string> lex;
    bool there_isLex = false;
    if(tokens.size()){
        lex = tokens.top();
        mv("lexema: ", lex.second)
        there_isLex = true;
    }
    /*-------------------------------*/
    tok = analizadorLexico(delta, a, lexema);
    mv("token: ", tok)
    if(!there_isLex)
        mv("lexema: ", lexema)
    if(tok == union){
        afn g;
        ini_afn(&g);
        if(T(&g, a, lexema, delta, t_solve)){
            /*AQUI, va acción semántica correspondientes al OR, es decir, 
            se hara la unicon de los afns del parametro de Ep con lo que nos arroge la llamada de T*/
            msj("operacion union")
            afn solve;
            ini_afn(&solve);
            join(f, &g, &solve,  "union", t_solve);
            //printMy_Afn(solve);
            vaciarAFN(&solve, f);
            if(Ep(f, a, lexema, delta, t_solve))
                return true;
        }
        return false; 
    }   
    ctrlZ_analizadorLexico(tok, lexema);
    return true;    
}
//Gramática regla 1 : E  ->  T Ep
bool E(afn *f, char **a, string &lexema, vector<reg> delta, int t_solve){
    //msj("esto llega a E")
    //printMy_Afn(*f); // esta es la funcion principal
    if(T(f, a, lexema, delta, t_solve)) // me devolvera el automata que entrara a Ep
        if(Ep(f, a, lexema, delta, t_solve))
            return true;
    return false;
}
//Gramática regla 7 : F -> ( E ) | [SIMB-SIMB] | SIMB

bool F(afn *f, char **a, string &lexema, vector<reg> delta, int t_solve){
    int tok;
    //msj("esto llega a F")
    //printMy_Afn(*f);
    /*solo es para recuperar el lexema*/
    pair<int, string> lex;
    bool there_isLex = false;
    if(tokens.size()){
        lex = tokens.top();
        mv("lexema: ", lex.second)
        there_isLex = true;
    }
    /*-------------------------------*/
    string lexemaChar1="", lexemaChar2="";
    tok = analizadorLexico(delta, a, lexema);
    mv("token: ", tok)
    if(!there_isLex)
        mv("lexema: ", lexema)
    switch(tok){
        case parentIzq:
            if(E(f, a, lexema, delta, t_solve)){
                /*solo es para recuperar el lexema*/
                pair<int, string> lex;
                bool there_isLex = false;
                if(tokens.size()){
                    lex = tokens.top();
                    mv("lexema: ", lex.second)
                    there_isLex = true;
                }
                /*-------------------------------*/
                tok = analizadorLexico(delta, a, lexema);
                mv("token: ", tok)
                if(!there_isLex)
                    mv("lexema: ", lexema)
                if(tok == parentDer)
                    return true;
            }
            return false;
        case corchIzq:{
            /*solo es para recuperar el lexema*/
            pair<int, string> lex;
            bool there_isLex = false;
            if(tokens.size()){
                lex = tokens.top();
                mv("lexema: ", lex.second)
                there_isLex = true;
            }
            /*-------------------------------*/
            tok = analizadorLexico(delta, a, lexemaChar1);
            mv("token: ", tok)
            if(!there_isLex)
                mv("lexema: ", lexemaChar1)
            if(tok == simb){// este será el simbolo inicial del automata
                /*solo es para recuperar el lexema*/
                pair<int, string> lex;
                bool there_isLex = false;
                if(tokens.size()){
                    lex = tokens.top();
                    mv("lexema: ", lex.second)
                    there_isLex = true;
                }
                /*-------------------------------*/
                tok = analizadorLexico(delta, a, lexema);
                mv("token: ", tok)
                if(!there_isLex)
                    mv("lexema: ", lexema)
                if(tok ==  guion){
                    /*solo es para recuperar el lexema*/
                    pair<int, string> lex;
                    bool there_isLex = false;
                    if(tokens.size()){
                        lex = tokens.top();
                        mv("lexema: ", lex.second)
                        there_isLex = true;
                    }
                    /*-------------------------------*/
                    tok = analizadorLexico(delta, a, lexemaChar2);
                    mv("token: ", tok)
                    if(!there_isLex)
                        mv("lexema: ", lexemaChar2)
                    if(tok == simb){
                        /*solo es para recuperar el lexema*/
                        pair<int, string> lex;
                        bool there_isLex = false;
                        if(tokens.size()){
                            lex = tokens.top();
                            mv("lexema: ", lex.second)
                            there_isLex = true;
                        }
                        /*-------------------------------*/
                        tok = analizadorLexico(delta, a, lexema);
                        mv("token: ", tok)
                        if(!there_isLex)
                            mv("lexema: ", lexema)
                        if(tok == corchDer){
                            /*AQUI va la accion semantica*/
                            //afn creacion;
                            if(lexemaChar1 <= lexemaChar2){
                            // es un ejemplo claro de como una expresion sintacticamente es correcto 
                            // pero semanticamente no es correcta
                                ini_afn(f);
                                createAFN(lexemaChar1[0], lexemaChar2[0], "afn_creacion" ,f, t_solve);
                                //msj("creando afn en F")
                                //mv(lexemaChar1[0], lexemaChar2[0])
                                //printMy_Afn(*f);
                                return true;
                            }
                            return false;
                        }
                    }
                }

            }
            return false;
        }
        case simb:
            /*AQUI va la accion semantica*/
            //afn creacion;
            ini_afn(f);
            createAFN(lexemaChar1[0], lexemaChar2[0], "afn_creacion" ,f, t_solve);
            //msj("creando afn en F con")
            //mv(lexemaChar1[0], lexemaChar2[0])
            //printMy_Afn(*f);
            return true;
    }
    return false;
}
//Gramática regla 5 :  C -> F Cp
bool C(afn *f,  char **a, string &lexema, vector<reg> delta, int t_solve){
    if(F(f, a, lexema, delta, t_solve)){
        if(Cp(f, a, lexema, delta, t_solve))
            return true;
    }
    return false;
}
int main(){
    afn solve; /*solucion de lo que se construya*/
    ini_afn(&solve);
    vector<reg> delta;
    lecturaAFD(delta);
    string lexema;
    string s = "[s-s]|[t-t]+|[p-p]*";
    char *a;
    a = &s[0];
    int token_solve = 10; 
    if(E(&solve, &a, lexema, delta, token_solve))
        printMy_Afn(solve);
    else
        msj("no se acepta la expresion regular de entrada")
    return 0;
}



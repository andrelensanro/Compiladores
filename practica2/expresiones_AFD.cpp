/*hay que sobrecargar el metodo push_back en las transiciones de cada nodo*/
/*falla la concatenacion*/
#include<bits/stdc++.h>
using namespace std;
#include "libraries/ep_postfijas.h"

#define endl "\n"
#define iden cout<<"\t\t";
#define mv(s, v) cout<<s<<" "<<v<<endl;
#define msj(t) cout<<t<<endl;
#define msj_(s) cout<<s<<" ";
#define range(a,b) cout<<"["<<a<<"-"<<b<<"] ";
#define tripleta(s, u, v) cout<<s<<" "<<u<<" "<<v<<endl;

typedef struct sim{
    char a;
    char b;
}sim;
typedef struct node{
    int val;
    bool initial;
    bool end;
    int token;
    vector<pair<sim, int>> transiLink;
}node;
typedef struct afn{
    string name;
    node A_initial;
    // delta va de la siguiente forma: nodo origen , sim , nodo destino
    vector<pair<int, pair<sim, int>>> delta;
    vector<sim> alphabet;
    vector<node> ends;  
    vector<node> states; 
    int number_states;
}afn;
typedef struct afd{
    string name;
    node A_initial;
    // delta va de la siguiente forma: nodo origen , sim , nodo destino
    vector<pair<int, pair<sim, int>>> delta;
    vector<sim> alphabet;
    vector<node> ends;  
    vector<node> states; 
    int number_states; 
}afd;
bool existsPair(sim z, int destino, vector<pair<sim, int>> conj){
    bool solve = false;// no está
    if(!conj.size())
        return solve;
    for(auto c: conj)
        if(c.first.a == z.a && c.first.b == z.b && c.second == destino){
            solve = true;
        }
    return solve;
}
bool existsChar(sim z, vector<sim> s_afd){ // retorna falso cuando no existe
    bool solve = false; // esta es la respuesta ideal
    if(!s_afd.size())
        return false;
    for(auto a: s_afd){// corriendo los simbolos
        if(z.a == a.a && z.b == a.b){
            return true;
        }
    }
    return solve;
}
void seeNode(node *nodo){
    mv("\t\tnodo:", nodo->val)
    mv("¿Es inicial?", nodo->initial)
    mv("¿Es final?", nodo->end)
    if(nodo->end)
        cout<<"TOKEN: "<<nodo->token<<endl;
    msj("Tiene las siguientes transciones:")
    for(int i=0; i<nodo->transiLink.size(); i++){
        range(nodo->transiLink[i].first.a, nodo->transiLink[i].first.b)
        msj(nodo->transiLink[i].second)
    }
}
void vaciarDatosNodo(node * destino, node origen){
    destino->val = origen.val;
    destino->initial = origen.initial;
    destino->end = origen.end;
    destino->token = origen.token;
    for(int i=0; i<origen.transiLink.size(); i++){
        sim z; z.a = origen.transiLink[i].first.a;
               z.b = origen.transiLink[i].first.b;
        destino->transiLink.push_back(make_pair(z, origen.transiLink[i].second));

    }
}
void updateNode(vector<node> &states, node *nodo){
    for(int i=0; i<states.size(); i++){
        if(states[i].val==nodo->val){
            vaciarDatosNodo(&states[i], *nodo);
            //seeNode(&states[i]);
        }
    }
}
void printMy_Afn(afn my_afn){
    mv("\t\t::::AFN::::", my_afn.name)
    if(my_afn.A_initial.initial)
        mv("1. Nodo inicial:", my_afn.A_initial.val)
    else
        mv("1. Nodo inicial:", -1)
    msj("2. Delta:")
    for(int i=0; i<my_afn.delta.size(); i++){
        msj_(my_afn.delta[i].first) // nodo origen 
        range(my_afn.delta[i].second.first.a, my_afn.delta[i].second.first.b) // conjunto de simbolos de transicion
        msj_(my_afn.delta[i].second.second) //nodo destino
        cout<<endl;
    }
    msj("3. Alphabet: {")
    for(auto a : my_afn.alphabet){
        range(a.a, a.b)
        cout<<endl;
    }
    msj("}")
    msj("4. Finals States: {")
    for(int i=0; i<my_afn.ends.size(); i++){
        seeNode(&my_afn.ends[i]);
    }
    msj("}")
    msj("5. Afn's States: {")
    for(int i=0; i<my_afn.states.size(); i++){
        seeNode(&my_afn.states[i]);
    }
    msj("}")
}
void printMy_Afd(afd my_afd){
    mv("\t\t::::AFD::::", my_afd.name)
    if(my_afd.A_initial.initial)
        mv("1. Nodo inicial:", my_afd.A_initial.val)
    else
        mv("1. Nodo inicial:", -1)
    msj("2. Delta:")
    for(auto a: my_afd.delta){
        msj_(a.first) // nodo origen 
        range(a.second.first.a, a.second.first.b) // conjunto de simbolos de transicion
        msj_(a.second.second) //nodo destino
        cout<<endl; 
    }
    msj("3. Alphabet: {")
    for(auto a : my_afd.alphabet){
        range(a.a, a.b)
        cout<<endl;
    }
    msj("}")
    msj("4. Finals States: {")
    for(int i=0; i<my_afd.ends.size(); i++){
        seeNode(&my_afd.ends[i]);
    }
    msj("}")
    msj("5. Afn's States: {")
    for(int i=0; i<my_afd.states.size(); i++){
        seeNode(&my_afd.states[i]);
    }
    msj("}")
}
void ini_n(node *nodo){// inicializa el valor del nodo, inicializa las banderas c/las que identidicamos si está bien. 
    nodo->val=-1;        
    nodo->initial = false;
    nodo->end = false;
    nodo->transiLink = {};
    nodo->token = 0;
}
void ini_afn(afn *afn_0){//el numero de estados lo pone a 0
    string name = "-";
    afn_0->A_initial.val = 0;
    afn_0->A_initial.transiLink = {};
    afn_0->A_initial.end = false;
    afn_0->A_initial.initial = true;
    afn_0->A_initial.token = 0;// no es estado final
    afn_0->delta = {};
    afn_0->alphabet = {};
    afn_0->ends = {};
    afn_0->states = {};
    afn_0->number_states=0;
}
void ini_afd(afd *afd_0){
    string name = "-";
    afd_0->A_initial.val = -1;
    afd_0->A_initial.transiLink = {};
    afd_0->A_initial.end = false;
    afd_0->A_initial.initial = true;
    afd_0->A_initial.token = 0;// no es estado final
    afd_0->delta = {};
    afd_0->alphabet = {};
    afd_0->ends = {};
    afd_0->states = {};
    afd_0->number_states=0;
}
void hacerDeltaAfn(afn *nuevo, node *nodo){
    /*por cada transicion que tenga nodo se la añadire a nuevo*/
    for(int i=0; i<nodo->transiLink.size(); i++){
        sim z; z.a = nodo->transiLink[i].first.a;
               z.b = nodo->transiLink[i].first.b;
        nuevo->delta.push_back(make_pair(nodo->val, make_pair(z, nodo->transiLink[i].second)));
    }
}
bool existsTransition(vector<pair<int, pair<sim, int>>> delta, int origen, sim z ,int destino){
    if(!delta.size())
        return false;
    for(auto d: delta)
        if(d.first == origen && d.second.first.a == z.a &&  d.second.second == destino)
            return true;
    return false;
}
void hacerDeltaAfd(afd *nuevo, node *nodo){
    /*por cada transicion que tenga nodo se la añadire a nuevo*/
    for(int i=0; i<nodo->transiLink.size(); i++){
        sim z; z.a = nodo->transiLink[i].first.a;
               z.b = nodo->transiLink[i].first.b;
        if(!existsTransition(nuevo->delta, nodo->val, z, nodo->transiLink[i].second))
            nuevo->delta.push_back(make_pair(nodo->val, make_pair(z, nodo->transiLink[i].second)));
    }
}
void renameNodes(afn *uno, afn *dos, int flag){
    //mi llave es el valor viejo
    int nodos_uno = uno->states.size()+flag; //8
    map<int,int> newsValores;   
    /*no cambio translink las transiciones de cada nodo*/
    for(int i=0; i<dos->states.size(); i++){
        //cout<<"valor antiguo: "<<dos->states[i].val<<" ";
        newsValores[dos->states[i].val] = nodos_uno+dos->states[i].val;//ya los guarde 
        dos->states[i].val = newsValores[dos->states[i].val];//cambio su conjunto states
        //cout<<"valor actual: "<<dos->states[i].val<<endl;
    }
    //printMy_Afn(*dos);
    /*msj("viendo que tiene el map")
    map<int, int>::iterator m;
    for(m = newsValores.begin(); m!=newsValores.end(); m++){
        cout<<m->first <<" "<<m->second<<endl;
    }*/
    /*rename initials*/
    //dos->A_initial.val = newsValores[dos->A_initial.val];
    
    /*hasta aquí ya renombre todo*/
    
    for(int i=0; i<dos->states.size(); i++){//por cada nodo 
        for(int j=0; j<dos->states[i].transiLink.size(); j++){//por cada transicion de cada nodo
            dos->states[i].transiLink[j].second = newsValores[dos->states[i].transiLink[j].second];//estos son los destinos
            //cout<<dos->states[i].val<<" y tiene tantas transiciones "<<dos->states[i].transiLink.size();
        }
        /*por cada transicion de cada estado, lo cambio*/
    }
    /*es aqui donde cambia el numero de las transiciones, no sé por qué*/
    dos->A_initial.val = newsValores[dos->A_initial.val];//cambio su inicial
    //cout<<"quien es inicial: "<<dos->A_initial.val<<endl;// es 2
    //cout<<"cuantas transiciones tiene initial: "<<dos->A_initial.transiLink.size();
    for(int i=0; i<dos->A_initial.transiLink.size(); i++){
        dos->A_initial.transiLink[i].second = newsValores[dos->A_initial.transiLink[i].second];
    }
    for(int i=0; i<dos->ends.size(); i++){
        dos->ends[i].val = newsValores[dos->ends[i].val];//cambio su conjunto de finales
        for(int j=0; j<dos->ends[i].transiLink.size(); j++)
            dos->ends[i].transiLink[j].second = newsValores[dos->ends[i].transiLink[j].second];
    }
    for(int i=0; i<dos->delta.size(); i++){//cambio los valores de delta
        dos->delta[i].first = newsValores[dos->delta[i].first];
        dos->delta[i].second.second = newsValores[dos->delta[i].second.second];
    }
}
void deselectEnd(afn *uno){
    for(int i=0; i<uno->states.size(); i++)
        if(uno->states[i].end)
            uno->states[i].end = false;
    uno->ends = {};
}
void deselectInitial(afn *uno){
    for(int i=0; i<uno->states.size(); i++)
        if(uno->states[i].initial)
            uno->states[i].initial = false;
    uno->A_initial.initial = false;
}
void join(afn *uno, afn *dos, afn *tres, string str, int token){// uso rename Nodos
    /*PROBLEMA: PIERDO AS TRANSICIONES DE VIEJO FINAL NODO 1 Y VIEJO FINAL 2*/
    uno->A_initial.val = uno->A_initial.val + 1;
    for(auto &nodosInicial: uno->A_initial.transiLink)
        nodosInicial.second = nodosInicial.second + 1;

    for(auto &deltaUno : uno->delta){
        deltaUno.first += 1;
        deltaUno.second.second += 1;
    }
    
    for(auto &finalesUno: uno->ends){
        finalesUno.val+=1;
        for(auto trans_cada_final: finalesUno.transiLink){
            trans_cada_final.second +=1;
        }
    }
    for(auto &statesUno: uno->states){
        statesUno.val+=1;
        for(auto &trans_cada_state: statesUno.transiLink){
            trans_cada_state.second +=1;
        }
    }
    /*dos, numerar respecto a uno*/
    node new_initial, new_end; //DEBEN DE ESTAR COMO5 NODO INITIAL Y DENTRO DE STATES
    char epsilon = 51;
    ini_n(&new_initial);
    ini_n(&new_end);
    ini_afn(tres);
    //marcamos a new_initial como inicial del afn, de igual forma que el new_end
    new_initial.initial=true;
    new_end.end=true;
    new_end.token=token;
    //int t_nodes = uno->states.size() + dos->states.size();
    //renombrar nodos 
    renameNodes(uno, dos, 1);//respecto a los nodos que tenga uno, seran los .val de los nodos que tenga dos
    msj("uno despues de renombrarse")
    printMy_Afn(*uno);
    msj("dos despues de renombrarse")
    printMy_Afn(*dos);
    int t_nodes = uno->states.size() + dos->states.size();
    new_initial.val = 0;
    new_end.val = t_nodes + 1;
    //vamos a agregar a new_Initial dos transiciones con epsilon '3'
    sim z; z.a = epsilon;
           z.b = epsilon;
    //if(!existsPair(z, uno->A_initial.val, new_initial.transiLink))
        new_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    //if(!existsPair(z, dos->A_initial.val, new_initial.transiLink))
    new_initial.transiLink.push_back(make_pair(z, dos->A_initial.val));
    //añadimos las transiciones de viejos finales a new_end
    for(int i=0; i<uno->ends.size(); i++){
        //if(!existsPair(z, new_end.val, uno->ends[i].transiLink))
            uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
        //seeNode(&uno->ends[i]);
        updateNode(uno->states, &uno->ends[i]);
    }
    for(int i=0; i<dos->ends.size(); i++){
        //if(!existsPair(z, new_end.val, dos->ends[i].transiLink))
            dos->ends[i].transiLink.push_back(make_pair(z, new_end.val));
        //seeNode(&dos->ends[i]);
        updateNode(dos->states, &dos->ends[i]);
    }
    //añadimos todo a tres
    //seeNode(&uno->ends[0]);
    //seeNode(&uno->ends[0]);
    /*actualizar ends de states de afn*/
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, new_initial);
    for(auto a: uno->alphabet) tres->alphabet.push_back(a);
    for(auto a: dos->alphabet) tres->alphabet.push_back(a);
    //agregamos new_initial
    tres->states.push_back(new_initial);
    //agregamos new_end
    tres->ends.push_back(new_end);
    tres->states.push_back(new_end);
    //desmarcar finales e iniciales
    deselectInitial(uno);
    deselectEnd(uno);
    //printMy_Afn(*uno);
    deselectInitial(dos);
    deselectEnd(dos);
    //printMy_Afn(*dos);
    //agregamos los estados de uno
    for(int i=0; i<uno->states.size(); i++)
        tres->states.push_back(uno->states[i]);
    //agregamos los estados de dos
    for(int i=0; i<dos->states.size(); i++)
        tres->states.push_back(dos->states[i]);
    //agregar las transiciones 
    for(int i=0; i<uno->states.size(); i++)
        hacerDeltaAfn(tres, &uno->states[i]);
    for(int i=0; i<dos->states.size(); i++){
        hacerDeltaAfn(tres, &dos->states[i]);
    }
    //agregar las transiciones de new_Initial y new_End
    hacerDeltaAfn(tres, &new_initial);
    hacerDeltaAfn(tres, &new_end);  
    msj("hemos terminado de unir");
    printMy_Afn(*tres);  
}
void concatenate(afn *uno, afn *dos, afn *tres, string str, int token){// uso rename Nodos
    /*0. renombrar nodos para no tener que cambiar las transiciones que se añaden a uno*/
    renameNodes(uno, dos, -1);
    //cout<<"uno al inicio de concatenar\n";
    //printMy_Afn(*uno);
    //cout<<"dos al inicio de concatenar\n";
    //printMy_Afn(*dos);
    //->>0-a-> 1 -b->((3))
    /*1. le añado la transicion a final.uno con initial.dos*/
    //cout<<"transiciones de dos: "<<dos->A_initial.transiLink.size()<<endl;
    for(int i=0; i<dos->A_initial.transiLink.size(); i++){
        //cout<<"Estas transiciones estan en automata dos:\n";
        //cout<<"simbolo uno: "<<dos->A_initial.transiLink[i].first.a<<endl;
        //cout<<"simbolo dos: "<<dos->A_initial.transiLink[i].first.b<<endl;
        //cout<<"destino: "<<dos->A_initial.transiLink[i].second<<endl;
        uno->ends[0].transiLink.push_back(dos->A_initial.transiLink[i]);
        sim z; z.a = dos->A_initial.transiLink[i].first.a;
               z.b = dos->A_initial.transiLink[i].first.b;
        uno->delta.push_back(make_pair(uno->ends[0].val, make_pair(z, dos->A_initial.transiLink[i].second)));
    }
    for(int i=0; i<uno->states.size(); i++)
        if(uno->states[i].val == uno->ends[0].val)
            for(int j =0; j<uno->ends[0].transiLink.size(); j++){
                sim z; z.a = uno->ends[0].transiLink[j].first.a;
                       z.b = uno->ends[0].transiLink[j].first.b;
                if(!existsPair(z, uno->ends[0].transiLink[j].second, uno->states[i].transiLink))
                    uno->states[i].transiLink.push_back(make_pair(z, uno->ends[0].transiLink[j].second));
            }
    /*PROBLEMA, LAS TRANSICIONES DEL NODO 1 SALEN MAL*/
    deselectEnd(uno);
    /*update del nodo final que se encuentra en states*/
    //printMy_Afn(*uno);//nodo uno en states no existe
    /*comenzar a llenar tres*/
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, uno->A_initial);
    for(auto a: uno->alphabet) tres->alphabet.push_back(a);
    for(auto b: dos->alphabet) tres->alphabet.push_back(b);
    for(int i=0; i<uno->states.size(); i++){
        tres->states.push_back(uno->states[i]);
        hacerDeltaAfn(tres, &uno->states[i]);
    }
    for(int i=0; i<dos->states.size(); i++)
        /*hay que vaciar a todos excepto a initial*/
        if(!dos->states[i].initial){
            tres->states.push_back(dos->states[i]);
            hacerDeltaAfn(tres, &dos->states[i]);
        }
    for(int i=0; i<dos->ends.size(); i++)
        tres->ends.push_back(dos->ends[i]);
    tres->number_states = uno->states.size() + dos->states.size() - 1;
    cout<<"al final de la operacion concatenar:\n";
    printMy_Afn(*tres);
}
void createAFN(char a, char b, string nomb, afn *nuevo, int token){
    node n1, n2;
    ini_afn(nuevo);
    ini_n(&n1); ini_n(&n2);
    nuevo->name = nomb;
    n1.val = 0;
    n2.val = 1;
    n1.initial = true;
    n2.end = true;
    n2.token=token;
    sim z; z.a = a;
           z.b = b;
    //if(!existsPair(z, n2.val, n1.transiLink))
    
    n1.transiLink.push_back(make_pair(z, n2.val));//{'a', 1} en el nodo 1 se guarda que con 'a' viaja al nodo 2
    vaciarDatosNodo(&nuevo->A_initial, n1);
    //for(char c=a; c<=b; c++)
    nuevo->alphabet.push_back(z);
    
    nuevo->states.push_back(n1);
    nuevo->states.push_back(n2);
    hacerDeltaAfn(nuevo, &n1);
    hacerDeltaAfn(nuevo, &n2);
    nuevo->ends.push_back(n2);
    nuevo->number_states = 2;
    cout<<"hemos creado:\n";
    printMy_Afn(*nuevo);
}
void lockTransitive(afn *uno, afn *dos,string name, int token){
    //---------------------------------------------------------------------
    uno->A_initial.val = uno->A_initial.val + 1;
    for(auto &nodosInicial: uno->A_initial.transiLink)
        nodosInicial.second = nodosInicial.second + 1;

    for(auto &deltaUno : uno->delta){
        deltaUno.first += 1;
        deltaUno.second.second += 1;
    }
    
    for(auto &finalesUno: uno->ends){
        finalesUno.val+=1;
        for(auto trans_cada_final: finalesUno.transiLink){
            trans_cada_final.second +=1;
        }
    }
    for(auto &statesUno: uno->states){
        statesUno.val+=1;
        for(auto &trans_cada_state: statesUno.transiLink){
            trans_cada_state.second +=1;
        }
    }
    //----------------------------------------------------------------------
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_afn(dos);
    dos->A_initial.val = 0;
    new_end.val = uno->states.size() + 1;
    
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token = token;
    uno->A_initial.initial=false;
    //me falta desmarcar los finales de uno 
    //ligar el nuevo inicial al viejo inicial 
    sim z; z.a = epsilon;
           z.b = epsilon;
    //if(!existsPair(z, uno->A_initial.val, dos->A_initial.transiLink))
        dos->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    //ligar el viejo final al nuevo final 
    for(int i=0; i<uno->ends.size(); i++)
        //if(!existsPair(z, new_end.val, uno->ends[i].transiLink))
            uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
    //hacer la transicion de viejo final a viejo nuevo 
    //if(!existsPair(z, uno->A_initial.val, uno->ends[0].transiLink))
        uno->ends[0].transiLink.push_back(make_pair(z, uno->A_initial.val));
    /*agrego todo lo que falta a dos*/
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet)
        dos->alphabet.push_back(a);
    deselectEnd(uno);
    deselectInitial(uno);
    for(int i=0; i<uno->states.size(); i++){
        dos->states.push_back(uno->states[i]);
        hacerDeltaAfn(dos, &uno->states[i]);
    }
    dos->states.push_back(dos->A_initial);
    hacerDeltaAfn(dos, &dos->A_initial);
    dos->states.push_back(new_end);
    hacerDeltaAfn(dos, &new_end);
    dos->ends.push_back(new_end);
    cout<<"despues de terminar de aplicar cerradura transitiva:\n";
    printMy_Afn(*dos);
}
void lockKleene(afn *uno, afn *dos,string name, int token){
    //---------------------------------------------------------------------
    uno->A_initial.val = uno->A_initial.val + 1;
    for(auto &nodosInicial: uno->A_initial.transiLink)
        nodosInicial.second = nodosInicial.second + 1;

    for(auto &deltaUno : uno->delta){
        deltaUno.first += 1;
        deltaUno.second.second += 1;
    }
    
    for(auto &finalesUno: uno->ends){
        finalesUno.val+=1;
        for(auto trans_cada_final: finalesUno.transiLink){
            trans_cada_final.second +=1;
        }
    }
    for(auto &statesUno: uno->states){
        statesUno.val+=1;
        for(auto &trans_cada_state: statesUno.transiLink){
            trans_cada_state.second +=1;
        }
    }
    //----------------------------------------------------------------------
    msj("uno despues de ser renumerado")
    printMy_Afn(*uno);
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_afn(dos);

    //dos->A_initial.val = uno->states.size();
    dos->A_initial.val = 0;
    new_end.val = uno->states.size() + 1;
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token=token;
    uno->A_initial.initial=false;
    //me falta desmarcar los finales de uno 
    //ligar el nuevo inicial al viejo inicial 
    sim z; 
    z.a = epsilon;
    z.b = epsilon;
    dos->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    dos->A_initial.transiLink.push_back(make_pair(z, new_end.val));
    //ligar el viejo final al nuevo final 
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
    //hacer la transicion de viejo final a viejo nuevo 
    uno->ends[0].transiLink.push_back(make_pair(z, uno->A_initial.val));
    /*agrego todo lo que falta a dos*/
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet)
        dos->alphabet.push_back(a);
    deselectEnd(uno);
    deselectInitial(uno);
    for(int i=0; i<uno->states.size(); i++){
        dos->states.push_back(uno->states[i]);
        hacerDeltaAfn(dos, &uno->states[i]);
    }
    dos->states.push_back(dos->A_initial);
    hacerDeltaAfn(dos, &dos->A_initial);
    dos->states.push_back(new_end);
    hacerDeltaAfn(dos, &new_end);
    dos->ends.push_back(new_end);
    msj("hemos terminado aplicar cerradura de kleene");
    printMy_Afn(*dos); 
}
void vaciarAutomataNoDeterminista(afn *origen, afn *destino){
/*
            lista de lo que tengo que pasar
    uno->A_initial; // es un nodo
    uno->alphabet; // es un vector<sim>
    uno->delta; // es un vector<int, sim, int>
    uno->ends; // es un vector<nodos>
    uno->states; // es un vector<nodos> contiene a los finales y al inicial
    uno->name; // string
    uno->number_states; // es un int

*/
    ini_n(&destino->A_initial);
    ini_afn(destino);
    vaciarDatosNodo(&destino->A_initial, origen->A_initial);
    for(int i=0; i<origen->alphabet.size(); i++)
        destino->alphabet.push_back(origen->alphabet[i]);
    for(auto d: origen->delta)
        destino->delta.push_back(d);
    for(auto e: origen->ends){
        destino->ends.push_back(e);
        hacerDeltaAfn(destino, &e);
    }
    for(auto s: origen->states){
        destino->states.push_back(s);// lo garego al conjunto de states
        hacerDeltaAfn(destino, &s);// agrego sus transiciones a delta
    }
    /*no modifico el nombre y el numero de estados*/
}
void optional(afn *uno, afn *solve, string name, int token){ // modifique los valores de los nodos, pero aun así no me da
    /*pienso que hay una confusion en las etiquetas de los nodos*/
    /*al automata que entra le tengo que modificar los valores de todos sus nodos*/
    //msj("uno al entrar a optional")
    //printMy_Afn(*uno);
    uno->A_initial.val = uno->A_initial.val + 1;
    for(auto &nodosInicial: uno->A_initial.transiLink)
        nodosInicial.second = nodosInicial.second + 1;

    for(auto &deltaUno : uno->delta){
        deltaUno.first += 1;
        deltaUno.second.second += 1;
    }
    
    for(auto &finalesUno: uno->ends){
        finalesUno.val+=1;
        for(auto trans_cada_final: finalesUno.transiLink){
            trans_cada_final.second +=1;
        }
    }
    for(auto &statesUno: uno->states){
        statesUno.val+=1;
        for(auto &trans_cada_state: statesUno.transiLink){
            trans_cada_state.second +=1;
        }
    }
    //msj("uno, cuando ya cmabie los valores")
    //printMy_Afn(*uno);
    char epsilon = 51;
    node new_end;
    ini_n(&solve->A_initial);// inicializa el inicial del automata solve
    ini_n(&new_end);// inicializo el nuevo final
    ini_afn(solve); // inicializo el afn solucion
    //solve->A_initial.val = uno->states.size(); // ANTES el valor del inicial de solucion es despendiendo al numero de estados que tiene uno
    solve->A_initial.val = 0;// DESPUES
    new_end.val = uno->states.size() + 1; // solo se añaden dos estados, el inicial y el final
    solve->A_initial.initial=true;
    new_end.end = true;
    new_end.token = token;
    uno->A_initial.initial=false;
    /*le sumamos 1 a todos los valores de los nodos*/
    /*
    caracteristica del metodo de thompson: que solo se tiene a lo mas dos transiciones por cada nodo y 
    solo se tiene un estado final y *un estado inicial*    
    */
    sim z; z.a = epsilon;
           z.b = epsilon;
    
    /*
    donde tengo nodos?
    
    */

    solve->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    solve->A_initial.transiLink.push_back(make_pair(z, new_end.val)); // transicion de opcional

    //cout<<"------------solo he modificado al inicial------------\n";
    //printMy_Afn(*solve);
    //cout<<"------------------------------------------------------\n";

    uno->ends[0].end = false;
    uno->ends[0].transiLink.push_back(make_pair(z, new_end.val));
    
    /*vaciar a solve*/
    /*
    deselectEnd(uno);//************************* vacio 
    uno->ends.push_back(new_end);//*************** meto al new_end
    uno->states.push_back(new_end);//************* ya lo meti al conjunto de states
    vaciarAutomataNoDeterminista(uno, solve);
    solve->name = name;
    solve->number_states = uno->states.size()+1;
    
    printMy_Afn(*solve);
    */
    /*el +1 es el estado inicial que no está en uno*/
    //cout<<"tenemos: "<<uno->ends.size()<<" estados finales\n";
    
    
    //for(int i=0; i<uno->ends.size(); i++){
    //    uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
        // a cada final le agrego la transicion con epsilon al nuevo final
    //}
    //hacer la transicion de viejo final a viejo nuevo 
    //agrego todo lo que falta a dos

    updateNode(uno->states, &uno->ends[0]);
    // actualizo el nodo fin
    solve->name = name;
    for(auto a: uno->alphabet)
        solve->alphabet.push_back(a);
    
    //cout<<"---------------he agregado el alphabet---------------\n";
    //printMy_Afn(*solve);
    //cout<<"------------------------------------------------------\n";
    /*voy a incrementar una sola vez states aquí*/

    deselectEnd(uno);
    deselectInitial(uno);
    for(int i=0; i<uno->states.size(); i++){
        solve->states.push_back(uno->states[i]);
        hacerDeltaAfn(solve, &uno->states[i]);// hacerDeltaAfn utiliza el valor del nodo que le paso
        //cout<<"----------------he agregado los estados---------------\n";
        //printMy_Afn(*solve);
        //cout<<"------------------------------------------------------\n";
    }
    solve->states.push_back(solve->A_initial);
    hacerDeltaAfn(solve, &solve->A_initial);
    //cout<<"------------he agregado el estado inicial-------------\n";
    //printMy_Afn(*solve);
    //cout<<"------------------------------------------------------\n";
    solve->states.push_back(new_end);
    hacerDeltaAfn(solve, &new_end);
    solve->ends.push_back(new_end);
    cout<<"al final de la operacion opcional:\n";
    printMy_Afn(*solve);
    
}
void returnNode(afn *uno, int val, node *solve){
    node aux;
    ini_n(&aux);
    for(int i=0; i<uno->states.size(); i++){
        if(uno->states[i].val == val){
            vaciarDatosNodo(solve, uno->states[i]);
            return;
        }
    }
    vaciarDatosNodo(solve, aux);
}
void returnNodeD(afd *uno, int val, node *solve){
    node aux;
    ini_n(&aux);
    for(int i=0; i<uno->states.size(); i++){
        if(uno->states[i].val == val){
            vaciarDatosNodo(solve, uno->states[i]);
            return;
        }
    }
    vaciarDatosNodo(solve, aux);
}
vector<int> lockEpsilon(afn *uno, node *nodo){//cambiar a revisar por referencia
    /*las transiciones destino a las que voy con epsilon*/
    vector<int> solve;
    vector<bool> visited(10e3, false);
    stack<node> a;
    a.push(*nodo);  
    while(!a.empty()){
        node tope = a.top();
        a.pop();
        solve.push_back(tope.val);
        for(int i=0; i<tope.transiLink.size(); i++){
            if(tope.transiLink[i].first.a == 51 && tope.transiLink[i].first.b == 51)
                if(!visited[tope.transiLink[i].second]){
                    //a.push(tope.transiLink[i].second);
                    node aux;
                    returnNode(uno, tope.transiLink[i].second, &aux);
                    a.push(aux);
                    visited[tope.transiLink[i].second] = true;
                }
        }
    }
    return solve;
}
set<int> convert2Set(vector<int> &v){
    set<int> solve = {};
    for(int i=0; i<v.size(); i++){
        solve.insert(v[i]);
    }
    return solve;
}
void joinAFN(vector<afn> exp, afn *solve, string name){
    ini_afn(solve);
    ini_n(&solve->A_initial);
    solve->name = name;
    solve->A_initial.val=0;
    solve->A_initial.initial=true;
    int count = 1; 
    char epsilon = 51;
    for(int i=0; i<exp.size(); i++){
        map<int, int> change_val;
        for(int j=0; j<exp[i].delta.size(); j++){
            //cout<<"------------------------------------antes eras: "<<exp[i].delta[j].first<<endl;
            if(change_val.count(exp[i].delta[j].first)==0){ // solamente se modifica cuando no existe
                //cout<<"no existo\n";
                change_val[exp[i].delta[j].first] = count;
                count++;
            }
            // cuando ya existe nadamas hay que asignar
            //cout<<"------------------------------------ahora es: "<<change_val[exp[i].delta[j].first]<<endl;
            exp[i].delta[j].first = change_val[exp[i].delta[j].first];
            
        }
        for(int j=0; j<exp[i].delta.size(); j++){
            if(change_val.count(exp[i].delta[j].second.second)!=0){
                exp[i].delta[j].second.second = change_val[exp[i].delta[j].second.second];
            }else{
                change_val[exp[i].delta[j].second.second] = count;
                exp[i].delta[j].second.second = change_val[exp[i].delta[j].second.second];
                count++;
            }
            solve->delta.push_back(exp[i].delta[j]);

        }
        sim z; z.a = epsilon; z.b = epsilon;
        solve->delta.push_back(make_pair(solve->A_initial.val,make_pair(z,change_val[exp[i].A_initial.val])));
        solve->A_initial.transiLink.push_back(make_pair(z,change_val[exp[i].A_initial.val]));
            
        for(auto a: exp[i].alphabet){
            if(!existsChar(a, solve->alphabet))            
                solve->alphabet.push_back(a);
        }
        for(int j=0; j<exp[i].ends.size(); j++){
            exp[i].ends[j].val = change_val[exp[i].ends[j].val];
            for(int k=0; k<exp[i].ends[j].transiLink.size(); k++)
                exp[i].ends[j].transiLink[k].second = change_val[exp[i].ends[j].transiLink[k].second];
            solve->ends.push_back(exp[i].ends[j]);
            solve->states.push_back(exp[i].ends[j]);
        }
        for(int j=0; j<exp[i].states.size(); j++){
            exp[i].states[j].val = change_val[exp[i].states[j].val];
            for(int k=0; k<exp[i].states[j].transiLink.size(); k++)
                exp[i].states[j].transiLink[k].second = change_val[exp[i].states[j].transiLink[k].second];
            if(!exp[i].states[j].end){
                if(exp[i].states[j].initial)
                    exp[i].states[j].initial = false;
                solve->states.push_back(exp[i].states[j]);
            }
        }
    }
    solve->states.push_back(solve->A_initial);
    cout<<"hemos terminado de unir los afns"<<endl;
    printMy_Afn(*solve);
}
vector<int> move_to(vector<int> &v, afn *uno, char a){
    vector<int> solve={};
    for(int i=0; i<v.size(); i++){
        node aux;
        returnNode(uno, v[i], &aux);
        if(aux.val!=-1){
            for(int j=0; j<aux.transiLink.size(); j++){
                if( a >= aux.transiLink[j].first.a && a <= aux.transiLink[j].first.b ){
                    solve.push_back(aux.transiLink[j].second);
                }
            }
        }
    }
    return solve;
}
vector<int> go_to(vector<int> &s, char a, afn *uno){
    vector<bool> visited(10e5, false);
    vector<int> v = move_to(s, uno, a);
    vector<int> solve={};
    vector<int> va={};
    for(int i=0; i<v.size(); i++){
        node aux;
        returnNode(uno, v[i], &aux);
        va = lockEpsilon(uno, &aux);
        for(int j=0; j<va.size(); j++){
            if(!visited[va[j]]){
                visited[va[j]] = true;
                solve.push_back(va[j]);
            }
        }
    }
    return solve;
}
vector<int> convert2vector(set<int> &s){
    vector<int> solve;
    for(auto a: s){
        solve.push_back(a);
    }
    return solve;
}
void convert_afn2afd(afn *c_afn, afd *s_afd, string name){
    set<set<int>> s_i;//se van a ir enumerando para meterlo como un nodo en el afd
    vector<int> s = lockEpsilon(c_afn, &c_afn->A_initial); set<int> 
    s0 = convert2Set(s);
    queue<set<int>> q;
    vector<pair<int, int>> finals;
    for(int i=0; i<c_afn->ends.size(); i++){
        finals.push_back(make_pair(c_afn->ends[i].val, c_afn->ends[i].token));
    }
    //cout<<endl;
    map<set<int>, int> m; // conjuntos s
    m[s0] = 0; 
    ini_afd(s_afd);// afd solución 
    s_afd->name = name;
    ini_n(&s_afd->A_initial); // nodo inicial de todo el afd
    s_afd->A_initial.val=0; // le ponemos el valor de cero
    s_afd->A_initial.initial=true; // y lo ponemos como nodo incial 
    s_i.insert(s0); // meto al primer conjunto, al conjunto de conjuntos
    q.push(s0); // meto al primer conjunto a la pila
    //node n, aux;
    for(auto a: c_afn->alphabet) // caracteres 
        if(!existsChar(a, s_afd->alphabet))
            s_afd->alphabet.push_back(a);
    while(!q.empty()){//vamos a ver si es un nuevo conjunto y sus transiciones
        set<int> tope = q.front(); vector<int> tope_ = convert2vector(tope);
        node n;
        ini_n(&n);//s0
        n.val = m[tope]; //el conjunto ya tenia valor, ************************************** //0      s_i.size()=1
        cout<<"--------------------creamos el nodo: "<<n.val<<endl;
        if(n.val==0)
            n.initial=true;
        
        for(auto alpha : s_afd->alphabet){
            vector<int> w = go_to(tope_, alpha.a, c_afn); 
            set<int> w_ = convert2Set(w);
            if(s_i.count(w_)==0 && w_.size()!=0){
                if(!existsPair(alpha, s_i.size(), n.transiLink)){
                    n.transiLink.push_back(make_pair(alpha, s_i.size()));
                    m[w_] =  s_i.size();
                    s_i.insert(w_);
                    q.push(w_);
                    /*
                    bool conjunto_final = false;
                    for(auto &b: w_){
                        //x.first == numero de nodo, x.second == token
                        for(auto &x: finals){
                            if(b==x.first){
                                //a.second pertenece a los finales del afd
                                n.end = true;
                                n.token = x.second;
                                s_afd->ends.push_back(n);
                                conjunto_final = true;
                                break;
                            }
                        }
                        if(conjunto_final)
                            break;
                    }   
                    */
                }else{
                    continue;
                }
            }else if(w_.size()){
                cout<<"ya existe, solo le falta esta transicion\n";
                if(!existsPair(alpha, m[w_], n.transiLink))// estoy mirando su 
                    n.transiLink.push_back(make_pair(alpha, m[w_]));
                else
                    continue;                
            }
            hacerDeltaAfd(s_afd, &n);
        }  
        
        s_afd->states.push_back(n);
        q.pop();
    }    

    bool conjunto_final = false;
        cout<<"----------------------cuantos finales tengo: "<<finals.size()<<endl;
        cout<<"----------------------elementos en m: "<<m.size()<<endl;
        for(auto &a: m){
            //es un set no hay repetidos
            conjunto_final = false;      
            for(auto &b: a.first){
                //x.first == numero de nodo, x.second == token
                for(auto &x: finals){
                    if(b==x.first){
                    //a.second pertenece a los finales del afd
                        for(auto &state : s_afd->states){//corro por los states del afd
                            if(state.val == a.second){
                                state.end = true;
                                state.token = x.second;
                                cout<<"token: "<<x.second<<" al state: "<<state.val<<endl;
                                s_afd->ends.push_back(state);
                                conjunto_final = true;
                                
                            }
                        }
                    }
                }
                //if(conjunto_final)
                //    break;
            }   
        }
     
    cout<<"al final de convertir el automata\n";
    printMy_Afd(*s_afd);
}
void validateString_afd(string &s, afd *afd_){                 //Quiza lo voy a eliminar 
}
bool validateString_afn(string s, afn *afn_){                  //Quiza lo voy a eliminar clase 4, que ya está en descargas
    vector<int> s0 = lockEpsilon(afn_, &afn_->A_initial);
    vector<int> aux={};
    set<int> finals;
    for(auto a: afn_->ends)
        finals.insert(a.val);
    for(int i=0; i<s.length(); i++){
        aux = go_to(s0, s[i], afn_);
        if(aux.size()==0)
            return false;
    }
    for(int i=0; i<aux.size(); i++)
        for(auto a: finals)
            if(aux[i]==a)
                return true;
    return false;
}
map<int, string> leerTXTexpresiones(){
    int nume_lineas = 2;
    vector<string> exp_token;
    string str;
    if(ifstream user {"./txt/inputs/gramaticaGv2.txt"}){
        while(getline(user, str)){
            exp_token.push_back(str);       
            str = "";
        }
    }
    string str_i, str_p, token="";
    int tok;
    bool space = false; 
    map<int, string> solve;
    for(string s: exp_token){
        for(char c: s){
            if(c!=' ' && !space){
                str_i.push_back(c);
            }else
                space = true;    
            if(space)
                token.push_back(c);
        }
        space = false;
        str_p = convertirERinfija(str_i);
        tok = stoi(token);
        solve[tok] = str_p;
        str_i = "";
        token = "";
    }
    return solve;
}
void escribirAFDtxt(afd *solve){// solo voy a vaciar states y adelante vere al token en caso de que sea final
    ofstream file;
    file.open("txt/outputs/gramaticaGv2.txt");
    
    //file<<"\t\t:::"<<"tabla_clases_lexicas_ER:::\n\n";
    /*file<<"\tDescripcion: se muestra el estado inicial seguido del (los) caracter(es) de transición\n"
          "\ty a continuación encuentra el estado destino. Si el estado inicial es final se encuentra\n"
          "\tun número distinto de 0 que representa el token. El estado que no tiene transiciones\n"
          "\ttendrá en su lugar '---'.\n\n";
    */
    //file<<"--\n";
    for(auto s: solve->states)
        if(s.transiLink.size())
            for(auto d: s.transiLink)// transiciones de cada state
                file<<s.val<<" ["<<d.first.a<<"-"<<d.first.b<<"] "<<d.second<<" "<<s.token<<endl;
        else
            file<<s.val<<" ----- -1 "<<s.token<<endl;      
    //file<<"--";  
    file.close();
}
void analisisExpresionRegular(map<int, string> &ep_token, string name){
    bool flag = false;
    bool opr_open = false;
    bool opr_close = false;
    map<char, int> oper;
    oper['|'] = 0; oper['!'] = 1;//operador de concatenacion
    oper['+'] = 2; oper['*'] = 2;
    oper['?'] = 2;
    int cont = 0;
    vector<afn> afns;
    stack<afn> p;
    int i=0;
    for(auto e: ep_token){//recorrer cada expresion regular 
        afn a, b, solve;
        cout<<"nuestra expresion es: "<<e.second<<endl;
        bool opr_open = true;
        bool opr_close = false;
        for(i=0; i<e.second.size(); i++){// [33-126]
            char aa, bb; 
            cont++;
            //cout<<"'"<<e.second[i]<<"' lugar: "<<i<<endl;
            if(e.second[i] == 92 && flag == false){
                flag = true;
                //opr_open = !opr_open;
                //opr_close = !opr_close;
                continue;
            }
            if(e.second[i]==91 && !flag){
                //cout<<"primer corchete\n";
                continue;
            }
            if(e.second[i]==45 && !flag){
                opr_open = false;
                opr_close = true;
                continue;
            }
            if(flag || oper.count(e.second[i])==0){
                //cout<<"es un operando: '"<<e.second[i]<<"' lugar: "<<i<<endl;
                flag = false;
                if(opr_open){
                    //opr_open = false;
                    aa = e.second[i];
                    //cout<<"aa es : "<<aa<<endl;
                    continue;
                }
                if(opr_close){
                    opr_open = false;
                    opr_close = false;
                    bb = e.second[i];
                    //cout<<"bb es : "<<bb<<endl;
                    continue;
                }
                if(!opr_close && !opr_open && e.second[i] == 93){
                    opr_open = true;
                }
                //cout<<"solamente creo cuando ya cierro un corchete\n";
                cout<<"creamos con los caracteres de transicion: "<<aa<<"    "<<bb<<endl;
                ini_afn(&solve);
                string name = "creacion ";
                name.push_back(aa);
                //cout<<"creamos "<<name<<endl;
                createAFN(aa, bb, name , &solve, e.first);
                //printMy_Afn(solve);
                p.push(solve);
                
            }else{
                cout<<"operacion"<<endl;
                //cout<<"operandos en la pila: "<<p.size()<<endl;
                int aux = e.second[i];
                switch(aux){
                    case 124 : { //join |
                        cout<<"Join\n";
                        if(p.empty()){
                            cout<<"HAY UN PROBLEMA, NO TIENES AFNs PARA TRABAJAR\n";
                            return;
                        }
                        ini_afn(&a);
                        ini_afn(&b);
                        a = p.top(); p.pop();
                        b = p.top(); p.pop();
                        //cout<<"Operacion sobre: "<<a.name<<" y "<<b.name<<endl;
                        join(&a, &b, &solve, "join", e.first);
                        //printMy_Afn(solve);
                        p.push(solve);
                        break;
                    }
                    case 43: {// cerradura transitiva * 
                        cout<<"Cerradura transitiva\n";
                        if(p.empty()){
                            cout<<"HAY UN PROBLEMA, NO TIENES AFNs PARA TRABAJAR\n";
                            return;
                        }
                        ini_afn(&a);
                        ini_afn(&solve);
                        a = p.top(); 
                        //cout<<"Operacion sobre: "<<a.name<<endl;
                        p.pop();
                        lockTransitive(&a,&solve,"transitiva", e.first);
                        //printMy_Afn(solve);
                        p.push(solve);
                        //cout<<"Nombre del afn que se creo y lo tenemos en la pila: "<<p.top().name<<endl;
                        //cout<<"Cantidad de elementos que tenemos en la pila: "<<p.size()<<endl;
                        break;
                    }
                    case 63:{// operador opcional ? 
                        cout<<"Operador opcional\n";
                        if(p.empty()){
                            cout<<"HAY UN PROBLEMA, NO TIENES AFNs PARA TRABAJAR\n";
                            return;
                        }
                        ini_afn(&a);
                        ini_afn(&solve);
                        a = p.top(); 
                        //cout<<"Operacion sobre: "<<a.name<<endl;
                        p.pop();
                        optional(&a,&solve,"opcional", e.first);
                        //printMy_Afn(solve);
                        p.push(solve);
                        //cout<<"Nombre del afn que se creo y lo tenemos en la pila: "<<p.top().name<<endl;
                        //cout<<"Cantidad de elementos que tenemos en la pila: "<<p.size()<<endl;
                        break;
                    }
                    case 33:{// concatenar dos elementos el primero de la pila es el segundo argumento
                        cout<<"Concatenar\n";
                        if(p.empty()){
                            cout<<"HAY UN PROBLEMA, NO TIENES AFNs PARA TRABAJAR\n";
                            return;
                        }
                        ini_afn(&a);
                        ini_afn(&b);
                        ini_afn(&solve);
                        b = p.top(); p.pop();
                        a = p.top(); p.pop();
                        //cout<<"Operacion sobre: "<<a.name<<" y "<<b.name<<endl;
                        concatenate(&a, &b, &solve,"concatenar", e.first);
                        //printMy_Afn(solve);
                        p.push(solve);
                        //cout<<"Nombre del afn que se creo y lo tenemos en la pila: "<<p.top().name<<endl;
                        //cout<<"Cantidad de elementos que tenemos en la pila: "<<p.size()<<endl;
                        break;
                    }
                    case 42:{// cerradura de kleene *
                        cout<<"Kleene\n";
                        if(p.empty()){
                            cout<<"HAY UN PROBLEMA, NO TIENES AFNs PARA TRABAJAR\n";
                            return;
                        }
                        ini_afn(&a);
                        ini_afn(&solve);
                        a = p.top(); 
                        //cout<<"Operacion sobre: "<<a.name<<endl;
                        p.pop();
                        lockKleene(&a, &solve, "kleene", e.first);
                        //printMy_Afn(solve);
                        p.push(solve);
                        //cout<<"Nombre del afn que se creo y lo tenemos en la pila: "<<p.top().name<<endl;
                        //cout<<"Cantidad de elementos que tenemos en la pila: "<<p.size()<<endl;
                        break;
                    }

                    default: break;
                }
            }
        }
        afn resultadoExpReg;
        ini_afn(&resultadoExpReg);
        resultadoExpReg = p.top();
        //printMy_Afn(resultadoExpReg);
        //cout<<"**nombre: "<<resultadoExpReg.name<<" con token: "<<resultadoExpReg.ends[0].token<<endl;
        p.pop();
        afns.push_back(resultadoExpReg);
        //cout<<"2. operandos en la pila: "<<p.size()<<endl;
    }
    //unir los afn para obtener el afd
    afn solAFN;
    ini_afn(&solAFN);
    afd sol;
    ini_afd(&sol);
    joinAFN(afns, &solAFN, name);
    convert_afn2afd(&solAFN, &sol, name);
    printMy_Afd(sol);
    escribirAFDtxt(&sol);
}

int main(){
    map<int, string> solve = leerTXTexpresiones();
    analisisExpresionRegular(solve, "solucion_uno");
    return 0;
}
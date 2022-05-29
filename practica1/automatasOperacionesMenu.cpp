#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define iden cout<<"\t\t";
#define mv(s, v) cout<<s<<" "<<v<<endl;
#define msj(s) cout<<s<<endl;
#define tripleta(s, u, v) cout<<s<<" "<<u<<" "<<v<<endl;
typedef struct node{
    int val;
    bool initial;
    bool end;
    int token;
    vector<pair<char, int>> transiLink;
}node;
typedef struct afn{
    string name;
    node A_initial;
    vector<pair<int, pair<char, int>>> delta;// con el alfabeto, que es lo que me forma las columnas guardare su code ascii
    set<char> alphabet;
    vector<node> ends;  
    vector<node> states; 
    int number_states;
}afn;
typedef struct afd{
    string name;
    node A_initial;
    set<pair<int, pair<char, int>>> delta;// con el alfabeto, que es lo que me forma las columnas guardare su code ascii
    set<char> alphabet;
    vector<node> ends;  
    vector<node> states; 
    int number_states; 
}afd;

void seeNode(node *nodo){
    mv("\t\tnodo:", nodo->val)
    mv("¿Es inicial?", nodo->initial)
    mv("¿Es final?", nodo->end)
    if(nodo->end)
        cout<<"TOKEN: "<<nodo->token<<endl;
    msj("Tiene las siguientes transciones:")
    for(int i=0; i<nodo->transiLink.size(); i++){
        mv(nodo->transiLink[i].first,nodo->transiLink[i].second)
    }
}
void vaciarDatosNodo(node * destino, node origen){
    destino->val = origen.val;
    destino->initial = origen.initial;
    destino->end = origen.end;
    destino->token = origen.token;
    for(int i=0; i<origen.transiLink.size(); i++)
        destino->transiLink.push_back(make_pair(origen.transiLink[i].first, origen.transiLink[i].second));
}
void updateNode(vector<node> &states, node *nodo){
    /*buscar el nodo en states*/
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
        tripleta(my_afn.delta[i].first, my_afn.delta[i].second.first, my_afn.delta[i].second.second);
    }
    msj("3. Alphabet: {")
    for(auto a : my_afn.alphabet)
        msj(a)
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
        tripleta(a.first, a.second.first, a.second.second);
    }
    msj("3. Alphabet: {")
    for(auto a : my_afd.alphabet)
        msj(a)
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
}
void ini_a(afn *afn_0){//el numero de estados lo pone a 0
    string name = "-";
    afn_0->A_initial.val = 0;
    afn_0->A_initial.end=false;
    afn_0->A_initial.initial=true;
    afn_0->A_initial.token=0;
    afn_0->A_initial.transiLink = {};
    afn_0->delta = {};
    afn_0->alphabet = {};
    afn_0->ends = {};
    afn_0->states = {};
    afn_0->number_states=0;
}
void ini_afd(afd *afd_0){
    string name = "-";
    afd_0->A_initial.val = -1;
    afd_0->A_initial.end=false;
    afd_0->A_initial.initial=true;
    afd_0->A_initial.token=0;
    afd_0->A_initial.transiLink = {};
    afd_0->delta = {};
    afd_0->alphabet = {};
    afd_0->ends = {};
    afd_0->states = {};
    afd_0->number_states=0;
}
void hacerDeltaAfn(afn *nuevo, node *nodo){
    /*por cada transicion que tenga nodo se la añadire a nuevo*/
    for(int i=0; i<nodo->transiLink.size(); i++)
        nuevo->delta.push_back(make_pair(nodo->val, make_pair(nodo->transiLink[i].first, nodo->transiLink[i].second)));
}
void hacerDeltaAfd(afd *nuevo, node *nodo){
    /*por cada transicion que tenga nodo se la añadire a nuevo*/
    for(int i=0; i<nodo->transiLink.size(); i++)
        nuevo->delta.insert(make_pair(nodo->val, make_pair(nodo->transiLink[i].first, nodo->transiLink[i].second)));
}
void renameNodes(afn *uno, afn *dos){
    //mi llave es el valor viejo
    int nodos_uno = uno->states.size(); //8
    map<int,int> newsValores;   
    /*no cambio translink las transiciones de cada nodo*/
    for(int i=0; i<dos->states.size(); i++){
        newsValores[dos->states[i].val] = nodos_uno+dos->states[i].val;//ya los guarde 
        dos->states[i].val = newsValores[dos->states[i].val];//cambio su conjunto states
    }
    /*msj("viendo que tiene el map")
    map<int, int>::iterator m;
    for(m = newsValores.begin(); m!=newsValores.end(); m++){
        cout<<m->first <<" "<<m->second<<endl;
    }*/
    /*rename initials*/
    //dos->A_initial.val = newsValores[dos->A_initial.val];

    for(int i=0; i<dos->states.size(); i++)//por cada nodo 
        for(int j=0; j<dos->states[i].transiLink.size(); j++)//por cada transicion de cada nodo
            dos->states[i].transiLink[j].second = newsValores[dos->states[i].transiLink[j].second];
    dos->A_initial.val = newsValores[dos->A_initial.val];//cambio su inicial
    for(int i=0; i<dos->A_initial.transiLink.size(); i++)
        dos->A_initial.transiLink[i].second = newsValores[dos->A_initial.transiLink[i].second];
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
void join(afn *uno, afn *dos, afn *tres, string str, int token){// mas_uno debe ser 0
    /*PROBLEMA: PIERDO AS TRANSICIONES DE VIEJO FINAL NODO 1 Y VIEJO FINAL 2*/
    node new_initial, new_end; //DEBEN DE ESTAR COMO NODO INITIAL Y DENTRO DE STATES
    char epsilon = 51;
    ini_n(&new_initial);
    ini_n(&new_end);
    ini_a(tres);
    //marcamos a new_initial como inicial del afn, de igual forma que el new_end
    new_initial.initial=true;
    new_end.end=true;
    new_end.token=token;
    //renombrar nodos 
    renameNodes(uno, dos);//respecto a los nodos que tenga uno, seran los .val de los nodos que tenga dos
    int t_nodes = uno->states.size() + dos->states.size();
    new_initial.val = t_nodes;
    new_end.val = t_nodes + 1;
    //vamos a agregar a new_Initial dos transiciones con epsilon '3'
    new_initial.transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    new_initial.transiLink.push_back(make_pair(epsilon, dos->A_initial.val));
    //añadimos las transiciones de viejos finales a new_end
    for(int i=0; i<uno->ends.size(); i++){
        uno->ends[i].transiLink.push_back(make_pair(epsilon, new_end.val));
        //seeNode(&uno->ends[i]);
        updateNode(uno->states, &uno->ends[i]);
    }
    for(int i=0; i<dos->ends.size(); i++){
        dos->ends[i].transiLink.push_back(make_pair(epsilon, new_end.val));
        //seeNode(&dos->ends[i]);
        updateNode(dos->states, &dos->ends[i]);
    }
    //añadimos todo a tres
    //seeNode(&uno->ends[0]);
    //seeNode(&uno->ends[0]);
    /*actualizar ends de states de afn*/
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, new_initial);
    for(auto a: uno->alphabet) tres->alphabet.insert(a);
    for(auto a: dos->alphabet) tres->alphabet.insert(a);
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
}
void concatenate(afn *uno, afn *dos, afn *tres, string str, int token){
    /*0. renombrar nodos para no tener que cambiar las transiciones que se añaden a uno*/
    renameNodes(uno, dos);
    cout<<"operacion de concatenar\n";
    cout<<"uno\n";
    printMy_Afn(*uno);
    cout<<"dos\n";
    printMy_Afn(*dos);
    //->>0-a-> 1 -b->((3))
    /*1. le añado la transicion a final.uno con initial.dos*/
    for(int i=0; i<dos->A_initial.transiLink.size(); i++){
        uno->ends[0].transiLink.push_back(dos->A_initial.transiLink[i]);
        uno->delta.push_back(make_pair(uno->ends[0].val, make_pair(dos->A_initial.transiLink[i].first, dos->A_initial.transiLink[i].second)));
    }
    for(int i=0; i<uno->states.size(); i++)
        if(uno->states[i].val == uno->ends[0].val)
            for(int j =0; j<uno->ends[0].transiLink.size(); j++)
                uno->states[i].transiLink.push_back(make_pair(uno->ends[0].transiLink[j].first, uno->ends[0].transiLink[j].second));
    /*PROBLEMA, LAS TRANSICIONES DEL NODO 1 SALEN MAL*/
    deselectEnd(uno);
    /*update del nodo final que se encuentra en states*/
    //printMy_Afn(*uno);//nodo uno en states no existe
    /*comenzar a llenar tres*/
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, uno->A_initial);
    for(auto a: uno->alphabet)
        tres->alphabet.insert(a);
    for(auto b: dos->alphabet)
        tres->alphabet.insert(b);
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
}
void createAFN(char a, string nomb, afn *nuevo, int token){
    node n1, n2;
    ini_a(nuevo);
    ini_n(&n1); ini_n(&n2);
    nuevo->name = nomb;
    n1.val = 0;
    n2.val = 1;
    n1.initial = true;
    n2.end = true;
    n2.token=token;
    n1.transiLink.push_back(make_pair(a, n2.val));//{'a', 1} en el nodo 1 se guarda que con 'a' viaja al nodo 2
    vaciarDatosNodo(&nuevo->A_initial, n1);
    nuevo->alphabet.insert(a);
    nuevo->states.push_back(n1);
    nuevo->states.push_back(n2);
    hacerDeltaAfn(nuevo, &n1);
    hacerDeltaAfn(nuevo, &n2);
    nuevo->ends.push_back(n2);
    nuevo->number_states = 2;
}
void lockTransitive(afn *uno, afn *dos,string name, int token){
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_a(dos);
    dos->A_initial.val = uno->states.size();
    new_end.val = uno->states.size() + 1;
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token = token;
    uno->A_initial.initial=false;
    //me falta desmarcar los finales de uno 
    //ligar el nuevo inicial al viejo inicial 
    dos->A_initial.transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    //ligar el viejo final al nuevo final 
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(epsilon, new_end.val));
    //hacer la transicion de viejo final a viejo nuevo 
    uno->ends[0].transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    /*agrego todo lo que falta a dos*/
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet)
        dos->alphabet.insert(a);
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
}
void lockKleene(afn *uno, afn *dos,string name, int token){
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_a(dos);
    dos->A_initial.val = uno->states.size();
    new_end.val = uno->states.size() + 1;
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token=token;
    uno->A_initial.initial=false;
    //me falta desmarcar los finales de uno 
    //ligar el nuevo inicial al viejo inicial 
    dos->A_initial.transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    dos->A_initial.transiLink.push_back(make_pair(epsilon, new_end.val));
    //ligar el viejo final al nuevo final 
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(epsilon, new_end.val));
    //hacer la transicion de viejo final a viejo nuevo 
    uno->ends[0].transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    /*agrego todo lo que falta a dos*/
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet)
        dos->alphabet.insert(a);
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

}
void optional(afn *uno, afn *dos,string name, int token){
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_a(dos);
    dos->A_initial.val = uno->states.size();
    new_end.val = uno->states.size() + 1;
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token = token;
    uno->A_initial.initial=false;
    //me falta desmarcar los finales de uno 
    //ligar el nuevo inicial al viejo inicial 
    dos->A_initial.transiLink.push_back(make_pair(epsilon, uno->A_initial.val));
    dos->A_initial.transiLink.push_back(make_pair(epsilon, new_end.val));
    //ligar el viejo final al nuevo final 
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(epsilon, new_end.val));
    //hacer la transicion de viejo final a viejo nuevo 
    /*agrego todo lo que falta a dos*/
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet)
        dos->alphabet.insert(a);
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
            if(tope.transiLink[i].first == 51)
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
    ini_a(solve);
    ini_n(&solve->A_initial);
    solve->name = name;
    solve->A_initial.val=0;
    solve->A_initial.initial=true;
    int count = 1; 
    char epsilon = 51;
    for(int i=0; i<exp.size(); i++){
        map<int, int> change_val;
        for(int j=0; j<exp[i].delta.size(); j++){
            change_val[exp[i].delta[j].first] = count;
            exp[i].delta[j].first = change_val[exp[i].delta[j].first];
            count++;
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
        solve->delta.push_back(make_pair(solve->A_initial.val,make_pair(epsilon,change_val[exp[i].A_initial.val])));
        solve->A_initial.transiLink.push_back(make_pair(epsilon,change_val[exp[i].A_initial.val]));
            
        for(auto a: exp[i].alphabet)
            solve->alphabet.insert(a);
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
}
vector<int> move_to(vector<int> &v, afn *uno, char a){
    vector<int> solve={};
    for(int i=0; i<v.size(); i++){
        node aux;
        returnNode(uno, v[i], &aux);
        if(aux.val!=-1){
            for(int j=0; j<aux.transiLink.size(); j++){
                if(aux.transiLink[j].first==a){
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
    vector<int> s = lockEpsilon(c_afn, &c_afn->A_initial); set<int> s0 = convert2Set(s);
    queue<set<int>> q;
    vector<pair<int, int>> finals;
    //vector<int> finals;
    //cout<<"Los finales son: ";
    for(int i=0; i<c_afn->ends.size(); i++){
        finals.push_back(make_pair(c_afn->ends[i].val, c_afn->ends[i].token));
        //finals.push_back(c_afn->ends[i].val);
        //cout<<c_afn->ends[i].val<<" ";
    }
    //cout<<endl;
    
    map<set<int>, int> m; 
    s_afd->name = name;
    m[s0] = 0;
    ini_afd(s_afd);
    ini_n(&s_afd->A_initial);
    s_afd->A_initial.val=0;
    s_afd->A_initial.initial=true;
    s_i.insert(s0);
    q.push(s0);
    node n, aux;
    for(auto a: c_afn->alphabet)
        s_afd->alphabet.insert(a);

    while(!q.empty()){//vamos a ver si es un nuevo conjunto y sus transiciones
        set<int> tope = q.front(); vector<int> tope_ = convert2vector(tope);
        //cout<<"tope de mi cola: ";
        //for(int i=0; i<tope_.size(); i++) cout<<tope_[i]<<" ";
        //cout<<endl;
        ini_n(&n);//s0
        n.val = m[tope];//sera el nodo inicial
        if(n.val==0)
            n.initial=true;
        //cout<<"elementos en set<set<>>: "<<s_i.size()<<endl;
        for(auto alpha : c_afn->alphabet){
            vector<int> w = go_to(tope_, alpha, c_afn); set<int> w_ = convert2Set(w);
            //cout<<"Ir_A del tope con "<<alpha<<": ";
            //cout<<endl;
            if(s_i.count(w_)==0 && w_.size()!=0){
                //cout<<"\n\tNo está ese set en el set, por lo que sería el s"<<s_i.size()<<endl;
                n.transiLink.push_back(make_pair(alpha, s_i.size()));
                m[w_] =  s_i.size();
                s_i.insert(w_);
                q.push(w_);
            }else if(w_.size()){
                //cout<<"\n\tSí está ese set en el set, y es s"<<m[w_]<<endl;
                n.transiLink.push_back(make_pair(alpha, m[w_]));
            }
            hacerDeltaAfd(s_afd, &n);
            //cout<<endl;
        }  
        for(auto a: m){//a.first {1, 2, 3, 4}
            for(auto b: a.first){//b: 1, b: 2 ...
                for(auto x: finals){// x: 1, x: 3 ....
                    if(b==x.first){
                    //if(b==x){
                        if(n.val==m[a.first]){//***************************************
                            n.end = true;
                            n.token = x.second;
                            s_afd->ends.push_back(n);
                        }
                    }
                }
            }   
        } 
        s_afd->states.push_back(n);
        q.pop();
    }    
    //cout<<endl;
    //printMy_Afd(*s_afd);
}
void validateString_afd(string &s, afd *afd_){                 //Quiza lo voy a eliminar 
}
bool validateString_afn(string s, afn *afn_){                  //Quiza lo voy a eliminar
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
int findTransition(afd *autom, int origen, char x){
    int destino = -1;
    for(auto a: autom->delta)
        if(a.first == origen && a.second.first == x)
            return a.second.second;
    return destino;
}

int yylex(int &caracter_actual, int &edo_actual, int &inilexema, int &finlexema, bool &ac, string &s, afd *automata, string &solve){
    /*
    msj("adentro de la funcion")
    printMy_Afd(*automata);
    msj("----Entra con estos valores: ----")
    mv("caracter_actual:", caracter_actual)
    mv("edo_actual", edo_actual)
    mv("inilexema", inilexema)
    mv("finlexema:", finlexema)
    mv("ac", ac)
    mv("string_analizar:", s)
    msj("----Se regresa al predeterminado solo estos: ----")
    */
    int token = 0; // token 0 es ERROR
    edo_actual = 0; 
    finlexema = -1;
    int cont=0;
    ac = false;
    /*
    mv("token", token)
    mv("edo_actual", edo_actual)
    mv("finlexema", finlexema)
    mv("ac", ac)
    */
    for(int i=caracter_actual; i<s.size(); i++){
        int destino = findTransition(automata,edo_actual,s[i]);
        if(destino!=-1){//si hay transicion 
            edo_actual = destino;
            finlexema = i;
            node aux; returnNodeD(automata, destino, &aux);
            iden cout<<"SI HAY TRANSICION con: "<<destino<<endl;
            if(aux.end){
                token = aux.token;
                solve.push_back(s[i]);
                ac = true;
            }
        }else{//no hay transicion, pero si hay estado de aceptacion
            if(ac){
                iden msj("NO HAY TRANSICION, PERO SI HUBO ESTADO DE ACEPTACION")
                solve.push_back(s[i]);
                caracter_actual = finlexema + 1;
                inilexema = finlexema+1;
                iden cout<<"return token: "<<token<<endl;
                return token;
            }else{
                iden msj("ERROR-no hay transicion ni estado de aceptacion")
                solve = "";
                token = 0;//estado de error - lexema error
                caracter_actual = inilexema + 1;//caracter actual
                edo_actual = 0;
                return token;
            }
        }
    }
    if(caracter_actual==s.size()-1){
        return -2;//finalizo el analisis de la cadena
    }
    return token;//token de ERROR
}

int main(){

    cout<<"\t\t\t\t\t:::::A U T ó M A T A S:::::\n";
    cout<<"\t\tCon este programa podrás construir autómatas por el Método de Thompson.\n"
          "\t\tEn el siguiente menú encontrarás las operaciones para armar un AFN que reconozca\n"
          "\t\ttus clases lexicas, el cual lo podrás convertir en AFD para aplicarle el método\n"
          "\t\tyylex() para el ANáLISIS LéXICO.\n"
          "\n\n\t\tElige la operación que desea hacer: ";
    int op, token;
    string names1, names2;
    char a;
    vector<afn> afn_creados;
    vector<bool> used_n;
    afn automata;
    vector<afd> afd_creados;
    vector<bool> used_d;
    afd solve;
        int caracter_actual = 0;
        int edo_actual = 0;
        int inilexema = 0;
        int finlexema = -1;
        bool ac = false;
    do{
        cout<<"\n\t\t0. Ver automata"
              "\n\t\t1. Create AFN"
              "\n\t\t2. Join two AFNs"
              "\n\t\t3. Concatenate two AFNs"
              "\n\t\t4. Kleene's lock"
              "\n\t\t5. Lock trasitive"
              "\n\t\t6. Optional"
              "\n\t\t7. Join for lexical analyser"
              "\n\t\t8. Convert AFN to AFD"
              "\n\t\t9. Validate string (AFN)"
              "\n\t\t10. Funcion yylex sobre un AFD"
              "\n\t\t11. Salir\n";
              
        iden cout<<"OPERACION: "; cin>>op;
        switch (op){
            case 0:{//see
                int i, j; bool found0=false, found1= false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"AFDs que tiene: ";
                for(i=0; i<afd_creados.size(); i++)
                    if(!used_d[i])
                        cout<<afd_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"Autómata que quiere ver: ";
                cin>>names1;
                
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                for(j=0; j<afd_creados.size(); j++)
                    if(afd_creados[j].name == names1 && !used_d[j]){
                        found1 = true;
                        break;
                    }
                if(!found0 && !found1){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }
                if(found0)
                    printMy_Afn(afn_creados[i]);
                else if(found1)
                    printMy_Afd(afd_creados[j]);
                string salir; 
                iden cout<<"Para regresar al menú presione cualquier letra seguido de ENTER: ";
                cin>>salir;
                break;
            }
            case 1:{//create
                iden cout<<"Nombre del AFN: ";
                cin>>names1;
                iden cout<<"Caracter de transición: ";
                cin>>a;
                iden cout<<"TOKEN: ";
                cin>>token;
                createAFN(a, names1, &automata, token);
                afn_creados.push_back(automata);
                used_n.push_back(false);
                break;
            }
            case 2:{//join
                string str; int i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"AFNs que quieres unir: ";
                cin>>names1>>names2;
                iden cout<<"Nombre del AFN nuevo: ";
                cin>>str;
                iden cout<<"TOKEN: ";
                cin>>token;
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                for(j=0; j<afn_creados.size(); j++)
                    if(afn_creados[j].name == names2 && !used_n[j]){
                        found1 = true;
                        break;
                    }
                if(!found0){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }
                if(!found1){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names2<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }
                if(found0 && found1){
                    join(&afn_creados[i], &afn_creados[j], &automata, str, token);
                    used_n[i]=true;
                    used_n[j]=true;
                    afn_creados.push_back(automata);
                }
                break;
            }
            case 3:{//concatenate
                string str; int i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                cout<<"\t\tAFNs que quieres Concatenar: ";
                cin>>names1>>names2;
                cout<<"\t\tNombre del AFN nuevo: ";
                cin>>str;
                iden cout<<"AVISO: el TOKEN del nuevo AFN es el mismo que tiene el segundo autómata que se eligió\n";
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                for(j=0; j<afn_creados.size(); j++)
                    if(afn_creados[j].name == names2 && !used_n[j]){
                        found1 = true; 
                        break;
                    }
                if(!found0){
                    cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }
                if(!found1){
                    cout<<"Aun no ha construido ese autómata o ya se uso: "<<names2<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }
                if(found0&&found1){
                    concatenate(&afn_creados[i], &afn_creados[j], &automata, str, token);
                    used_n[i]=true;
                    used_n[j]=true;
                    afn_creados.push_back(automata);
                }
                break;
            }
            case 4:{//Kleene's lock
                string str; int i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                cout<<"\t\tAFN al que le aplicará Cerradura de Kleene: ";
                cin>>names1;
                cout<<"\t\tNombre del AFN nuevo: ";
                cin>>str;
                iden cout<<"TOKEN: ";
                cin>>token;
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                if(!found0){
                    cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }else{
                    lockKleene(&afn_creados[i], &automata, str, token);
                    afn_creados.push_back(automata);
                    used_n[i]=true;
                }
                break;
            }
            case 5:{//lock transitive
                string str; int i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"AFN al que le aplicará Cerradura Transitiva: ";
                cin>>names1;
                iden cout<<"Nombre del AFN nuevo: ";
                cin>>str;
                iden cout<<"TOKEN: ";
                cin>>token;
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                if(!found0){
                    cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n";
                    break;
                }else{
                    lockTransitive(&afn_creados[i], &automata, str, token);
                    afn_creados.push_back(automata);
                    used_n[i]=true;
                }
                break;
            }
            case 6:{//optional
                string str; int i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                cout<<"\t\tAFN al que le aplicará Opcional: ";
                cin>>names1;
                cout<<"\t\tNombre del AFN nuevo: ";
                cin>>str;
                iden cout<<"TOKEN: ";
                cin>>token;
                for(i=0; i<afn_creados.size(); i++)
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                if(!found0){
                    cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n";
                    break;
                }else{
                    optional(&afn_creados[i], &automata, str, token);
                    afn_creados.push_back(automata);
                    used_n[i]=true;
                }
                break; 
            }
            case 7:{//construction
                int n, i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                vector<string> str; string aux, s;
                vector<afn> forjoin;
                iden cout<<"Nombre de los AFNs que usará para construir el AFN para análisis léxico: ";
                while(cin>>aux)
                    str.push_back(aux);
                iden cout<<"Nombre del AFN nuevo: ";
                cin>>s;
                iden cout<<"Aviso: el valor de los TOKENs son los que ya tienen definidos los AFNs\n";
                for(i=0; i<afn_creados.size(); i++){
                    found0 = false;
                    for(j=0; j<str.size(); j++){
                        if(afn_creados[i].name == str[j] && !used_n[i]){
                            found0 = true;
                            forjoin.push_back(afn_creados[i]);
                        }else{
                            cout<<"Aun no ha construido un automata que eligio o ya se uso."
                                  " Vuelva a intentarlo.\n";
                            break;
                        }
                    }
                }
                if(found0){
                    joinAFN(forjoin, &automata, s);
                    afn_creados.push_back(automata);
                    for(j=0; j<str.size(); j++)
                        if(afn_creados[i].name == str[j])
                            used_n[i] = true;
                }
                break;
            }
            case 8:{//convert
                string str, salir, convertir; int n, i=-1, j=-1; bool found0=false, found1=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"AFDs que tiene: ";
                for(i=0; i<afd_creados.size(); i++)
                    if(!used_d[i])
                        cout<<afd_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"Nombre del AFN que desea convertir a AFD: ";
                cin>>names1;
                iden cout<<"Nombre del AFD nuevo: ";
                cin>>str;
                iden cout<<"Aviso: el valor de los TOKENs son los que ya estan definidos en el AFN\n";
                for(i=0; i<afn_creados.size(); i++){
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                }
                if(!found0){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                               "Vuelva a intentarlo.\n"; 
                    break;
                }else{
                    convert_afn2afd(&afn_creados[i], &solve, str);
                    afd_creados.push_back(solve);
                    used_d.push_back(false);
                    used_n[i] = true;
                }
                iden cout<<"Para regresar al menú presione cualquier letra seguido de ENTER: ";
                cin>>salir;
                break;
            }
            case 9:{//validate string
                string cadena, salir; int i; bool found0=false, resp=false;
                iden cout<<"AFNs que tiene: ";
                for(i=0; i<afn_creados.size(); i++)
                    if(!used_n[i])
                        cout<<afn_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"Nombre del AFN que desea usar para Validar una cadena: ";
                cin>>names1;
                iden cout<<"Cadena que se validará: ";
                cin>>cadena;
                for(i=0; i<afn_creados.size(); i++){
                    if(afn_creados[i].name == names1 && !used_n[i]){
                        found0 = true;
                        break;
                    }
                }
                if(!found0){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                          "Vuelva a intentarlo.\n"; 
                    break;
                }else{
                    resp = validateString_afn(cadena, &afn_creados[i]);
                    if(resp){
                        iden cout<<"La cadena: "<<cadena<<" fue aceptada por el autómata "<<names1<<"\n";
                        
                    }else{
                        iden cout<<"La cadena: "<<cadena<<" NO fue aceptada por el autómata "<<names1<<"\n";
                    }
                    iden cout<<"Para regresar al menú presione cualquier letra seguido de ENTER: ";
                    cin>>salir;
                }
            }
            case 10:{//yylex
                int i, token_p; string str, ss="", salir, aux; bool found0 = false;
                iden cout<<"AFDs que tiene: ";
                for(i=0; i<afd_creados.size(); i++)
                    if(!used_d[i])
                        cout<<afd_creados[i].name<<" ";
                cout<<endl;
                iden cout<<"Nombre del AFD que desea usar: ";
                cin>>str;
                for(i=0; i<afd_creados.size(); i++){
                    if(afd_creados[i].name == str && !used_d[i]){
                        found0 = true;
                        break;
                    }
                }
                if(!found0){
                    iden cout<<"Aun no ha construido ese autómata o ya se uso: "<<names1<<". "
                               "Vuelva a intentarlo.\n"; 
                    break;
                }else{
                    iden cout<<"Cadena a analizar: ";
                    cin>>aux;
                    token_p = yylex(caracter_actual, edo_actual, inilexema, finlexema, ac, aux, &solve, ss);
                    do{
                        token_p = yylex(caracter_actual, edo_actual, inilexema, finlexema, ac, aux, &solve, ss);
                        iden cout<<"return token: "<<token_p<<endl;
                        iden cout<<"yytext : "<<ss<<endl;
                    }while(token_p && finlexema!=aux.size()-1);
                }
                cout<<endl;
                iden cout<<"Para regresar al menú presione cualquier letra seguido de ENTER: ";
                cin>>salir;
                break;
            }
        }
        //system("clear");
    }while(op!=11 && op>-1 && op <11);

    return 0;
}
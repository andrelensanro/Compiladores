#include<bits/stdc++.h>
using namespace std;
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

void ini_n(node *nodo){
    nodo->val=-1;        
    nodo->initial = false;
    nodo->end = false;
    nodo->transiLink = {};
    nodo->token = 0;
}
void ini_afn(afn *afn_0){
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
    afd_0->A_initial.token = 0;
    afd_0->delta = {};
    afd_0->alphabet = {};
    afd_0->ends = {};
    afd_0->states = {};
    afd_0->number_states=0;
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
void hacerDeltaAfn(afn *nuevo, node *nodo){
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
    for(int i=0; i<nodo->transiLink.size(); i++){
        sim z; z.a = nodo->transiLink[i].first.a;
               z.b = nodo->transiLink[i].first.b;
        if(!existsTransition(nuevo->delta, nodo->val, z, nodo->transiLink[i].second))
            nuevo->delta.push_back(make_pair(nodo->val, make_pair(z, nodo->transiLink[i].second)));
    }
}
void renameNodes(afn *uno, afn *dos, int flag){
    int nodos_uno = uno->states.size()+flag;
    map<int,int> newsValores;   
    for(int i=0; i<dos->states.size(); i++){
        newsValores[dos->states[i].val] = nodos_uno+dos->states[i].val;//ya los guarde 
        dos->states[i].val = newsValores[dos->states[i].val];//cambio su conjunto states
    }
    for(int i=0; i<dos->states.size(); i++){//por cada nodo 
        for(int j=0; j<dos->states[i].transiLink.size(); j++){//por cada transicion de cada nodo
            dos->states[i].transiLink[j].second = newsValores[dos->states[i].transiLink[j].second];//estos son los destinos
        }
    }
    dos->A_initial.val = newsValores[dos->A_initial.val];//cambio su inicial
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
        }
    }
}
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
void vaciarAFN(afn *viejo, afn *nuevo){
    ini_afn(nuevo);
    /*vaciando datos de nodo inicial*/
    vaciarDatosNodo(&nuevo->A_initial, viejo->A_initial);
    /*vaciando alfabeto*/
    for(auto a: viejo->alphabet)
        nuevo->alphabet.push_back(a);
    /*vaciando delta*/
    for(auto d: viejo->delta)
        nuevo->delta.push_back(d);
    /*vaciando finales*/
    for(auto &e: viejo->ends)
        nuevo->ends.push_back(e);
    /*vaciando estados*/
    for(auto &s: viejo->states)
        nuevo->states.push_back(s);
    nuevo->name = viejo->name;
    nuevo->number_states = viejo->number_states;
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
vector<int> lockEpsilon(afn *uno, node *nodo){
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
void renumerarUno(afn *uno){
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
}
void join(afn *uno, afn *dos, afn *tres, string str, int token){
    renumerarUno(uno);
    node new_initial, new_end; 
    char epsilon = 51;
    ini_n(&new_initial);
    ini_n(&new_end);
    ini_afn(tres);
    new_initial.initial=true;
    new_end.end=true;
    new_end.token=token;
    renameNodes(uno, dos, 1);//respecto a los nodos que tenga uno, seran los .val de los nodos que tenga dos
    int t_nodes = uno->states.size() + dos->states.size();
    new_initial.val = 0;
    new_end.val = t_nodes + 1;
    sim z; z.a = epsilon; z.b = epsilon;
    new_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    new_initial.transiLink.push_back(make_pair(z, dos->A_initial.val));
    for(int i=0; i<uno->ends.size(); i++){
        uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
        updateNode(uno->states, &uno->ends[i]);
    }
    for(int i=0; i<dos->ends.size(); i++){
        dos->ends[i].transiLink.push_back(make_pair(z, new_end.val));
        updateNode(dos->states, &dos->ends[i]);
    }
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, new_initial);
    for(auto a: uno->alphabet) tres->alphabet.push_back(a);
    for(auto a: dos->alphabet) tres->alphabet.push_back(a);
    tres->states.push_back(new_initial);
    tres->ends.push_back(new_end);
    tres->states.push_back(new_end);
    deselectInitial(uno);
    deselectEnd(uno);
    deselectInitial(dos);
    deselectEnd(dos);
    for(int i=0; i<uno->states.size(); i++) tres->states.push_back(uno->states[i]);
    for(int i=0; i<dos->states.size(); i++) tres->states.push_back(dos->states[i]);
    for(int i=0; i<uno->states.size(); i++) hacerDeltaAfn(tres, &uno->states[i]);
    for(int i=0; i<dos->states.size(); i++) hacerDeltaAfn(tres, &dos->states[i]);
    hacerDeltaAfn(tres, &new_initial);
    hacerDeltaAfn(tres, &new_end);  
}
void concatenate(afn *uno, afn *dos, afn *tres, string str, int token){// uso rename Nodos
    renameNodes(uno, dos, -1);
    for(int i=0; i<dos->A_initial.transiLink.size(); i++){
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
    deselectEnd(uno);
    tres->name = str;
    vaciarDatosNodo(&tres->A_initial, uno->A_initial);
    for(auto a: uno->alphabet) tres->alphabet.push_back(a);
    for(auto b: dos->alphabet) tres->alphabet.push_back(b);
    for(int i=0; i<uno->states.size(); i++){
        tres->states.push_back(uno->states[i]);
        hacerDeltaAfn(tres, &uno->states[i]);
    }
    for(int i=0; i<dos->states.size(); i++)
        if(!dos->states[i].initial){
            tres->states.push_back(dos->states[i]);
            hacerDeltaAfn(tres, &dos->states[i]);
        }
    for(int i=0; i<dos->ends.size(); i++) tres->ends.push_back(dos->ends[i]);
    tres->number_states = uno->states.size() + dos->states.size() - 1;
}
void lockTransitive(afn *uno, afn *dos,string name, int token){
    renumerarUno(uno);
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
    sim z; z.a = epsilon; z.b = epsilon;
    dos->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
    uno->ends[0].transiLink.push_back(make_pair(z, uno->A_initial.val));
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet) dos->alphabet.push_back(a);
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
    renumerarUno(uno);
    char epsilon = 51;
    node new_end;
    ini_n(&dos->A_initial);
    ini_n(&new_end);
    ini_afn(dos);
    dos->A_initial.val = 0;
    new_end.val = uno->states.size() + 1;
    dos->A_initial.initial=true;
    new_end.end = true;
    new_end.token=token;
    uno->A_initial.initial=false;
    sim z; z.a = epsilon; z.b = epsilon;
    dos->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    dos->A_initial.transiLink.push_back(make_pair(z, new_end.val));
    for(int i=0; i<uno->ends.size(); i++)
        uno->ends[i].transiLink.push_back(make_pair(z, new_end.val));
    uno->ends[0].transiLink.push_back(make_pair(z, uno->A_initial.val));
    updateNode(uno->states, &uno->ends[0]);
    dos->name = name;
    for(auto a: uno->alphabet) dos->alphabet.push_back(a);
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
void optional(afn *uno, afn *solve, string name, int token){ // modifique los valores de los nodos, pero aun así no me da
    renumerarUno(uno);
    char epsilon = 51;
    node new_end;
    ini_n(&solve->A_initial);
    ini_n(&new_end);
    ini_afn(solve);
    solve->A_initial.val = 0;
    new_end.val = uno->states.size() + 1;
    solve->A_initial.initial=true;
    new_end.end = true;
    new_end.token = token;
    uno->A_initial.initial=false;
    sim z; z.a = epsilon; z.b = epsilon;
    solve->A_initial.transiLink.push_back(make_pair(z, uno->A_initial.val));
    solve->A_initial.transiLink.push_back(make_pair(z, new_end.val)); // transicion de opcional
    uno->ends[0].end = false;
    uno->ends[0].transiLink.push_back(make_pair(z, new_end.val));
    updateNode(uno->states, &uno->ends[0]);
    solve->name = name;
    for(auto a: uno->alphabet)
        solve->alphabet.push_back(a);
    deselectEnd(uno);
    deselectInitial(uno);
    for(int i=0; i<uno->states.size(); i++){
        solve->states.push_back(uno->states[i]);
        hacerDeltaAfn(solve, &uno->states[i]);
    }
    solve->states.push_back(solve->A_initial);
    hacerDeltaAfn(solve, &solve->A_initial);
    solve->states.push_back(new_end);
    hacerDeltaAfn(solve, &new_end);
    solve->ends.push_back(new_end);
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
    n1.transiLink.push_back(make_pair(z, n2.val));//{'a', 1} en el nodo 1 se guarda que con 'a' viaja al nodo 2
    vaciarDatosNodo(&nuevo->A_initial, n1);
    nuevo->alphabet.push_back(z);
    nuevo->states.push_back(n1);
    nuevo->states.push_back(n2);
    hacerDeltaAfn(nuevo, &n1);
    hacerDeltaAfn(nuevo, &n2);
    nuevo->ends.push_back(n2);
    nuevo->number_states = 2;
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
            if(change_val.count(exp[i].delta[j].first)==0){
                change_val[exp[i].delta[j].first] = count;
                count++;
            }
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
}
void convert_afn2afd(afn *c_afn, afd *s_afd, string name){
    set<set<int>> s_i;
    vector<int> s = lockEpsilon(c_afn, &c_afn->A_initial); set<int> s0 = convert2Set(s);
    queue<set<int>> q;
    vector<pair<int, int>> finals;
    for(int i=0; i<c_afn->ends.size(); i++){
        finals.push_back(make_pair(c_afn->ends[i].val, c_afn->ends[i].token));
    }
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
        if(!existsChar(a, s_afd->alphabet))
            s_afd->alphabet.push_back(a);
    while(!q.empty()){
        set<int> tope = q.front(); vector<int> tope_ = convert2vector(tope);
        ini_n(&n);
        n.val = m[tope];
        if(n.val==0)
            n.initial=true;
        for(auto alpha : s_afd->alphabet){
            vector<int> w = go_to(tope_, alpha.a, c_afn); 
            set<int> w_ = convert2Set(w);
            if(s_i.count(w_)==0 && w_.size()!=0){
                if(!existsPair(alpha, s_i.size(), n.transiLink))
                    n.transiLink.push_back(make_pair(alpha, s_i.size()));
                else
                    continue;
                m[w_] =  s_i.size();
                s_i.insert(w_);
                q.push(w_);
            }else if(w_.size()){
                if(!existsPair(alpha, m[w_], n.transiLink))// estoy mirando su 
                    n.transiLink.push_back(make_pair(alpha, m[w_]));
                else
                    continue;                
            }
            hacerDeltaAfd(s_afd, &n);
        }  
        for(auto &a: m){
            for(auto &b: a.first){
                for(auto &x: finals){
                    if(b==x.first){
                        if(n.val==m[a.first]){
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
}
/*
int main(){

    return 0;
}
*/





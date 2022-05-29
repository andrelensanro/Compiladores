// D+!(.!D+)?
string convertirERinfija(string er_infija){
    //cout<<"entro a convertirERinfija\n"<<endl;
    map<char, int> precOper;
    precOper['|'] = 0;
    precOper['!'] = 1;//operador de concatenacion
    precOper['+'] = 2;
    precOper['*'] = 2;
    precOper['?'] = 2;
    precOper['('] = -1;
    precOper[')'] = -1;
    stack<char> operadores;
    string solve;
    char aux;
    bool flag = false;
    for(int i=0; i<er_infija.size(); i++){// L°(L|D)
        //cout<<"caracter actual: '"<<er_infija[i]<<"'"<<endl;
        if(precOper.count(er_infija[i+1])==1 && er_infija[i] == 92){/*si hay como substring \* \+ \- \/ \a 
        entonces diremos que es un operando, por lo tanto hay que meter \ a solve 
        */
            flag = true;
            solve.push_back(er_infija[i]);
            continue;
        }
        if(precOper.count(er_infija[i])==0 || flag){//es un operando
            //cout<<"corresponde a un operando, por lo tanto va solve\n";
            solve.push_back(er_infija[i]);
            flag = false;
        }else if(!flag){
            flag = false;
            if(er_infija[i]==')'){
                //cout<<"corresponde a ), por lo tanto saco los operandos hasta encontrar a (\n";
                while(!operadores.empty() && operadores.top()!='('){
                    aux = operadores.top();
                    solve.push_back(aux);
                    operadores.pop();
                }
                //cout<<"Falta sacar a (\n";
                operadores.pop();
                //cout<<"Ya lo saque\n";
            }else if(operadores.empty() || er_infija[i] == '('){
                //cout<<"como la pila esta vacia lo meto sin preocupacion o soy (\n";
                operadores.push(er_infija[i]);
            }else{
                aux = operadores.top();
                //cout<<"no esta vacia, por lo que tengo que ver mi tope: "<<aux<<endl;
                if(precOper[aux]<precOper[er_infija[i]]){
                    //cout<<"voy a caer en uno menor que yo :)"<<endl;
                    operadores.push(er_infija[i]);
                }else{
                    //cout<<"el que esta abajo de mí es mayor que yo :("<<endl;
                    solve.push_back(aux);
                    operadores.pop();
                    while(!operadores.empty() && precOper[operadores.top()]>= precOper[er_infija[i]]){
                        aux = operadores.top();
                        solve.push_back(aux);
                        operadores.pop();
                    }
                    operadores.push(er_infija[i]);
                }
            }
        }
    }
    while(!operadores.empty()){
        aux = operadores.top();
        solve.push_back(aux);
        operadores.pop();
    }
    //cout<<"sanglo de  a convertirERinfija\n"<<endl;
    return solve;
}

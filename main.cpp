#include <iostream>
#define TAM 50

//plantillas
class Pila{
private:
    std::string datos[TAM],elem;
    int ult;
    bool inserta(std::string , int);
    bool elimina(int);
    std::string recupera(int)const;
    int primero()const;
    int ultimo()const;
    void imprime()const;
public:
    Pila():ult(-1){}
    bool vacia()const;
    bool llena()const;
    int buscar(std::string);
    bool push(std::string);
    bool pop();
    int Precedencia(std::string);
    std::string InfijaAPostfija(std::string);
    std::string top()const;

    bool operator==(const Pila& otro) const { return elem == otro.elem && datos == otro.datos; }
    bool operator!=(const Pila& otro) const { return !(*this == otro); }
};

std::string Pila::top()const{
    return datos[ult];
}

bool Pila::pop(){
    if(vacia()){
        return false;
    }
    else{
        elimina(ultimo());
    }
    return true;
}

bool Pila::push(std::string elem){
    if(llena()){
        return false;
    }
    if(vacia()){
        inserta(elem,0);
    }
    else{
        inserta(elem,ultimo()+1);
    }
    return true;
}

int Pila::buscar(std::string elem){
    int i=0;
    while(i<=ult){
        if(elem ==datos[i]){
            return i;
        }
        i++;
    }
    return -1;
}

void Pila::imprime()const{
    if(!vacia()){
        std::string x;
        for(int i=0; i<=ult; i++){
            x=datos[i];
            std::cout<<x<<std::endl;
        }
    }
}

bool Pila::vacia()const{
    return ult==-1;
}
bool Pila::llena()const{
    return ult==TAM-1;
}

bool Pila::inserta(std::string elem, int pos){
    if(llena() || pos<0 || pos>ult+1){
        std::cout<<"\n No se pudo insertar";
        return false;
    }
    int i=ult+1;
    while(i>pos){
        datos[i]=datos[i-1];
        i--;
    }
    datos[pos]=elem;
    ult++;
    return true;
}

bool Pila::elimina(int pos){
    if(vacia() || pos<0 || pos>ult){
        std::cout<<"\n No se pudo eliminar";
        return false;
    }
    int i=pos;
    while(i<ult){
        datos[i]=datos[i+1];
        i++;
    }
    ult--;
    return true;
}

std::string Pila::recupera(int pos)const{
    if(vacia() || pos<0 || pos>ult-1){
        std::cout<<"\n Insuficiencia de datos";
        //Manejar exceptions
    }
    else{
       return datos[pos];
    }
}

int Pila::primero()const{
    if(vacia()){
       return -1;
    }
    return 0;
}
int Pila::ultimo()const{
    if(vacia()){
       return -1;
    }
    return ult;
}


//funciones nuevas
int Pila::Precedencia(std::string c){
    if(c == "*" || c == "/")
        return 2;
    else if(c == "+" || c == "-")
        return 1;
    else
        return -1;
}

std::string Pila::InfijaAPostfija(std::string notacion){
    std::string resultado = "",elem;

    for(int i = 0; i < notacion.size(); i++){
            elem = notacion[i];

        if(elem >= "a" && elem <= "z")
            resultado += elem;

        else if(elem == "(")
        {
            push(elem);
        }

        else if(elem == ")"){
            while(top() != "("){
                resultado += top();
                pop();
            }
            pop();
        }
        else{
            while(Precedencia(top()) >= Precedencia(elem)){
                resultado += top();
                pop();
            }
            push(elem);
        }
    }

    while(!vacia()){
        resultado += top();
        pop();
    }

    return resultado;
}

int main()
{
    int i,j,tamanio;
    Pila MiPila;
    std::string notacion,elem;
    std::cout<<"Ingresa la notacion infija"<<std::endl;
    std::cin>>notacion;
    std::string postfija = MiPila.InfijaAPostfija(notacion);
    std::cout << "Expresion postfija: " << postfija << std::endl;
    return 0;
}

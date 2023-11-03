/*
Desarrollar una Aplicación que deba calcular una ruta basada en los medios de transporte habituales.
El usuario puede elegir entre tres opciones:
    • Peatón (ConcreteStrategyA)
    • Coche (ConcreteStrategyB)
    • Transporte público (ConcreteStrategyC)

El patrón de diseño strategy permite establecer en tiempo de ejecución el rol de
comportamiento de una clase. Strategy se basa en el polimorfismo para
implementar una serie de comportamientos que podrán ser intercambiados
durante la ejecución del programa, logrando con esto que un objeto se pueda
comportar de forma distinta según la estrategia establecida.
*/

#include <iostream>

using namespace std;

//Creo la clase abstracta Strategy que va a ser implementada por cada medio de transporte que agregue a la aplicación
class StrategyTravel
{       public:
        virtual void viajar() = 0;    
        //La dejo virtual por si después quiero implementar la función miembro de manera diferente en las clases concretas
        virtual int calcularDistancia(int coordenadasOrigen, int coordenadasDestino)
        {
            int distancia = coordenadasDestino - coordenadasOrigen;
            return distancia;
        }
};
//Implementación de la estrategia del transporte para el peatón

class Peaton:public StrategyTravel
{
    public:
        void viajar()
        {
        cout << "caminando" << endl;
        }
       
};
class Coche:public StrategyTravel
{
    public:
        void viajar()
        {
            cout << "viajando en automovil" << endl;
        }
};

class TransportePublico:public StrategyTravel
{
    public:
        void viajar()
        {
            cout << "viajando en colectivo" << endl;
        }
};

//Creo la clase Contexto, que tiene una relación de agregación con strategy
class UsuarioTransporte
{
    private:
        string nombre;
        string genero;
        int edad;
        /*
        Aca va la agregación, tengo que "apuntar" a la clase abstracta o interfaz Strategy
        Con la instancia "dentro", puedo usar los métodos de la clase
        Y el puntero me permite elegir en tiempo de ejecución que estrategia implementada en las clases derivadas usar.
        Al apuntar a la interfaz o clase abstracta, puedo elegir cualquiera de sus implementaciones en las clases derivadas,
        esto es el POLIMORFISMO DE SUBTIPADO.
        */
        StrategyTravel* strategyTravel;//Instancio un objeto de la clase StrategyTravel
    public:
        //Creo el constructor para poder inicializar la clase
        UsuarioTransporte(string _nombre,string _genero,int _edad)
        {
            nombre = _nombre;
            genero = _genero;
            edad = _edad;
        }
    
        //Función que tiene como parámetro una variable del tipo puntero que "apunta" a la clase StrategyTravel
        void elegirEstrategia(StrategyTravel* strategyTravel)
        {
            this->strategyTravel = strategyTravel;
        }
        void mostrarInfo()
        {
            cout << "El usuario " << nombre << " de genero " << genero << " y edad " << edad << endl;
        }
        //Esta es la función miembro que hace que tenga sentido aplicar el patrón strategy, hace que
        //un usuario pueda "elegir" la estrategia que proviene del encapsulamiento del comportamiento del módulo
        //abstracto Strategy y a traves de él, acceder a las estrategias concretas. Tambien es lo que le da flexibilidad
        //al código, ya que puedo agregar un comportamiento específico con solo agregar un modulo concreto a la interfaz Strategy 
        void viajar()
        {
            strategyTravel->viajar();
        }

};


int main()
{   
    //Creo una instancia de UsuarioTransporte con un puntero que apunte a una variable para poder
    //asignarle datos en tiempo de ejecución, logrando mayor flexibilidad
    UsuarioTransporte *ptrPersona1 = new UsuarioTransporte("Juancho","Masculino", 45);

    //Creo un puntero que apunta a la clase base abstracta, y creo en memoria dinámica un objeto del tipo TransportePublico
    //Que tiene métodos que me intesa usar
    StrategyTravel* ptrEstrategiaTransporte = new TransportePublico(); 

    //Uso la función que muestra por pantalla los datos del usuario
    ptrPersona1->mostrarInfo();
    ptrEstrategiaTransporte->viajar(); 
    //Uso el puntero para apuntar a un objeto de una clase derivada distinta
    ptrEstrategiaTransporte = new Peaton();
    
    ptrPersona1->elegirEstrategia(ptrEstrategiaTransporte);
    
    
    
    //Con esto aplico polimorfismo de subtipado
    ptrEstrategiaTransporte->viajar();
       
    //Limpieza de memoria
    delete ptrEstrategiaTransporte;
    delete ptrPersona1;
    
    return 0;
}
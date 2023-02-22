/*! 
    @author Francesco Ercolino 
    @brief Programma in linguaggio C++ che simula una gara di kitesnowboarding 
    @brief determina il podio tramita la generazione casuale delle coordinate degli atleti
    @file Coordinate.cpp
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#define NOMEfile "dati.txt"
using namespace std;


//Dichiarazione struct
/*!
    @struct DatiAtleta
    @brief Contiene i dati dell'atleta
    @param Matricola Contine il numero matricola dell'atleta
    @param Cognome Contine il cognome inserito dall'utente dell'atleta
*/
struct DatiAtleta
{
    string Matricola;
    string Cognome;
} Dati[100];


//Dichiarazione globale di stringhe che servono in varie funzioni
string max_cognome, secondo_max_cognome, terzo_max_cognome;

// Dichiarazione anticipata della funzioni
void GeneraRiempi(DatiAtleta* p_Dati, int cont, fstream& f);
void CalcolaPodio(DatiAtleta* p_Dati, int cont);

/*!
    @brief Simula l'animazione di salvataggio dopo che l'utente 
    @brief ha inserito i cognomi degli atleti e le coordinate sono state generate
    @param fileName Parametro che si riferisce al nome del file utilizzato 
*/
//Funzione che stampa la simulazione del salvataggio
void Salvataggio(const std::string& fileName) 
{
    system("clear");
    cout<<"\n\n";
    
    for(int i = 0; i <= 100; i++) 
    {
        cout << "\r Salvataggio dei dati in corso... " << i << "% [";
        
        int numBarre = (int)(i / 5);
        int numSpazi = 20 - numBarre;
        
        /*! @brief Cicli di visualizzazione barra di caricamento */
        for (int j = 0; j < numBarre; j++) { cout << "#"; }
        
        for (int j = 0; j < numSpazi; j++) { cout << " "; }
        
        cout << "]";

        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout<<"\n Dati salvati sul file "<<fileName<<"!"<<endl;
}


//Funzione che calcola il podio
/*!
    @brief Funzione che calcola il podio vincente prelevando i dati dal file testuale dati.txt
    @param p_Dati Importazione vettore strutturato
    @param cont Importazione della variabile per gestire gli elementi della struct
*/
void CalcolaPodio(DatiAtleta* p_Dati, int cont) 
{
    ifstream f(NOMEfile);

    //Dichiarazione variabili
    string appoggio, matricola, risultato, n_cord, nome;
    int max = 0, secondo_max = 0, terzo_max = 0;

    //Acquisizione dal file dei dati
    while (getline(f, nome, ',') && getline(f, matricola, ',') && getline(f, risultato, ',') && getline(f, n_cord)) 
    {
        // Converte il risultato in un numero intero
        /*! @brief Converte il risultato in formato stringa preso dal file testuale in intero per permettere di calcolare il podio*/
        int int_risultato = std::stoi(risultato);

        /*! @brief Calcolo del podio */
        // Calcola il podio
        if (int_risultato > max) 
        {
            terzo_max = secondo_max;
            terzo_max_cognome = secondo_max_cognome;
            secondo_max = max;
            secondo_max_cognome = max_cognome;
            max = int_risultato;
            max_cognome = nome;
        } 
        else if (int_risultato > secondo_max) 
        {
            terzo_max = secondo_max;
            terzo_max_cognome = secondo_max_cognome;
            secondo_max = int_risultato;
            secondo_max_cognome = nome;
        } 
        else if (int_risultato > terzo_max) 
        {
            terzo_max = int_risultato;
            terzo_max_cognome = nome;
        }

        // Trova il cognome dell'atleta con il risultato e il numero di coordinate generate più alto
        int int_n_cord = std::stoi(n_cord);
        
        if (int_risultato == max && int_n_cord > std::stoi(p_Dati[cont].Matricola)) 
            max_cognome = nome;
        
    }
}


/*! @brief Funzione che permette di visualizzare il podio dopo aver calcolato le posizioni */
//Funzione che visualizza il podio
void VisualizzaPodio()
{
    string appoggio;
    
    cout<<"\n Il podio è pronto! Premi ENTER per visualizzare la classifica finale...";
    cin.ignore();
    getline(cin, appoggio); // aspetta l'input dell'utente
    cout << "\n\n Podio finale :\n"
    << " 1. " << max_cognome << endl
    << " 2. " << secondo_max_cognome << endl
    << " 3. " << terzo_max_cognome << endl;
}

/*! @brief Funzione che si occupa di prendere da input dell'utente i cognomi inseriti e inserirli nel file dati.txt */
//Funzione che fa inserire il cognome dell'atleta all'utente e crea / sovrascrive il file "dati.txt"
void InserisciDati()
{
    /*! @param p_Dati Vettore puntatore strutturato che punto al vettore strutturato Dati*/
    DatiAtleta* p_Dati = &Dati[0];

    fstream f(NOMEfile, ios::app);

    system("clear");

    char continua = 's';
    int cont = 0;

    //Ciclo di input cognome e inserimento nel file 
    while(continua=='s')
    {
        cin.ignore();
        
        if(cont==0)
            system("clear");

        //Inserimento cognome dell'atleta
        cout<<"\n INSERIMENTO COGNOME ATLETI :\n\n";
        cout<<" Cognome atleta n."<<cont+1<<" : ";

        //Riempimento vettore e scrittura sul file
        getline(cin, p_Dati[cont].Cognome);

        //Genera le coordinate che si riferiscono all'atleta inserito
        GeneraRiempi(p_Dati, cont, f);
        CalcolaPodio(p_Dati, cont);

        cout<<" Continuare l'inserimento? (s/n) : ";
        cin>>continua;
        
        system("clear");


        //Controllo sulla validità della scelta inserita
        if(continua=='s'||continua=='n') {
           cont++;

           if(continua=='n')
           {
                //Salvataggio finale e animazione salvataggio
                f.close();
                Salvataggio(NOMEfile);
                VisualizzaPodio();
           }
        }
        else {
            cout<<"\a\n La scelta inserita non è tra quelle valide!";
            cin.clear();
            cin.ignore();
        }
    }
}

/*! 
    @brief Funzione che si occupa di generare le coordinate per ogni atleta e inserirle nel file dati.txt
    @param p_Dati Importazione vettore strutturato per riempire la struct
    @param cont Importazione della variabile per gestire gli elementi della struct
    @param f Importazione variabile file per sovrascrivere il file dati.txt
*/
//Funzione che genera i dati e riempie la struct
void GeneraRiempi(DatiAtleta* p_Dati, int cont, fstream& f)
{
    //Generazione coordinate
    int n_Matricola = rand()%1000+1;
    int n_cord = rand()%10+1;
    float n_cordX1 = rand()%100+1;
    float n_cordX2 = rand()%100+1;
    float n_cordY1 = rand()%100+1;
    float n_cordY2 = rand()%100+1;


    //Elevamento a potenza coordinate
    float pow_x1 = pow(n_cordX1, 2);
    float pow_x2 = pow(n_cordX2, 2);
    
    float pow_y1 = pow(n_cordY1, 2);
    float pow_y2 = pow(n_cordY2, 2);


    //Calcolo risultato con la formula della distanza tra due punti
    int risultato = sqrt((pow_x1-pow_x2)+(pow_y1-pow_y2));

    //Conversione a stringa 
    p_Dati[cont].Matricola = to_string(n_Matricola);

    //Scrittura sul file 
    f<<p_Dati[cont].Cognome<<","
     <<p_Dati[cont].Matricola<<","
     <<risultato<<","
     <<n_cord<<endl;
}


//Funzione principale
int main()
{
    cout<<"\n Benvenuto alla gara di KiteSnowboarding!\n\n Premi ENTER per inserire i cognomi degli atleti...";
    InserisciDati();

    return 0;
}
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
struct DatiAtleta
{
    string Matricola;
    string Cognome;
} Dati[100];


//Dichiarazione globale di stringhe che servono in varie funzioni
string max_cognome, secondo_max_cognome, terzo_max_cognome;

// Dichiarazione anticipata della funzione GeneraRiempi
void GeneraRiempi(DatiAtleta* p_Dati, int cont, fstream& f);
void CalcolaPodio(DatiAtleta* p_Dati, int cont);


//Funzione che stampa la simulazione del salvataggio
void Salvataggio(const std::string& fileName) 
{
    for(int i = 0; i <= 100; i++) 
    {
        cout << "\rSalvataggio dei dati in corso... " << i << "% [";
        
        int numBarre = (int)(i / 5);
        int numSpazi = 20 - numBarre;
        
        for (int j = 0; j < numBarre; j++) { cout << "#"; }
        
        for (int j = 0; j < numSpazi; j++) { cout << " "; }
        
        cout << "]";

        this_thread::sleep_for(chrono::milliseconds(50));
    }
    std::cout << "\nDati salvati sul file " << fileName << std::endl;
}


//Funzione che calcola il podio
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
        int int_risultato = std::stoi(risultato);

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


//Funzione che visualizza il podio
void VisualizzaPodio()
{
  cout << " Podio:\n";
  cout << " 1. " << max_cognome << endl;
  cout << " 2. " << secondo_max_cognome << endl;
  cout << " 3. " << terzo_max_cognome << endl;
}


//Funzione che fa inserire il cognome dell'atleta all'utente e crea / sovrascrive il file "dati.txt"
void InserisciDati()
{
    DatiAtleta* p_Dati = &Dati[0];

    fstream f(NOMEfile, ios::app);

    system("clear");

    char continua = 's';
    int cont = 0;

    //Ciclo di input cognome e inserimento nel file 
    while(continua=='s')
    {
        cin.ignore();

        //Inserimento cognome dell'atleta
        cout<<" Cognome atleta n."<<cont+1<<" : ";

        //Riempimento vettore e scrittura sul file
        getline(cin, p_Dati[cont].Cognome);

        //Genera le coordinate che si riferiscono all'atleta inserito
        GeneraRiempi(p_Dati, cont, f);
        CalcolaPodio(p_Dati, cont);

        cout<<" Continuare l'inserimento? (s/n) : ";
        cin>>continua;


        //Controllo sulla validità della scelta inserita
        if(continua=='s'||continua=='n') {
           cont++;

           if(continua=='n') {
                
                //Salvataggio finale e animazione salvataggio
                f.close();
                Salvataggio(NOMEfile);
                VisualizzaPodio();
           }
        }
        else {
            cout<<"\a La scelta inserita non è tra quelle valide!";
            cin.clear();
            cin.ignore();
        }
    }
}

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
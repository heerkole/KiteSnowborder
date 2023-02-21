#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#define NOMEfile "dati.txt"
using namespace std;

struct DatiAtleta
{
    string Matricola;
    string Cognome;
} Dati[100];


// Dichiarazione anticipata della funzione GeneraRiempi
void GeneraRiempi(DatiAtleta* p_Dati, int cont, fstream& f);
void CalcolaPodio(DatiAtleta* p_Dati, int cont);

void InserisciDati()
{
    DatiAtleta* p_Dati = &Dati[0];

    fstream f(NOMEfile, ios::app);

    system("cls");

    char continua = 's';
    int cont = 0;

    while(continua=='s')
    {
        cin.ignore();

        //inserimento cognome dell'atleta
        cout<<" Cognome atleta n."<<cont+1<<" : ";

        //Riempimento vettore e scrittura sul file
        getline(cin, p_Dati[cont].Cognome);

        //Genera le coordinate che si riferiscono all'atleta inserito
        GeneraRiempi(p_Dati, cont, f);

        cout<<" Continuare l'inserimento? (s/n) : ";
        cin>>continua;


        //Controllo sulla validità della scelta inserita
        if(continua=='s'||continua=='n') {
           cont++;

           if(continua=='n') {
                //salvataggio
                CalcolaPodio(p_Dati, cont);
                f.close();
                cout<<"Dati salvati su file "<<NOMEfile<<endl;
               
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


    //Calcolo risultato
    int risultato = sqrt((pow_x1-pow_x2)+(pow_y1-pow_y2));

    p_Dati[cont].Matricola = to_string(n_Matricola);


    f<<p_Dati[cont].Cognome<<","
     <<p_Dati[cont].Matricola<<","
     <<risultato<<","
     <<n_cord<<endl;
    
    
}

void CalcolaPodio(DatiAtleta* p_Dati, int cont)
{
    ifstream f(NOMEfile);

    string appoggio, nome;
    int matricola, risultato, n_Cord, max = 0, secondo_max = 0, terzo_max = 0;
    string max_cognome, secondo_max_cognome, terzo_max_cognome;

    while(getline(f, nome, ',') && getline(f, appoggio, ',') && getline(f, appoggio, ',') && getline(f, appoggio))
    {
        matricola = stoi(appoggio);
        risultato = stoi(appoggio);
        n_Cord = stoi(appoggio);

        // Calcola il podio
        if (risultato > max)
        {
            terzo_max = secondo_max;
            terzo_max_cognome = secondo_max_cognome;
            secondo_max = max;
            secondo_max_cognome = max_cognome;
            max = risultato;
            max_cognome = nome;
        }
        else if (risultato > secondo_max)
        {
            terzo_max = secondo_max;
            terzo_max_cognome = secondo_max_cognome;
            secondo_max = risultato;
            secondo_max_cognome = nome;
        }
        else if (risultato > terzo_max)
        {
            terzo_max = risultato;
            terzo_max_cognome = nome;
        }

        // Trova il cognome dell'atleta con il risultato e n_Cord più alti
        if (risultato == max && n_Cord > stoi(p_Dati[cont].Matricola))
        {
            max_cognome = nome;
        }
    }

    cout << "Podio:\n";
    cout << "1. " << max_cognome << endl;
    cout << "2. " << secondo_max_cognome << endl;
    cout << "3. " << terzo_max_cognome << endl;
}

int main()
{
    cout<<" Benvenuto alla gara di KiteSnowboarding!\n\n Premi ENTER per inserire i cognomi degli atleti...";
    InserisciDati();

    return 0;
}

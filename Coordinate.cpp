#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#define NOMEfile "dati.txt"
using namespace std;

struct DatiAtleta
{
    int Matricola;
    string Cognome;
} Dati[100];


// Dichiarazione anticipata della funzione GeneraRiempi
void GeneraRiempi(DatiAtleta* p_Dati, int cont, fstream& f);


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
    srand(time(NULL));

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


    //Riempimento struct con i dati 
    p_Dati[cont].Matricola = n_Matricola;


    //Scrittura sul file dei dati 
    f<<p_Dati[cont].Cognome<<","
     <<p_Dati[cont].Matricola<<","
     <<risultato<<","
     <<n_cord<<endl;
     
    f.close();
    cout<<" Dati inseriti correttamente";
}



int main()
{
    cout<<" Benvenuto alla gara di KiteSnowboarding!\n\n Premi ENTER per inserire i cognomi degli atleti...";
    InserisciDati();

    return 0;
}

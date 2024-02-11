#include <iostream>
#include <climits>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

struct studentas
{
    string vardas;
    string pavarde;
    vector<int> ND; 
    int EGZ;
    double GalutinisV;
    double GalutinisM;
};

int main()
{
    int m, n;
    cout << "Iveskite studentu skaicius: ";
    cin >> m;

    cout << endl << "Iveskite namu darbu skaiciu: ";
    cin >> n; 
    
    cout << endl << "Kaip norite apskaiciuoti galutini bala? (iveskite m - jei su mediana, v su vidukriu) "; //balo apskaiciavimo budas
        char budas;
        cin >> budas;

    vector<studentas> C(m); 

    for (int i = 0; i < m; i++)
    {
         
        cout <<  "Iveskite studento varda ir pavarde: "; //vardas ir pavarde
        cin >> C[i].vardas >> C[i].pavarde;

        cout << endl << "Iveskite namu darbu rezultatus:"; //namu darbu rezultatu ivedimas
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            C[i].ND.push_back(temp); 
        }

        cout << endl << "Iveskite egzamino rezultata:"; 
        cin >> C[i].EGZ;//ivedamas egzamino balas


        if (budas == 'v') //galutinis balas apskaiciuojamas su vidurkiu
        {
            int suma = 0;
            double vid = 0.0;
            for (int j = 0; j < n; j++)
            {
                suma = suma + C[i].ND[j];
            }
            vid = suma * 1.0/ n ;
            C[i].GalutinisV = 0.4 * vid + 0.6 * C[i].EGZ;
            
        }
        if (budas == 'm') //galutinis balas apskaiciuojamas su mediana
        {
            int mediana;
            sort(C[i].ND.begin(), C[i].ND.end()); 
            if (n % 2 == 0)
            {
                int m1 = round(n / 2.0);
                int m2 = m1 - 1;
               C[i].GalutinisM = 0.4 *( (C[i].ND[m1] + C[i].ND[m2])/2.0 ) + 0.6 * C[i].EGZ;

            }
            else
            {
                mediana = round(n / 2.0) - 1;
                C[i].GalutinisM = 0.4 * C[i].ND[mediana] + 0.6 * C[i].EGZ;

            }   
            
        }
        cout << endl;
    }
    // rezultatu spausdinimas
    for (int i = 0; i < m; i++)
    {
      
        if (budas == 'v')
        {
            if (i == 0)
            {
                cout << endl << "Pavarde \t Vardas \t Galutinis (Vid. )" << endl;
                cout << "-----------------------------------------------" << endl;
            }
            cout << C[i].pavarde << " \t " << C[i].vardas << " \t " << setprecision(2) << C[i].GalutinisV << endl;
        }
        if (budas == 'm')
        {
            if (i == 0)
            {
                cout << endl << "Pavarde \t Vardas \t  Galutinis (Med. )" << endl;
                cout << "-------------------------------------------------" << endl;
            }
            cout << C[i].pavarde << " \t " << C[i].vardas << " \t " << setprecision(2) << C[i].GalutinisM << endl;
        }
    }
            return 0;
}

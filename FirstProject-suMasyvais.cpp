#include <iostream>
#include <climits>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>
#include <string>

using namespace std;
random_device rd;
mt19937 generuoti(random_device{}());
const int MAX_LENGTH = 11;
uniform_int_distribution<int> dis(1, 10);

uniform_int_distribution<int> dis_lytis(0, 1);
string vardaiV[] = { "Jonas", "Petras", "Antanas", "Juozas", "Kazys", "Darius", "Linas", "Tomas", "Giedrius", "Marius" };
string vardaiM[] = { "Ona", "Marytė", "Aldona", "Gabija", "Dalia", "Danute", "Asta", "Rasa", "Nijole", "Aiste", "Gabriele" };
string pavardesV[] = { "Jonaitis", "Petraitis", "Antanaitis", "Juozaitis", "Kaziukaitis", "Dariukaitis", "Linaitis", "Tomaitis", "Giedraitis", "Mariukaitis" };
string pavardesM[] = { "Jonaite", "Petraityte", "Antanaite", "Juozaite", "Kaziukaite", "Dariukaite", "Linaite", "Tomaite", "Giedraite", "Mariukaite" };

char TaipNePaz;
char TaipNe;

struct studentas
{
	string vardas;
	string pavarde;
	int* ND;
	int EGZ = 0;
	double GalutinisV = 0;
	double GalutinisM = 0;
	int n;//namu darbu kiekis
};

void GeneruotiVardusV(int m, studentas* S)
{
	S[m].vardas = vardaiV[dis(generuoti) % 10];
	S[m].pavarde = pavardesV[dis(generuoti) % 10];
}
void GeneruotiVardusM(int m, studentas* S)
{
	S[m].vardas = vardaiM[dis(generuoti) % 10];
	S[m].pavarde = pavardesM[dis(generuoti) % 10];
}
void rezultatai(int m, studentas* S)
{
	char budas;
	cout << endl << "Kaip norite apskaiciuoti galutini bala? (iveskite M - jei su mediana, V su vidukriu) ";
	cin >> budas;
	if (budas != 'M' && budas != 'V')//tikrinama ar ivestas tinkamas simbolis
	{
		bool ivedimas = false;
		while (ivedimas == false)
		{
			cout << "Ivestas netinkamas simbolis, bandykite dar karta (M/V):";
			cin >> budas;
			if (budas == 'M' || budas == 'V')
				ivedimas = true;
		}
	}

	if (budas == 'V')
	{

		for (int i = 0; i < m; i++)
		{
			double suma = 0.0;
			for (int j = 0; j < S[i].n; j++)
			{
				suma += S[i].ND[j];
			}
			S[i].GalutinisV = 0.4 * suma / S[i].n + 0.6 * S[i].EGZ;
		}
	}

	if (budas == 'M')
	{
		for (int i = 0; i < m; i++)
		{
			if (S[i].n - 1 == 0)
				S[i].GalutinisM = 0.4 * S[i].ND[0] + 0.6 * S[i].EGZ;

			if (S[i].n - 1 > 0)
			{
				sort(S[i].ND, S[i].ND + S[i].n);
				if (S[i].n % 2 == 0)
				{
					int m1 = round(S[i].n / 2);
					int m2 = m1 - 1;
					double medianaD = (S[i].ND[m1] + S[i].ND[m2]) / 2.0;
					S[i].GalutinisM = 0.4 * medianaD + 0.6 * S[i].EGZ;
				}
				if (S[i].n % 2 != 0)
				{
					int mediana = round(S[i].n / 2);
					S[i].GalutinisM = 0.4 * S[i].ND[mediana] + 0.6 * S[i].EGZ;
				}
			}


		}
	}
	//rezultatu spausdinimas
	for (int i = 0; i < m; i++)
	{
		if (budas == 'V')
		{
			if (i == 0)
				cout << endl << setw(5) << "Nr." << setw(25) << "Pavarde" << setw(25) << "Vardas" << setw(25) << "Galutinis (Vid.)" << endl << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

			cout << setw(5) << i + 1 << setw(25) << S[i].pavarde << setw(25) << S[i].vardas << setw(25) << setprecision(3) << S[i].GalutinisV << endl;
		}
		if (budas == 'M')
		{
			if (i == 0)
				cout << endl << setw(5) << "Nr." << setw(25) << "Pavarde" << setw(25) << "Vardas" << setw(25) << "Galutinis (Med.)" << endl << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

			cout << setw(5) << i + 1 << setw(25) << S[i].pavarde << setw(25) << S[i].vardas << setw(25) << setprecision(3) << S[i].GalutinisM << endl;
		}
	}
	for (int i = 0; i < m; i++)
		delete[] S[i].ND;
	delete[] S;
}

int main()
{

	cout << "Pasirinkite veiksma:\n 1. Suvesti visus studentu duomenis\n 2. Sugeneruoti tik studentu pazymius\n 3. Sugeneruoti studentu vardus ir pazymius\n Iveskite pasirinkimo numeri: ";
	int Pasirinkimas;
	cin >> Pasirinkimas;
	if (Pasirinkimas != 1 && Pasirinkimas != 2 && Pasirinkimas != 3)
	{
		bool ivedimas = false;
		while (ivedimas == false)
		{
			cout << "Ivestas netinkamas simbolis, bandykite dar karta:";
			if (Pasirinkimas == 1 || Pasirinkimas == 2 || Pasirinkimas == 3)
				ivedimas = true;
		}
	}
	int m = 0;
	if (Pasirinkimas == 1)
	{
		studentas* S = new studentas[MAX_LENGTH];
		do
		{
			cout << endl << "Iveskite studento varda ir pavarde: ";
			cin >> S[m].vardas >> S[m].pavarde;
			cout << endl << "Iveskite namu darbu pazymi: ";
			S[m].ND = new int[MAX_LENGTH];
			S[m].n = 0;
			do
			{
				int pazimys;
				cin >> pazimys;
				S[m].ND[S[m].n] = pazimys;
				S[m].n++;
				cout << "Ar norite ivesti dar viena pazymi? (T jei taip , N - ne): ";
				cin >> TaipNePaz;
				if (TaipNePaz != 'T' && TaipNePaz != 'N')//tikrinama ar ivestas tinkamas simbolis
				{
					bool ivedimas = false;
					while (ivedimas == false)
					{
						cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
						cin >> TaipNePaz;
						if (TaipNePaz == 'T' || TaipNePaz == 'N')
							ivedimas = true;
					}
				}
				if (TaipNePaz == 'T') cout << endl << "Iveskite namu darbu pazymi: ";
			} while (TaipNePaz == 'T');

			cout << endl << "Iveskite egzamino rezultata: ";
			cin >> S[m].EGZ;

			cout << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			m++;
			cin >> TaipNe;
			if (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				bool ivedimas = false;
				while (ivedimas == false)
				{
					cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
					cin >> TaipNe;
					if (TaipNe == 'T' || TaipNe == 'N')
						ivedimas = true;
				}
			}

		} while (TaipNe == 'T');

		rezultatai(m, S);
	}
	if (Pasirinkimas == 2)
	{

		studentas* S = new studentas[MAX_LENGTH];
		do
		{
			cout << endl << "Iveskite studento varda ir pavarde:";
			cin >> S[m].vardas >> S[m].pavarde;
			S[m].ND = new int[MAX_LENGTH];
			S[m].n = 0;
			do
			{
				S[m].ND[S[m].n] = dis(generuoti);
				cout << endl << "Sugeneruotas pazimys: " << S[m].ND[S[m].n] << endl;
				S[m].n++;
				cout << "Ar norite sugeneruoti dar viena pazimi? (iveskite T, jei taip , N, jei ne): ";
				cin >> TaipNePaz;
				if (TaipNePaz != 'T' && TaipNePaz != 'N')//tikrinama ar ivestas tinkamas simbolis
				{
					bool ivedimas = false;
					while (ivedimas == false)
					{
						cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
						cin >> TaipNePaz;
						if (TaipNePaz == 'T' || TaipNePaz == 'N')
							ivedimas = true;
					}
				}

			} while (TaipNePaz == 'T');
			S[m].EGZ = dis(generuoti);
			cout << endl << "Sugeneruotas egzamino pazimys: " << S[m].EGZ;
			m++;
			cout << endl << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			cin >> TaipNe;
			if (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				bool ivedimas = false;
				while (ivedimas == false)
				{
					cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
					cin >> TaipNe;
					if (TaipNe == 'T' || TaipNe == 'N')
						ivedimas = true;
				}
			}


		} while (TaipNe == 'T');

		rezultatai(m, S);

	}
	if (Pasirinkimas == 3)
	{
		studentas* S = new studentas[MAX_LENGTH];

		do
		{

			int lytis = dis_lytis(generuoti);
			if (lytis == 0)  GeneruotiVardusV(m, S);
			else GeneruotiVardusM(m, S);

			S[m].n = 0;
			S[m].ND = new int[MAX_LENGTH];
			cout << endl << "Sugeneruotas vardas ir pavarde: " << S[m].vardas << " " << S[m].pavarde << endl;
			do
			{
				S[m].ND[S[m].n] = dis(generuoti);
				cout << endl << "Sugeneruotas pazimys: " << S[m].ND[S[m].n] << endl;
				cout << "Ar norite sugeneruoti dar viena pazimi? (iveskite T, jei taip , N, jei ne): ";
				S[m].n++;
				cin >> TaipNePaz;
				if (TaipNePaz != 'T' && TaipNePaz != 'N')//tikrinama ar ivestas tinkamas simbolis
				{
					bool ivedimas = false;
					while (ivedimas == false)
					{
						cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
						cin >> TaipNePaz;
						if (TaipNePaz == 'T' || TaipNePaz == 'N')
							ivedimas = true;
					}
				}


			} while (TaipNePaz == 'T');
			S[m].EGZ = dis(generuoti);
			cout << endl << "Sugeneruotas egzamino pazimys: " << S[m].EGZ;
			m++;
			cout << endl << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			cin >> TaipNe;
			if (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				bool ivedimas = false;
				while (ivedimas == false)
				{
					cout << "Ivestas netinkamas simbolis, bandykite dar karta (T/N):";
					cin >> TaipNe;
					if (TaipNe == 'T' || TaipNe == 'N')
						ivedimas = true;
				}
			}

		} while (TaipNe == 'T');

		rezultatai(m, S);
	}

	return 0;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
int n;
int *sprawdzana;
int *mozliweWystapienia;
vector<vector<int>> mozliweOdpowiedzi;

void przygotowujeTabliceDoSprawdzenia(string permutacja)
{
    for (int i = 0; i < n; i++)
        sprawdzana[i] = permutacja[i] - '0';
}

void drukujPermutacje(string permutacja)
{
    for (int i = 0; i < n; i++)
        cout << permutacja[i] - '0' + 1;
    cout << endl;
}
bool czyMoznaStoworzyc = true;
void przygotowujeTabliceDoSprawdzarki(int *skojarzenia)
{
    mozliweWystapienia = new int[n]{};
    bool *czyPewneNaPozycji = new bool[n]{false};
    bool *CzyPewnaLiczba = new bool[n]{false};
    vector<int> temp;
    for (int i = 0; i < n; i++)
        mozliweOdpowiedzi.push_back(temp);

    bool *CzyKazdaWystepuje = new bool[n]{false};
    for (int i = 0; i < n; i++)
    {
        CzyKazdaWystepuje[skojarzenia[i]] = true;
    }
    bool czyWszystkieWystepuja = true;
    for (int i = 0; i < n; i++)
    {
        if (!CzyKazdaWystepuje[i])
        {
            czyWszystkieWystepuja = false;
            break;
        }
    }

    // zasada 1 - skrajne krasnale musza mowic o 'przedskrajnych'
    mozliweOdpowiedzi[1].push_back(skojarzenia[0]);
    mozliweOdpowiedzi[n - 2].push_back(skojarzenia[n - 1]);
    mozliweWystapienia[skojarzenia[0]] = 1;
    mozliweWystapienia[skojarzenia[n - 1]] = 1;
    czyPewneNaPozycji[1] = true;
    czyPewneNaPozycji[n - 2] = true;
    CzyPewnaLiczba[skojarzenia[0]] = true;
    CzyPewnaLiczba[skojarzenia[n - 1]] = true;

    //zasada 2 - jesli dwa krasnale sie potwierdzaja o swoim sasiedzie to on tam musial siedziec
    for (int i = 1; i < n - 1; i++)
    {
        if (skojarzenia[i - 1] == skojarzenia[i + 1])
            if (mozliweOdpowiedzi[i].empty())
            {
                mozliweOdpowiedzi[i].push_back(skojarzenia[i - 1]);
                mozliweWystapienia[skojarzenia[i - 1]] = 1;
                czyPewneNaPozycji[i] = true;
                CzyPewnaLiczba[skojarzenia[i - 1]] = true;
            }
    }
    //zasada 3 - jeden juz potwierdzil innego to sluchamy drugiego - potrzeba wiecej zrozumienia

    //dodanie krasnali ktorzy byli tylko kojarzeni
    for (int i = 1; i < n - 1; i++)
    {
        if (!CzyPewnaLiczba[skojarzenia[i]])
        {
            bool czyDoLewej = true;
            bool czyWstawilismy = false;
            if (!czyPewneNaPozycji[i - 1])
            {
                mozliweOdpowiedzi[i - 1].push_back(skojarzenia[i]);
                mozliweWystapienia[skojarzenia[i]]++;
                czyWstawilismy = true;
                if (czyWszystkieWystepuja && mozliweOdpowiedzi[i - 1].size() == 1)
                    continue;
            }
            if (!czyPewneNaPozycji[i + 1])
            {
                mozliweOdpowiedzi[i + 1].push_back(skojarzenia[i]);
                mozliweWystapienia[skojarzenia[i]]++;
                czyDoLewej = false;
                czyWstawilismy = true;
            }
            if (!czyWstawilismy)
            {
                czyMoznaStoworzyc = false;
                return;
            }
            if (mozliweWystapienia[skojarzenia[i]] == 1)
            {
                if (czyDoLewej)
                    czyPewneNaPozycji[i - 1] = true;
                else
                    czyPewneNaPozycji[i + 1] = true;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (mozliweWystapienia[i] == 0)
        {
            for (int j = 0; j < n; j++)
            {
                if (!czyPewneNaPozycji[j])
                    mozliweOdpowiedzi[j].push_back(i);
            }
        }
    }
    
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t";
    cout << endl;
    for (int i = 0; i < n; i++)
        // cout << mozliweWystapienia[i] << " ";

        cout << mozliweWystapienia[i] << "\t";
    cout << endl;
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < mozliweOdpowiedzi[i].size(); j++)
        {
            cout << mozliweOdpowiedzi[i][j] + 1 << ',';
        }
        cout << "\t";
    }
    cout << endl;
}
long long obliczaIloscMozliwosci()
{
    int ilosc0 = 0;
    int ilosc0i2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (mozliweWystapienia[i] == 0)
        {
            ilosc0++;
        }
        else if (mozliweWystapienia[i] == 2)
            ilosc0i2++;
    }
    ilosc0i2 += ilosc0;
    long long wynik;
    wynik = pow(2, ilosc0 - 1) * (ilosc0i2); //wzor nie dziala na razie
    return wynik;
    // cout << wynik << endl;
}
bool znajdzW2DTablicy(int pozycja, int szukane)
{
    for (int i = 0; i < mozliweOdpowiedzi[pozycja].size(); i++)
    {
        if (mozliweOdpowiedzi[pozycja][i] == szukane)
            return true;
    }
    return false;
}

bool sprawdzarka()
{
    for (int i = 0; i < n; i++)
        if (!znajdzW2DTablicy(i, sprawdzana[i]))
            return false;
    return true;
}
int main()
{
    cin >> n;
    int *skojarzenia = new int[n];
    sprawdzana = new int[n];

    // if (n > 9)
    // {
    //     cout << "-";
    //     return 0;
    // }
    int skojarzenie;
    for (int i = 0; i < n; i++)
    {
        cin >> skojarzenie;
        skojarzenie--;
        skojarzenia[i] = skojarzenie;
    }

    przygotowujeTabliceDoSprawdzarki(skojarzenia);
    if (!czyMoznaStoworzyc)
    {
        cout << 0 << endl;
        return 0;
    }

    string doPermutacji;
    for (int i = 0; i < n; i++)
        doPermutacji += to_string(i);
    int licznik = 0;
    do
    {
        przygotowujeTabliceDoSprawdzenia(doPermutacji);

        // if (doPermutacji == "3451206")
        //     cout << endl;
        if (sprawdzarka())
        {
            // drukujPermutacje(doPermutacji);
            licznik++;
        }
    } while (next_permutation(doPermutacji.begin(), doPermutacji.end()));
    cout << licznik << endl;
    long long wynik2 = obliczaIloscMozliwosci();
    // if (licznik != wynik2)
    // cout << licznik  << " " << wynik2 << endl;
    // else
    // cout << licznik;

    // cout << wynik2 << endl;

    return 0;
}

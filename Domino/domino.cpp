#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
long long n;
vector<long long> ciagFibonacciego;

void generujCiagFibonacciego()
{
    ciagFibonacciego.push_back(1);
    ciagFibonacciego.push_back(1);
    int i = 1;
    long long kolejnyWyrazCiagu = ciagFibonacciego[i] + ciagFibonacciego[i - 1];
    while (kolejnyWyrazCiagu < n)
    {
        ciagFibonacciego.push_back(kolejnyWyrazCiagu);
        i++;
        kolejnyWyrazCiagu = ciagFibonacciego[i] + ciagFibonacciego[i - 1];
    }
}

vector<int> DzieliNaCzynnikiFibIZwracaPozycje()
{
    vector<int> pozycje;
    long long roboczaN = n;
    int i = ciagFibonacciego.size() - 1;
    while (roboczaN != 1)
    {
        if (i == 1)
            return vector<int>();
        if (roboczaN % ciagFibonacciego[i] == 0)
        {
            pozycje.push_back(i);
            roboczaN /= ciagFibonacciego[i];
        }
        else
            i--;
    }
    return pozycje;
}

int przeliczWzor(vector<int> pozycje)
{
    int wynik = 0;
    for (int i = 0; i < pozycje.size(); i++)
    {
        wynik += pozycje[i];
        wynik++;
    }
    wynik--;
    return wynik;
}
int main()
{
    cin >> n;

    generujCiagFibonacciego();
    vector<int> pozycje = DzieliNaCzynnikiFibIZwracaPozycje();
    if (pozycje.empty())
    {
        cout << "NIE" << endl;
        return 0;
    }
    cout << przeliczWzor(pozycje) << endl;
    return 0;
}

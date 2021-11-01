#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;
int n;
int *sprawdzana;
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
void przygotowujeTabliceDoSprawdzarki(int *skojarzenia)
{
    int *mozliweWystapienia = new int[n]{};
    bool *czyPewne = new bool[n]{false};
    vector<int> temp;
    for (int i = 0; i < n; i++)
        mozliweOdpowiedzi.push_back(temp);

    // zasada 1 - skrajne krasnale musza mowic o 'przedskrajnych'
    mozliweOdpowiedzi[1].push_back(skojarzenia[0]);
    mozliweOdpowiedzi[n - 2].push_back(skojarzenia[n - 1]);
    mozliweWystapienia[skojarzenia[0]] = 1;
    mozliweWystapienia[skojarzenia[n - 1]] = 1;
    czyPewne[1] = true;
    czyPewne[n - 2] = true;

    //zasada 2 - jesli dwa krasnale sie potwierdzaja o swoim sasiedzie to on tam musial siedziec
    for (int i = 1; i < n - 1; i++)
    {
        if (skojarzenia[i - 1] == skojarzenia[i + 1])
            if (mozliweOdpowiedzi[i].empty())
            {
                mozliweOdpowiedzi[i].push_back(skojarzenia[i - 1]);
                mozliweWystapienia[skojarzenia[i - 1]] = 1;
                czyPewne[i] = true;
            }
    }
    //zasada 3 - jeden juz potwierdzil innego to sluchamy drugiego - potrzeba wiecej zrozumienia

    //dodanie krasnali ktorzy byli tylko kojarzeni
    if (mozliweWystapienia[skojarzenia[1]] != 1)
    {
        mozliweOdpowiedzi[0].push_back(skojarzenia[1]);
        mozliweWystapienia[skojarzenia[1]] = 2;
    }
    if (mozliweWystapienia[skojarzenia[n - 2]] != 1)
    {
        mozliweOdpowiedzi[n - 1].push_back(skojarzenia[n - 2]);
        mozliweWystapienia[skojarzenia[n - 2]] = 2;
    }
    int czapkaNaLewo;
    int czapkaNaPrawo;
    for (int i = 1; i < n - 1; i++)
    {
        czapkaNaLewo = skojarzenia[i - 1];
        czapkaNaPrawo = skojarzenia[i + 1];
        if (!czyPewne[i])
            if (czapkaNaLewo != czapkaNaPrawo)
            {
                bool CzyJednoZajete = 0;
                if (mozliweWystapienia[czapkaNaLewo] == 0 || mozliweWystapienia[czapkaNaLewo] == 2)
                {
                    mozliweOdpowiedzi[i].push_back(czapkaNaLewo);
                    mozliweWystapienia[czapkaNaLewo] = 2;
                    CzyJednoZajete++;
                }
                if (mozliweWystapienia[czapkaNaPrawo] == 0 || mozliweWystapienia[czapkaNaPrawo] == 2)
                {
                    mozliweOdpowiedzi[i].push_back(czapkaNaPrawo);
                    mozliweWystapienia[czapkaNaPrawo] = 2;
                    CzyJednoZajete++;
                }
                if (CzyJednoZajete == 1)
                    czyPewne[i] == true;
            }
    }
    for (int i = 0; i < n; i++)
    {
        if (mozliweWystapienia[i] == 0)
        {
            for (int j = 0; j < n; j++)
            {
                if (!czyPewne[j])
                    mozliweOdpowiedzi[j].push_back(i);
            }
        }
    }

    // for (int i = 0; i < n; i++)
    // cout << i + 1 << "\t";
    // cout << endl;
    // for (int i = 0; i < n; i++)
    //     cout << mozliweWystapienia[i] << " ";

    // cout << mozliweWystapienia[i] << "\t";
    // cout << endl;
    // cout << endl;

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

    int skojarzenie;
    for (int i = 0; i < n; i++)
    {
        cin >> skojarzenie;
        skojarzenie--;
        skojarzenia[i] = skojarzenie;
    }

    przygotowujeTabliceDoSprawdzarki(skojarzenia);

    string doPermutacji;
    for (int i = 0; i < n; i++)
        doPermutacji += to_string(i);
    int licznik = 0;
    do
    {
        przygotowujeTabliceDoSprawdzenia(doPermutacji);

        if (sprawdzarka())
        {
            // drukujPermutacje(doPermutacji);
            licznik++;
        }
    } while (next_permutation(doPermutacji.begin(), doPermutacji.end()));
    cout << licznik << endl;
}

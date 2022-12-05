#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXINT = 2147483647;

struct Job
{
    int deadline, duration, idx;

    bool operator<(Job o) const
    {
        return deadline < o.deadline;
    }
};
int n;

vector<pair<int, int>> compute_schedule(vector<Job> jobs)
{
    sort(jobs.begin(), jobs.end());

    set<pair<int, pair<int, int>>> s;
    vector<pair<int, int>> schedule;
    for (int i = jobs.size() - 1; i >= 0; i--)
    {
        int t = jobs[i].deadline - (i ? jobs[i - 1].deadline : 0);
        s.insert(make_pair(jobs[i].duration, make_pair(jobs[i].idx,jobs[i].deadline)));
        while (t && !s.empty())
        {
            auto it = s.begin();
            if (it->first <= t)
            {
                t -= it->first;
                schedule.push_back(it->second);
            }
            else
            {
                s.insert(make_pair(it->first - t, it->second));
                t = 0;
            }
            s.erase(it);
        }
    }
    return schedule;
}

int main()
{
    vector<Job> filmyDoZmontowania;
    int index = 1, duration, deadline;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> duration >> deadline;
        Job nowy;
        nowy.deadline = deadline;
        nowy.duration = duration;
        nowy.idx = index;
        // cout << nowy.duration << " " << nowy.deadline << " " << nowy.idx << endl;
        filmyDoZmontowania.push_back(nowy);
        index++;
    }
    auto wyniki = compute_schedule(filmyDoZmontowania);
    cout << wyniki.size() << endl;
    sort(wyniki.begin(), wyniki.end());
    int najwczesniejszyTermin = MAXINT;
    vector<pair<int, int>> wynikiSchedule;
    for (int i = wyniki.size() - 1; i >= 0; i--)
    {
        Job aktualnyFilm = filmyDoZmontowania[wyniki[i].first - 1];
        int kiedyTrzebaZaczac = min(aktualnyFilm.deadline - aktualnyFilm.duration+1, najwczesniejszyTermin);
        wynikiSchedule.push_back(make_pair(aktualnyFilm.idx, kiedyTrzebaZaczac));
        najwczesniejszyTermin = kiedyTrzebaZaczac - 1;
    }
    for (int i = wynikiSchedule.size()-1; i >= 0 ;i--)
    {
        cout << wynikiSchedule[i].first << " " << wynikiSchedule[i].second << endl;
    }
        return 0;
}

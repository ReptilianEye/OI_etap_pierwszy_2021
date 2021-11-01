#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct Job
{
    int deadline, duration, idx;

    bool operator<(Job o) const
    {
        return deadline < o.deadline;
    }
};
int n;

vector<int> compute_schedule(vector<Job> jobs)
{
    sort(jobs.begin(), jobs.end());

    set<pair<int, int>> s;
    vector<int> schedule;
    for (int i = jobs.size() - 1; i >= 0; i--)
    {
        int t = jobs[i].deadline - (i ? jobs[i - 1].deadline : 0);
        s.insert(make_pair(jobs[i].duration, jobs[i].idx));
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
    // for (auto film : wyniki)
    // {
    //     cout << film << endl;
    // }
    return 0;
}

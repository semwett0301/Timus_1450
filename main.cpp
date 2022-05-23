#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class GasStation {
public:
    int index;
    vector<pair<int, int>> heirs;
    int resultSum = -500 * 100000;
    int incomingGasStations = 0;

    GasStation(int index) {
        this->index = index;
    }
};

bool operator<(const GasStation &a, const GasStation &b) {
    return a.resultSum < b.resultSum;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<GasStation> stations;
    for (int i = 0; i < n; i++) {
        stations.emplace_back(i);
    }

    for (int i = 0; i < m; i++) {
        int index, heir, weight;
        cin >> index >> heir >> weight;
        index--;
        heir--;
        stations[index].heirs.emplace_back(heir, weight);
        stations[heir].incomingGasStations++;
    }

    int s, f;
    cin >> s >> f;
    s--;
    f--;

    priority_queue<GasStation> myQueue;
    stations[s].resultSum = 0;
    for (GasStation s : stations) {
        if (s.incomingGasStations == 0) {
            myQueue.push(s);
        }
    }
    while (!myQueue.empty()) {
        GasStation tmp = myQueue.top();
        myQueue.pop();

        for (auto heir: tmp.heirs) {
            if (stations[heir.first].resultSum < tmp.resultSum + heir.second) {
                stations[heir.first].resultSum = tmp.resultSum + heir.second;
            }
            stations[heir.first].incomingGasStations--;

            if (stations[heir.first].incomingGasStations == 0) {
                myQueue.push(stations[heir.first]);
            }
        }


    }

    if (stations[f].resultSum >= 0) {
        cout << stations[f].resultSum;
    } else {
        cout << "No solution";
    }
    return 0;
}

// Q3 : MLVL Q

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int pr;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
};

struct Comparepr {
    bool operator()(const Process &p1, const Process &p2) {
        return p1.pr > p2.pr;
    }
};

void multiLevelQueueScheduling(vector <Process> &processes) {
    vector < priority_queue < Process, vector < Process >, Comparepr > > queues(3);

    int currT = 0;

    for (Process &process: processes) {
        int pr = process.pr - 1;
        queues[pr].push(process);
    }

    cout << "Queue Execution Order:" << endl;

    for (int i = 2; i >= 0; i--) {
        while (!queues[i].empty()) {
            Process process = queues[i].top();
            queues[i].pop();

            int execT = min(process.bt, 2);
            process.bt -= execT;
            currT += execT;

            process.ct = currT;
            process.tat = process.ct - process.at;
            process.wt = process.tat - process.bt;

            cout << "Running Process ID " << process.id << " (Priority " << process.pr << ") for " << execT
                 << " units" << endl;
        }
    }
}

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector <Process> processes(n);

    cout << "Enter process details (ID, Priority, Burst Time, Arrival Time):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> processes[i].id >> processes[i].pr >> processes[i].bt >> processes[i].at;
    }

    multiLevelQueueScheduling(processes);

    cout << "\nPID\tPRIO\tBT\tAT\tCT\tTAT\tWT" << endl;
    for (Process &process: processes) {
        cout << process.id << "\t" << process.pr << "\t" << process.bt << "\t" << process.at << "\t" << process.ct
             << "\t" << process.tat << "\t" << process.wt << endl;
    }

    return 0;
}

//
//#include <iostream>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//struct Process {
//    int id;
//    int pr;
//    int bt;
//};
//
//struct Comparepr {
//    bool operator()(const Process &p1, const Process &p2) {
//        return p1.pr > p2.pr;
//    }
//};
//
//
//void multiLevelQueueScheduling(vector <Process> &processes) {
//    vector < priority_queue < Process, vector < Process >, Comparepr > > queues(3);
//    for (Process &process: processes) {
//        int pr = process.pr - 1;
//        queues[pr].push(process);
//    }
//
//    cout << "Queue Execution Order:" << endl;
//
//    for (int i = 2; i >= 0; i--) {
//        while (!queues[i].empty()) {
//            Process process = queues[i].top();
//            queues[i].pop();
//            cout << "Running Process ID " << process.id << " (pr " << process.pr << ") for "
//                 << process.bt << " units" << endl;
//        }
//    }
//}
//
//int main() {
//    int n;
//
//    cout << "Enter the number of processes: ";
//    cin >> n;
//
//    vector <Process> processes(n);
//
//    cout << "Enter process details (ID, pr, Burst Time):" << endl;
//    for (int i = 0; i < n; i++) {
//        cin >> processes[i].id >> processes[i].pr >> processes[i].bt;
//    }
//
//    multiLevelQueueScheduling(processes);
//
//    return 0;
//}

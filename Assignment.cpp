#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, ct, wt, tat, rt, priority, queue, rem;
};

// Calculate metrics
void calcMetrics(vector<Process>& p) {
    for(auto &proc : p) {
        proc.tat = proc.ct - proc.at;
        proc.wt = proc.tat - proc.bt;
    }
}

// Display results
void display(vector<Process>& p, string algo) {
    double avgWT = 0, avgTAT = 0, avgRT = 0;
    
    cout << "\n" << string(50, '=');
    cout << "\n" << algo;
    cout << "\n" << string(50, '=');
    
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\tRT";
    if(algo.find("PRIORITY") != string::npos) cout << "\tPRI";
    if(algo.find("MLQ") != string::npos) cout << "\tQUEUE";
    
    for(auto &proc : p) {
        cout << "\nP" << proc.pid << "\t" << proc.at << "\t" << proc.bt 
             << "\t" << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\t" << proc.rt;
        if(algo.find("PRIORITY") != string::npos) cout << "\t" << proc.priority;
        if(algo.find("MLQ") != string::npos) cout << "\t" << proc.queue;
        
        avgWT += proc.wt;
        avgTAT += proc.tat;
        avgRT += proc.rt;
    }
    
    int n = p.size();
    cout << "\n\nAverage Waiting Time: " << avgWT/n;
    cout << "\nAverage Turnaround Time: " << avgTAT/n;
    cout << "\nAverage Response Time: " << avgRT/n;
    cout << "\n" << string(50, '-') << "\n";
}

// ========== ROUND ROBIN ==========
void RoundRobin(vector<Process> p) {
    int tq;
    cout << "\nEnter Time Quantum for Round Robin: ";
    cin >> tq;
    
    int n = p.size(), time = 0, completed = 0;
    queue<int> readyQueue;
    vector<bool> inQueue(n, false), started(n, false);
    
    for(int i = 0; i < n; i++) p[i].rem = p[i].bt;
    
    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });
    
    // Initial processes arriving at time 0
    int nextProc = 0;
    while(nextProc < n && p[nextProc].at == 0) {
        readyQueue.push(nextProc);
        inQueue[nextProc] = true;
        nextProc++;
    }
    
    while(completed < n) {
        if(readyQueue.empty()) {
            time++;
            
            // Check for new arrivals
            while(nextProc < n && p[nextProc].at <= time && p[nextProc].rem > 0) {
                if(!inQueue[nextProc]) {
                    readyQueue.push(nextProc);
                    inQueue[nextProc] = true;
                }
                nextProc++;
            }
            continue;
        }
        
        int idx = readyQueue.front();
        readyQueue.pop();
        inQueue[idx] = false;
        
        if(!started[idx]) {
            p[idx].rt = time - p[idx].at;
            started[idx] = true;
        }
        
        int execTime = min(tq, p[idx].rem);
        p[idx].rem -= execTime;
        time += execTime;
        
        // Check for new arrivals during execution
        while(nextProc < n && p[nextProc].at <= time && p[nextProc].rem > 0) {
            if(!inQueue[nextProc]) {
                readyQueue.push(nextProc);
                inQueue[nextProc] = true;
            }
            nextProc++;
        }
        
        if(p[idx].rem > 0) {
            readyQueue.push(idx);
            inQueue[idx] = true;
        } else {
            p[idx].ct = time;
            completed++;
        }
    }
    
    calcMetrics(p);
    display(p, "ROUND ROBIN (TQ=" + to_string(tq) + ")");
}

// ========== PRIORITY ==========
void PriorityScheduling(vector<Process> p) {
    int n = p.size(), time = 0, completed = 0;
    vector<bool> done(n, false);
    
    // Sort by arrival time first
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });
    
    while(completed < n) {
        int idx = -1, maxPriority = -1;
        
        // Find highest priority process that has arrived
        for(int i = 0; i < n; i++) {
            if(!done[i] && p[i].at <= time && p[i].priority > maxPriority) {
                maxPriority = p[i].priority;
                idx = i;
            }
        }
        
        if(idx == -1) {
            time++;
            continue;
        }
        
        p[idx].rt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].ct = time;
        done[idx] = true;
        completed++;
    }
    
    calcMetrics(p);
    display(p, "PRIORITY SCHEDULING");
}

// ========== MULTILEVEL QUEUE ==========
void MultilevelQueue(vector<Process> p) {
    int tq;
    cout << "\nEnter Time Quantum for Round Robin queue: ";
    cin >> tq;
    
    int n = p.size(), time = 0, completed = 0;
    queue<int> queueRR, queueFCFS;
    vector<bool> inRR(n, false), inFCFS(n, false), started(n, false), done(n, false);
    
    for(int i = 0; i < n; i++) p[i].rem = p[i].bt;
    
    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });
    
    // Initial assignment to queues
    int nextProc = 0;
    while(nextProc < n && p[nextProc].at == 0) {
        if(p[nextProc].queue == 0) {
            queueRR.push(nextProc);
            inRR[nextProc] = true;
        } else {
            queueFCFS.push(nextProc);
            inFCFS[nextProc] = true;
        }
        nextProc++;
    }
    
    while(completed < n) {
        // Priority to RR queue
        if(!queueRR.empty()) {
            int idx = queueRR.front();
            queueRR.pop();
            inRR[idx] = false;
            
            if(!started[idx]) {
                p[idx].rt = time - p[idx].at;
                started[idx] = true;
            }
            
            int execTime = min(tq, p[idx].rem);
            p[idx].rem -= execTime;
            time += execTime;
            
            // Check for new arrivals
            while(nextProc < n && p[nextProc].at <= time) {
                if(p[nextProc].queue == 0 && !inRR[nextProc] && p[nextProc].rem > 0) {
                    queueRR.push(nextProc);
                    inRR[nextProc] = true;
                } else if(p[nextProc].queue == 1 && !inFCFS[nextProc] && p[nextProc].rem > 0) {
                    queueFCFS.push(nextProc);
                    inFCFS[nextProc] = true;
                }
                nextProc++;
            }
            
            // Re-add to RR queue if not finished
            if(p[idx].rem > 0) {
                queueRR.push(idx);
                inRR[idx] = true;
            } else {
                p[idx].ct = time;
                done[idx] = true;
                completed++;
            }
        }
        // Execute from FCFS queue
        else if(!queueFCFS.empty()) {
            int idx = queueFCFS.front();
            queueFCFS.pop();
            inFCFS[idx] = false;
            
            if(!started[idx]) {
                p[idx].rt = time - p[idx].at;
                started[idx] = true;
            }
            
            time += p[idx].rem;
            p[idx].rem = 0;
            p[idx].ct = time;
            done[idx] = true;
            completed++;
            
            // Check for new arrivals
            while(nextProc < n && p[nextProc].at <= time) {
                if(p[nextProc].queue == 0 && !inRR[nextProc] && p[nextProc].rem > 0) {
                    queueRR.push(nextProc);
                    inRR[nextProc] = true;
                } else if(p[nextProc].queue == 1 && !inFCFS[nextProc] && p[nextProc].rem > 0) {
                    queueFCFS.push(nextProc);
                    inFCFS[nextProc] = true;
                }
                nextProc++;
            }
        } else {
            time++;
            // Check for new arrivals when both queues are empty
            while(nextProc < n && p[nextProc].at <= time) {
                if(p[nextProc].queue == 0 && !inRR[nextProc] && p[nextProc].rem > 0) {
                    queueRR.push(nextProc);
                    inRR[nextProc] = true;
                } else if(p[nextProc].queue == 1 && !inFCFS[nextProc] && p[nextProc].rem > 0) {
                    queueFCFS.push(nextProc);
                    inFCFS[nextProc] = true;
                }
                nextProc++;
            }
        }
    }
    
    calcMetrics(p);
    display(p, "MULTILEVEL QUEUE (Q0=RR, Q1=FCFS)");
}

// ========== COMPARE ALL ALGORITHMS ==========
void compareAlgorithms(vector<Process> processes) {
    cout << "\n" << string(60, '=');
    cout << "\n\tPERFORMANCE COMPARISON";
    cout << "\n" << string(60, '=');
    
    vector<pair<string, vector<double>>> comparisons;
    
    // Run Round Robin
    auto rr = processes;
    RoundRobin(rr);
    
    // Run Priority
    auto prio = processes;
    PriorityScheduling(prio);
    
    // Run MLQ
    auto mlq = processes;
    MultilevelQueue(mlq);
    
    cout << "\n\nSUMMARY:";
    cout << "\n- Round Robin: Good for time-sharing, fair to all processes";
    cout << "\n- Priority: Suitable for real-time systems, critical tasks get priority";
    cout << "\n- Multilevel Queue: Combines benefits of multiple algorithms";
    cout << "\n" << string(60, '=') << "\n";
}

// ========== MAIN FUNCTION ==========
int main() {
    cout << "\n" << string(60, '=');
    cout << "\n\tCPU SCHEDULING ALGORITHMS";
    cout << "\n\t(Round Robin, Priority, Multilevel Queue)";
    cout << "\n" << string(60, '=');
    
    int n;
    cout << "\n\nEnter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    cout << "\nEnter process details:\n";
    for(int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "\nProcess P" << (i + 1) << ":\n";
        cout << "  Arrival Time: ";
        cin >> processes[i].at;
        cout << "  Burst Time: ";
        cin >> processes[i].bt;
        cout << "  Priority (1-10, higher=higher priority): ";
        cin >> processes[i].priority;
        cout << "  Queue (0 for RR, 1 for FCFS in MLQ): ";
        cin >> processes[i].queue;
    }
    
    // Compare all algorithms
    compareAlgorithms(processes);
    
    return 0;
}

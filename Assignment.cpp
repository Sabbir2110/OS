#include <bits/stdc++.h>
using namespace std;

struct P{int id,at,bt,ct,wt,tat,rt,pr,q,rem;};

void calc(vector<P>&p){for(auto&x:p){x.tat=x.ct-x.at;x.wt=x.tat-x.bt;}}

void show(vector<P>&p,string a){
    double aw=0,at=0,ar=0;
    cout<<"\n--- "<<a<<" ---\nPID AT BT CT TAT WT RT";
    if(a.find("PR")!=string::npos)cout<<" PR";
    if(a.find("MLQ")!=string::npos)cout<<" Q";
    for(auto&x:p){
        cout<<"\nP"<<x.id<<" "<<x.at<<" "<<x.bt<<" "<<x.ct<<" "<<x.tat<<" "<<x.wt<<" "<<x.rt;
        if(a.find("PR")!=string::npos)cout<<" "<<x.pr;
        if(a.find("MLQ")!=string::npos)cout<<" "<<x.q;
        aw+=x.wt;at+=x.tat;ar+=x.rt;
    }
    int n=p.size();
    cout<<"\n\nAvg WT:"<<aw/n<<"\nAvg TAT:"<<at/n<<"\nAvg RT:"<<ar/n<<"\n";
}

void RR(vector<P>p){
    int tq;cout<<"\nTime Quantum: ";cin>>tq;
    int n=p.size(),t=0,c=0,next=0;
    queue<int>q;vector<bool>inq(n,0),s(n,0);
    for(int i=0;i<n;i++)p[i].rem=p[i].bt;
    sort(p.begin(),p.end(),[](P a,P b){return a.at<b.at;});
    while(next<n&&p[next].at==0){q.push(next);inq[next]=1;next++;}
    while(c<n){
        if(q.empty()){t++;
            while(next<n&&p[next].at<=t&&p[next].rem>0){
                if(!inq[next]){q.push(next);inq[next]=1;}next++;}
            continue;}
        int i=q.front();q.pop();inq[i]=0;
        if(!s[i]){p[i].rt=t-p[i].at;s[i]=1;}
        int ex=min(tq,p[i].rem);p[i].rem-=ex;t+=ex;
        while(next<n&&p[next].at<=t&&p[next].rem>0){
            if(!inq[next]){q.push(next);inq[next]=1;}next++;}
        if(p[i].rem>0){q.push(i);inq[i]=1;}
        else{p[i].ct=t;c++;}
    }
    calc(p);show(p,"RR(TQ="+to_string(tq)+")");
}

void Prio(vector<P>p){
    int n=p.size(),t=0,c=0;vector<bool>d(n,0);
    sort(p.begin(),p.end(),[](P a,P b){return a.at<b.at;});
    while(c<n){
        int idx=-1,mx=-1;
        for(int i=0;i<n;i++)
            if(!d[i]&&p[i].at<=t&&p[i].pr>mx){mx=p[i].pr;idx=i;}
        if(idx==-1){t++;continue;}
        p[idx].rt=t-p[idx].at;t+=p[idx].bt;
        p[idx].ct=t;d[idx]=1;c++;
    }
    calc(p);show(p,"PRIORITY");
}

void MLQ(vector<P>p){
    int tq;cout<<"\nRR Queue Time Quantum: ";cin>>tq;
    int n=p.size(),t=0,c=0,next=0;
    queue<int>q0,q1;
    vector<bool>inq0(n,0),inq1(n,0),s(n,0),d(n,0);
    for(int i=0;i<n;i++)p[i].rem=p[i].bt;
    sort(p.begin(),p.end(),[](P a,P b){return a.at<b.at;});
    while(next<n&&p[next].at==0){
        if(p[next].q==0){q0.push(next);inq0[next]=1;}
        else{q1.push(next);inq1[next]=1;}next++;}
    while(c<n){
        if(!q0.empty()){
            int i=q0.front();q0.pop();inq0[i]=0;
            if(!s[i]){p[i].rt=t-p[i].at;s[i]=1;}
            int ex=min(tq,p[i].rem);p[i].rem-=ex;t+=ex;
            while(next<n&&p[next].at<=t){
                if(p[next].q==0&&!inq0[next]&&p[next].rem>0){q0.push(next);inq0[next]=1;}
                else if(p[next].q==1&&!inq1[next]&&p[next].rem>0){q1.push(next);inq1[next]=1;}
                next++;}
            if(p[i].rem>0){q0.push(i);inq0[i]=1;}
            else{p[i].ct=t;d[i]=1;c++;}
        }
        else if(!q1.empty()){
            int i=q1.front();q1.pop();inq1[i]=0;
            if(!s[i]){p[i].rt=t-p[i].at;s[i]=1;}
            t+=p[i].rem;p[i].rem=0;
            p[i].ct=t;d[i]=1;c++;
            while(next<n&&p[next].at<=t){
                if(p[next].q==0&&!inq0[next]&&p[next].rem>0){q0.push(next);inq0[next]=1;}
                else if(p[next].q==1&&!inq1[next]&&p[next].rem>0){q1.push(next);inq1[next]=1;}
                next++;}
        }
        else{t++;
            while(next<n&&p[next].at<=t){
                if(p[next].q==0&&!inq0[next]&&p[next].rem>0){q0.push(next);inq0[next]=1;}
                else if(p[next].q==1&&!inq1[next]&&p[next].rem>0){q1.push(next);inq1[next]=1;}
                next++;}
        }
    }
    calc(p);show(p,"MLQ");
}

int main(){
    int n;cout<<"Processes: ";cin>>n;
    vector<P>p(n);
    for(int i=0;i<n;i++){
        p[i].id=i+1;cout<<"P"<<i+1<<" AT BT PR Q: ";
        cin>>p[i].at>>p[i].bt>>p[i].pr>>p[i].q;
    }
    RR(p);Prio(p);MLQ(p);
    return 0;
}

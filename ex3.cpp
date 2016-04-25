#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<double, ii> dii;

ii pos[26];
double dist[26][26];
int demand[26][26];
bool used[26][26];

int flow[26][26];

priority_queue<iii> pq;
priority_queue<dii> pqdist;

int main() {
  for(int i = 1; i < 26; i++)
    for(int j = 1; j < 26; j++)
      used[i][j] = false;
  
  for(int i = 1; i < 26; i++)
    memset(flow[i], 0, sizeof(flow[i]));
  
  double cost = 0;
  
  for(int i = 1; i < 26; i++)
    cin >> pos[i].F >> pos[i].S;
  
  for(int i = 1; i < 26; i++)
    for(int j = 1; j < 26; j++)
      dist[i][j] = sqrt((pos[i].F - pos[j].F) * (pos[i].F - pos[j].F) + (pos[i].S - pos[j].S) * (pos[i].S - pos[j].S));
  
  for(int i = 1; i < 25; i++)
    for(int j = 1; j < 25; j++) {
      cin >> demand[i][j];
      pq.push(iii(demand[i][j], ii(i, j)));
    }
  
  while(pq.top().F >= 1000) {
    iii top = pq.top(); pq.pop();
    int i = top.S.F, j = top.S.S;
    
    demand[i][j] -= 1000;
    used[i][j] = true;
    
    if(demand[i][j] != 0)
      pq.push(iii(demand[i][j], ii(i, j)));
    
    cost += 1000 + 1000 * dist[i][j];
    flow[i][j] = 1000;
  }
  
  while(!pq.empty())
    pq.pop();
  
  for(int i = 1; i < 26; i++)
    for(int j = 1; j < 26; j++)
      if(!used[i][j])
	pqdist.push(dii(-dist[i][j], ii(i, j)));
  
  while(!pqdist.empty()) {
    dii top = pqdist.top(); pqdist.pop();
    int i = top.S.F, j = top.S.S;
    
    if(flow[i][j] == 1000) {
      continue;
    }
    
    else if(flow[i][j] == 0) {
      flow[i][j] += demand[i][j];
      demand[i][j] = 0;
      
      for(int k = 1; k < 26; k++) {
	
      }
    }
    
    else {
      
    }
  }
  
  return 0;
}

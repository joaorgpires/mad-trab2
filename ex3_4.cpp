#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<double, ii> dii;

ii pos[5];
double dist[5][5];
int demand[5][5];
bool used[5][5];

int flow[5][5];

priority_queue<iii> pq;
priority_queue<dii> pqdist;

int main() {
  for(int i = 1; i < 5; i++)
    for(int j = 1; j < 5; j++)
      used[i][j] = false;
  
  for(int i = 1; i < 5; i++)
    memset(flow[i], 0, sizeof(flow[i]));
  
  double cost = 0;
  
  for(int i = 1; i < 5; i++)
    cin >> pos[i].F >> pos[i].S;
  
  for(int i = 1; i < 5; i++)
    for(int j = 1; j < 5; j++)
      dist[i][j] = sqrt((pos[i].F - pos[j].F) * (pos[i].F - pos[j].F) + (pos[i].S - pos[j].S) * (pos[i].S - pos[j].S));
  
  for(int i = 1; i < 5; i++)
    for(int j = 1; j < 5; j++) {
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
    
    flow[i][j] = 1000;
  }
  
  while(!pq.empty())
    pq.pop();
  
  for(int i = 1; i < 5; i++)
    for(int j = 1; j < 5; j++)
      if(i != j)
	if(!used[i][j])
	  pqdist.push(dii(-dist[i][j], ii(i, j)));

  while(!pqdist.empty()) {
    dii top = pqdist.top(); pqdist.pop();
    int i = top.S.F, j = top.S.S;
    
    if(flow[i][j] == 1000) {
      continue;
    }
    
    else {
      int disp = 1000 - flow[i][j];
      
      if(disp >= demand[i][j]) {
	disp -= demand[i][j];
	flow[i][j] += demand[i][j];
	demand[i][j] = 0;
	used[i][j] = true;
      }
      else {
	int d = demand[i][j] - disp;
	flow[i][j] += d;
	demand[i][j] -= d;
	used[i][j] = true;
	disp = 0;
      }
      
      if(disp == 0)
	continue;
      
      for(int k = 1; k < 5; k++) {	
	if(disp == 0)
	  break;

	if(demand[i][k] > 0) {
	  if(demand[i][k] <= disp) {
	    if(demand[i][k] + flow[j][k] <= 1000) {
	      disp -= demand[i][k];
	      flow[i][j] += demand[i][k];
	      flow[j][k] += demand[i][k];
	      used[j][k] = true;
	      demand[i][k] = 0;
	    }
	    else {
	      int dmn = 1000 - flow[j][k];
	      demand[i][k] -= dmn;
	      flow[i][j] += dmn;
	      flow[j][k] += dmn;
	      used[j][k] = true;
	      disp -= dmn;
	    }
	  }
	  else {
	    if(disp + flow[j][k] <= 1000) {
	      flow[i][j] += disp;
	      flow[j][k] += disp;
	      used[j][k] = true;
	      demand[i][k] -= disp;
	      disp = 0;
	    }
	    else {
	      int dmn = 1000 - flow[j][k];
	      demand[i][k] -= dmn;
	      flow[i][j] += dmn;
	      flow[j][k] += dmn;
	      used[j][k] = true;
	      disp -= dmn;
	    }
	  }
	}
      }
    }    
  }
  
  for(int i = 1; i < 5; i++) {
    for(int j = 1; j < 5; j++) {
      cost += dist[i][j] * flow[i][j];
      if(used[i][j])
	cost += 1000;
            
      //cout << "demand " << i << " " << j << ": " << demand[i][j] << endl;
    }
  }

  for(int i = 1; i < 5; i++) {
    for(int j = 1; j < 5; j++) {
      cout << "flow " << i << " " << j << ": " << flow[i][j] << endl;
    }
  }
  
  cout << "------------------------" << endl;
  
  cout << "min cost: " << cost << endl;
  
  return 0;
}

param N;            # number of nodes
set I := 1..N;      # set of nodes
set J := 1..5;      # set of only 4 nodes
param pos_x{I};     # position on x axis (for computing distance/cost)
param pos_y{I};     # position on y axis
param d{I,I};       # demand
param M;            # arc capacity
param C;            # cost of preparing a ship from i to j
param dist{i in I, j in I} :=
    sqrt((pos_x[i]- pos_x[j])^2 + (pos_y[i]- pos_y[j])^2);       # cost (exo)


var y{i in J, j in J: j != i}, binary;     #Variable that will be 1 if there is a connection between i and j
var x{i in J, j in J, a in J, b in J: j != i and b != a} >= 0;        #Flow between i and j

Flow {i in J, a in J, b in J: b != a}:
    sum {j in J : j != i} x[i,j,a,b] - sum {j in J : j != i} x[j,i,a,b] =
        if i = a then d[a,b] else if i = b then -d[a,b] else 0;

Capacity {i in J, j in J : j != i}:
    sum {a in J, b in J: b != a} x[i,j,a,b] <= M * y[i, j];

minimize cost:
    sum {i in J, j in J, a in J, b in J : j != i and b != a} dist[i,j]*x[i,j,a,b] + sum {i in J, j in J: j != i} C*y[i,j];

solve;

end;

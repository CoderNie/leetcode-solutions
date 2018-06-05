#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


// Employee info
class Employee {
public:
  Employee (int id, int importance, vector<int> & subordinates) {
    this->id = id;
    this->importance = importance;
    this->subordinates = subordinates;
  }
  // It's the unique ID of each node.
  // unique id of this employee
  int id;
  // the importance value of this employee
  int importance;
  // the id of direct subordinates
  vector<int> subordinates;
};

class Solution {
public:
  // 743. Network Delay Time
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    int adjMar[N + 1][N + 1];
    int cheapest[N + 1];
    for (int i = 1; i <= N; i++) {
      cheapest[i] = 1000000;
      for (int j = 1; j <= N; j++)
        adjMar[i][j] = -1;
    }
    for (int i = 0; i < times.size(); i++) {
      adjMar[times[i][0]][times[i][1]] = times[i][2];
    }
    queue<vector<int>> bfsQueue;
    bfsQueue.push({K, 0});
    vector<int> nowElement;
    int nowIndex, nowPrice;
    while (!bfsQueue.empty()) {
      nowElement = bfsQueue.front();
      nowIndex = nowElement[0];
      nowPrice = nowElement[1];
      bfsQueue.pop();
      if (cheapest[nowIndex] <= nowPrice) {
        continue;
      } else {
        cheapest[nowIndex] = nowPrice;
        for (int i = 1; i <= N; i++) {
          if (i != nowIndex && adjMar[nowIndex][i] > 0) {
            bfsQueue.push({i, nowPrice + adjMar[nowIndex][i]});
          }
        }
      }
    }
    int max = 0;
    for (int i = 1; i <= N; i++) {
      if (cheapest[i] == 1000000) {
        return -1;
      } else {
        if (cheapest[i] > max) {
          max = cheapest[i];
        }
      }
    }
    return max;
  }
  int findLocationById (vector<Employee*> & employees, int id) {
    for (int i = 0; i < employees.size(); i++) {
      if (employees[i]->id == id) {
        return i;
      }
    }
    return -1;
  }
  // 690. Employee Importance
  int getImportance(vector<Employee*> employees, int id) {
    queue<int> bfsQueue;
    bfsQueue.push(findLocationById(employees, id));
    int nowIndex;
    int importanceTotal = 0;
    while (!bfsQueue.empty()) {
      nowIndex = bfsQueue.front();
      importanceTotal += employees[nowIndex]->importance;
      cout << "nowIndex:" << nowIndex << "\timportance:" << employees[nowIndex]->importance << endl;
      bfsQueue.pop();
      for (int i = 0; i < employees[nowIndex]->subordinates.size(); i++) {
        bfsQueue.push(findLocationById(employees, employees[nowIndex]->subordinates[i]));
      }
    }
    cout << importanceTotal << endl;
    return 0;
  }
  // 787. Cheapest Flights Within K Stops
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    // initial adjacent matrix
    int adjMar[n][n];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        adjMar[i][j] = 0;
    for (int i = 0; i < flights.size(); i++) {
      adjMar[flights[i][0]][flights[i][1]] = flights[i][2];
    }

    // BreadthFirstSearch
    queue<vector<int>> bfsQueue;
    bfsQueue.push({src, 0, 1});
    int nowIndex, nowPriceTotal, nextPrice, nextTotal;
    int min = 10000000;
    // cut branches here
    int cheapest[n];
    for (int i = 0; i < n; i++) {
      cheapest[i] = 10000000;
    }
    while (!bfsQueue.empty()) {
      vector<int> nowElement = bfsQueue.front();
      nowIndex = nowElement[0];
      nowPriceTotal = nowElement[1];
      int nowK = nowElement[2];
      bfsQueue.pop();
      if (nowPriceTotal <= cheapest[nowIndex]) {
        cheapest[nowIndex] = nowPriceTotal;
      } else {
        continue;
      }
      for (int i = 0; i < n; i++) {
        nextPrice = adjMar[nowIndex][i];
        nextTotal = nowPriceTotal + nextPrice;
        if ((i != nowIndex) && (nextPrice > 0) && (nowK - 1 <= K)) {
          bfsQueue.push({i, nextTotal, nowK + 1});
          if (i == dst && nextTotal < min) {
            min = nextTotal;
          }
        }
      }
    }
    if (min == 10000000) {
      return -1;
    } else {
      return min;
    }
  }

  // 847. Shortest Path Visiting All Nodes
  int shortestPathLength(vector<vector<int>>& graph) {
    queue<pair<int, int>> states;
    int length = graph.size();
    for (int i = 0; i < length; i++)
      states.push({(2 << i >> 1), i});
    vector<vector<int>> res((2 << length >> 1), vector<int>(length, 0));
    while (!states.empty()) {
      int nowCover = states.front().first;
      int nowHead = states.front().second;
      states.pop();
      if (nowCover == ((2 << length >> 1) - 1))
        return res[nowCover][nowHead];
      for (int j = 0; j < graph[nowHead].size(); j++) {
        int nextCover = nowCover, nextHead = graph[nowHead][j];
        if (!((nowCover >> graph[nowHead][j]) % 2) == 1)
          nextCover += ((2 << graph[nowHead][j]) >> 1); 
        if (res[nextCover][nextHead] == 0) {
          res[nextCover][nextHead] = res[nowCover][nowHead] + 1;
          states.push({nextCover, nextHead});
        }
      }
    }
    return -1;
  }
};

// 690. Employee Importance
int employeeImportance () {
  vector<int> a = {2 ,3, 4}, b = {},        c = {},       d = {};
  Employee    em1(1, 10, a), em2(2, -1, b),  em3(3, -2, c), em4(4, -3, d);
  Solution solution;
  vector<Employee*> employees;
  employees.push_back(&em1);
  employees.push_back(&em2);
  employees.push_back(&em3);
  employees.push_back(&em4);
  solution.getImportance(employees, 1);
  return 0;
}

int main () {
  vector<vector<int>> list = {{1,2,3},{0},{0},{0}};
  Solution solution;
  cout << solution.shortestPathLength(list) << endl;
  // cout << (2 << (-1)) << endl;
  return 0;
}

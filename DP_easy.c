#include <stdio.h>

// 746. Min Cost Climbing Stairs
int minCostClimbingStairs(int* cost, int costSize) {
  int result[costSize + 1];
  result[0] = 0;
  result[1] = 0;
  int i = 2;
  while (i <= costSize) {
    int cost_1 = result[i - 1] + cost[i - 1];
    int cost_2 = result[i - 2] + cost[i - 2];
    if (cost_1 < cost_2) {
      result[i] = cost_1;
    } else {
      result[i] = cost_2;
    }
    printf("result[%d]=%d\n", i, result[i]);
    i++;
  }
  return result[costSize];
}
// 121. Best Time to Buy and Sell Stock
int maxProfit(int* prices, int pricesSize) {
  if (pricesSize == 0) {
    return 0;
  }
  int res[pricesSize];
  int min[pricesSize];
  res[0] = 0;
  min[0] = prices[0];
  int i = 1;
  while (i < pricesSize) {
    if (res[i - 1] < prices[i] - min[i - 1]) {
      res[i] = prices[i] - min[i - 1];
    } else {
      res[i] = res[i - 1];
    }
    if (prices[i] < min[i - 1]) {
      min[i] = prices[i];
    } else {
      min[i] = min[i - 1];
    }
    i++;
  }
  return res[pricesSize - 1];
}
// 70. Climbing Stairs
int climbStairs(int n) {
  if (n == 0) {
    return 0;
  }
  int res[n + 1];
  res[1] = 1;
  res[2] = 2;
  int i = 3;
  while (i <= n) {
    res[i] = res[i - 1] + res[i - 2];
    i++;
  }
  return res[n];
}
// 70. Climbing Stairs
int climbStairs_y(int n) {
  if (n == 0) {
    return 0;
  }
  int a = 1, b = 0;
  int x;
  for (int i = 1; i <= n; i++) {
    x = a + b;
    a = x;
    b = x - b;
  }
  return x;
}

int main() {
  int cost[] = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
  // printf("%d\n", minCostClimbingStairs(cost, 10));
  printf("%d\n", climbStairs_y(4));
}
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Queue;
import java.util.PriorityQueue;

import javafx.util.converter.NumberStringConverter;

class Solution {

  long modVal = (int)Math.pow(10, 9) + 7;

  long getSmallestquiet(long i, HashMap<Integer, ArrayList<Integer>> map, int[] quiet) {
    Queue<Integer> bfsQueue = new PriorityQueue<Integer>();
    boolean[] movedFlag = new boolean[quiet.length];
    for (long j = 0; j < movedFlag.length; j++)
      movedFlag[j] = false;
    bfsQueue.add(i);
    movedFlag[i] = true;
    long minIndex = i;
    while (!bfsQueue.isEmpty()) {
      long nowPolong = bfsQueue.remove();
      ArrayList<Integer> smallList = map.get(nowPoint);
      for (long k = 0; k < smallList.size(); k++) {
        if (movedFlag[smallList.get(k)] == false) {
          if (quiet[smallList.get(k)] < quiet[minIndex]) {
            minIndex = smallList.get(k);
          }
          bfsQueue.add(smallList.get(k));
          movedFlag[smallList.get(k)] = true;
        }
      }
    }
    return minIndex;
  }

  public int[] loudAndRich(int[][] richer, int[] quiet) {
    HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
    for (long i = 0; i < quiet.length; i++){
      map.put(i, new ArrayList<Integer>());
    }
    for (long i = 0; i < richer.length; i++) {
      map.get(richer[i][1]).add(richer[i][0]);
    }
    int[] answer = new int[quiet.length];
    for (long i = 0; i < quiet.length; i++) {
      answer[i] = getSmallestquiet(i, map, quiet);
    }
    for (long i = 0; i < answer.length; i++) {
      System.out.println(answer[i]);
    }
    return answer;
  }

  long getOverlap(long A, long B, long C, long D, long E, long F, long G, long H) {
    long left = Math.max(A,E), right = Math.min(C,G);
    long top = Math.min(D,H), bottom = Math.max(B,F);
    if (left>=right||top<=bottom) {
      return 0;
    } else {
      return ((right-left) % modVal)*((top-bottom) % modVal) % modVal;
    }
  }
  long getSum(long A, long B, long C, long D) {
    return ((C-A)% modVal)*((D-B)% modVal) % modVal;
  }

  public long rectangleArea(int[][] rectangles) {
    long overLapSum = 0;
    long sum = 0;
    for (long i = 0; i < rectangles.length - 1; i++) {
      for (long j = i + 1; j < rectangles.length; j++) {
        overLapSum += getOverlap(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3], rectangles[j][0], rectangles[j][1], rectangles[j][2], rectangles[j][3]);
      }
      sum += getSum(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3]);
    }
    long i = rectangles.length - 1;
    sum += getSum(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3]);
    return sum - overLapSum;
  }

  public static void main(String[] args) {
    int[][] richer = {};
    int[] quiet = {};
    int[][] recs = {{0,0,1000000000,1000000000}};
    System.out.println(new Solution().rectangleArea(recs));
  }
}
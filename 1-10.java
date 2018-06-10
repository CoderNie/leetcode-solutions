import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

import javafx.util.converter.NumberStringConverter;

class Solution {
  // 3
  public int lengthOfLongestSubstring(String s) {
    HashMap<Character, Integer> map = new HashMap<>();
    int res = 0;
    for (int j = 0, i = 0; j < s.length(); j++) {
      if (map.containsKey(s.charAt(j))) {
          i = Math.max(map.get(s.charAt(j)), i);
      }
      res = Math.max(res, j - i + 1);
      map.put(s.charAt(j), j + 1);
    }
    return res;
  }

  double getMidValue(int[] arr, int start, int end) {
    if ((end - start) % 2 == 0) {
      return arr[(end - start) / 2 + start];
    } else {
      double sum = arr[(end - start) / 2  + start] + arr[(end - start) / 2 + start + 1];
      return sum / 2;
    }
  }

  int getHalfLength(int start, int end) {
    return (end - start) / 2;
  }

  double getLastValue(ArrayList<Integer> arr) {
    int[] lastArr = new int[arr.size()];
    for(int i = 0; i < arr.size(); i++){  
      lastArr[i] = arr.get(i);
    }  
    Arrays.sort(lastArr);
    return getMidValue(lastArr, 0, lastArr.length - 1);
  }

  // 4. Median of Two Sorted Arrays__Brute Force
  public double findMedianSortedArrays(int[] nums1, int[] nums2) {
    if (nums1.length == 0) {
      return getMidValue(nums2, 0, nums2.length - 1);
    } else if (nums2.length == 0) {
      return getMidValue(nums1, 0, nums1.length - 1);
    }
    int firstStart = 0, secondStart = 0;
    int firstEnd = nums1.length - 1;
    int secondEnd = nums2.length - 1;
    double firstMid, secondMid;
    int cutLength;
    while (firstEnd - firstStart > 1 && secondEnd - secondStart > 1) {
      firstMid = getMidValue(nums1, firstStart, firstEnd);
      secondMid = getMidValue(nums2, secondStart, secondEnd);
      cutLength = Math.min(getHalfLength(firstStart, firstEnd), getHalfLength(secondStart, secondEnd));
      if (firstMid < secondMid) {
        firstStart += cutLength;
        secondEnd -= cutLength;
      } else {
        secondStart += cutLength;
        firstEnd -= cutLength;
      }
    }
    // System.out.println(firstStart + "" + firstEnd + "" + secondStart + "" + secondEnd);
    ArrayList<Integer> arr = new ArrayList<>();
    int midIndex = (secondStart + secondEnd) / 2;
    if ((secondEnd - secondStart) % 2 == 0) {
      arr.add(nums2[midIndex]);
      if (secondEnd - secondStart > 0) {
        arr.add(nums2[midIndex - 1]);
        arr.add(nums2[midIndex + 1]);
      }
    } else {
      arr.add(nums2[midIndex]);
      arr.add(nums2[midIndex + 1]);
      if (secondEnd - secondStart > 2) {
        arr.add(nums2[midIndex - 1]);
        arr.add(nums2[midIndex + 2]);
      }
    }
    midIndex = (firstStart + firstEnd) / 2;
    if ((firstEnd - firstStart) % 2 == 0) {
      arr.add(nums1[midIndex]);
      if (firstEnd - firstStart > 0) {
        arr.add(nums1[midIndex - 1]);
        arr.add(nums1[midIndex + 1]);
      }
    } else {
      arr.add(nums1[midIndex]);
      arr.add(nums1[midIndex + 1]);
      if (firstEnd - firstStart > 2) {
        arr.add(nums1[midIndex - 1]);
        arr.add(nums1[midIndex + 2]);
      }
    }
    return getLastValue(arr);
  }

  // 6. ZigZag Conversion
  public String convert(String s, int numRows) {
    if (numRows == 1) {
      return s;
    }
    int i = 0;
    Boolean shouldIncrease = true;
    ArrayList<ArrayList<Character>> res = new ArrayList<ArrayList<Character>>();
    for (int n = 0; n < numRows; n++) {
      res.add(new ArrayList<Character>());
    }
    for (int index = 0; index < s.length(); index++) {
      res.get(i).add(s.charAt(index));
      if (shouldIncrease) {
        i++;
      } else {
        i--;
      }
      if (i == numRows - 1) {
        shouldIncrease = false;
      } else if (i == 0) {
        shouldIncrease = true;
      }
    }
    StringBuilder ans = new StringBuilder();
    for (int p = 0; p < numRows; p++) {
      for (Character c: res.get(p)) {
        ans.append(c);
      }
    }
    return ans.toString();
  }
  
  // 7. Reverse Integer
  public int reverse(int x) {
    Boolean flag = false;
    if (x < 0) flag = true;
    String ans = Math.abs(x) + "";
    ans = new StringBuffer(ans).reverse().toString();
    int res;
    try {
      res = Integer.parseInt(ans);
    } catch (Exception e) {
      return 0;
    }
    if (flag) res = -res;
    return res;
  }
  // 8. String to Integer (atoi)
  public int myAtoi(String str) {
    str = str.trim();
    long res = 0, linshi;
    Character c;
    int i = 0;
    Boolean flag = false;
    if (str.startsWith("-")) {
      flag = true;
      i++;
    }
    if (str.startsWith("+")) {
      i++;
    }
    for (; i < str.length(); i++) {
      c = str.charAt(i);
      if (c >= 48 && c <= 57){
        res *= 10;
        res += (c - 48);
        if (res > Integer.MAX_VALUE) {
          if (flag) {
          return Integer.MIN_VALUE;
          } else {
            return Integer.MAX_VALUE;
          }
        }
      } else {
        break;
      }
    }
    return (int)(res * (flag ? -1 : 1));
  }

  public boolean isPalindrome(int x) {
    return new StringBuffer(x + "").reverse().toString().equals(new StringBuffer(x + "").toString()); 
  }

  public static void main(String[] args) {
    int[] nums1 = {1, 2};
    int[] nums2 = {3, 4, 5, 6};
    System.out.println(new Solution().isPalindrome(10));
  }
}


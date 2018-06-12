public class Solution {
  public String replaceSpace(StringBuffer str) {
    return str.toString().replaceAll(" ", "%20");
  }
  
  public static void main(String[] args) {
    StringBuffer str = new StringBuffer("Hello World");
    System.out.println(str);
    System.out.println(new Solution().replaceSpace(str));
  }
}
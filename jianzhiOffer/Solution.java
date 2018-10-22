import java.util.Stack;
class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;
    public TreeNode(int val) {
        this.val = val;

    }
}

public class Solution {
    public String replaceSpace(StringBuffer str) {
        return str.toString().replaceAll(" ", "%20");
    }
  
    public static void main(String[] args) {
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(1);
        root.right = new TreeNode(5);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(6);
        Solution s = new Solution();
        root = null;
        System.out.println(s.Serialize(root));
        TreeNode newRoot = s.Deserialize(s.Serialize(root));
        // s.preTraverse(root);
        // System.out.println("");
        // System.out.println(s.Serialize(root));
        // s.preTraverse(newRoot);
        // System.out.println("");
    }
    void preTraverse(TreeNode root) {
        if (root != null) {
            System.out.print(root.val);
            preTraverse(root.left);
            preTraverse(root.right);
        }
    }
    String Serialize(TreeNode root) {
        if (root == null) return "";
        StringBuffer res = new StringBuffer("");
        Stack<TreeNode> treeStack = new Stack<TreeNode>();
        treeStack.push(root);
        TreeNode node = null;
        while (!treeStack.empty()) {
            node = treeStack.pop();
            if (node == null) {
                res.append("#!");
            } else {
                res.append(node.val + "!");
                treeStack.push(node.right);
                treeStack.push(node.left);
            }
        }
        return res.toString();
    }
    int index = 0;
    TreeNode Deserialize(String str) {
        if(str == null || str.length() <= 0) return null;
        String[] strs = str.split("!");
        index = 0;
        return recur(strs);
    }
    TreeNode recur(String[] strs) {
        if (strs[index].equals("#")) {
            index++;
            return null;
        } else {
            int val = Integer.parseInt(strs[index]);
            index++;
            TreeNode newNode = new TreeNode(val);
            newNode.left = recur(strs);
            newNode.right = recur(strs);
            return newNode;
        }
    }
}
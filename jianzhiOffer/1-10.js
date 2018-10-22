function TreeNode(x) {
    this.val = x;
    this.left = null;
    this.right = null;
}

// 1. 二维数组中查找
function Find(target, array) {
    if (!Array.isArray(array) || array.length == 0 || array[0].length == 0)
        return false;
    var lenX = array.length, lenY = array[0].length;
    // 从左下角开始寻找
    var i = lenX - 1, j = 0;
    while (true) {
        if (array[i][j] === target) {
            return true;
        } else if (array[i][j] > target) {
            if (i > 0) {
                i--;
            } else {
                return false;
            }
        } else {
            if (j + 1 < lenY) {
                j++;
            } else {
                return false;
            }
        }
    }
    return false;
}

// 2. 替换空格
function replaceSpace(str){
    var res = "";
    for (var i = 0; i < str.length; i++) {
        if (str[i] !== ' ') {
            res += str[i];
        } else {
            res += "%20";
        }
    }
    return res;
}

// 3. 从尾到头打印链表
function printListFromTailToHead(head){
    var res = [];
    while (head) {
        res.unshift(head.val);
        head = head.next;
    }
    return res;
}

// 4. 重建二叉树
function reConstructBinaryTree(pre, vin){
    return reConstructRecur(pre, 0, pre.length - 1, vin, 0, vin.length - 1);
}

function reConstructRecur(pre, preBegin, preEnd, vin, vinStart, vinEnd) {
    if (preBegin > preEnd) {
        return null;
    } else {
        var nowNode = new TreeNode(pre[preBegin]);
        if (preBegin < preEnd) {
            var key = vinStart;
            for (; key <= vinEnd; key++) {
                if (vin[key] === pre[preBegin])
                    break;
            }
            var leftLen = key - vinStart;
            var rightLen = vinEnd - key;
            nowNode.left = reConstructRecur(pre, preBegin + 1, preBegin + leftLen, vin, vinStart, vinStart + leftLen - 1);
            nowNode.right = reConstructRecur(pre, preEnd - rightLen + 1, preEnd, vin, vinEnd - rightLen + 1, vinEnd);
        }
        return nowNode;
    }
}

// 5. 用两个栈实现队列
var stack1 = []
var stack2 = []
function push(node){
    stack1.push(node);
}

function pop(){
    while (stack1.length > 0) {
        stack2.push(stack1.pop());
    }
    var res = stack2.pop();
    while (stack2.length > 0) {
        stack1.push(stack2.pop());
    }
    return res
}

// 6. 旋转数组的最小数字



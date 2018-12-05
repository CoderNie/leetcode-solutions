#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <stack>

#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isWord;
    TrieNode(): isWord(false) {}
};

// 208. Implement Trie (Prefix Tree)
class Trie {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        delete root;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                cur->children[ch] = new TrieNode();
            }
            cur = cur->children[ch];
        }
        cur->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                return false;
            } else {
                cur = cur->children[ch];
            }
        }
        return cur->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            char ch = prefix[i];
            if (cur->children.find(ch) == cur->children.end()) {
                return false;
            } else {
                cur = cur->children[ch];
            }
        }
        return true;
    }

    string getPrefix(string word) {
        TrieNode *cur = root;
        string res = "";
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                break;
            } else {
                res += ch;
                cur = cur->children[ch];
                if (cur->isWord)
                    break;
            }
        }
        return (res == "" || !cur->isWord) ? word : res;
    }
};

// 211. Add and Search Word - Data structure design
class WordDictionary {
private:
    TrieNode *root;
    bool searchRecur(string &word, int index, TrieNode* node) {
        if (word.size() == index) {
            return node->isWord;
        }    
        if (word[index] == '.') {
            unordered_map<char, TrieNode*>::iterator iter;
            for (iter = node->children.begin(); iter != node->children.end(); iter++) {
                if (searchRecur(word, index + 1, iter->second)) {
                    return true;
                }
            }
            return false;
        } else {
            if (node->children.find(word[index]) == node->children.end()) {
                return false;
            } else {
                return searchRecur(word, index + 1, node->children[word[index]]);
            }
        }
    }
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    ~WordDictionary() {
        delete root;
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (cur->children.find(ch) == cur->children.end()) {
                cur->children[ch] = new TrieNode();
            }
            cur = cur->children[ch];
        }
        cur->isWord = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchRecur(word, 0, root);
    }
};

// 421. Maximum XOR of Two Numbers in an Array
struct TrieNodeForXOR {
    TrieNodeForXOR *zero, *one;
    bool isNum;
    int val;
    TrieNodeForXOR(): isNum(false), zero(NULL), one(NULL) {}
};
class TrieForXOR {
private:
    TrieNodeForXOR *root;
    int findMaxiumXORRecur (TrieNodeForXOR *zero, TrieNodeForXOR *one) {
        if (zero->isNum && one->isNum)
            return zero->val ^ one->val;
        // zero/one 都只有一个分支
        if ((zero->zero == NULL || zero->one == NULL) && (one->zero == NULL || one->one == NULL)) {
            return findMaxiumXORRecur(zero->zero == NULL ? zero->one : zero->zero, one->zero == NULL ? one->one : one->zero);
        // zero 只有一个分支
        } else if (zero->zero == NULL) {
            return findMaxiumXORRecur(zero->one, one->zero);
        } else if (zero->one == NULL) {
            return findMaxiumXORRecur(zero->zero, one->one);
        // one 只有一个分支
        } else if (one->zero == NULL) {
            return findMaxiumXORRecur(zero->zero, one->one);
        } else if (one->one == NULL) {
            return findMaxiumXORRecur(zero->one, one->zero);
        // 都有两个分支
        } else {
            return max(findMaxiumXORRecur(zero->zero, one->one), findMaxiumXORRecur(zero->one, one->zero));
        }
    }
public:
    TrieForXOR() {
        root = new TrieNodeForXOR();
    }
    void insert(int num) {
        TrieNodeForXOR *cur = root;
        for (int i = 31; i >= 0; i--) {
            int now = (num >> i) & 1;
            // cout << now;
            if (now == 0) {
                if (cur->zero == NULL)
                    cur->zero = new TrieNodeForXOR();
                cur = cur->zero;
            } else {
                if (cur->one == NULL)
                    cur->one = new TrieNodeForXOR();
                cur = cur->one;
            }
        }
        // cout << endl;
        cur->isNum = true;
        cur->val = num;
    }
    int findMaxiumXOR () {
        TrieNodeForXOR *realRoot = root;
        // find real root
        while (true) {
            if (realRoot->zero == NULL && realRoot->one != NULL) {
                realRoot = realRoot->one;
            } else if (realRoot->zero != NULL && realRoot->one == NULL) {
                realRoot = realRoot->zero;
            } else {
                break;
            }
        }
        return findMaxiumXORRecur(realRoot->zero, realRoot->one);
    }
};

class Solution {
public:

    vector<string> split(const string& str, const string& delim) {
        vector<string> res;
        if("" == str) return res;
        //先将要切割的字符串从string类型转换为char*类型
        char * strs = new char[str.length() + 1] ; //不要忘了
        strcpy(strs, str.c_str()); 
    
        char * d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());
    
        char *p = strtok(strs, d);
        while(p) {
            string s = p; //分割得到的字符串转换为string类型
            res.push_back(s); //存入结果数组
            p = strtok(NULL, d);
        }
    
        return res;
    }

    // 648. Replace Words
    string replaceWords(vector<string>& dict, string sentence) {
        Trie trie;
        for (string str : dict)
            trie.insert(str);
        vector<string> words = split(sentence, " ");
        string res = "";
        for (int i = 0; i < words.size() - 1; i++)
            res += trie.getPrefix(words[i]) + " ";
        res += trie.getPrefix(words[words.size() - 1]);
        return res;
    }

    // 421. Maximum XOR of Two Numbers in an Array
    int findMaximumXOR(vector<int>& nums) {
        if (nums.size() <= 1)
            return 0;
        TrieForXOR trieForXOR;
        for (int num : nums) {
            trieForXOR.insert(num);
        }
        return trieForXOR.findMaxiumXOR();
    }
};

int main() {
    int m = 2147483646;
    int n = 2147483647;
    Solution solution;
    vector<int> nums = {2, 3, 5, 8, 10, 25};
    cout << solution.findMaximumXOR(nums) << endl;
}
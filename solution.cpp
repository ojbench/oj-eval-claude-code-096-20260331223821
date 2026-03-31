#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    unordered_map<int, int> depth_map;  // node value -> depth
    unordered_map<int, int> parent_map; // node value -> parent value
    int index;

    TreeNode* buildTree(const vector<int>& preorder) {
        if (index >= preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[index++]);
        root->left = buildTree(preorder);
        root->right = buildTree(preorder);
        return root;
    }

    void findDepthAndParent(TreeNode* node, int depth, int parent) {
        if (!node) return;

        depth_map[node->val] = depth;
        parent_map[node->val] = parent;

        findDepthAndParent(node->left, depth + 1, node->val);
        findDepthAndParent(node->right, depth + 1, node->val);
    }

    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    bool isCousins(int x, int y) {
        // Check if both nodes exist
        if (depth_map.find(x) == depth_map.end() ||
            depth_map.find(y) == depth_map.end()) {
            return false;
        }

        // Check if same depth and different parents
        return depth_map[x] == depth_map[y] &&
               parent_map[x] != parent_map[y];
    }

public:
    void solve() {
        int q;
        cin >> q;

        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }

        vector<int> preorder;
        int val;
        while (cin >> val) {
            preorder.push_back(val);
        }

        // Build tree
        index = 0;
        TreeNode* root = buildTree(preorder);

        // Find depth and parent for all nodes
        findDepthAndParent(root, 0, -1);

        // Answer queries
        for (const auto& query : queries) {
            cout << (isCousins(query.first, query.second) ? 1 : 0) << endl;
        }

        // Clean up memory
        deleteTree(root);
    }
};

int main() {
    Solution sol;
    sol.solve();
    return 0;
}

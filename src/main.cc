#include <iostream>
#include <vector>

using namespace std;
// Definition for a QuadTree node.
class Node {
private:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
public:
    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    static bool gridIsUniform(vector<vector<int>>& grid) {
        int firstVal = grid[0][0];
        for (auto it: grid) {
            for (auto it2: it) {
                if (it2 != firstVal) return false;
            }
        }
        return true;
    }

    static void getSubgrids(vector<vector<vector<int>>>& subgrids, vector<vector<int>>& grid) {
        vector<vector<int>> topLeft, topRight, botLeft, botRight;
        for (u_int32_t i = 0; i < grid.size()/2; i++) {
            topLeft.push_back({});
            topRight.push_back({});
            botLeft.push_back({});
            botRight.push_back({});
            for (u_int32_t j = 0; j < grid.size()/2; j++) {
                topLeft[i].push_back(grid[i][j]);
                topRight[i].push_back(grid[i][j+grid.size()/2]);
                botLeft[i].push_back(grid[i+grid.size()/2][j]);
                botRight[i].push_back(grid[i + grid.size()/2][j + grid.size()/2]);
            }
        }
        subgrids.push_back(topLeft);
        subgrids.push_back(topRight);
        subgrids.push_back(botLeft);
        subgrids.push_back(botRight);
    }
    Node* construct(vector<vector<int>>& grid) {
        Node *output;
        if (gridIsUniform(grid)) {
            // set leaf true and val to val
            output = new Node(grid[0][0], true);
        }
        else {
            vector<vector<vector<int>>> subgrids;
            getSubgrids(subgrids, grid);
            // call construct on 4 subgrids and add to output node
            Node *topLeft, *topRight, *botLeft, *botRight;
            topLeft = construct(subgrids[0]);
            topRight = construct(subgrids[1]);
            botLeft = construct(subgrids[2]);
            botRight = construct(subgrids[3]);
            
            output = new Node(1, 0, topLeft, topRight, botLeft, botRight);
        }
            
        return output;
    }
};

int main() {
    vector<vector<int>> input = {{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}};
    // vector<vector<int>> input = {{0,1},{1,0}};
    Solution s;
    Node* output = s.construct(input);
    cout << output << endl;
    return 0;
}
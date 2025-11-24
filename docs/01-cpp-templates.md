# C++ 面接テンプレート集

このドキュメントは「見ずに書けるレベル」まで暗記すべきC++コードをまとめたものです。

---

## 📌 学習方法

1. **毎日1つずつ手書きで写経**（タイピングではなく紙に書く）
2. **翌日、見ずに書けるかテスト**
3. **LeetCodeで実際に使ってみる**

---

## 1️⃣ vector（最重要）

### 基本操作
```cpp
#include <vector>
using namespace std;// 初期化

vector<int> v;              // 空のvector
vector<int> v(10);          // サイズ10、値は0
vector<int> v(10, -1);      // サイズ10、値は-1
vector<int> v = {1, 2, 3};  // 初期値指定// 2D配列
vector<vector<int>> grid(n, vector<int>(m));     // n×m
vector<vector<int>> grid(n, vector<int>(m, 0));  // 0で初期化// 操作

v.push_back(x);      // 末尾に追加
v.pop_back();        // 末尾を削除
v.size();            // サイズ
v.empty();           // 空かどうか
v.front();           // 先頭要素
v.back();            // 末尾要素// イテレート

for(int x : v) { }                    // 範囲for
for(int i = 0; i < v.size(); i++) { } // index for// ソート

sort(v.begin(), v.end());              // 昇順
sort(v.begin(), v.end(), greater<int>()); // 降順// カスタムソート（ラムダ）
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;  // 降順
});
```

### Prefix Sum（超頻出）
```cpp
// 1D Prefix Sum
vector<int> prefix(n + 1, 0);

for(int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + nums[i];
}

// 区間[l, r]の和 = prefix[r+1] - prefix[l]// 2D Prefix Sum
vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
        prefix[i][j] = grid[i-1][j-1]
        + prefix[i-1][j]
        + prefix[i][j-1]
        - prefix[i-1][j-1];
    }
}
```

---

## 2️⃣ unordered_map / unordered_set

### unordered_map（ハッシュマップ）
```cpp
#include <unordered_map>
using namespace std;

unordered_map<int, int> mp;// 追加・更新
mp[key] = value;
mp[key]++;  // カウントアップ// 存在確認

if(mp.count(key)) { }      // 存在するか
if(mp.find(key) != mp.end()) { }  // 同上// イテレート

for(auto& [key, val] : mp) {
    // keyとvalを使う
}// 削除
mp.erase(key);
```

### unordered_set（ハッシュセット）
```cpp
#include <unordered_set>
using namespace std;

unordered_set<int> seen;// 追加
seen.insert(x);// 存在確認
if(seen.count(x)) { }// 削除
seen.erase(x);
```

### 使い分け
- **unordered_map**: カウント、値の対応
- **unordered_set**: 訪問済み管理、重複排除
- **map/set**: 順序が必要な場合（O(log n)）

---

## 3️⃣ priority_queue（ヒープ）
```cpp
#include <queue>
using namespace std;// Max Heap（デフォルト）

priority_queue<int> maxHeap;
maxHeap.push(10);

int top = maxHeap.top();  // 最大値
maxHeap.pop();// Min Heap（重要！）
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(10);

int top = minHeap.top();  // 最小値
minHeap.pop();// カスタム比較（ペア）
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({distance, node});
```

### 典型的な使い方
```cpp
// Top K 問題
priority_queue<int, vector<int>, greater<int>> minHeap;
for(int x : nums) {
    minHeap.push(x);
    if(minHeap.size() > k) {
        minHeap.pop();
    }
}
// minHeap.top() が k番目に大きい要素
```

---

## 4️⃣ Binary Search（二分探索）

### パターン1: 値の検索
```cpp
// 配列から target を探す
int binarySearch(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;

    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(arr[mid] == target) return mid;
        else if(arr[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;  // 見つからない
}
```

### パターン2: 境界探索（lower_bound的）
```cpp
// target 以上の最小のインデックス
int lowerBound(vector<int>& arr, int target) {
    int l = 0, r = arr.size();

    while(l < r) {
        int mid = l + (r - l) / 2;
        if(arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}
```

### パターン3: 答えの二分探索（超頻出）
```cpp
// 「条件を満たす最小値」を探す
bool check(int x) {
    // x が条件を満たすか判定
    return true;
}

int binarySearchOnAnswer() {
    int l = 1, r = 1e9;  // 探索範囲
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            r = mid;  // 答えを小さくできる
        } else {
            l = mid + 1;
        }
    }
    return l;
}
```

---

## 5️⃣ Tree（木構造）

### TreeNode定義（LeetCode標準）
```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

### DFS（再帰・ラムダ）
```cpp
// 前順走査（preorder）
auto dfs = [&](auto&& self, TreeNode* node) -> void {
    if(!node) return;
    // 処理（前）
    self(self, node->left);
    self(self, node->right);
};
dfs(dfs, root);// 中順走査（inorder）

auto dfs = [&](auto&& self, TreeNode* node) -> void {
    if(!node) return;
    self(self, node->left);
    // 処理（中）
    self(self, node->right);
};

// 後順走査（postorder）
auto dfs = [&](auto&& self, TreeNode* node) -> void {
    if(!node) return;
    self(self, node->left);
    self(self, node->right);
    // 処理（後）
};
```

### BFS（レベル順走査）
```cpp
#include <queue>void bfs(TreeNode* root) {
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();        // 処理        if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
}
```

---

## 6️⃣ Graph（グラフ）

### グラフ表現
```cpp
// 隣接リスト
int n = 5;  // ノード数
vector<vector<int>> graph(n);
graph[u].push_back(v);  // u -> v の辺// 重み付き
vector<vector<pair<int,int>>> graph(n);  // {隣接ノード, 重み}
graph[u].push_back({v, weight});
```

### DFS（再帰）
```cpp
vector<bool> visited(n, false);auto dfs = [&](auto&& self, int u) -> void {
    visited[u] = true;

    // 処理
    for(int v : graph[u]) {
        if(!visited[v]) {
            self(self, v);
        }
    }
};
dfs(dfs, start);
```

### BFS（最短経路）
```cpp
vector<int> dist(n, -1);
queue<int> q;
q.push(start);
dist[start] = 0;

while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(int v : graph[u]) {
        if(dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}
```

### Union-Find（素集合データ構造）
```cpp
class UnionFind {
public:
    vector<int> parent, rank;UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);  // 経路圧縮
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py) return false;    if(rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if(rank[px] == rank[py]) rank[px]++;    return true;
    }
};

---

## 7️⃣ よく使うイディオム

### 例外処理テンプレ
```cpp
// 空配列チェック
if(nums.empty()) return {};// サイズ1の処理
if(nums.size() == 1) return nums[0];// nullptr チェック
if(!root) return 0;// 範囲チェック
if(i < 0 || i >= n) continue;
```

### ラムダでの再帰
```cpp
// 戻り値あり
auto dfs = [&](auto&& self, int x) -> int {
    // 処理
    return self(self, x - 1);
};

int result = dfs(dfs, n);// 戻り値なし
auto dfs = [&](auto&& self, int x) -> void {
    // 処理
    self(self, x - 1);
};
dfs(dfs, n);
```

### よく使う初期化
```cpp
// 無限大
const int INF = 1e9;
const long long LINF = 1e18;// 4方向移動
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};// 8方向移動
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
```

---

## 🎯 暗記チェックリスト

毎週確認してください：

- [ ] vector の初期化・操作を見ずに書ける
- [ ] unordered_map/set の使い分けができる
- [ ] priority_queue の min/max を正しく書ける
- [ ] Binary Search の3パターンを説明できる
- [ ] Tree の DFS/BFS を見ずに書ける
- [ ] Graph の DFS/BFS を見ずに書ける
- [ ] Union-Find を見ずに書ける
- [ ] ラムダ再帰を理解している
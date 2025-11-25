# Priority Queue（優先度キュー / ヒープ）解説

## 1. 基本的な使い方

### Max Heap（デフォルト）

```cpp
priority_queue<int> maxHeap;

maxHeap.push(10);
maxHeap.push(30);
maxHeap.push(20);

cout << maxHeap.top();  // 30（最大値）
maxHeap.pop();
```

### Min Heap

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;

minHeap.push(10);
minHeap.push(30);
minHeap.push(20);

cout << minHeap.top();  // 10（最小値）
```

**暗記:** `greater<int>` = Min Heap（greater = 大きい方を下に = 小さい方が top）

---

## 2. 計算量

| 操作 | 計算量 |
|------|--------|
| `push()` | O(log n) |
| `pop()` | O(log n) |
| `top()` | O(1) |
| `size()` | O(1) |
| `empty()` | O(1) |

---

## 3. pair での使用

```cpp
// Max Heap（first 優先、次に second）
priority_queue<pair<int, int>> maxPairHeap;

// Min Heap
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPairHeap;

maxPairHeap.push({10, 1});
maxPairHeap.push({30, 2});

auto [val, idx] = maxPairHeap.top();  // {30, 2}
```

---

## 4. カスタム比較関数

### 構造体を使う方法

```cpp
struct CompareDistance {
    bool operator()(const Point& a, const Point& b) {
        int distA = a.x * a.x + a.y * a.y;
        int distB = b.x * b.x + b.y * b.y;
        return distA > distB;  // Min Heap（距離が小さい順）
    }
};

priority_queue<Point, vector<Point>, CompareDistance> pq;
```

### ラムダを使う方法

```cpp
auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second > b.second;  // second の小さい順
};

priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
```

**比較関数のルール:**
- `return a > b` → Min Heap（a が大きいと後ろに行く）
- `return a < b` → Max Heap（a が小さいと後ろに行く）

---

## 5. Top-K 問題パターン

「K 番目に大きい/小さい」「上位 K 個」を求める問題。

### Kth Largest Element (LC 215)

```cpp
int findKthLargest(vector<int>& nums, int k) {
    // サイズ k の Min Heap を維持
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();  // 最小値を削除
        }
    }

    return minHeap.top();  // k 番目に大きい
}
```

**考え方:**
- Min Heap でサイズ k を維持
- サイズが k を超えたら最小値を削除
- 最終的に top() が k 番目に大きい値

**計算量:** O(n log k)

---

### Top K Frequent Elements (LC 347)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    // 頻度カウント
    unordered_map<int, int> freq;
    for (int num : nums) freq[num]++;

    // サイズ k の Min Heap（頻度でソート）
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> minHeap(cmp);

    for (auto& [num, count] : freq) {
        minHeap.push({num, count});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }

    return result;
}
```

---

### K Closest Points to Origin (LC 973)

```cpp
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // サイズ k の Max Heap（距離が遠い順）
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
    };

    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxHeap(cmp);

    for (auto& point : points) {
        maxHeap.push(point);
        if (maxHeap.size() > k) {
            maxHeap.pop();  // 最も遠い点を削除
        }
    }

    // 結果を取り出す
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return result;
}
```

**注意:** 「最も近い k 個」を求めるには Max Heap を使う（遠いものを削除）

---

## 6. Find Median from Data Stream (LC 295)

2つのヒープを使って中央値をリアルタイムで求める。

```cpp
class MedianFinder {
private:
    priority_queue<int> maxHeap;  // 小さい方の半分（max heap）
    priority_queue<int, vector<int>, greater<int>> minHeap;  // 大きい方の半分（min heap）

public:
    void addNum(int num) {
        // 1. まず maxHeap に追加
        maxHeap.push(num);

        // 2. maxHeap の最大値を minHeap に移動
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // 3. サイズのバランスを取る（maxHeap >= minHeap）
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();  // 奇数個
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;  // 偶数個
    }
};
```

**図解:**
```
        maxHeap (小さい方)     |     minHeap (大きい方)
        [3, 2, 1]             |     [4, 5, 6]
             ↑ top=3          |      top=4 ↑
                      中央値 = (3 + 4) / 2 = 3.5
```

---

## 7. K-way Merge パターン

複数のソート済みリストをマージする。

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;  // Min Heap
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);

    // 各リストの先頭をヒープに追加
    for (ListNode* head : lists) {
        if (head) minHeap.push(head);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();

        tail->next = node;
        tail = tail->next;

        if (node->next) {
            minHeap.push(node->next);  // 次のノードをヒープに追加
        }
    }

    return dummy.next;
}
```

**計算量:** O(n log k)（n = 全要素数、k = リスト数）

---

## 8. Dijkstra での使用

```cpp
vector<int> dijkstra(vector<vector<pair<int,int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);

    // Min Heap: {距離, ノード}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // 古い情報はスキップ

        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

**ポイント:** `greater<>` で Min Heap にする（距離が小さい順に処理）

---

## 9. よくあるパターンまとめ

| パターン | ヒープの種類 | 理由 |
|----------|-------------|------|
| K 番目に大きい | Min Heap (サイズ k) | 小さいものを削除 |
| K 番目に小さい | Max Heap (サイズ k) | 大きいものを削除 |
| 中央値 | Max + Min | 半分ずつ管理 |
| K-way Merge | Min Heap | 最小値を順番に取り出す |
| Dijkstra | Min Heap | 距離が小さい順に処理 |

---

## 10. デバッグのコツ

```cpp
// ヒープの内容を確認（破壊的）
priority_queue<int> temp = originalHeap;  // コピー
while (!temp.empty()) {
    cout << temp.top() << " ";
    temp.pop();
}
```

**注意:** priority_queue はイテレートできないので、コピーして確認

---

## 11. よくある間違い

### Min Heap の宣言忘れ

```cpp
// NG: Max Heap になる
priority_queue<int> pq;

// OK: Min Heap
priority_queue<int, vector<int>, greater<int>> pq;
```

### 比較関数の向きを間違える

```cpp
// Max Heap にしたい場合
return a < b;  // a が小さいと後ろに行く = 大きいものが top

// Min Heap にしたい場合
return a > b;  // a が大きいと後ろに行く = 小さいものが top
```

### ラムダで decltype を忘れる

```cpp
// NG: コンパイルエラー
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;

// OK: decltype を使う
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
```

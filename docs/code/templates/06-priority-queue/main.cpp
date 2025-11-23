/**
 * Priority Queue（優先度キュー / ヒープ）テンプレート
 * Top-K 問題や Dijkstra で頻出
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

// ========================================
// 1. 基本的な使い方
// ========================================

void basicUsage()
{
    // Max Heap（デフォルト、最大値が top）
    priority_queue<int> maxHeap;

    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);

    cout << "Max Heap: ";
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << " "; // 30, 20, 10, 5
        maxHeap.pop();
    }
    cout << "\n";

    // Min Heap（最小値が top）
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);
    minHeap.push(5);

    cout << "Min Heap: ";
    while (!minHeap.empty())
    {
        cout << minHeap.top() << " "; // 5, 10, 20, 30
        minHeap.pop();
    }
    cout << "\n";
}

// ========================================
// 2. pair での使用
// ========================================

void pairHeap()
{
    // pair<int, int> の Max Heap（first優先、次にsecond）
    priority_queue<pair<int, int>> maxPairHeap;

    maxPairHeap.push({10, 1});
    maxPairHeap.push({30, 2});
    maxPairHeap.push({20, 3});

    cout << "Max Pair Heap: ";
    while (!maxPairHeap.empty())
    {
        auto [val, idx] = maxPairHeap.top();
        cout << "(" << val << "," << idx << ") ";
        maxPairHeap.pop();
    }
    cout << "\n";

    // pair<int, int> の Min Heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPairHeap;

    minPairHeap.push({10, 1});
    minPairHeap.push({30, 2});
    minPairHeap.push({20, 3});

    cout << "Min Pair Heap: ";
    while (!minPairHeap.empty())
    {
        auto [val, idx] = minPairHeap.top();
        cout << "(" << val << "," << idx << ") ";
        minPairHeap.pop();
    }
    cout << "\n";
}

// ========================================
// 3. カスタム比較関数
// ========================================

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// 距離で比較
struct CompareDistance
{
    bool operator()(const Point &a, const Point &b)
    {
        int distA = a.x * a.x + a.y * a.y;
        int distB = b.x * b.x + b.y * b.y;
        return distA > distB; // Min Heap（距離が小さい順）
    }
};

void customComparator()
{
    priority_queue<Point, vector<Point>, CompareDistance> pq;

    pq.push(Point(3, 4)); // 距離 5
    pq.push(Point(1, 1)); // 距離 1.41
    pq.push(Point(2, 2)); // 距離 2.83

    cout << "Custom comparator (distance): ";
    while (!pq.empty())
    {
        Point p = pq.top();
        pq.pop();
        cout << "(" << p.x << "," << p.y << ") ";
    }
    cout << "\n";
}

// ========================================
// 4. ラムダでの比較（C++11以降）
// ========================================

void lambdaComparator()
{
    // ラムダ比較関数
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second; // second の小さい順（Min Heap）
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    pq.push({1, 100});
    pq.push({2, 50});
    pq.push({3, 75});

    cout << "Lambda comparator: ";
    while (!pq.empty())
    {
        auto [id, val] = pq.top();
        pq.pop();
        cout << "(" << id << "," << val << ") ";
    }
    cout << "\n";
}

// ========================================
// 実戦問題パターン
// ========================================

// 問題1: Kth Largest Element in an Array (LC 215)
int findKthLargest(vector<int> &nums, int k)
{
    // Min Heap でサイズ k を維持
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums)
    {
        minHeap.push(num);
        if (minHeap.size() > k)
        {
            minHeap.pop(); // 最小値を削除
        }
    }

    return minHeap.top();
}

// 問題2: Top K Frequent Elements (LC 347)
vector<int> topKFrequent(vector<int> &nums, int k)
{
    // 頻度カウント
    unordered_map<int, int> freq;
    for (int num : nums)
    {
        freq[num]++;
    }

    // Min Heap（頻度でソート）
    auto cmp = [](pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

    for (auto &[num, count] : freq)
    {
        minHeap.push({num, count});
        if (minHeap.size() > k)
        {
            minHeap.pop();
        }
    }

    vector<int> result;
    while (!minHeap.empty())
    {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }

    return result;
}

// 問題3: K Closest Points to Origin (LC 973)
vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
{
    // Max Heap（距離で管理）
    auto cmp = [](const vector<int> &a, const vector<int> &b)
    {
        return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
    };

    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxHeap(cmp);

    for (auto &point : points)
    {
        maxHeap.push(point);
        if (maxHeap.size() > k)
        {
            maxHeap.pop();
        }
    }

    vector<vector<int>> result;
    while (!maxHeap.empty())
    {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return result;
}

// 問題4: Merge K Sorted Lists (LC 23)
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    // Min Heap
    auto cmp = [](ListNode *a, ListNode *b)
    {
        return a->val > b->val;
    };
    priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> minHeap(cmp);

    // 各リストの先頭をヒープに追加
    for (ListNode *head : lists)
    {
        if (head)
            minHeap.push(head);
    }

    ListNode dummy(0);
    ListNode *tail = &dummy;

    while (!minHeap.empty())
    {
        ListNode *node = minHeap.top();
        minHeap.pop();

        tail->next = node;
        tail = tail->next;

        if (node->next)
        {
            minHeap.push(node->next);
        }
    }

    return dummy.next;
}

// 問題5: Find Median from Data Stream (LC 295)
class MedianFinder
{
private:
    priority_queue<int> maxHeap;                            // 小さい方の半分
    priority_queue<int, vector<int>, greater<int>> minHeap; // 大きい方の半分

public:
    void addNum(int num)
    {
        // まず maxHeap に追加
        maxHeap.push(num);

        // maxHeap の最大値を minHeap に移動
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // サイズのバランスを取る
        if (maxHeap.size() < minHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian()
    {
        if (maxHeap.size() > minHeap.size())
        {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

// 問題6: Kth Smallest Element in a Sorted Matrix (LC 378)
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size();

    // Min Heap: {値, 行, 列}
    auto cmp = [](const vector<int> &a, const vector<int> &b)
    {
        return a[0] > b[0];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> minHeap(cmp);

    // 各行の最初の要素をヒープに追加
    for (int i = 0; i < n; i++)
    {
        minHeap.push({matrix[i][0], i, 0});
    }

    int count = 0;
    int result = 0;

    while (!minHeap.empty())
    {
        auto top = minHeap.top();
        minHeap.pop();

        int val = top[0];
        int row = top[1];
        int col = top[2];

        count++;
        if (count == k)
        {
            result = val;
            break;
        }

        // 同じ行の次の要素を追加
        if (col + 1 < n)
        {
            minHeap.push({matrix[row][col + 1], row, col + 1});
        }
    }

    return result;
}

// 問題7: Reorganize String (LC 767)
string reorganizeString(string s)
{
    // 文字の頻度カウント
    unordered_map<char, int> freq;
    for (char c : s)
    {
        freq[c]++;
    }

    // Max Heap（頻度順）
    priority_queue<pair<int, char>> maxHeap;
    for (auto &[c, count] : freq)
    {
        maxHeap.push({count, c});
    }

    string result = "";
    pair<int, char> prev = {-1, '#'};

    while (!maxHeap.empty())
    {
        auto [count, c] = maxHeap.top();
        maxHeap.pop();

        result += c;

        // 前の文字を戻す
        if (prev.first > 0)
        {
            maxHeap.push(prev);
        }

        prev = {count - 1, c};
    }

    return result.length() == s.length() ? result : "";
}

// ========================================
// Dijkstra での使用（重要パターン）
// ========================================

vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int start)
{
    int n = graph.size();
    vector<int> dist(n, INT_MAX);

    // Min Heap: {距離, ノード}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, weight] : graph[u])
        {
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// ========================================
// よく使うパターンまとめ
// ========================================

void commonPatterns()
{
    // パターン1: Top-K 問題（Min Heap、サイズ k を維持）
    {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        int k = 2;

        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums)
        {
            minHeap.push(num);
            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }
        // minHeap.top() が k 番目に大きい要素
    }

    // パターン2: K-way Merge（複数のソート済みリストをマージ）
    {
        vector<vector<int>> lists = {{1, 4, 5}, {1, 3, 4}, {2, 6}};

        auto cmp = [](pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
        {
            return a.first > b.first;
        };
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       decltype(cmp)>
            minHeap(cmp);

        // {値, {リストID, インデックス}}
        for (int i = 0; i < lists.size(); i++)
        {
            if (!lists[i].empty())
            {
                minHeap.push({lists[i][0], {i, 0}});
            }
        }

        vector<int> result;
        while (!minHeap.empty())
        {
            auto [val, pos] = minHeap.top();
            minHeap.pop();

            result.push_back(val);

            int listId = pos.first;
            int idx = pos.second;

            if (idx + 1 < lists[listId].size())
            {
                minHeap.push({lists[listId][idx + 1], {listId, idx + 1}});
            }
        }
    }

    // パターン3: Sliding Window Maximum（デック使用が普通だが、ヒープでも可能）
    {
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        priority_queue<pair<int, int>> maxHeap; // {値, インデックス}
        vector<int> result;

        for (int i = 0; i < nums.size(); i++)
        {
            maxHeap.push({nums[i], i});

            // ウィンドウ外の要素を削除
            while (!maxHeap.empty() && maxHeap.top().second <= i - k)
            {
                maxHeap.pop();
            }

            if (i >= k - 1)
            {
                result.push_back(maxHeap.top().first);
            }
        }
    }
}

// ========================================
// デバッグのコツ
// ========================================

void debugHeap()
{
    priority_queue<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);

    // ヒープの内容を確認（破壊的）
    cout << "Heap contents: ";
    priority_queue<int> temp = maxHeap; // コピー
    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << "\n";

    // 元のヒープは保持される
    cout << "Original heap top: " << maxHeap.top() << "\n";
}

// ========================================
// 時間計算量
// ========================================

void timeComplexity()
{
    /*
     * Priority Queue の計算量:
     *
     * push():    O(log n)
     * pop():     O(log n)
     * top():     O(1)
     * size():    O(1)
     * empty():   O(1)
     *
     * 構築:
     * - 空から1つずつ追加: O(n log n)
     * - make_heap 使用: O(n)
     *
     * よくあるパターン:
     * - Top-K 問題: O(n log k)
     * - K-way Merge: O(n log k)
     * - Dijkstra: O((V + E) log V)
     */
}

int main()
{
    cout << "=== Basic Usage ===\n";
    basicUsage();

    cout << "\n=== Pair Heap ===\n";
    pairHeap();

    cout << "\n=== Custom Comparator ===\n";
    customComparator();

    cout << "\n=== Lambda Comparator ===\n";
    lambdaComparator();

    // Kth Largest Element
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "\n=== Kth Largest Element ===\n";
    cout << "3rd largest: " << findKthLargest(nums, 3) << "\n";

    // Top K Frequent
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    cout << "\n=== Top K Frequent ===\n";
    vector<int> topK = topKFrequent(nums2, 2);
    cout << "Top 2 frequent: ";
    for (int x : topK)
        cout << x << " ";
    cout << "\n";

    // Median Finder
    cout << "\n=== Median Finder ===\n";
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << "Median: " << mf.findMedian() << "\n";
    mf.addNum(3);
    cout << "Median: " << mf.findMedian() << "\n";

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] Max Heap の作り方
 * [ ] Min Heap の作り方（greater<int>）
 * [ ] pair での使用
 * [ ] カスタム比較関数
 * [ ] Top-K 問題のパターン（Min Heap、サイズ k）
 * [ ] K-way Merge のパターン
 * [ ] Median Finder（2つのヒープ）
 * [ ] Dijkstra での使用
 * [ ] push, pop, top の計算量
 * [ ] ヒープのコピー方法
 */
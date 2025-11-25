/**
 * Priority Queue（優先度キュー / ヒープ）- 解答
 *
 * problems.cpp の解答です。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <climits>
using namespace std;

// ========================================
// 解答1: 基本的な使い方
// ========================================

void basicUsage()
{
    // A1-1: Max Heap を作成（デフォルト）
    priority_queue<int> maxHeap;

    // A1-2: 10, 30, 20, 5 を追加
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);

    // A1-3: 全要素を取り出して出力
    cout << "Max Heap: ";
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << " "; // 30, 20, 10, 5
        maxHeap.pop();
    }
    cout << "\n";

    // A1-4: Min Heap を作成
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // A1-5: 同じ要素を追加
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
// 解答2: pair での使用
// ========================================

void pairHeap()
{
    // A2-1: pair<int,int> の Max Heap
    priority_queue<pair<int, int>> maxPairHeap;

    // A2-2: 追加して出力
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

    // A2-3: pair<int,int> の Min Heap
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
// 解答3: カスタム比較関数
// ========================================

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// A3-1: 距離で比較
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
    // A3-2: CompareDistance を使用
    priority_queue<Point, vector<Point>, CompareDistance> pq;

    // A3-3: 追加して出力
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
// 解答4: ラムダでの比較
// ========================================

void lambdaComparator()
{
    // A4: second の小さい順
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second; // Min Heap
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
// 解答5: Kth Largest Element
// ========================================

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

// ========================================
// 解答6: Top K Frequent Elements
// ========================================

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

// ========================================
// 解答7: K Closest Points to Origin
// ========================================

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

// ========================================
// 解答8: Find Median from Data Stream
// ========================================

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

// ========================================
// 解答9: Dijkstra での使用
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
// 解答10: Merge K Sorted Lists
// ========================================

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
    cout << "3rd largest: " << findKthLargest(nums, 3) << "\n"; // 4

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
    cout << "Median: " << mf.findMedian() << "\n"; // 1.5
    mf.addNum(3);
    cout << "Median: " << mf.findMedian() << "\n"; // 2

    return 0;
}

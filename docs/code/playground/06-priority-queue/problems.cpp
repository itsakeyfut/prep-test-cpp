/**
 * Priority Queue（優先度キュー / ヒープ）- アクティブリコール問題
 *
 * 各パターンを見ずに書いてみましょう。
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
// 問題1: 基本的な使い方
// ========================================

void basicUsage()
{
    // Q1-1: Max Heap を作成（デフォルト）
    // TODO:

    // Q1-2: 10, 30, 20, 5 を追加
    // TODO:

    // Q1-3: 全要素を取り出して出力（30, 20, 10, 5 の順）
    // TODO:

    // Q1-4: Min Heap を作成
    // ヒント: greater<int> を使用
    // TODO:

    // Q1-5: 同じ要素を追加して、全要素を取り出して出力（5, 10, 20, 30 の順）
    // TODO:
}

// ========================================
// 問題2: pair での使用
// ========================================

void pairHeap()
{
    // Q2-1: pair<int,int> の Max Heap を作成
    // TODO:

    // Q2-2: {10,1}, {30,2}, {20,3} を追加して出力
    // TODO:

    // Q2-3: pair<int,int> の Min Heap を作成
    // TODO:
}

// ========================================
// 問題3: カスタム比較関数
// ========================================

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// Q3-1: 原点からの距離で比較する構造体を定義（小さい順 = Min Heap）
// ヒント: operator() で distA > distB を返す
struct CompareDistance
{
    // TODO:
};

void customComparator()
{
    // Q3-2: CompareDistance を使って priority_queue を作成
    // TODO:

    // Q3-3: Point(3,4), Point(1,1), Point(2,2) を追加して出力
    // TODO:
}

// ========================================
// 問題4: ラムダでの比較
// ========================================

void lambdaComparator()
{
    // Q4: second の小さい順で並ぶ priority_queue を作成
    // ヒント: decltype(cmp) を使用
    // TODO:
}

// ========================================
// 問題5: Kth Largest Element (LC 215)
// ========================================

// Q5: 配列で k 番目に大きい要素を返す
// ヒント: サイズ k の Min Heap を維持
int findKthLargest(vector<int> &nums, int k)
{
    // TODO:
    return 0;
}

// ========================================
// 問題6: Top K Frequent Elements (LC 347)
// ========================================

// Q6: 配列で出現頻度が高い上位 k 個の要素を返す
// ヒント: 頻度カウント → サイズ k の Min Heap
vector<int> topKFrequent(vector<int> &nums, int k)
{
    // TODO:
    return {};
}

// ========================================
// 問題7: K Closest Points to Origin (LC 973)
// ========================================

// Q7: 原点から最も近い k 個の点を返す
// ヒント: サイズ k の Max Heap（距離が遠い順）
vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
{
    // TODO:
    return {};
}

// ========================================
// 問題8: Find Median from Data Stream (LC 295)
// ========================================

// Q8: データストリームの中央値をリアルタイムで求める
// ヒント: 2つのヒープ（maxHeap: 小さい方の半分、minHeap: 大きい方の半分）
class MedianFinder
{
private:
    // TODO: 2つのヒープを定義

public:
    void addNum(int num)
    {
        // TODO:
    }

    double findMedian()
    {
        // TODO:
        return 0;
    }
};

// ========================================
// 問題9: Dijkstra での使用
// ========================================

// Q9: 重み付きグラフで start から各ノードへの最短距離
// graph[u] = [{v, weight}, ...]
vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int start)
{
    // TODO: Min Heap を使用
    return {};
}

// ========================================
// 問題10: Merge K Sorted Lists パターン
// ========================================

// Q10: K 個のソート済みリストをマージ
// ヒント: Min Heap で各リストの先頭を管理
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    // TODO:
    return nullptr;
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
 * チェックリスト（答えを見ずに書けたか？）:
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
 */

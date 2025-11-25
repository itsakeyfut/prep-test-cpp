/**
 * Graph（グラフ）- アクティブリコール問題
 *
 * 各パターンを見ずに書いてみましょう。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// 4方向移動
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// ========================================
// 問題1: グラフの表現
// ========================================

// Q1-1: 隣接リストで無向グラフを作成（ノード数n、辺のリストedges）
void createAdjacencyList(int n, vector<vector<int>> &edges)
{
    // TODO: graph を作成
}

// Q1-2: 重み付きグラフを隣接リストで作成
void createWeightedGraph(int n, vector<vector<int>> &edges)
{
    // edges = [[from, to, weight], ...]
    // TODO: vector<vector<pair<int,int>>> graph を作成
}

// ========================================
// 問題2: DFS（深さ優先探索）- 再帰
// ========================================

// Q2: ノード start から DFS で全ノードを訪問
void dfsRecursive(vector<vector<int>> &graph, int start)
{
    // TODO: visited 配列とラムダ DFS
}

// ========================================
// 問題3: DFS - 反復（スタック）
// ========================================

// Q3: スタックを使った DFS
void dfsIterative(vector<vector<int>> &graph, int start)
{
    // TODO:
}

// ========================================
// 問題4: BFS（幅優先探索）
// ========================================

// Q4-1: 基本的な BFS
void bfs(vector<vector<int>> &graph, int start)
{
    // TODO:
}

// Q4-2: BFS で最短距離を求める
// 戻り値: dist[i] = start から i への最短距離（到達不可は -1）
vector<int> bfsDistance(vector<vector<int>> &graph, int start)
{
    // TODO:
    return {};
}

// ========================================
// 問題5: Grid BFS（迷路の最短経路）
// ========================================

// Q5: grid 上で start から end への最短距離
// grid[i][j] = 0 は通行可能、1 は壁
int gridBFS(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
    // TODO: 4方向移動、dist 配列
    return -1;
}

// ========================================
// 問題6: Number of Islands (LC 200)
// ========================================

// Q6: '1' の連結成分の数を数える
// grid を直接変更して訪問済みをマーク
int numIslands(vector<vector<char>> &grid)
{
    // TODO:
    return 0;
}

// ========================================
// 問題7: Course Schedule (LC 207) - トポロジカルソート
// ========================================

// Q7: 全てのコースを履修可能か判定
// prerequisites[i] = [a, b] は「b を履修してから a」
// ヒント: 入次数 (indegree) を使った BFS
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    // TODO:
    return false;
}

// ========================================
// 問題8: Union-Find（素集合データ構造）
// ========================================

// Q8-1: Union-Find クラスを実装
// - find(x): x の親を返す（経路圧縮）
// - unite(x, y): x と y を結合
// - connected(x, y): x と y が同じ集合か
class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank_;

public:
    UnionFind(int n)
    {
        // TODO:
    }

    int find(int x)
    {
        // TODO: 経路圧縮
        return -1;
    }

    bool unite(int x, int y)
    {
        // TODO: ランクによる結合
        return false;
    }

    bool connected(int x, int y)
    {
        // TODO:
        return false;
    }
};

// Q8-2: Union-Find でグラフの連結成分数を数える
int countComponents(int n, vector<vector<int>> &edges)
{
    // TODO:
    return 0;
}

// ========================================
// 問題9: Dijkstra（最短経路）
// ========================================

// Q9: 重み付きグラフで start から各ノードへの最短距離
// graph[u] = [{v, weight}, ...]
vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int start)
{
    // TODO: priority_queue を使用
    return {};
}

// ========================================
// 問題10: サイクル検出
// ========================================

// Q10-1: 無向グラフのサイクル検出
// ヒント: DFS で parent を追跡
bool hasCycleUndirected(vector<vector<int>> &graph)
{
    // TODO:
    return false;
}

// Q10-2: 有向グラフのサイクル検出
// ヒント: 状態を 0=未訪問, 1=処理中, 2=完了 で管理
bool hasCycleDirected(vector<vector<int>> &graph)
{
    // TODO:
    return false;
}

int main()
{
    // テスト: BFS
    vector<vector<int>> graph = {
        {1, 2},    // 0
        {0, 3},    // 1
        {0, 3},    // 2
        {1, 2, 4}, // 3
        {3}        // 4
    };

    cout << "=== BFS from node 0 ===\n";
    bfs(graph, 0);
    cout << "\n";

    cout << "=== DFS from node 0 ===\n";
    dfsRecursive(graph, 0);
    cout << "\n";

    // Union-Find テスト
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "\n=== Union-Find ===\n";
    cout << "0 and 2 connected: " << uf.connected(0, 2) << "\n";
    cout << "0 and 3 connected: " << uf.connected(0, 3) << "\n";

    return 0;
}

/**
 * チェックリスト（答えを見ずに書けたか？）:
 *
 * [ ] 隣接リストでグラフを表現
 * [ ] DFS（再帰・反復）を書ける
 * [ ] BFS を書ける
 * [ ] Grid での BFS/DFS
 * [ ] 訪問済み管理（visited配列）
 * [ ] トポロジカルソート
 * [ ] Union-Find の実装
 * [ ] Dijkstra の実装
 * [ ] サイクル検出（無向・有向）
 * [ ] 4方向移動の定義
 */

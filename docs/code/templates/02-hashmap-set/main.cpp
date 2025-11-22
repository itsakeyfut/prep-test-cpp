/**
 * HashMap / HashSet テンプレート
 * O(1) の検索・挿入・削除が必要な時に使う
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

int main()
{
    // ========================================
    // 1. unordered_map（ハッシュマップ）
    // ========================================

    unordered_map<int, int> mp;

    // 追加・更新
    mp[1] = 10;
    mp[2] = 20;
    mp[3] = 30;

    // カウントアップ（頻出パターン）
    mp[1]++; // 11

    // 存在確認（方法1）
    if (mp.count(2))
    {
        cout << "Key 2 exists\n";
    }

    // 存在確認（方法2）
    if (mp.find(2) != mp.end())
    {
        cout << "Key 2 exists\n";
    }

    // 値の取得
    int val = mp[1]; // 存在しない場合は0が返る

    // イテレート（順序は不定）
    for (auto &[key, value] : mp)
    {
        cout << key << ": " << value << "\n";
    }

    // イテレート（従来の書き方）
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        cout << it->first << ": " << it->second << "\n";
    }

    // 削除
    mp.erase(1); // キー1を削除

    // サイズ
    int size = mp.size();

    // クリア
    mp.clear();

    // ========================================
    // 2. unordered_set（ハッシュセット）
    // ========================================

    unordered_set<int> st;

    // 追加
    st.insert(1);
    st.insert(2);
    st.insert(3);
    st.insert(2); // 重複は無視される

    // 存在確認
    if (st.count(2))
    {
        cout << "2 exists in set\n";
    }

    // 削除
    st.erase(2);

    // イテレート
    for (int x : st)
    {
        cout << x << " ";
    }
    cout << "\n";

    // サイズ
    int set_size = st.size();

    // ========================================
    // 3. map（順序付きマップ、O(log n)）
    // ========================================

    map<int, int> ordered_mp;

    ordered_mp[3] = 30;
    ordered_mp[1] = 10;
    ordered_mp[2] = 20;

    // キーの昇順でイテレート
    for (auto &[key, value] : ordered_mp)
    {
        cout << key << ": " << value << "\n";
    }
    // 出力: 1:10, 2:20, 3:30

    // lower_bound（key以上の最初の要素）
    auto lb = ordered_mp.lower_bound(2);
    cout << "lower_bound(2): " << lb->first << "\n";

    // upper_bound（keyより大きい最初の要素）
    auto ub = ordered_mp.upper_bound(2);
    cout << "upper_bound(2): " << ub->first << "\n";

    // ========================================
    // 4. set（順序付きセット、O(log n)）
    // ========================================

    set<int> ordered_st;

    ordered_st.insert(5);
    ordered_st.insert(2);
    ordered_st.insert(8);
    ordered_st.insert(1);

    // 昇順でイテレート
    for (int x : ordered_st)
    {
        cout << x << " ";
    }
    cout << "\n";
    // 出力: 1 2 5 8

    // lower_bound
    auto it = ordered_st.lower_bound(3);
    cout << "lower_bound(3): " << *it << "\n"; // 5

    // ========================================
    // 5. 典型的な使い方パターン
    // ========================================

    // パターン1: 頻度カウント
    vector<int> nums = {1, 2, 2, 3, 3, 3, 4};
    unordered_map<int, int> freq;
    for (int x : nums)
    {
        freq[x]++;
    }
    // freq = {1:1, 2:2, 3:3, 4:1}

    // パターン2: Two Sum（超頻出）
    auto twoSum = [](vector<int> &nums, int target)
    {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++)
        {
            int complement = target - nums[i];
            if (seen.count(complement))
            {
                return vector<int>{seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return vector<int>{};
    };

    // パターン3: 訪問済み管理
    auto hasPath = [](vector<vector<int>> &graph, int start, int end)
    {
        unordered_set<int> visited;

        auto dfs = [&](auto &&self, int node) -> bool
        {
            if (node == end)
                return true;
            visited.insert(node);

            for (int neighbor : graph[node])
            {
                if (!visited.count(neighbor))
                {
                    if (self(self, neighbor))
                        return true;
                }
            }
            return false;
        };

        return dfs(dfs, start);
    };

    // パターン4: 重複チェック
    vector<int> arr = {1, 2, 3, 2, 4};
    unordered_set<int> check;
    bool hasDuplicate = false;
    for (int x : arr)
    {
        if (check.count(x))
        {
            hasDuplicate = true;
            break;
        }
        check.insert(x);
    }

    // パターン5: Group Anagrams（文字列のグループ化）
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    unordered_map<string, vector<string>> groups;

    for (string &s : strs)
    {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    // groups = {"aet": ["eat","tea","ate"], "ant": ["tan","nat"], "abt": ["bat"]}

    // ========================================
    // 6. string をキーにする場合
    // ========================================

    unordered_map<string, int> word_count;
    word_count["hello"] = 1;
    word_count["world"] = 2;

    if (word_count.count("hello"))
    {
        cout << "hello: " << word_count["hello"] << "\n";
    }

    // ========================================
    // 7. pair をキーにする場合（ハッシュ関数が必要）
    // ========================================

    // カスタムハッシュ関数
    struct PairHash
    {
        size_t operator()(const pair<int, int> &p) const
        {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    unordered_map<pair<int, int>, int, PairHash> pair_map;
    pair_map[{1, 2}] = 10;
    pair_map[{3, 4}] = 20;

    if (pair_map.count({1, 2}))
    {
        cout << "Pair (1,2) exists\n";
    }

    // ========================================
    // 8. 使い分けのガイドライン
    // ========================================

    /*
     * unordered_map vs map:
     * - unordered_map: O(1) 平均、順序不要
     * - map: O(log n)、順序必要、範囲検索必要
     *
     * unordered_set vs set:
     * - unordered_set: O(1) 平均、順序不要
     * - set: O(log n)、順序必要、lower_bound/upper_bound必要
     *
     * 面接では unordered_map/set を使うのが基本
     * 順序が必要な場合のみ map/set
     */

    // ========================================
    // 9. よくある例外処理
    // ========================================

    unordered_map<int, int> test_map;

    // 存在しないキーにアクセス
    int x = test_map[999]; // 0が返る（自動で追加される）

    // 存在確認してからアクセス（推奨）
    if (test_map.count(999))
    {
        int val = test_map[999];
    }
    else
    {
        cout << "Key not found\n";
    }

    // at() を使う（存在しない場合は例外）
    try
    {
        int val = test_map.at(999);
    }
    catch (const out_of_range &e)
    {
        cout << "Key not found\n";
    }

    return 0;
}

/**
 * 暗記チェックリスト:
 *
 * [ ] unordered_map の基本操作（追加、検索、削除）
 * [ ] count() と find() の使い分け
 * [ ] unordered_set の基本操作
 * [ ] map/set との違いを説明できる
 * [ ] Two Sum パターン
 * [ ] 頻度カウントパターン
 * [ ] 訪問済み管理パターン
 * [ ] string をキーにする方法
 * [ ] pair をキーにする方法（カスタムハッシュ）
 */
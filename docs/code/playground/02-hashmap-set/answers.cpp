/**
 * HashMap / HashSet - 解答
 *
 * problems.cpp の解答です。
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
    // 解答1: unordered_map（ハッシュマップ）
    // ========================================

    // A1-1: 空のunordered_mapを作成
    unordered_map<int, int> mp;

    // A1-2: キー1に値10、キー2に値20を追加
    mp[1] = 10;
    mp[2] = 20;

    // A1-3: キー1の値をインクリメント
    mp[1]++; // 11

    // A1-4: キー2が存在するか確認（count使用）
    if (mp.count(2))
    {
        cout << "Key 2 exists\n";
    }

    // A1-5: キー2が存在するか確認（find使用）
    if (mp.find(2) != mp.end())
    {
        cout << "Key 2 exists\n";
    }

    // A1-6: 構造化束縛でイテレート
    for (auto &[key, value] : mp)
    {
        cout << key << ": " << value << "\n";
    }

    // A1-7: キー1を削除
    mp.erase(1);

    // ========================================
    // 解答2: unordered_set（ハッシュセット）
    // ========================================

    // A2-1: 空のunordered_setを作成
    unordered_set<int> st;

    // A2-2: 1, 2, 3を追加
    st.insert(1);
    st.insert(2);
    st.insert(3);

    // A2-3: 2が存在するか確認
    if (st.count(2))
    {
        cout << "2 exists in set\n";
    }

    // A2-4: 2を削除
    st.erase(2);

    // A2-5: 範囲forでイテレート
    for (int x : st)
    {
        cout << x << " ";
    }
    cout << "\n";

    // ========================================
    // 解答3: map（順序付きマップ）
    // ========================================

    // A3-1: 順序付きmapを作成
    map<int, int> ordered_mp;
    ordered_mp[3] = 30;
    ordered_mp[1] = 10;
    ordered_mp[2] = 20;

    // A3-2: キーの昇順でイテレート
    for (auto &[key, value] : ordered_mp)
    {
        cout << key << ": " << value << "\n";
    }
    // 出力: 1:10, 2:20, 3:30

    // A3-3: lower_bound(2)を使用
    auto lb = ordered_mp.lower_bound(2);
    cout << "lower_bound(2): " << lb->first << "\n";

    // ========================================
    // 解答4: set（順序付きセット）
    // ========================================

    // A4-1: 順序付きsetを作成
    set<int> ordered_st;
    ordered_st.insert(5);
    ordered_st.insert(2);
    ordered_st.insert(8);
    ordered_st.insert(1);

    // A4-2: lower_bound(3)を使用
    auto it = ordered_st.lower_bound(3);
    cout << "lower_bound(3): " << *it << "\n"; // 5

    // ========================================
    // 解答5: 頻度カウントパターン
    // ========================================

    vector<int> nums = {1, 2, 2, 3, 3, 3, 4};

    // A5-1: 各要素の出現回数をカウント
    unordered_map<int, int> freq;
    for (int x : nums)
    {
        freq[x]++;
    }
    // freq = {1:1, 2:2, 3:3, 4:1}

    // ========================================
    // 解答6: Two Sum パターン
    // ========================================

    // A6-1: Two Sumを実装
    auto twoSum = [](vector<int> &nums, int target) -> vector<int>
    {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++)
        {
            int complement = target - nums[i];
            if (seen.count(complement))
            {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {};
    };

    // ========================================
    // 解答7: 重複チェックパターン
    // ========================================

    vector<int> arr = {1, 2, 3, 2, 4};

    // A7-1: 重複があるかチェック
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

    // ========================================
    // 解答8: Group Anagrams パターン
    // ========================================

    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    // A8-1: アナグラムをグループ化
    unordered_map<string, vector<string>> groups;
    for (string &s : strs)
    {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    // groups = {"aet": ["eat","tea","ate"], "ant": ["tan","nat"], "abt": ["bat"]}

    // ========================================
    // 解答9: pairをキーにする
    // ========================================

    // A9-1: ハッシュ関数を定義
    struct PairHash
    {
        size_t operator()(const pair<int, int> &p) const
        {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    // A9-2: PairHashを使ってunordered_mapを作成
    unordered_map<pair<int, int>, int, PairHash> pair_map;
    pair_map[{1, 2}] = 10;
    pair_map[{3, 4}] = 20;

    if (pair_map.count({1, 2}))
    {
        cout << "Pair (1,2) exists\n";
    }

    // ========================================
    // 解答10: 例外処理パターン
    // ========================================

    unordered_map<int, int> test_map;

    // A10-1: 存在しないキーにアクセス
    int x = test_map[999]; // 0が返る（自動で追加される）

    // A10-2: 存在確認してからアクセス（推奨）
    if (test_map.count(999))
    {
        int val = test_map[999];
    }
    else
    {
        cout << "Key not found\n";
    }

    return 0;
}

# HashMap / HashSet 解説

## 1. unordered_map vs map

| 特徴 | unordered_map | map |
|------|---------------|-----|
| 内部構造 | ハッシュテーブル | 赤黒木 |
| 検索/挿入/削除 | O(1) 平均 | O(log n) |
| 順序 | 不定 | キー順（昇順） |
| lower_bound | 使用不可 | 使用可能 |
| 用途 | 一般的なケース | 順序・範囲検索が必要 |

**面接では基本的に `unordered_map` を使用。順序が必要な場合のみ `map`。**

---

## 2. 基本操作

```cpp
unordered_map<int, int> mp;

// 追加・更新
mp[key] = value;

// カウントアップ（超頻出）
mp[key]++;

// 存在確認（2通り）
if (mp.count(key)) { ... }           // シンプル
if (mp.find(key) != mp.end()) { ... } // イテレータが必要な場合

// 値の取得
int val = mp[key];  // 存在しない場合は0を返し、キーが追加される！

// 削除
mp.erase(key);

// イテレート
for (auto& [key, value] : mp) { ... }  // C++17 構造化束縛
```

| 操作 | 計算量 | 備考 |
|------|--------|------|
| `mp[key]` | O(1) 平均 | 存在しなければ追加される |
| `count(key)` | O(1) 平均 | 0 or 1 を返す |
| `find(key)` | O(1) 平均 | イテレータを返す |
| `erase(key)` | O(1) 平均 | |

---

## 3. unordered_set

```cpp
unordered_set<int> st;

st.insert(value);      // 追加
st.count(value);       // 存在確認（0 or 1）
st.erase(value);       // 削除

for (int x : st) { }   // イテレート
```

**主な用途:**
- 重複チェック
- 訪問済み管理（グラフ探索）
- O(1) での存在確認

---

## 4. count() vs find()

```cpp
// count(): シンプルに存在確認
if (mp.count(key)) {
    // 存在する
}

// find(): イテレータが必要な場合
auto it = mp.find(key);
if (it != mp.end()) {
    cout << it->first << ": " << it->second;
}
```

**使い分け:**
- 存在確認だけなら `count()` がシンプル
- 値も同時に使いたい場合は `find()` で二重検索を避ける

---

## 5. 典型パターン

### パターン1: 頻度カウント

```cpp
vector<int> nums = {1, 2, 2, 3, 3, 3};
unordered_map<int, int> freq;

for (int x : nums) {
    freq[x]++;
}
// freq = {1:1, 2:2, 3:3}
```

**ポイント:** `mp[key]++` は、キーが存在しなくても 0 から始まる。

---

### パターン2: Two Sum（超頻出！）

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // 値 → インデックス

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }

        seen[nums[i]] = i;
    }

    return {};
}
```

**考え方:**
1. 各要素について、`target - 現在の値` が既に見たかチェック
2. 見つかれば、その2つのインデックスを返す
3. 見つからなければ、現在の値とインデックスを記録

**計算量:** O(n)（全要素を1回ずつ見る）

---

### パターン3: 重複チェック

```cpp
bool hasDuplicate(vector<int>& nums) {
    unordered_set<int> seen;

    for (int x : nums) {
        if (seen.count(x)) {
            return true;
        }
        seen.insert(x);
    }

    return false;
}
```

---

### パターン4: 訪問済み管理

```cpp
void dfs(int node, unordered_set<int>& visited, vector<vector<int>>& graph) {
    if (visited.count(node)) return;

    visited.insert(node);

    for (int neighbor : graph[node]) {
        dfs(neighbor, visited, graph);
    }
}
```

---

### パターン5: Group Anagrams

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());  // ソートした文字列をキーに
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }

    return result;
}
```

**考え方:** アナグラムはソートすると同じ文字列になる。

---

## 6. pair をキーにする

`unordered_map` で `pair` をキーにするにはカスタムハッシュ関数が必要。

```cpp
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

unordered_map<pair<int, int>, int, PairHash> mp;
mp[{1, 2}] = 10;
```

**代替案:** `map<pair<int,int>, int>` なら追加定義不要（ただし O(log n)）

---

## 7. map / set の特別な機能

```cpp
map<int, int> mp;
set<int> st;

// lower_bound: key 以上の最初の要素
auto lb = mp.lower_bound(key);
auto lb = st.lower_bound(key);

// upper_bound: key より大きい最初の要素
auto ub = mp.upper_bound(key);
auto ub = st.upper_bound(key);
```

**用途:**
- 範囲検索
- 「x以上で最小の値」を見つける

---

## 8. 注意点とよくあるミス

### 存在しないキーへのアクセス

```cpp
unordered_map<int, int> mp;

// 危険: キーが自動追加される
int x = mp[999];  // 0 が返り、mp[999] = 0 が追加される

// 安全: 先に存在確認
if (mp.count(999)) {
    int x = mp[999];
}
```

### イテレート中の削除

```cpp
// 危険: イテレータが無効になる
for (auto it = mp.begin(); it != mp.end(); it++) {
    if (shouldDelete) {
        mp.erase(it);  // NG: itが無効に
    }
}

// 安全: eraseの戻り値を使う
for (auto it = mp.begin(); it != mp.end(); ) {
    if (shouldDelete) {
        it = mp.erase(it);  // 次のイテレータを返す
    } else {
        it++;
    }
}
```

---

## 9. 計算量まとめ

### unordered_map / unordered_set

| 操作 | 平均 | 最悪 |
|------|------|------|
| 検索 | O(1) | O(n) |
| 挿入 | O(1) | O(n) |
| 削除 | O(1) | O(n) |

**最悪ケース:** ハッシュ衝突が多い場合（まれ）

### map / set

| 操作 | 計算量 |
|------|--------|
| 検索 | O(log n) |
| 挿入 | O(log n) |
| 削除 | O(log n) |
| lower/upper_bound | O(log n) |

---

## 10. 使い分けガイドライン

```
Q: 順序は必要？
├─ No → unordered_map / unordered_set（O(1)）
└─ Yes
    └─ Q: lower_bound / upper_bound が必要？
        ├─ Yes → map / set（O(log n)）
        └─ No → どちらでも可（速度優先なら unordered）
```

**面接での基本戦略:**
1. まず `unordered_map` / `unordered_set` を使う
2. 順序や範囲検索が必要な場合のみ `map` / `set` に切り替える

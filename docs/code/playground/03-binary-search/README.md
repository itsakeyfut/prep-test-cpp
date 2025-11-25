# Binary Search（二分探索）解説

## 1. 二分探索の2大パターン

| パターン | ループ条件 | 用途 |
|----------|-----------|------|
| `while (l <= r)` | 値を探す | 特定の値を見つける |
| `while (l < r)` | 境界を探す | 条件を満たす最小/最大を見つける |

---

## 2. パターン1: 値の検索（基本）

```cpp
int binarySearch(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;  // オーバーフロー防止

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return -1;
}
```

**ポイント:**
- `l <= r`: l と r が交差するまで探索
- 見つかったら即 return
- 見つからなければ -1

---

## 3. パターン2: 境界探索（lower_bound / upper_bound）

### lower_bound: target 以上の最初の位置

```cpp
int lowerBound(vector<int>& arr, int target) {
    int l = 0, r = arr.size();

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}
```

### upper_bound: target より大きい最初の位置

```cpp
int upperBound(vector<int>& arr, int target) {
    int l = 0, r = arr.size();

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] <= target) {  // 違いはここだけ！
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}
```

**図解:**
```
配列: [1, 2, 2, 2, 3, 4]
              ↑     ↑
              lb    ub  (target = 2)

lower_bound(2) → index 1（最初の2）
upper_bound(2) → index 4（3の位置）

target の個数 = upper_bound - lower_bound = 3
```

---

## 4. パターン3: 答えの二分探索

「条件を満たす最小/最大の値」を探す問題で使用。

### 最小値を探す

```cpp
int binarySearchMin() {
    int l = 0, r = 1e9;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (check(mid)) {
            r = mid;      // 答えを小さくできる
        } else {
            l = mid + 1;
        }
    }

    return l;
}
```

### 最大値を探す

```cpp
int binarySearchMax() {
    int l = 0, r = 1e9;

    while (l < r) {
        int mid = l + (r - l + 1) / 2;  // +1 で切り上げ！

        if (check(mid)) {
            l = mid;      // 答えを大きくできる
        } else {
            r = mid - 1;
        }
    }

    return l;
}
```

**なぜ最大値で +1 が必要か:**
- `l = mid` の場合、`mid = (l + r) / 2` だと l と r が隣接した時に `mid = l` となり無限ループ
- `+1` で切り上げると `mid = r` となり進む

---

## 5. mid の計算

```cpp
// NG: オーバーフローの可能性
int mid = (l + r) / 2;

// OK: オーバーフロー防止
int mid = l + (r - l) / 2;

// 最大値探索用（切り上げ）
int mid = l + (r - l + 1) / 2;
```

---

## 6. 典型問題

### Koko Eating Bananas (LC 875)

バナナを h 時間以内に食べきる最小速度を求める。

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    // k 本/時で全部食べられるか
    auto canFinish = [&](int k) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + k - 1) / k;  // 切り上げ除算
        }
        return hours <= h;
    };

    int l = 1, r = *max_element(piles.begin(), piles.end());

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (canFinish(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}
```

**考え方:**
1. 答え（速度 k）で二分探索
2. `check(k)` = 「速度 k で h 時間以内に食べられるか」
3. 条件を満たす最小の k を探す

---

### Search in Rotated Sorted Array (LC 33)

```cpp
int searchRotated(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (nums[mid] == target) return mid;

        // 左半分がソート済みか？
        if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && target < nums[mid]) {
                r = mid - 1;  // target は左半分
            } else {
                l = mid + 1;
            }
        } else {
            // 右半分がソート済み
            if (nums[mid] < target && target <= nums[r]) {
                l = mid + 1;  // target は右半分
            } else {
                r = mid - 1;
            }
        }
    }

    return -1;
}
```

**考え方:**
1. 回転配列では、常に片側がソート済み
2. `nums[l] <= nums[mid]` なら左半分がソート済み
3. ソート済みの側に target があるか判定して探索範囲を絞る

---

### Find Minimum in Rotated Sorted Array (LC 153)

```cpp
int findMin(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (nums[mid] > nums[r]) {
            l = mid + 1;  // 最小値は右側
        } else {
            r = mid;      // 最小値は左側（mid含む）
        }
    }

    return nums[l];
}
```

---

## 7. 浮動小数点数での二分探索

```cpp
double mySqrt(double x) {
    double l = 0, r = x;
    double eps = 1e-9;

    while (r - l > eps) {
        double mid = (l + r) / 2;

        if (mid * mid < x) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return l;
}
```

**ポイント:**
- `l < r` ではなく `r - l > eps` で精度を管理
- 整数と違い `mid + 1` ではなく `mid` を使用

---

## 8. よくあるミス

### ミス1: 無限ループ

```cpp
// NG: 最大値探索で無限ループ
while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
        l = mid;  // l と r が隣接すると mid = l で進まない
    } else {
        r = mid - 1;
    }
}

// OK: 切り上げで解決
int mid = (l + r + 1) / 2;
```

### ミス2: l <= r vs l < r の混同

```cpp
// 値を探す: l <= r
while (l <= r) { ... }  // l と r が交差するまで

// 境界を探す: l < r
while (l < r) { ... }   // l == r になったら終了
```

### ミス3: r の初期値

```cpp
// 境界探索では r = arr.size()（配列外を許容）
int l = 0, r = arr.size();

// 値検索では r = arr.size() - 1
int l = 0, r = arr.size() - 1;
```

---

## 9. check() 関数の設計

答えの二分探索では `check()` 関数の設計が重要。

**テンプレート:**
```cpp
// 最小値を探す場合
// check(x) = "x で条件を満たすか"
// check(x) が true なら、それより小さい値も試す → r = mid

// 最大値を探す場合
// check(x) = "x で条件を満たすか"
// check(x) が true なら、それより大きい値も試す → l = mid
```

---

## 10. 計算量

| 操作 | 計算量 |
|------|--------|
| 二分探索 | O(log n) |
| 答えの二分探索 | O(log(探索範囲) × check の計算量) |

**例:** Koko Eating Bananas
- 探索範囲: 1 ～ max(piles) ≈ 10^9
- check: O(n)
- 全体: O(n log(max))

---

## 11. STL の二分探索関数

```cpp
vector<int> arr = {1, 2, 2, 2, 3, 4};

// lower_bound: target以上の最初のイテレータ
auto lb = lower_bound(arr.begin(), arr.end(), 2);
int lb_idx = lb - arr.begin();  // 1

// upper_bound: targetより大きい最初のイテレータ
auto ub = upper_bound(arr.begin(), arr.end(), 2);
int ub_idx = ub - arr.begin();  // 4

// binary_search: 存在確認
bool found = binary_search(arr.begin(), arr.end(), 2);  // true
```

**注意:** STL の関数はソート済み配列が前提。

# 学習リソース集

---

## 🎓 メイン教材

### 1. NeetCode.io
- **URL**: https://neetcode.io/
- **用途**: パターン学習の中核
- **特徴**:
  - 問題が体系的に整理されている
  - 動画解説（英語）が非常に分かりやすい
  - C++ コードが全て揃っている
  - NeetCode 150 が Big Tech 対策の標準

**推奨コース:**
- NeetCode 25（基礎、Week 3-6）
- NeetCode 75（面接頻出、Week 7-10）
- NeetCode 150（完全版、Week 11-12）

**使い方:**
1. Roadmap から問題を選ぶ
2. 動画解説を見る（15分）
3. 自分で実装
4. Solutions タブで C++ コードを確認

---

### 2. CP-Algorithms
- **URL**: https://cp-algorithms.com/
- **用途**: アルゴリズムの理論と実装
- **特徴**:
  - 説明が簡潔で実戦的
  - C++ 実装が中心
  - 競技プログラミングレベルの最適化

**重要なページ:**
- Data Structures
  - Stacks and Queues
  - Minimum Stack / Minimum Queue
  - Disjoint Set Union (Union-Find)
- Graph Theory
  - Breadth First Search
  - Depth First Search
  - Topological Sort
  - Dijkstra
- Dynamic Programming
  - Divide and Conquer DP
  - Dynamic Programming on Trees

**使い方:**
1. NeetCode で解けない問題があったら該当アルゴリズムを読む
2. コードをコピーして自分で書き直す
3. LeetCode で実際に使ってみる

---

### 3. Tech Interview Handbook
- **URL**: https://www.techinterviewhandbook.org/
- **用途**: 面接戦略とマインドセット
- **特徴**:
  - Google 面接官経験者が作成
  - 面接の全フェーズをカバー
  - 実戦的なアドバイス

**重要なセクション:**
- **Algorithms Study Cheatsheet**
  - 各アルゴリズムの要点まとめ
  - 時間計算量の一覧
- **Coding Interview Best Practices**
  - 面接での振る舞い方
  - コミュニケーションの取り方
- **Grind 75**
  - LeetCode 問題の推奨リスト
  - 週次で進めるプラン

**使い方:**
- Week 1-10: たまに参考程度に読む
- Week 11-12: 集中的に読み込む

---

## 📝 問題演習プラットフォーム

### 4. LeetCode
- **URL**: https://leetcode.com/
- **用途**: 問題演習とMock Interview
- **特徴**:
  - 問題数が最も多い
  - 企業別の頻出問題リストがある
  - Mock Interview 機能が優秀

**推奨機能:**
- **Problems**: NeetCode と併用
- **Mock Interview**: Week 11-12 で使う
- **Discuss**: 解けなかった問題の別解を見る

**有料版（LeetCode Premium）の価値:**
- 企業別頻出問題（Google, Meta, Amazon等）
- より多くの Mock Interview
- Video Explanations

→ **Week 7以降に検討**（月額 $35）

---

### 5. Pramp（無料 Mock Interview）
- **URL**: https://www.pramp.com/
- **用途**: 実際の人と Mock Interview
- **特徴**:
  - 完全無料
  - 相手も面接対策中の人
  - 面接官役と受験者役を交代

**使い方:**
- Week 11-12 に週1回
- 英語での説明練習にもなる

---

## 📚 補助教材

### 6. Visualgo
- **URL**: https://visualgo.net/
- **用途**: アルゴリズムの視覚化
- **特徴**:
  - アニメーションで動きが分かる
  - ソート、グラフ、木、DPなど

**使い方:**
- アルゴリズムの動きが理解できない時
- 特に Graph (BFS/DFS/Dijkstra) で有効

---

### 7. Big-O Cheat Sheet
- **URL**: https://www.bigocheatsheet.com/
- **用途**: 時間計算量のクイックリファレンス
- **特徴**:
  - 各データ構造の操作計算量
  - 各アルゴリズムの時間・空間計算量

**使い方:**
- 面接前に確認
- 不安な時にさっと見る

---

## 🎥 YouTube チャンネル

### 8. NeetCode (YouTubeチャンネル)
- **URL**: https://www.youtube.com/@NeetCode
- **用途**: 動画解説
- **特徴**:
  - NeetCode.io の動画版
  - 問題ごとに丁寧な解説

---

### 9. Back To Back SWE
- **URL**: https://www.youtube.com/@BackToBackSWE
- **用途**: 深い理解
- **特徴**:
  - 理論的な説明が詳しい
  - 難しい問題の解説

---

## 📖 書籍（オプション）

### 10. Cracking the Coding Interview
- **著者**: Gayle Laakmann McDowell
- **用途**: 面接全般の理解
- **特徴**:
  - Big Tech 面接のバイブル
  - 問題+解説+解法の考え方

**使い方:**
- 時間があれば読む（必須ではない）
- 特に「面接の進め方」の章が有用

---

### 11. Elements of Programming Interviews in C++
- **著者**: Adnan Aziz, Tsung-Hsien Lee, Amit Prakash
- **用途**: C++ 特化の面接対策
- **特徴**:
  - C++ の idiom を含めた解説
  - より高度な問題も含む

**使い方:**
- C++ の書き方に不安がある場合
- Week 7以降で参考程度に

---

## 🛠️ 開発環境

### 12. LeetCode Playground
- オンラインで C++ を実行
- デバッグ機能あり
- テストケースを自分で追加可能

### 13. Compiler Explorer (Godbolt)
- **URL**: https://godbolt.org/
- **用途**: C++ のアセンブリ確認（上級者向け）
- **特徴**:
  - 最適化の確認
  - 複数コンパイラで比較

---

## 🗂️ リソースの優先順位

### Phase 1（Week 1-2）
1. CP-Algorithms（理論）
2. 01-cpp-templates.md（テンプレート）
3. LeetCode（問題演習）

### Phase 2（Week 3-6）
1. NeetCode.io（パターン学習）
2. LeetCode（問題演習）
3. Visualgo（理解補助）

### Phase 3（Week 7-10）
1. NeetCode.io（面接問題）
2. LeetCode（問題演習）
3. CP-Algorithms（詰まった時）

### Phase 4（Week 11-12）
1. LeetCode Mock Interview
2. Pramp
3. Tech Interview Handbook（面接戦略）

---

## 📌 ブックマーク推奨リスト

即座にアクセスできるようにブックマーク:

1. https://neetcode.io/practice
2. https://leetcode.com/problemset/
3. https://cp-algorithms.com/
4. https://www.techinterviewhandbook.org/
5. https://www.bigocheatsheet.com/
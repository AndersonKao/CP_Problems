# 配分

- 子任務 1：5 分

總分 20 分。

# 解法

## 子任務 1

預期複雜度$O(PQ)$，對於每一筆詢問從第一天開始檢查到第$P$天看何時符合條件。

## 完整作法
離線處理這一題，對糖果編號掃描線也就是從糖果編號 1 開始依序處理，開一顆維護區間最大值的線段樹，掃到編號$k$時線段樹上的第$i$項代表編號$k$的糖果第$i$天的數量是多少，因此遇到對於第 $i$ 天的操作 $l_i, r_i, y_i$ 就轉換成掃描線掃到$l_i$就對線段樹上的$[i, P]$ 區間加 $y_i$，掃到$r_i + 1$就對線段樹上的$[i, P]$區間加$-y_i$。對於每筆詢問，問題變成當維護好要詢問的糖果編號的線段樹後，在線段樹上二分搜第一次前綴最值大於等於 $k_i$是在哪裡。
總時間複雜度：$O(N + PlogP + QlogP)$。
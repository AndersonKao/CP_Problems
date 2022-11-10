# 糖果商店

## 問題敘述
喵喵遊俠很喜歡吃糖果，因此他決定自己開一家糖果店來賺錢。他的店有販賣 $N$ 種糖果，編號 $1$ 到 $N$，初始每一種糖果的數量都是 $0$。糖果店到目前為止已經營業了 $P$ 天，每一天喵喵遊俠都會選定一段連續編號的糖果進行補貨或者是有一段連續編號的糖果售出，也就是說，每一天都會有一段編號區間 $l$ 到 $r$ 的糖果的數量一起加 $y$。若 $y$ 大於等於 $0$ 代表補貨，若 $y$ 是負的代表售出，注意到糖果的數量可以是負數，代表顧客先預訂了該種類的糖果。

喵喵遊俠好奇某些種類的糖果的數量是在哪一天第一次大於等於 $k$。請你寫一支程式幫助喵喵遊俠。

## 輸入格式
第一行輸入三個整數 $N, P, Q$ 代表糖果有 $N$ 種、糖果店已經營業了 $P$ 天以及有 $Q$ 筆詢問。
接著輸入 $P$ 行，每一行有三個整數 $l_i, r_i, y_i$，其中的第 $i$ 行代表在第 $i$ 天編號 $l_i$ 到 $r_i$ 的糖果數量都加 $y_i$。
接著輸入 $Q$ 行，每一行有兩個整數 $x_i, k_i$，代表詢問第 $x_i$ 種糖果的數量是在哪一天第一次大於等於 $k_i$。
## 輸出格式
對於每一筆詢問，若第 $x_i$ 種糖果的數量從來沒有大於等於 $k_i$ 過則輸出 $-1$，反之則輸出答案。
## 資料範圍
- $1 \leq N, P, Q \leq 5 \times 10^5$
- $1 \leq l_i \leq r_i \leq N$
- $-10^9 \leq y_i \leq 10^9$
- $1 \leq x_i \leq N$
- $1 \leq k_i \leq 10^9$

## 子任務
- 子任務 1 滿足 $1 \leq P, Q \le 2000$

### 輸入範例 1

```
5 3 3
3 4 2
2 5 10
4 4 7
4 1
1 2
4 19
```

### 輸出範例 1

```
1
-1
3
```
### 輸入範例 2

```
10 4 4
2 9 3
4 8 -2
8 10 4
2 9 5
8 10
10 1
4 7
2 8
```

### 輸出範例 2

```
4
3
-1
4
```

### 輸入範例 3

```
2 3 2
1 1 -10
1 2 10
2 2 -10
1 10
2 10
```

### 輸出範例 3

```
-1
2
```



## 範例說明
- 第一筆範例中，編號四的糖果數量在這三天的變化是 $2, 12, 19$，第一天糖果數量就大於等於 $1$ 因此第一筆詢問要輸出 1。第三天糖果數量第一次大於等於 $19$ 因此第三筆詢問要輸出 $3$。而因為編號 $1$ 的糖果的數量經過三天後都沒有變動，因此第二筆詢問輸出 $-1$。
- 第二筆範例中，編號八的糖果數量在這四天的變化是 $3, 1, 5, 10$，因此數量第一次大於等於 $10$ 是第四天的時候因此第一筆詢問輸出 $4$。編號十的糖果數量在這四天的變化是 $0, 0, 4, 4$，因此數量第一次大於等於 $1$ 是第三天的時候因此第二筆詢問輸出 $3$。編號四的糖果數量在這四天的變化是 $3, 1, 1, 6$，因為不存在數量大於等於 $7$ 的日子因此第三筆詢問輸出 $-1$。編號二的糖果數量在這四天的變化是 $3, 3, 3, 8$，因此數量第一次大於等於 $8$ 是第四天的時候因此第四筆詢問輸出 $4$。
- 第三筆範例中，編號一的糖果數量在這三天的變化是 $-10, 0, 0$，因此第一筆詢問輸出 $-1$。編號二的糖果數量在這三天的變化是 $0, 10, 0$，因此數量第一次大於等於 $10$ 是第二天的時候，因此第二筆詢問輸出$2$。

***



# Candy Shop

## Description
meowmeowRanger loves candy, so he decided to open his own candy shop to make money. His shop has $N$ kinds of candies numbered from $1$ to $N$. Initially, the number of all kinds of candies is $0$. The candy shop will be open for $P$ days. On each day, meowmeowRanger will replenish a consecutive interval of candies or there will be a consecutive interval of candies been sold for some specific number. That is, on each day, there will be $l, r, y$ such that the number of candies numbered from $l$ to $r$ is added by $y$. It represents replenishment if $y$ is greater than or equal to $0$. If $y$ is less than $0$, it means selling off. Notice that the number of candy is possible to become negative, which means that the customers order the candies in advance.

meowmeowRanger is curious about the time that the number of some kinds of candies first becomes greater than or equal to $k$. Please write a program to help meowmeowRanger.

## Input Format
The first line contains three integers $N, P, Q$ representing that there are $N$ kinds of candies, the candy shop will be opened for $P$ days and there are $Q$ queries.
Next, input $P$ lines, each line contains three integers $l_i, r_i, y_i$, the $i$-th line of the input in this section represents that the number of the candies in the consecutive interval $l_i$ to $r_i$ are adding $y_i$ on the $i$-th day.
Next, input $Q$ lines, each line contains two integers $x_i, k_i$ representing that querying the first time that the number of the $x_i$ candy is greater than or equal to $k_i$.

## Output Format
For each query, if the number of the $x_i$ candy will never be greater than or equal to $k_i$ then output $-1$, otherwise, output the answer.

## Data Range
- $1 \leq N, P, Q \leq 5 \times 10^5$
- $1 \leq l_i \leq r_i \leq N$
- $-10^9 \leq y_i \leq 10^9$
- $1 \leq x_i \leq N$
- $1 \leq k_i \leq 10^9$

## Subtasks
- Subtask 1 satisfies $1 \leq P, Q \le 2000$

### Input Example 1
```
5 3 3
3 4 2
2 5 10
4 4 7
4 1
1 2
4 19
```
### Output Example 1
```
1
-1
3
```

### Input Example 2
```
10 4 4
2 9 3
4 8 -2
8 10 4
2 9 5
8 10
10 1
4 7
2 8
```


### Output Example 2

```
4
3
-1
4
```

### Input Example 3
```
2 3 2
1 1 -10
1 2 10
2 2 -10
1 10
2 10
```

### Output Example 3
```
-1
2
```

## Example Explanation:
- In the first example, the number of the fourth candy in three days is $2, 12, 19$, so the number of the candy has been greater than or equal to $1$ on the first day so output $1$ for the first query.The third day is the first time that the number of the candy is greater than or equal to $19$ so output $3$ for the third query. Since the number of the first candy never changes, so the output of the second query is $-1$.
- In the second example, the number of the eighth candy in four days is $3, 1, 5, 10$, so the fourth day is the first time the number of the candy is greater than or equal to $10$ so output $4$ for the first query. The number of the tenth candy in four days is $0, 0, 4, 4$, so the third day is the first time the number of the candy is greater than or equal to $10$ so output $3$ for the second query. The number of the fourth candy in four days is $3, 1, 1, 6$, since the number isn't greater than or equal to $7$ on any days, so output $-1$ for the third query. The number of the second candy in four days is $3, 3, 3, 8$, so the fourth day is the first time the number of the candy is greater than or equal to $8$ so output 4 in the forth query.
- In the third example, the number of the first candy in three days is $-10, 0, 0$, so output $-1$ for the first query. The number of second candy in three days is $0, 10, 0$, so the second day is the first time the number of the candy is greater than or equal to $10$ so ourpur $2$ for the second query.

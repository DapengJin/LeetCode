##
- 行内公式：$E = mc^2$
- 块级公式：
  $$\nabla \cdot \mathbf{E} = \frac{\rho}{\varepsilon_0}$$

- 行向量乘矩阵 → 线性组合 行向量
  $$
  \boldsymbol{\alpha} V
  =\begin{bmatrix}\alpha_1 & \dots & \alpha_n\end{bmatrix}
  \begin{bmatrix}
      v_1\\ v_2\\ \vdots\\ v_n
  \end{bmatrix}
  =\sum_{i=1}^{n}\alpha_i(常数)\,r_i(向量)\
  = b_1
  $$
- 矩阵乘行向量
  $$
  \mathbf b_1
  =\boldsymbol{\alpha}\,\mathbf V
  =\begin{bmatrix}\alpha_1 & \dots & \alpha_n\end{bmatrix}
    \begin{bmatrix}
        \mathbf v_1\\ \mathbf v_2\\ \vdots\\ \mathbf v_n
    \end{bmatrix}
  = \sum_{i=1}^{n}\alpha_i\,\mathbf v_i
  \;\in\;\mathbb R^{1\times d}.
  $$

- **Self-Attention 批处理公式**

  $$
  \underbrace{\mathbf A}_{m\times n}
  \; \underbrace{\mathbf V}_{n\times d}
  \;=\;
  \mathbf B \in\mathbb R^{m\times d},
  \qquad
  \mathbf A=
  \begin{bmatrix}
  \boldsymbol{\alpha}^{(1)}\\
  \boldsymbol{\alpha}^{(2)}\\
  \vdots\\
  \boldsymbol{\alpha}^{(m)}
  \end{bmatrix},
  \quad
  \boldsymbol{\alpha}^{(k)}=
  \begin{bmatrix}
  \alpha^{(k)}_1 & \dots & \alpha^{(k)}_n
  \end{bmatrix}.
  $$
  
- 对第 \(k\) 行有：

  $$
  \mathbf b_k
  = \boldsymbol{\alpha}^{(k)} \mathbf V
  = \sum_{i=1}^{n}\alpha^{(k)}_i \mathbf v_i,
  \qquad k = 1,\dots,m.
  $$
  $$
  \underbrace{K_{\text{cache}}}_{(n-1)\times d_k}
  $$



## 新 Qₙ 与旧 K 缓存做点积

## 场景
- 模型已经生成到第 n 步（token tₙ）
- 为节省推理时间
    - 不再把全部序列重新送进模型
    - 只给新 token 做一次前向
    - 把前面 1 ~ n-1 步的 K、V 向量存在缓存里（KV cache）

## 各符号含义
| 符号             | 维度 / 计算                     | 具体内容                                                                 |
|------------------|---------------------------------|--------------------------------------------------------------------------|
| **h_n** | $1 \times d_{\text{model}}$     | 当前 token 的隐藏表示（来自前一层或 embedding）                               |
| **q_n** | $h_n W_Q$ <br/> $1 \times d_k$    | 新 Query：用本层的查询权重矩阵 $W_Q$ 把 $h_n$ 线性映射得到                    |
| **$K_{\text{cache}}$** | $(n-1)\times d_k$             | 前 n-1 个 token 的 Key 向量，解码到上一步时已经算好并存下来了                  |
| **k_n** | $h_n W_K$ <br/> $1 \times d_k$    | 当前 token 的 Key（也会加入缓存，供下轮用）                                  |

## “点积”怎么做？
1.  **拼接 K**
    -   $K’ = \begin{bmatrix} K_{\text{cache}} \\[2pt] k_n \end{bmatrix} \in \mathbb R^{n \times d_k}$
2.  **计算分数向量**
    -   ${\bf s}_n = \frac{q_n \, K’^{\!\top}}{\sqrt{d_k}} \in \mathbb R^{1 \times n}$
    -   这里的 点积指 $q_n$ 与 每一行 $k_j$ 做内积（相似度）
    -   结果是一个长度 n 的分数向量： $s_{n,j} = \frac{q_n \cdot k_j}{\sqrt{d_k}},\quad j=1,\dots,n.$
3.  **softmax 得到权重**
    -   $\boldsymbol{\alpha}^{(n)} = \operatorname{softmax}({\bf s}_n)$
    -   这就是当前 token 对 自己以及所有历史 token 的注意力权重，保证权重和为 1。
4.  **加权求和 Value**
    -   $o_n = \boldsymbol{\alpha}^{(n)} \! \begin{bmatrix} V_{\text{cache}}\\ v_n \end{bmatrix} = \sum_{j=1}^{n}\alpha^{(n)}_j\,v_j$
    -   得到本层输出向量 $o_n$，随后送入下一层或投影到词表。

## 为什么这么做？
-   **效率**
    -   全序列重算分数是 $O(n^2 d_k)$
    -   只算新 Query × 缓存 Key 是 $O(n d_k)$
    -   推理长度越长，差距越大。
-   **权重复用**
    -   $W_Q, W_K, W_V$ 在所有时间步共享
    -   我们只是把同一层的线性变换和点积操作 拆成多次调用，而不是为 $t_1, t_2, \dots$ 建不同的注意力模块。

## 小结一句
-   “新 Qₙ 与旧 K 缓存点积” 就是：用当前 token 的 Query 向量 一次性 去和“历史 Key 序列”做内积，从而得到它对所有过去位置（再加自己）的注意力分数。这样既保持自注意力计算逻辑，又避免重复计算历史部分，极大提高了自回归解码效率。
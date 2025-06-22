

- $
        dfs(i, j) =
        \begin{cases}
        dfs(i+1, j-1) + 2, & \text{如果 } s[i] = s[j] \\
        \max(dfs(i+1, j), dfs(i, j-1)), & \text{如果 } s[i] \neq s[j]
        \end{cases}
$

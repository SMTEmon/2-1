# Theory of Computation: Formal Definitions
---

## 1. Deterministic Finite Automata (DFA)

### 1.1 Formal Definition of a DFA
A **Deterministic Finite Automaton** is a 5-tuple $(Q, \Sigma, \delta, q_0, F)$, where:

> [!DEFINITION] The 5-Tuple
> 1.  **$Q$** is a finite set called the **states**.
> 2.  **$\Sigma$** is a finite set called the **alphabet**.
> 3.  **$\delta : Q \times \Sigma \rightarrow Q$** is the **transition function**.
> 4.  **$q_0 \in Q$** is the **start state**.
> 5.  **$F \subseteq Q$** is the set of **accept states**.

### 1.2 Formal Definition of Computation
Let $M = (Q, \Sigma, \delta, q_0, F)$ be a DFA and $w = w_1w_2\dots w_n$ be a string where each $w_i \in \Sigma$.

> [!IMPORTANT] Acceptance Condition
> $M$ **accepts** $w$ if there exists a sequence of states $r_0, r_1, \dots, r_n$ in $Q$ such that:
> 1.  $r_0 = q_0$
> 2.  $\delta(r_i, w_{i+1}) = r_{i+1}$ for $i = 0, \dots, n-1$
> 3.  $r_n \in F$

> [!NOTE] Language of M
> The language recognized by $M$, denoted **$L(M)$**, is the set of all strings accepted by $M$.
> $$L(M) = \{ w \mid M \text{ accepts } w \}

---

## 2. Nondeterministic Finite Automata (NFA)

### 2.1 Formal Definition of an NFA
A **Nondeterministic Finite Automaton** is a 5-tuple $(Q, \Sigma, \delta, q_0, F)$, where:

> [!DEFINITION] The 5-Tuple
> 1.  **$Q$** is a finite set of states.
> 2.  **$\Sigma$** is a finite set of alphabet symbols.
> 3.  **$\delta : Q \times \Sigma_{\varepsilon} \rightarrow \mathcal{P}(Q)$** is the transition function.
>     *   $\Sigma_{\varepsilon} = \Sigma \cup \{\varepsilon\}$
>     *   $\mathcal{P}(Q)$ is the power set of $Q$.
> 4.  **$q_0 \in Q$** is the start state.
> 5.  **$F \subseteq Q$** is the set of accept states.

### 2.2 Formal Definition of Computation
Let $N = (Q, \Sigma, \delta, q_0, F)$ be an NFA and $w$ be a string over $\Sigma$.

> [!IMPORTANT] Acceptance Condition
> $N$ **accepts** $w$ if we can write $w = y_1y_2\dots y_m$ where each $y_i \in \Sigma_{\varepsilon}$, and there exists a sequence of states $r_0, r_1, \dots, r_m$ in $Q$ such that:
> 1.  $r_0 = q_0$
> 2.  $r_{i+1} \in \delta(r_i, y_{i+1})$ for $i = 0, \dots, m-1$
> 3.  $r_m \in F$

---

## 3. Regular Expressions

### 3.1 Formal Definition
$R$ is a **regular expression** if $R$ is:

> [!DEFINITION] Recursive Definition
> 1.  $a$ for some $a \in \Sigma$
> 2.  $\varepsilon$
> 3.  $\emptyset$
> 4.  $(R_1 \cup R_2)$, where $R_1$ and $R_2$ are regular expressions.
> 5.  $(R_1 \circ R_2)$, where $R_1$ and $R_2$ are regular expressions.
> 6.  $(R_1^*)$, where $R_1$ is a regular expression.

### 3.2 Associated Theorems

> [!QUOTE] Arden's Theorem
> For regular expressions $P, Q, R$ where $P$ does not contain $\varepsilon$:
> $$ R = Q + RP \implies R = QP^* \}

---

## 4. The Pumping Lemma

### 4.1 Formal Statement

> [!WARNING] The Pumping Lemma for Regular Languages
> If $A$ is a regular language, then there is a number $p$ (the pumping length) where, if $s$ is any string in $A$ of length at least $p$, then $s$ may be divided into three pieces, $s = xyz$, satisfying the following conditions:
>
> 1.  **$for\ all\ i \ge 0, xy^iz \in A$**
> 2.  **$|y| > 0$**
> 3.  **$|xy| \le p$

---

## 5. Closure Properties

> [!TIP] Closure Theorems
> The class of regular languages is closed under:
> *   **Union:** $A \cup B$
> *   **Concatenation:** $A \circ B$
> *   **Star:** $A^*$
> *   **Intersection:** $A \cap B$ (proved via De Morgan's laws or product construction)
> *   **Complement:** $\bar{A}$ (proved by flipping accept/reject states in a DFA)
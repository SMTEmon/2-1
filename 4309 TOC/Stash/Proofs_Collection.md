# Theory of Computation: Collected Proofs

---

## 1. Closure Properties of Regular Languages

We prove that the class of regular languages is closed under Union, Concatenation, and Star operations.

### 1.1 Closure under Union (The Product Construction)

> [!THEOREM] Theorem
> If $A_1$ and $A_2$ are regular languages, then $A_1 \cup A_2$ is regular.

> [!TIP] Proof Idea
> Construct a DFA $M$ that runs $M_1$ and $M_2$ in parallel. $M$ accepts if either $M_1$ or $M_2$ accepts.

> [!ABSTRACT] Formal Construction
> Let $M_1 = (Q_1, \Sigma, \delta_1, q_1, F_1)$ recognize $A_1$, and $M_2 = (Q_2, \Sigma, \delta_2, q_2, F_2)$ recognize $A_2$.
> Construct $M = (Q, \Sigma, \delta, q_0, F)$ where:
> 1.  **$Q = Q_1 \times Q_2$**: The set of all pairs of states.
> 2.  **$\Sigma = \Sigma$**: The same alphabet.
> 3.  **$\delta((r_1, r_2), a) = (\delta_1(r_1, a), \delta_2(r_2, a))$**: Transition each component independently.
> 4.  **$q_0 = (q_1, q_2)$**: Start at the pair of start states.
> 5.  **$F = \{(r_1, r_2) \mid r_1 \in F_1 \text{ or } r_2 \in F_2\}$**: Accept if *at least one* machine is in an accept state.

---

### 1.2 Closure under Concatenation

> [!THEOREM] Theorem
> If $A_1$ and $A_2$ are regular languages, then $A_1 \circ A_2$ is regular.

> [!TIP] Proof Idea
> Use NFAs. Construct an NFA $N$ that runs $N_1$, and non-deterministically jumps to the start of $N_2$ whenever $N_1$ accepts.

> [!ABSTRACT] Formal Construction
> Let $N_1 = (Q_1, \Sigma, \delta_1, q_1, F_1)$ recognize $A_1$, and $N_2 = (Q_2, \Sigma, \delta_2, q_2, F_2)$ recognize $A_2$.
> Construct $N = (Q, \Sigma, \delta, q_1, F_2)$ where:
> 1.  **$Q = Q_1 \cup Q_2$**: The states of both machines.
> 2.  **$q_1$**: The start state of $N_1$ is the start state of $N$.
> 3.  **$F_2$**: The accept states of $N_2$ are the accept states of $N$.
> 4.  **$\delta$**:
>     $$ \delta(q, a) = \begin{cases} \delta_1(q, a) & q \in Q_1 \\ \delta_2(q, a) & q \in Q_2 \\ \delta_1(q, a) \cup \{q_2\} & q \in F_1 \text{ and } a = \varepsilon \\ \end{cases} $$
>     *(Informally: Add $\varepsilon$-transitions from all states in $F_1$ to $q_2$.)*

---

### 1.3 Closure under Star

> [!THEOREM] Theorem
> If $A$ is a regular language, then $A^*$ is regular.

> [!TIP] Proof Idea
> Use NFAs. Construct an NFA $N$ that loops back to the start state whenever it hits an accept state. Also, allow accepting $\varepsilon$ (empty string).

> [!ABSTRACT] Formal Construction
> Let $N_1 = (Q_1, \Sigma, \delta_1, q_1, F_1)$ recognize $A$.
> Construct $N = (Q, \Sigma, \delta, q_0, F)$ where:
> 1.  **$Q = Q_1 \cup \{q_0\}$**: Add a new start state.
> 2.  **$F = F_1 \cup \{q_0\}$**: The new start state is also an accept state (for $\varepsilon$).
> 3.  **$\delta$**:
>     *   $\delta(q_0, \varepsilon) = \{q_1\}$ (Jump to old start).
>     *   $\delta(q, a) = \delta_1(q, a)$ for $q \in Q_1, a \neq \varepsilon$.
>     *   For $q \in F_1$, add transition $\varepsilon \to q_1$ (Loop back).

---

## 2. Equivalence of NFA and DFA

> [!THEOREM] Theorem
> Every NFA has an equivalent DFA.

> [!TIP] Proof Idea (The Subset Construction)
> We construct a DFA where each state represents a *set* of possible states the NFA could be in simultaneously.

> [!ABSTRACT] Formal Construction
> Let $N = (Q, \Sigma, \delta, q_0, F)$ be an NFA.
> Construct DFA $M = (Q', \Sigma, \delta', q_0', F')$:
> 1.  **$Q' = \mathcal{P}(Q)$**: The power set of $Q$ (states are sets like $\{q_1, q_2\}$).
> 2.  **$q_0' = E(\{q_0\})$**: The $\varepsilon$-closure of the start state.
> 3.  **$F' = \{R \in Q' \mid R \cap F \neq \emptyset\}$**: Any set containing an NFA accept state.
> 4.  **$\delta'(R, a) = \bigcup_{r \in R} E(\delta(r, a))$**: 
>     *   For a set of states $R$, feed input $a$ to all of them.
>     *   Take the union of all resulting states.
>     *   Apply $\varepsilon$-closure ($E$) to the result.

---

## 3. Proving Non-Regularity (Pumping Lemma Applications)

> [!IMPORTANT] The Pumping Lemma
> For any regular language $L$, there exists a length $p$ such that any $s \in L$ with $|s| \ge p$ can be split into $xyz$ where:
> 1.  $|xy| \le p$
> 2.  $|y| > 0$
> 3.  $xy^iz \in L$ for all $i \ge 0$.

### 3.1 Proof: $L = \{0^n 1^n \mid n \ge 0\}$ is not regular

> [!FAIL] Proof by Contradiction
> 1.  **Assume** $L$ is regular with pumping length $p$.
> 2.  **Choose string** $s = 0^p 1^p$. Note that $s \in L$ and $|s| = 2p \ge p$.
> 3.  **Split $s = xyz$**. Since $|xy| \le p$, $y$ must be contained entirely within the first $p$ zeros.
>     *   Therefore, $y = 0^k$ for some $k > 0$.
> 4.  **Pump up ($i=2$):** Consider $xy^2z$.
>     *   We added extra zeros ($y$) but no ones.
>     *   Number of 0s is $p+k$, number of 1s is still $p$.
>     *   Since $p+k \neq p$, $xy^2z \notin L$.
> 5.  **Contradiction.** $L$ is not regular.

### 3.2 Proof: $L = \{ww \mid w \in \{0,1\}^*\}$ is not regular

> [!FAIL] Proof by Contradiction
> 1.  **Assume** $L$ is regular with pumping length $p$.
> 2.  **Choose string** $s = 0^p 1 0^p 1$. ($w = 0^p 1$).
> 3.  **Split $s = xyz$**. Since $|xy| \le p$, $y$ consists only of 0s from the first segment.
>     *   $y = 0^k$ with $k > 0$.
> 4.  **Pump up ($i=2$):** Consider $xy^2z$.
>     *   The string becomes $0^{p+k} 1 0^p 1$.
>     *   The first half is $0^{p+k} 1$, the second half is $0^p 1$.
>     *   They are not equal, so the string is not in the form $ww$.
> 5.  **Contradiction.** $L$ is not regular.

---

## 4. Other Theorems

### 4.1 Arden's Theorem (for Regex)

> [!THEOREM] Theorem
> If $P, Q, R$ are regular expressions and $\varepsilon \notin P$, then the equation $R = Q + RP$ has the unique solution $R = QP^*$.

> [!EXAMPLE] Proof Sketch (Substitution)
> $$
> \begin{aligned}
> R &= Q + RP \\
> &= Q + (Q + RP)P = Q + QP + RP^2 \\
> &= Q + QP + (Q + RP)P^2 = Q + QP + QP^2 + RP^3 \\
> &\dots \\
> &= Q(1 + P + P^2 + \dots + P^n) + RP^{n+1}
> \end{aligned}
> $$
> As $n \to \infty$, this series approaches $QP^*$. The term $RP^{n+1}$ vanishes effectively because the length of the shortest string in $P^{n+1}$ grows indefinitely (since $\varepsilon \notin P$), so it cannot match any fixed finite string in $R$.
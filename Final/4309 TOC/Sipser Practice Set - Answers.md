***

**Tags:** #TheoryOfComputation #ExamPrep #AnswerKey #SipserExercises #CSE4309
**Linked Note:** [[Sipser Practice Set]]

---

# Answer Key: Sipser Practice Set (Corrected)

> [!tip] How to Use
> - Attempt the problem first. Check answers only to verify logic or unblock yourself.
> - For CFG/PDA problems, multiple valid solutions exist. Focus on the core idea.
> - For proofs, memorize the **structure** (Assume $\to$ Construct $\to$ Contradict).

---

## 1. CFG Analysis & Language Interpretation

> [!check] Ex 2.3
> a. **Variables:** $\{R, S, T, X\}$. **Terminals:** $\{a, b\}$. **Start:** $R$.
> b. **In:** `ab`, `ba`, `aab`. **Not in:** `a`, `b`, `aaa`, `aba`, `abba`.
> c. $T \xRightarrow{*} aba$: **True**. $XXX \xRightarrow{*} aba$: **True**. $T \xRightarrow{*} XXX$: **True**.
> d. **$L(G)$**: The set of all **non-palindromes** over $\{a, b\}$. 
>    - $T$ generates $\Sigma^*$. 
>    - $S$ generates strings with different first/last symbols. 
>    - $R$ wraps $S$ with symmetric padding. Thus, $w \in L(G)$ iff $w$ has at least one mismatched symmetric pair $\iff w \neq w^R$.

> [!check] Ex 2.13
> a. **$L(G)$**: 
>    - $T$ generates strings with exactly one `#` and any number of `0`s: $\{0^i \# 0^j \mid i,j \geq 0\}$.
>    - $S \to TT$ generates strings with exactly two `#`s: $\{0^i \# 0^j \# 0^k \mid i,j,k \geq 0\}$.
>    - $U$ generates $\{0^n \# 0^{2n} \mid n \geq 0\}$.
>    - $L(G) = \{0^i \# 0^j \# 0^k \mid i,j,k \geq 0\} \cup \{0^n \# 0^{2n} \mid n \geq 0\}$.
> b. **Not regular**: The subset $\{0^n \# 0^{2n}\}$ requires counting, violating pumping lemma for regular languages.

---

## 2. CFG Construction

> [!example] Ex 2.4
> a. $\{w \mid w \text{ has } \geq 3 \text{ 1s}\}$: $S \to A1A1A1A$, $A \to 0A \mid 1A \mid \epsilon$
> b. $\{w \mid w \text{ starts and ends with same symbol}\}$: $S \to 0A0 \mid 1A1 \mid 0 \mid 1$, $A \to 0A \mid 1A \mid \epsilon$
> c. $\{w \mid |w| \text{ is odd}\}$: $S \to 00S \mid 11S \mid 0 \mid 1$
> d. $\{w \mid |w| \text{ is odd, middle is 0}\}$: $S \to 0S0 \mid 0S1 \mid 1S0 \mid 1S1 \mid 0$
> e. $\{w \mid w = w^R\}$: $S \to 0S0 \mid 1S1 \mid 0 \mid 1 \mid \epsilon$

> [!example] Ex 2.6a
> **More a's than b's**: 
> Let $B$ generate balanced strings ($|w|_a = |w|_b$): $B \to aBbB \mid bBaB \mid \epsilon$
> Let $S$ generate strings with more a's: $S \to aS \mid aB \mid Ba$
> *Explanation:* $B$ ensures equal counts. $S$ adds at least one extra $a$ to a balanced string, or recursively adds more $a$'s.

> [!example] Ex 2.6b
> **Complement of $a^n b^n$**: Strings that are NOT of form $a^n b^n$. Either not in $a^*b^*$, or in $a^*b^*$ but $i \neq j$.
> $S \to A \mid B \mid C$
> $A \to bA \mid aA \mid b$ *(b before a)*
> $B \to aBb \mid aB \mid a$ *(more a's)*
> $C \to aCb \mid Cb \mid b$ *(more b's)*

> [!example] Ex 2.9
> $S \to X \mid Y$
> $X \to aXb \mid C$ *(handles $i=j$)*
> $Y \to aY \mid bZc$ *(handles $j=k$)*
> $C \to cC \mid \epsilon$, $Z \to bZc \mid \epsilon$
> **Ambiguous**: Yes. String $a^n b^n c^n$ can be derived via $X$ (matching $a,b$) or $Y$ (matching $b,c$), giving two parse trees.

> [!example] Ex 2.15
> **Why $S \to SS$ fails**: The construction assumes $S$ only appears as the start symbol. If $S$ appears on the RHS of other rules, adding $S \to SS$ allows duplication at arbitrary points in the derivation tree, not just at the "top level" where concatenation should occur.
> 
> **Counterexample**: Let $G: S \to aSb \mid \epsilon$. $L(G) = \{a^n b^n\}$. $A^* = \{(a^{n_1} b^{n_1}) \dots (a^{n_k} b^{n_k})\}$.
> Add $S \to SS$. $G'$ can derive: $S \Rightarrow SS \Rightarrow aSbS \Rightarrow a(SS)b \Rightarrow a(aSb)(\epsilon)b \Rightarrow aabb$. This IS in $A^*$.
> But $G'$ can also derive: $S \Rightarrow SS \Rightarrow aSbS \Rightarrow a(\epsilon)bS \Rightarrow abS \Rightarrow ab(aSb) \Rightarrow abaSb \Rightarrow abab$. This IS in $A^*$.
> The real failure occurs when $S$ is used recursively inside other rules. Example: $G: S \to aSb \mid aS \mid \epsilon$. $L(G) = \{a^i b^j \mid i \geq j\}$. Adding $S \to SS$ allows derivations like $S \Rightarrow SS \Rightarrow aSbS \Rightarrow a(aS)bS \Rightarrow aaSbS \Rightarrow aa(SS)b \Rightarrow \dots$ which can generate strings where the "concatenation boundary" cuts through the middle of an $a^i b^j$ block, producing strings not in $A^*$.

---

## 3. PDA Construction

> [!hint] Ex 2.5/2.7/2.10
> - **Equal 0s/1s**: Push on 0, pop on 1 (and vice versa). Accept on empty stack.
> - **More a's than b's**: Use stack as counter. Push $A$ for $a$, pop $A$ for $b$. If stack empty on $b$, push $B$. Accept if final stack has net $A$'s.
> - **$a^i b^j c^k$ ($i=j$ or $j=k$)**: Nondeterministically branch at start. Branch 1: match $a$'s and $b$'s, verify $c$'s free. Branch 2: skip $a$'s, match $b$'s and $c$'s.

> [!hint] Ex 2.11 (CFG $\to$ PDA)
> Standard 3-state construction:
> 1. Push $E$.
> 2. If top is variable, replace with RHS (nondeterministically).
> 3. If top is terminal, match input and pop.
> 4. Accept if stack empty.

---

## 4. CNF, Ambiguity & Closure

> [!example] Ex 2.14 (CNF)
> 1. $S_0 \to A$
> 2. Remove $\epsilon$: $A \to BAB \mid BA \mid AB \mid B \mid A \mid BB \mid \epsilon$, $B \to 00$
> 3. Remove unit rules.
> 4. Replace terminals: $U_0 \to 0$. Binarize: $A \to B U_1$, $U_1 \to AB$, etc.

> [!example] Ex 2.2 (Closure)
> a. $A \cap B = \{a^n b^n c^n\}$. Both $A, B$ are CFLs. Intersection is not CFL. Thus CFLs not closed under $\cap$.
> b. DeMorgan: $\overline{A \cap B} = \overline{A} \cup \overline{B}$. If CFLs closed under complement, $\overline{A}, \overline{B}$ are CFLs. CFLs closed under $\cup$, so $\overline{A} \cup \overline{B}$ is CFL. Then $\overline{\overline{A} \cup \overline{B}} = A \cap B$ would be CFL. Contradiction.

> [!example] Ex 2.16 (Closure Proof)
> Given $G_1, G_2$ for $L_1, L_2$ (disjoint variables).
> - **Union**: New start $S \to S_1 \mid S_2$.
> - **Concatenation**: New start $S \to S_1 S_2$.
> - **Star**: New start $S \to S_1 S \mid \epsilon$.

---

## 5. TM Constructions

> [!check] Ex 3.8a
> **Equal 0s and 1s**: Sweep left-to-right. Cross off one 0 and one 1 per pass. Repeat. If all crossed off, accept. If one type remains, reject.

> [!check] Ex 3.8b
> **Twice as many 0s as 1s**: Per pass, cross off two 0s and one 1. Repeat. Verify all crossed.

> [!check] Ex 3.8c
> **NOT twice as many**: Run TM from (b). If it accepts, reject. If it rejects, accept. (Closure under complement for decidable languages).

---

## 6. TM Variants, Church-Turing & Theory

> [!abstract] Ex 3.3
> NTM $\to$ DTM for decidability: Use BFS on computation tree. Since NTM is a decider, all branches are finite. A finite tree with finite branching has finitely many nodes. BFS visits all nodes in finite time. DTM accepts if any branch accepts, rejects if all reject.

> [!abstract] Ex 3.4
> **Enumerator**: $E = (Q, \Sigma, \Gamma, \delta, q_0, q_{acc}, q_{rej})$ with two tapes. Tape 1: work tape. Tape 2: printer (write-only, moves right only). $L(E) = \{w \mid w \text{ is eventually printed on tape 2}\}$.

> [!abstract] Ex 3.5
> a. **Yes**. $\sqcup \in \Gamma$, TM can write any tape symbol.
> b. **No**. $\Gamma$ must contain $\sqcup$, but $\Sigma$ cannot. So $\Gamma \supset \Sigma$.
> c. **No**. Transition function requires $L$ or $R$ move.
> d. **Yes**, but trivial. Must have at least $q_{acc}$ and $q_{rej}$, so minimum 3 states if they're distinct. If $q_0 = q_{acc}$, accepts everything immediately.

> [!abstract] Ex 3.6
> **Fails because of looping**. If $M$ loops on $s_1$, step 2 never finishes. $s_2, s_3, \dots$ are never tested. Correct algorithm uses **dovetailing** to interleave steps across all inputs.

> [!abstract] Ex 3.7
> **Not legitimate** because step 1 ("Try all possible settings") is an infinite loop if no solution exists. A TM must halt on all inputs to be a decider. This describes an unbounded search with no termination guarantee on negative instances.

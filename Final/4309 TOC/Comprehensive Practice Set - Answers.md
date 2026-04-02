***

**Tags:** #TheoryOfComputation #ExamPrep #AnswerKey #CSE4309
**Linked Note:** [[Comprehensive Practice Set]]

---

# Answer Key: Comprehensive Practice Set

> [!tip] How to Use This Key
> - Use this **only after** attempting the problems yourself.
> - Pay close attention to the **structure of proofs** (Sections 7 & 8). Examiners award marks for clear logical flow, not just the final answer.
> - For CYK tables, verify your split points ($k$) carefully.

---

## 1. CFG Language Interpretation

1. **$G_1$**: $L = \{w \in \{0,1\}^* \mid |w|_0 = |w|_1\}$. (Equal number of 0s and 1s). Examples: `01`, `1001`.
2. **$G_2$**: $L = \{a^n b^n \mid n \geq 0\} \cup \{a^m \mid m \geq 0\} \cup \{b^m \mid m \geq 0\}$. Examples: `aabb`, `aaaa`.
3. **$G_3$**: $L = \{w \in \{a,b\}^* \mid w = w^R\}$. (All palindromes over $\{a,b\}$). Examples: `aba`, `abba`.
4. **$G_4$**: $L = \{w \in \{a,b\}^* \mid |w|_a = |w|_b\}$. (Equal number of a's and b's). Examples: `ab`, `baba`.
5. **$G_5$**: $L = \{w \in \{a,b\}^* \mid |w|_a = |w|_b\}$. (Classic grammar for equal counts). Examples: `ab`, `aabb`.

---

## 2. PDA Construction

> [!hint] Q1: $0^n 1^n$
> Push `X` for every `0`. Pop `X` for every `1`. Accept if stack is empty (or reaches bottom marker) exactly when input ends.

> [!hint] Q2: More 0s than 1s
> Treat stack as counter. Push `A` on `0`, pop `A` on `1`. If stack empty and `1` arrives, push `B`. Accept if final stack has more `A`s than `B`s. Nondeterminism helps guess the "excess" portion.

> [!hint] Q3: $a^i b^j c^k$ ($i=j$ XOR $j=k$)
> Nondeterministically branch:
> - **Branch 1:** Match $a$'s and $b$'s ($i=j$), then verify $c$'s count $\neq j$ by consuming extra/fewer $c$'s.
> - **Branch 2:** Ignore $a$'s, match $b$'s and $c$'s ($j=k$), verify $a$'s count $\neq j$.

> [!hint] Q4: $ww^R$
> Push input symbols onto stack. Nondeterministically guess the middle of the string. Switch to popping mode: match each popped symbol with the next input symbol. Accept if stack empties with input.

> [!hint] Q5: CFG $\to$ PDA
> 3-state standard construction:
> 1. Push start symbol $S$.
> 2. If top is variable $V$, replace with RHS of a rule (nondeterministically).
> 3. If top is terminal $a$, match with input and pop.
> 4. Accept if stack empty and input consumed.

---

## 3. TM Construction & Decidability Proofs

> [!check] Q1: $A_{DFA}$ Decidable
> TM $M$: On input $\langle A, w \rangle$, simulate $A$ on $w$. If simulation ends in accept state, accept. Else reject. Always halts because DFA simulation is finite.

> [!check] Q2: $E_{DFA}$ Decidable
> TM $M$: On input $\langle A \rangle$, mark start state. Iteratively mark any state reachable from a marked state via a transition. If any accept state is marked, reject. Else accept.

> [!check] Q3: $EQ_{DFA}$ Decidable
> TM $M$: On input $\langle A, B \rangle$, construct DFA $C$ for symmetric difference $L(C) = (L(A) \cap \overline{L(B)}) \cup (\overline{L(A)} \cap L(B))$. Run $E_{DFA}$ decider on $C$. If $L(C) = \emptyset$, accept; else reject.

> [!check] Q4: $A_{CFG}$ Decidable
> TM $M$: On input $\langle G, w \rangle$, convert $G$ to CNF. Generate all possible derivations of length $2|w|-1$ (finite set). If any yields $w$, accept. Else reject.

> [!check] Q5: $L(G) \neq \emptyset$ Decidable
> TM $M$: On input $\langle G \rangle$, mark all terminals. Iteratively mark variables that have a rule consisting entirely of already-marked symbols. If start variable $S$ gets marked, accept. Else reject.

> [!check] Q6: "Accepts exactly 2 strings"
> **Undecidable.** If decidable, we could decide $E_{TM}$ (emptiness) by constructing a machine that accepts 2 fixed strings if $M$ accepts $w$, and 0 otherwise. Contradiction.

---

## 4. CNF Conversion & CYK Algorithm

> [!example] Q1: CNF Conversion
> 1. New start: $S_0 \to S$
> 2. Remove $\epsilon$ ($B \to \epsilon$): $S \to ASA \mid AS \mid SA \mid S \mid aB \mid a$
> 3. Remove unit ($A \to B, A \to S$): Substitute recursively until only terminals/multi-vars remain.
> 4. Replace terminals in mixed rules: $U_a \to a, U_b \to b$
> 5. Binarize long rules: $S \to A U_1, U_1 \to SA$, etc.

> [!example] Q2: CNF Conversion
> 1. $S_0 \to S$
> 2. Remove $\epsilon$: $S \to aSb \mid ab \mid SS \mid S$
> 3. Remove unit $S \to S$
> 4. Terminals: $U_a \to a, U_b \to b$
> 5. Binarize: $S \to U_a V \mid U_a U_b \mid SS$, $V \to S U_b$

> [!table] Q3: CYK Table for `baaba`
> | Length $j$ | $i=1$ | $i=2$ | $i=3$ | $i=4$ | $i=5$ |
> |---|---|---|---|---|---|
> | 1 | `{B}` | `{A,C}` | `{A,C}` | `{B}` | `{A,C}` |
> | 2 | `{A}` | `{B}` | `{S,C}` | `{A}` | |
> | 3 | $\emptyset$ | `{B}` | `{B}` | | |
> | 4 | $\emptyset$ | `{S,C,A}` | | | |
> | 5 | `{S,A,C}` | | | | |
> **Result:** $S \in T[1,5] \implies$ **Accepted**.

> [!table] Q4: CYK Table for `abab`
> | Length $j$ | $i=1$ | $i=2$ | $i=3$ | $i=4$ |
> |---|---|---|---|---|
> | 1 | `{A}` | `{B}` | `{A}` | `{B}` |
> | 2 | `{S,C}` | `{A}` | `{S,C}` | |
> | 3 | `{B}` | `{B}` | | |
> | 4 | `{S,C,A}` | | | |
> **Result:** $S \in T[1,4] \implies$ **Accepted**.

---

## 5. Pumping Lemma for CFLs

> [!warning] Q1: $a^n b^n c^n$
> Choose $s = a^p b^p c^p$. Since $|vxy| \leq p$, $vxy$ spans at most 2 symbol types. Pumping ($i=2$) increases only those 2 types, breaking the $n=n=n$ balance. $\notin L$. Contradiction.

> [!warning] Q2: $a^n b^m c^n d^m$
> Choose $s = a^p b^p c^p d^p$. $vxy$ cannot cover both $a$'s and $c$'s, nor $b$'s and $d$'s simultaneously. Pumping breaks at least one paired equality.

> [!warning] Q3: $ww$
> Choose $s = 0^p 1^p 0^p 1^p$. $vxy$ is confined to one half or crosses the middle. Pumping changes one half's structure without mirroring it in the other half.

> [!warning] Q4: $a^{n^2}$
> Choose $s = a^{p^2}$. Pumping adds $|vy|$ symbols. The gap between consecutive squares $(p+1)^2 - p^2 = 2p+1$ grows faster than $|vy| \leq p$. Pumped string lands between squares.

> [!warning] Q5: $i < j < k$
> Choose $s = a^p b^{p+1} c^{p+2}$. $vxy$ spans $\leq p$ symbols, so it misses at least one block. Pumping increases counts of covered blocks but not others, breaking the strict inequality chain.

---

## 6. TM Variants, Church-Turing & Encodings

> [!info] Q1: 2-Tape Simulation
> Single tape stores both tapes interleaved or separated by `#`. "Dotted" symbols mark head positions. Overhead: $O(T(n)^2)$ because the single head must sweep back and forth to simulate $k$ heads.

> [!info] Q2: NTM BFS vs DFS
> DFS may follow an infinite rejecting branch forever, missing a finite accepting branch. BFS explores all branches level-by-level, guaranteeing discovery of an accepting path if one exists.

> [!info] Q3: Graph Encoding
> Adjacency list: `<u1,v1>#<u2,v2>#...` or matrix as binary string. TM parses `#` delimiters to reconstruct edges.

> [!info] Q4: Church-Turing Thesis
> "Any effective algorithmic procedure can be computed by a TM." Justifies high-level ops (e.g., "sort array") because we trust they compile to finite TM states/transitions.

> [!info] Q5: Turing Enumerator
> TM with a printer. Outputs strings one by one. **Theorem:** $L$ is T-recognizable $\iff$ some enumerator enumerates $L$. Proof uses dovetailing to avoid looping hazards on non-members.

---

## 7. Undecidability Proofs

> [!danger] Q1: $A_{TM}$ Diagonalization
> Assume decider $H$. Build $D$: on $\langle M \rangle$, run $H(\langle M, \langle M \rangle \rangle)$ and flip output. Run $D(\langle D \rangle)$. If $D$ accepts $\implies H$ said reject $\implies D$ rejects. Paradox. $H$ cannot exist.

> [!danger] Q2: $HALT_{TM}$ Diagonalization
> Assume decider $H$. Build $D$: on $\langle M \rangle$, run $H(\langle M, \langle M \rangle \rangle)$. If $H$ says halts $\to$ loop. If $H$ says loops $\to$ halt. Run $D(\langle D \rangle)$. Paradox. $H$ cannot exist.

> [!danger] Q3: $HALT_{TM}$ Reduction from $A_{TM}$
> Assume $R$ decides $HALT$. Build $S$ for $A_{TM}$: On $\langle M, w \rangle$, run $R(\langle M, w \rangle)$. If rejects, reject. If accepts, simulate $M$ on $w$ and output result. $S$ always halts $\implies A_{TM}$ decidable. Contradiction.

> [!danger] Q4: $E_{TM}$ Reduction from $A_{TM}$
> Assume $E$ decides $E_{TM}$. Build $S$ for $A_{TM}$: On $\langle M, w \rangle$, construct $M'$ that ignores input, simulates $M$ on $w$, accepts if $M$ accepts. If $M$ accepts $w$, $L(M') = \Sigma^*$ (not empty). If not, $L(M') = \emptyset$. Run $E$ on $\langle M' \rangle$ and flip output. Contradiction.

> [!danger] Q5: $REGULAR_{TM}$ Reduction
> Assume $R$ decides $REGULAR_{TM}$. Build $S$ for $A_{TM}$: On $\langle M, w \rangle$, construct $M'$: on input $x$, if $x \in \{0^n 1^n\}$ accept. Else simulate $M$ on $w$; if $M$ accepts, accept. If $M$ accepts $w$, $L(M') = \Sigma^*$ (regular). If not, $L(M') = \{0^n 1^n\}$ (not regular). Run $R$ on $\langle M' \rangle$. Contradiction.

---

## 8. TM Recognizability vs Decidability

> [!abstract] Q1: $A_{TM}$ Recognizable
> UTM $U$: Simulate $M$ on $w$. If $M$ accepts, $U$ accepts. If $M$ loops, $U$ loops. Recognizer need not halt on rejects.

> [!abstract] Q2: $\overline{A_{TM}}$ Not Recognizable
> If both $A_{TM}$ and $\overline{A_{TM}}$ were recognizable, $A_{TM}$ would be decidable (run both in parallel). Since $A_{TM}$ is undecidable, $\overline{A_{TM}}$ cannot be recognizable.

> [!abstract] Q3: $A, \overline{A}$ Recognizable $\implies$ Decidable
> Run recognizer $M_1$ for $A$ and $M_2$ for $\overline{A}$ in parallel (dovetailing). One must eventually accept. If $M_1$ accepts $\to$ accept. If $M_2$ accepts $\to$ reject. Always halts.

> [!abstract] Q4: $HALT_{TM}$ Recognizable
> TM $U$: Simulate $M$ on $w$. If simulation halts, accept. If $M$ loops, $U$ loops. Recognizes halting pairs.

---

## 9. True/False with Justification

1. **True**. Regular $\subset$ CFL $\subset$ Decidable. Every regular language has a CFG ($S \to aS \mid \epsilon$).
2. **False**. CFLs are not closed under intersection. $\{a^n b^n c^m\} \cap \{a^m b^n c^n\} = \{a^n b^n c^n\}$ (not CFL).
3. **True**. Decidable languages are closed under complement and reduction. If $B$ decidable, run $B$'s decider on reduced input.
4. **False**. This is $ALL_{TM}$ (Totality), which is not even Turing-recognizable (strictly harder than $A_{TM}$).
5. **False**. Inherently ambiguous languages exist (e.g., $\{a^n b^n c^m\} \cup \{a^n b^m c^m\}$). No unambiguous CFG can generate them.
6. **False**. NPDA $\supset$ DPDA. NPDA can recognize palindromes $ww^R$; DPDA cannot.
7. **True**. TMs can count and compare arbitrarily. A TM can simulate three counters or use a multi-tape approach to verify $a^n b^n c^n$.
8. **True**. Reductions preserve decidability downwards. If $A \leq_m B$ and $B$ decidable, compose reduction with $B$'s decider.
9. **False**. CYK strictly requires CNF to guarantee $\mathcal{O}(n^3)$ binary splits. Arbitrary CFGs break the dynamic programming structure.
10. **True**. Enumerator Theorem. A language is T-recognizable iff some enumerator lists its strings.

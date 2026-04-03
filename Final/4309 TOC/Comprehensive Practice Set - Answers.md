***

**Tags:** #TheoryOfComputation #ExamPrep #AnswerKey #CSE4309
**Linked Note:** [[Comprehensive Practice Set]]

---

# Answer Key: Comprehensive Practice Set (Corrected)

> [!tip] How to Use This Key
> - This key has been corrected to fix previous errors in language interpretation and CYK tables.
> - For CYK tables, verify your split points ($k$) carefully. The table is filled bottom-up.

---

## 1. CFG Language Interpretation

1. **$G_1$**: $L = \{w \in \{0,1\}^* \mid |w| = 2n \text{ and } w_i \neq w_{2n-i+1} \text{ for all } 1 \leq i \leq n\}$. 
   *Explanation:* Every 0 must be matched with a 1 at the mirror position, and every 1 with a 0.
   Examples: `01`, `10`, `0011`, `0101`, `1100`, `1010`. (Note: `0110` is NOT in the language).

2. **$G_2$**: $L = \{a^i b^j \mid i, j \geq 0\}$. (The language $a^* b^*$).
   *Explanation:* $S \to aSb$ generates $a^n S b^n$. $S \to A$ allows any number of extra $a$'s, and $S \to B$ allows any number of extra $b$'s. Combined, they can generate any string of $a$'s followed by any string of $b$'s.
   Examples: `ab`, `aab`, `abb`, `aaaa`, `bb`.

3. **$G_3$**: $L = \{w \in \{a,b\}^* \mid w = w^R\}$. (All palindromes over $\{a,b\}$).
   Examples: `aba`, `abba`, `a`, `b`, `$\epsilon$`.

4. **$G_4$**: $L = \{w \in \{a,b\}^* \mid |w|_a = |w|_b\}$. (Equal number of a's and b's).
   Examples: `ab`, `baba`, `aabb`.

5. **$G_5$**: $L = \{w \in \{a,b\}^* \mid |w|_a = |w|_b\}$. (Alternative grammar for equal counts).
   Examples: `ab`, `aabb`, `ba`.

---

## 2. PDA Construction

> [!hint] Q1: $0^n 1^n$
> Push `$` (bottom marker) and then `X` for every `0`. Pop `X` for every `1`. If input ends and top is `$`, accept.

> [!hint] Q2: More 0s than 1s
> Use stack to track the net difference.
> - If stack is empty or has `0`, push `0` on input `0`.
> - If stack has `1` and input is `0`, pop `1`.
> - (Vice versa for input `1`).
> - Accept if, after consuming input, the stack contains at least one `0`.

> [!hint] Q3: $a^i b^j c^k$ ($i=j$ XOR $j=k$)
> Nondeterministically branch:
> - **Branch 1:** Match $a$'s and $b$'s ($i=j$). Then read $c$'s and ensure $|c| \neq |b|$ (by either running out of $c$'s early or having $c$'s left over).
> - **Branch 2:** Skip $a$'s (ensuring $|a| \neq |b|$), then match $b$'s and $c$'s ($j=k$).

> [!hint] Q4: $ww^R$
> Push input symbols. Nondeterministically guess the middle. Switch to popping and matching. Accept on empty stack + empty input.

> [!hint] Q5: CFG $\to$ PDA (Top-Down)
> 1. Push `$`, then Start Variable $S$.
> 2. If Top is Variable $V$, replace with RHS (nondeterministic).
> 3. If Top is Terminal $a$, match with input and pop.
> 4. Accept on `$`.

---

## 3. TM Construction & Decidability Proofs

> [!check] Q1-Q5 (Standard Results)
> - $A_{DFA}, E_{DFA}, EQ_{DFA}, A_{CFG}$ are all decidable.
> - $L(G) \neq \emptyset$ (Emptiness for CFG) is decidable via the marking algorithm (mark terminals, then variables that derive marked symbols).

> [!check] Q6: "Accepts exactly 2 strings"
> **Undecidable.** By Rice's Theorem, any non-trivial property of the language is undecidable. "Cardinality is 2" is non-trivial.

---

## 4. CNF Conversion & CYK Algorithm

> [!example] Q1: CNF Conversion ($S \to ASA \mid aB, A \to B \mid S, B \to b \mid \epsilon$)
> 1. $S_0 \to S$
> 2. $\epsilon$-removal ($B \to \epsilon$): $S \to ASA \mid aB \mid a$. $A \to B \mid S \mid \epsilon$.
> 3. $\epsilon$-removal ($A \to \epsilon$): $S \to ASA \mid AS \mid SA \mid S \mid aB \mid a$.
> 4. Unit removal ($A \to B, A \to S$, etc.): Substitute until all unit rules are gone.
> 5. Binarize and Terminal-fix.

> [!table] Q3: CYK Table for `baaba`
> **Grammar:** $S \to AB \mid BC, A \to BA \mid a, B \to CC \mid b, C \to AB \mid a$
> 
> | $j \setminus i$ | 1 (`b`) | 2 (`a`) | 3 (`a`) | 4 (`b`) | 5 (`a`) |
> | :--- | :--- | :--- | :--- | :--- | :--- |
> | **1** | {B} | {A,C} | {A,C} | {B} | {A,C} |
> | **2** | {A,S} | {B} | {S} | {A,S} | |
> | **3** | {B} | {S,A,C} | {B} | | |
> | **4** | {S,A,C} | {S,A,C} | | | |
> | **5** | {S,A,C} | | | | |
> **Result:** $S \in T[1,5] \implies$ **Accepted**.

> [!table] Q4: CYK Table for `abab`
> **Grammar:** $S \to AB \mid BC, A \to a, B \to b \mid AB, C \to a$
> 
> | $j \setminus i$ | 1 (`a`) | 2 (`b`) | 3 (`a`) | 4 (`b`) |
> | :--- | :--- | :--- | :--- | :--- |
> | **1** | {A,C} | {B} | {A,C} | {B} |
> | **2** | {S,B} | $\emptyset$ | {S,B} | |
> | **3** | {S,B} | {S,B} | | |
> | **4** | {S,B} | | | |
> **Result:** $S \in T[1,4] \implies$ **Accepted**.

---

## 5. Pumping Lemma for CFLs
*(All proofs follow the standard structure: Assume $L$ is CFL, let $p$ be pumping length, choose string $s \in L$ where $|s| \ge p$, show all splits $s=vuxyz$ fail at least one condition after pumping.)*

---

## 6. TM Variants, Church-Turing & Encodings

> [!info] Q1: 2-Tape TM Simulation on a 1-Tape TM
> A standard 1-tape TM simulates $k$ tapes by partitioning its single tape into $k$ virtual tracks (or by separating tape contents with a special delimiter like `#`). 
> *   **The "Dotted Symbol" Method:** To track the $k$ head positions, the 1-tape TM uses an expanded alphabet where every symbol $a \in \Gamma$ has a "dotted" version $\dot{a}$. A dot indicates a virtual head is currently at that cell.
> *   **Simulation Step:** To simulate one move, the 1-tape TM sweeps from the leftmost `#` to the rightmost `#` to read all dotted symbols, stores the state changes in its finite control, and then sweeps back to update the symbols and move the dots.
> *   **Time Complexity:** If the $k$-tape TM runs in $T(n)$ time, the 1-tape TM requires **$O(T(n)^2)$** time because each step of the $k$-tape TM requires a full sweep of the 1-tape TM's active tape area (which can grow up to $T(n)$).

> [!info] Q2: NTM Simulation: BFS vs. DFS
> An NTM's computation can be viewed as a tree where each node is a configuration and branches represent nondeterministic choices.
> *   **The Risk of DFS:** A Depth-First Search (DFS) might follow an **infinite rejecting branch** forever. Even if a finite accepting branch exists elsewhere in the tree, the DFS will never backtrack to find it.
> *   **The Guarantee of BFS:** A Breadth-First Search (BFS) explores the tree level-by-level (all branches of length 1, then all of length 2, etc.). This ensures that if an accepting configuration exists at some finite depth $d$, the DTM **will eventually reach it**, making BFS essential for proving that NTMs and DTMs are equivalent in power.

> [!info] Q3: Encoding a Directed Graph $G$
> A graph $G = (V, E)$ is typically encoded as a string $\langle G \rangle$ by listing its nodes and edges using delimiters:
> *   **Format:** `(nodes)#(edges)`
> *   **Example:** For a graph with nodes $\{1, 2, 3\}$ and edges $\{(1,2), (2,3)\}$, the encoding might be `(1,2,3)#((1,2),(2,3))`.
> *   The TM can then parse this string by moving its head to find specific nodes or verify the existence of edges during a simulation (e.g., a reachability algorithm).

> [!info] Q4: The Church-Turing Thesis
> **Definition:** The "intuitive" notion of an algorithm or an "effective procedure" corresponds exactly to the set of functions computable by a Turing Machine. Essentially, any calculation that can be performed by a human or a computer following a finite set of rules can be performed by a TM.
> **High-Level Examples:**
> 1.  **"Mark all nodes reachable from $s$":** Using a marking algorithm like BFS/DFS on a graph.
> 2.  **"Sort the input string alphabetically":** Implementing a bubble sort or merge sort by swapping symbols on the tape.

> [!info] Q5: Turing Enumerators
> A **Turing Enumerator** is a TM variant equipped with an attached "printer." It starts on an empty tape and prints out a list of strings (potentially infinitely many). The language "enumerated" by the machine is the set of all strings it eventually prints.
> 
> **Theorem:** A language is Turing-recognizable iff some enumerator enumerates it.
> *   **($\Leftarrow$):** If an enumerator $E$ exists, we build a TM $M$ that, on input $w$, runs $E$ and compares every printed string to $w$. If $w$ appears, $M$ accepts.
> *   **($\Rightarrow$):** If a TM $M$ recognizes $L$, we build an enumerator $E$. $E$ must avoid getting stuck on a string that $M$ loops on. It uses **dovetailing**:
>     1.  Run $M$ for 1 step on string $s_1$.
>     2.  Run $M$ for 2 steps on strings $s_1, s_2$.
>     3.  Run $M$ for $n$ steps on $s_1, \dots, s_n$.
>     Whenever $M$ accepts a string during this interleaved process, the enumerator prints it. Since every $w \in L$ is accepted in some finite number of steps, every $w$ will eventually be printed.

---

## 7. Undecidability Proofs

> [!danger] Q1: $A_{TM}$ is Undecidable (Diagonalization)
> **Proof by contradiction:**
> 1.  Assume $H$ is a decider for $A_{TM}$. $H(\langle M, w \rangle)$ accepts if $M$ accepts $w$, and rejects otherwise.
> 2.  Construct a new TM $D$ that takes $\langle M \rangle$ as input:
>     - $D$ runs $H$ on input $\langle M, \langle M \rangle \rangle$.
>     - $D$ does the **opposite** of $H$: If $H$ accepts, $D$ rejects. If $H$ rejects, $D$ accepts.
> 3.  **The Paradox:** Run $D$ on its own description $\langle D \rangle$.
>     - If $D$ accepts $\langle D \rangle \implies H$ rejected $\langle D, \langle D \rangle \rangle \implies D$ rejects $\langle D \rangle$.
>     - If $D$ rejects $\langle D \rangle \implies H$ accepted $\langle D, \langle D \rangle \rangle \implies D$ accepts $\langle D \rangle$.
> 4.  **Conclusion:** A contradiction exists. $H$ cannot exist.

> [!danger] Q2: $HALT_{TM}$ is Undecidable (Diagonalization)
> **Logic Flow:**
> 1.  Assume $H$ decides $HALT_{TM}$.
> 2.  Construct $D$: On input $\langle M \rangle$, run $H(\langle M, \langle M \rangle \rangle)$.
> 3.  If $H$ says "halts", $D$ enters an **infinite loop**.
> 4.  If $H$ says "loops", $D$ **halts and accepts**.
> 5.  Running $D(\langle D \rangle)$ leads to: $D$ halts iff $D$ loops. Contradiction.

> [!danger] Q3: $HALT_{TM}$ is Undecidable (Reduction from $A_{TM}$)
> **Goal:** Show that if $HALT_{TM}$ were decidable, $A_{TM}$ would be too.
> 1.  Assume $R$ decides $HALT_{TM}$.
> 2.  Construct a decider $S$ for $A_{TM}$: On input $\langle M, w \rangle$:
>     - First, run $R$ on $\langle M, w \rangle$ to see if $M$ halts on $w$.
>     - If $R$ rejects (loops), then $M$ definitely doesn't accept $w \implies$ **Reject**.
>     - If $R$ accepts (halts), **simulate** $M$ on $w$. Since we know it halts, the simulation is safe.
>     - If $M$ accepts $w$, **Accept**; else **Reject**.
> 3.  Since $A_{TM}$ is undecidable, $R$ cannot exist.

> [!danger] Q4: $E_{TM}$ is Undecidable (Reduction from $A_{TM}$)
> **Goal:** Prove $L(M) = \emptyset$ is undecidable.
> 1.  Assume $E$ decides $E_{TM}$.
> 2.  Construct $S$ for $A_{TM}$: On input $\langle M, w \rangle$:
>     - Construct a "helper" TM $M_{w}$ that ignores its own input $x$ and just simulates $M$ on $w$.
>     - If $M$ accepts $w$, then $M_{w}$ accepts *everything* ($L(M_{w}) = \Sigma^* \neq \emptyset$).
>     - If $M$ doesn't accept $w$, then $M_{w}$ accepts *nothing* ($L(M_{w}) = \emptyset$).
>     - Run $E$ on $\langle M_{w} \rangle$. 
>     - If $E$ accepts ($\emptyset$), then $M$ doesn't accept $w \implies$ **Reject**.
>     - If $E$ rejects ($\neq \emptyset$), then $M$ accepts $w \implies$ **Accept**.
> 3.  Contradiction.

> [!danger] Q5: $REGULAR_{TM}$ is Undecidable (Reduction from $A_{TM}$)
> **Logic Flow:**
> 1.  Assume $R$ decides $REGULAR_{TM}$.
> 2.  Construct $S$ for $A_{TM}$: On input $\langle M, w \rangle$:
>     - Construct TM $M'$: On input $x$:
>       - If $x$ is of the form $0^n 1^n$, **Accept**.
>       - Else, simulate $M$ on $w$. If $M$ accepts, **Accept**.
>     - **Analyze $L(M')$:**
>       - If $M$ accepts $w$, $L(M') = \Sigma^*$ (which is **Regular**).
>       - If $M$ doesn't accept $w$, $L(M') = \{0^n 1^n\}$ (which is **NOT Regular**).
>     - Run $R$ on $\langle M' \rangle$. If it accepts, then $M$ accepts $w \implies$ **Accept**.
> 3.  Contradiction.

---

## 8. TM Recognizability vs Decidability
1. $A_{TM}$ is **Recognizable** (UTM can simulate and accept).
2. $\overline{A_{TM}}$ is **Not Recognizable** (If it were, $A_{TM}$ would be decidable).
3. $A, \overline{A}$ Recognizable $\implies$ Decidable (Run both in parallel; one must halt).

---

## 9. True/False with Justification

1. **True**. Regular $\subset$ CFL. Every DFA can be seen as a PDA that ignores the stack.
2. **False**. $\{a^n b^n c^m\} \cap \{a^m b^n c^n\} = \{a^n b^n c^n\}$ (not CFL).
3. **True**. By definition, a decider is a TM that halts on all inputs. Any such machine is also a recognizer.
4. **False**. Halting on empty input ($HALT_\epsilon$) is undecidable (equivalent to $A_{TM}$).
5. **False**. Inherently ambiguous languages exist (e.g., $\{a^i b^j c^k \mid i=j \lor j=k\}$).
6. **False**. NPDA are strictly more powerful than DPDA (e.g., $ww^R$ is NPDA but not DPDA).
7. **True**. TMs can count and verify $a^n b^n c^n$ using multiple tracks or marks.
8. **True**. If $B$ is decidable and $A \leq_m B$, the reduction $f$ followed by $B$'s decider decides $A$.
9. **False**. The standard CYK requires CNF to ensure exactly two children for every non-terminal node in the parse tree (binary splits).
10. **True**. A language is Turing-recognizable iff some enumerator enumerates it.

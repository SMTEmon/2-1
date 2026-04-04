***

**Tags:** #TheoryOfComputation #ExamPrep #AnswerKey #SipserExercises #CSE4309
**Linked Note:** [[Sipser Practice Set]]

---

# Sipser Practice Set: CSE 4309 Final Solutions

> [!tip] Exam Mapping
> - **Q1/Q2 Focus:** CFG construction, PDA design, CNF conversion, closure properties.
> - **Q3 Focus:** TM descriptions, configurations, Church-Turing thesis, variants.
> - **Q4 Focus:** True/False justifications, theoretical properties.

---

## 1. CFG Analysis & Language Interpretation
*Pattern: Quiz 3 Q2 / Q2.1*

### 1. (Ex 2.3) Grammar $G$ Analysis
**a. Variables and Terminals:**
- **Variables ($V$):** $\{R, S, T, X\}$
- **Terminals ($\Sigma$):** $\{a, b\}$

**b. Strings in / not in $L(G)$:**
- **In $L(G)$:** `ab`, `ba`, `aab`. (The grammar generates strings where the first half and second half differ at some mirror index; i.e., non-palindromes).
- **Not in $L(G)$:** `a`, `b`, `aba`, `$\epsilon$`. (All palindromes are excluded).

**c. True or False:**
- $T \xRightarrow{*} aba$: **True**. ($T \Rightarrow XTX \Rightarrow aTa \Rightarrow abTa \Rightarrow aba$)
- $XXX \xRightarrow{*} aba$: **True**. ($XXX \Rightarrow aXX \Rightarrow abX \Rightarrow aba$)
- $T \xRightarrow{*} XXX$: **True**. ($T \Rightarrow XTX \Rightarrow XX$)

**d. Describe $L(G)$ in English:**
$L(G)$ is the language of all strings over $\{a, b\}$ that are **not palindromes**. (The $S$ rule forces a mismatch $a \dots b$ or $b \dots a$ across the center, and $R$ wraps it in equal-length prefixes/suffixes, ensuring the string breaks palindrome symmetry).

### 2. (Ex 2.13) Grammar $G$ with $\Sigma = \{0, \#\}$
**a. Describe $L(G)$ in English:**
$L(G) = \{0^i \# 0^j \# 0^k \mid i, j, k \geq 0\} \cup \{0^n \# 0^{2n} \mid n \geq 0\}$. 
*(Explanation: $T$ generates any number of $0$s with exactly one $\#$. $TT$ generates strings with exactly two $\#$s. $U$ generates strings with exactly one $\#$ and twice as many $0$s on the right).*

**b. Prove that $L(G)$ is not regular:**
Assume $L(G)$ is regular. Let $p$ be the pumping length. Choose $s = 0^p \# 0^{2p} \in L(G)$. By the Pumping Lemma, $s = xyz$ where $|xy| \le p$ and $|y| > 0$. Thus, $y$ consists only of $0$s from the first block. 
Pumping up ($xy^2z$) yields $0^{p+|y|} \# 0^{2p}$. Since it only has one `#`, it must belong to the $U$ subset of the language. However, $2(p+|y|) \neq 2p$, so the ratio is broken. $xy^2z \notin L(G)$, a contradiction. Thus, $L(G)$ is not regular.

---

## 2. CFG Construction
*Pattern: Q2.2 / Q1.1*

### 1. (Ex 2.4) CFGs over $\Sigma = \{0, 1\}$
**a. At least three 1s:**
$S \rightarrow A 1 A 1 A 1 A$
$A \rightarrow 0A \mid 1A \mid \epsilon$

**b. Starts and ends with the same symbol:**
$S \rightarrow 0A0 \mid 1A1 \mid 0 \mid 1$
$A \rightarrow 0A \mid 1A \mid \epsilon$

**c. Length of $w$ is odd:**
$S \rightarrow X S X \mid X$
$X \rightarrow 0 \mid 1$

**d. Length of $w$ is odd and middle symbol is 0:**
$S \rightarrow 0S0 \mid 0S1 \mid 1S0 \mid 1S1 \mid 0$

**e. Palindromes ($w = w^R$):**
$S \rightarrow 0S0 \mid 1S1 \mid 0 \mid 1 \mid \epsilon$

### 2. (Ex 2.6) CFGs over $\{a, b\}$
**a. More $a$'s than $b$'s:**
$S \rightarrow T a T \mid T a S$
$T \rightarrow a T b T \mid b T a T \mid \epsilon$
*(Explanation: $T$ generates strings with equal $a$'s and $b$'s. $S$ ensures at least one extra $a$).*

**b. Complement of $\{a^n b^n \mid n \geq 0\}$:**
$S \rightarrow A \mid B \mid C$
$A \rightarrow U b U a U$ *(Out of order: $b$ before $a$)*
$B \rightarrow a B b \mid a B_1$ ($B_1 \rightarrow a B_1 \mid \epsilon$) *(More a's)*
$C \rightarrow a C b \mid C_1 b$ ($C_1 \rightarrow b C_1 \mid \epsilon$) *(More b's)*
$U \rightarrow aU \mid bU \mid \epsilon$

**c. $w \# x$ where $w^R$ is a substring of $x$:**
$S \rightarrow T X$
$T \rightarrow 0T0 \mid 1T1 \mid \# X$
$X \rightarrow 0X \mid 1X \mid \epsilon$

> [!info] Explanation
> - $X$ generates any string $\{0,1\}^*$.
> - $T$ generates $w \# u w^R$ by wrapping $\#X$ with matching terminals.
> - $S$ appends another arbitrary string $v$ via $X$.
> - Result: $w \# u w^R v$. Let $x = u w^R v$. Since $u,v \in \{0,1\}^*$, $w^R$ is a substring of $x$.

### 3. (Ex 2.9) $A = \{a^i b^j c^k \mid i = j \text{ or } j = k\}$
**CFG:**
$S \rightarrow X \mid Y$
$X \rightarrow A C$ ($A \to aAb \mid \epsilon$, $C \to cC \mid \epsilon$) *(Handles $i=j$)*
$Y \rightarrow D B$ ($D \to aD \mid \epsilon$, $B \to bBc \mid \epsilon$) *(Handles $j=k$)*
**Ambiguous?** Yes. The string $a^n b^n c^n$ (where $i=j=k$) can be derived through both the $X$ branch and the $Y$ branch, resulting in two distinct leftmost derivations / parse trees.

### 4. (Ex 2.15) CFG Star Closure Failure
**The Flawed Construction:** Add $S \rightarrow SS$ to $G$.
**Counterexample:** Let $L = \{0\}$. Original CFG $G$: $S \rightarrow 0$.
If we use the construction, $G'$ is: $S \rightarrow SS \mid 0$.
The language of $G'$ is $\{0^n \mid n \ge 1\}$. However, $L^* = \{0^n \mid n \ge 0\}$, which includes $\epsilon$. $G'$ cannot generate $\epsilon$, so $L(G') \neq L^*$.
*(Correct construction: Add a new start variable $S_0 \rightarrow S_0 S \mid \epsilon$)*.

---

## 3. PDA Construction & CFG $\leftrightarrow$ PDA
*Pattern: Q1.2 / Q1.3*

### 1. (Ex 2.5) PDAs for Section 2, Problem 1
> [!note] These are informal descriptions. Formal state diagrams require defining $Q, \Sigma, \Gamma, \delta, q_0, F$.
- **a (At least three 1s):** Don't use the stack. Read input, change state on seeing '1'. Accept when reaching state $q_3$.
- **b (Same start/end):** Read first symbol, remember it in the state (no stack needed). Transition through input. If the last symbol read matches the remembered state, accept.
- **d (Odd length, middle 0):** Push symbols to stack. Non-deterministically guess the middle. If it's a 0, read it (don't push/pop). Then, for every remaining input symbol, pop one stack symbol. Accept if stack is empty when input ends.

### 2. (Ex 2.7) PDAs for Section 2, Problem 2
- **a (More $a$'s than $b$'s):** Read input. If stack is empty or has $a$, push $a$. If stack has $b$ and read $a$, pop. Conversely for reading $b$. At the end of the string, accept if the stack contains $a$'s.
- **c ($w \# x$ where $w^R$ is substring of $x$):** Push $w$ onto stack. Read `#`. Non-deterministically guess the start of $w^R$ in $x$. Pop stack symbols matching the input. Once stack is empty, read any remaining symbols of $x$ and accept.

### 3. (Ex 2.10) PDA for $A = \{a^i b^j c^k \mid i = j \text{ or } j = k\}$
**Informal Description:**
Start by non-deterministically branching into two paths via $\epsilon$-transitions:
- **Path 1 ($i=j$):** Read $a$'s and push them. Read $b$'s and pop $a$'s. If stack is empty, read and ignore all $c$'s. Accept.
- **Path 2 ($j=k$):** Read and ignore all $a$'s. Read $b$'s and push them. Read $c$'s and pop $b$'s. Accept if stack is empty when input ends.

### 4. (Ex 2.11) CFG to PDA Conversion
Standard Sipser procedure (top-down parser):
1. Push `$` and then start variable `E` onto the stack.
2. **Loop:**
   - If top of stack is a variable ($E, T, F$), non-deterministically replace it with its reversed right-hand side.
     *(e.g., Pop $E$, Push $T, +, E$)*
   - If top of stack is a terminal ($+, \times, (, ), a$), read input. If it matches the stack, pop the stack.
   - If top of stack is `$`, accept.

---

## 4. CNF, Ambiguity & Closure Properties
*Pattern: Q2.2 / Q2.4*

### 1. (Ex 2.14) Convert to Chomsky Normal Form
**Original:** $A \rightarrow BAB \mid B \mid \epsilon$, $B \rightarrow 00 \mid \epsilon$
**Step 1 (New Start):** $S_0 \rightarrow A$
**Step 2 (Remove $\epsilon$):**
- Remove $B \to \epsilon$: $A \rightarrow BAB \mid AB \mid BA \mid A \mid \epsilon$, $B \rightarrow 00$
- Remove $A \to \epsilon$: $S_0 \rightarrow A \mid \epsilon$, $A \rightarrow BAB \mid AB \mid BA \mid BB \mid B$ (discard $A \to A$)
**Step 3 (Remove Unit Rules):**
- Remove $A \to B$: $A \rightarrow 00$
- Remove $S_0 \to A$: $S_0 \rightarrow BAB \mid AB \mid BA \mid BB \mid 00 \mid \epsilon$
**Step 4 (Format rules):**
Introduce $U_0 \rightarrow 0$.
$A \rightarrow BU_1 \mid AB \mid BA \mid BB \mid U_0 U_0$, $U_1 \rightarrow AB$
*(Apply similarly to $S_0$ and ensure exactly 2 variables per rule).*

### 2. (Ex 2.1) Parse Trees
For `a+a`:
- Leftmost Derivation: $E \Rightarrow E + T \Rightarrow T + T \Rightarrow F + T \Rightarrow a + T \Rightarrow a + F \Rightarrow a + a$
*(Parse trees visually reflect this: root $E$ splits to $E, +, T$, left $E$ goes down to $a$, right $T$ goes down to $a$.)*

### 3. (Ex 2.8) English Ambiguity
*"the girl touches the boy with the flower"*
- **Meaning 1:** The girl uses a flower as an instrument to touch the boy. (Prepositional phrase "with the flower" attaches to the verb phrase "touches").
- **Meaning 2:** The girl touches a specific boy who is holding a flower. (Prepositional phrase attaches to the noun phrase "the boy").

### 4. (Ex 2.2) Closure Properties Proof
**Intersection:**
$A = \{a^m b^n c^n\}$ (CFL: push b, pop c)
$B = \{a^n b^n c^m\}$ (CFL: push a, pop b)
$A \cap B = \{a^n b^n c^n \mid n \ge 0\}$, which is the classic non-CFL (provable via Pumping Lemma). Therefore, CFLs are **not closed under intersection**.

**Complementation:**
By DeMorgan's Law, $A \cap B = \overline{\overline{A} \cup \overline{B}}$. 
If CFLs were closed under complement, then since they are closed under union ($\cup$), the intersection $A \cap B = \overline{\overline{A} \cup \overline{B}}$ would also be a CFL. Since we know $A \cap B$ is not a CFL, the class of CFLs cannot be closed under complementation.

---

## 5. TM Constructions & Configurations
*Pattern: Q3.3 / Q3.4*

> [!check] Ex 3.8a: Equal 0s and 1s
> Sweep left-to-right. Cross off one 0 and one 1 per pass. Repeat. If all crossed off, accept. If one type remains, reject.

> [!check] Ex 3.8b: Twice as many 0s as 1s
> Per pass, cross off two 0s and one 1. Repeat. Verify all crossed.

> [!check] Ex 3.8c: NOT twice as many
> Run TM from (b). If it accepts, reject. If it rejects, accept. (Closure under complement for decidable languages).

---

## 6. TM Variants, Church-Turing & Theory
*Pattern: Q3.1 / Q3.2 / Q4*

> [!abstract] Ex 3.1/3.2: Tracing Configurations
> **Note:** Based on standard Sipser 3rd Ed. examples:
> - **$M_2$ (Ex 3.7)** decides $\{0^n 1^n \mid n \ge 0\}$.
> - **$M_1$ (Ex 3.9)** decides $\{w \# w \mid w \in \{0, 1\}^*\}$.
> 
> **Trace for $M_2$ on `00` (Rejects):**
> 1. $q_1 0 0$
> 2. $\vdash x q_2 0$ *(Mark first 0, move right)*
> 3. $\vdash x 0 q_2 \sqcup$ *(Scan past 0s, hit blank, no 1 found)*
> 4. $\vdash x q_{reject} 0 \sqcup$ *(Reject)*
> 
> **Trace for $M_2$ on `0011` (Accepts):**
> 1. $q_1 0 0 1 1$
> 2. $\vdash x q_2 0 1 1$ *(Mark 0)*
> 3. $\vdash x 0 q_2 1 1$
> 4. $\vdash x 0 x q_3 1$ *(Mark first 1)*
> 5. $\vdash x q_4 0 x 1$ *(Move left to start)*
> 6. $\vdash x 0 q_2 x 1$
> 7. $\vdash x 0 x q_3 1$ *(Mark second 1)*
> 8. $\vdash x q_{accept} 0 x 1$ *(All matched, accept)*
> 
> **Trace for $M_1$ on `1#1` (Accepts):**
> 1. $q_1 1 \# 1$
> 2. $\vdash x q_2 \# 1$ *(Mark left 1)*
> 3. $\vdash x \# q_3 1$ *(Cross #)*
> 4. $\vdash x \# x q_4$ *(Mark right 1)*
> 5. $\vdash x q_5 \# x$ *(Move left)*
> 6. $\vdash q_6 x \# x$ *(Move left to start)*
> 7. $\vdash x q_7 \# x$ *(Check left done)*
> 8. $\vdash x \# q_8 x$ *(Check right done)*
> 9. $\vdash q_{accept} x \# x$ *(Accept)*
> 
> **Trace for $M_1$ on `10#11` (Rejects):**
> 1. $q_1 1 0 \# 1 1$
> 2. $\vdash x q_2 0 \# 1 1$ *(Mark left 1)*
> 3. $\vdash x 0 q_2 \# 1 1$
> 4. $\vdash x 0 \# q_3 1 1$
> 5. $\vdash x 0 \# x q_4 1$ *(Mark right 1)*
> 6. $\vdash x 0 q_5 \# x 1$ *(Move left)*
> 7. $\vdash x q_5 0 \# x 1$
> 8. $\vdash x 0 q_2 \# x 1$ *(Try next left char)*
> 9. $\vdash x 0 \# q_3 x 1$ *(Cross #)*
> 10. $\vdash x 0 \# x q_4 1$ *(Next right is 1, but left was 0. Mismatch $\to$ Reject)*

> [!abstract] Ex 3.3: NTM $\to$ DTM Decidability
> Use BFS on computation tree. Since NTM is a decider, all branches are finite. A finite tree with finite branching has finitely many nodes. BFS visits all nodes in finite time. DTM accepts if any branch accepts, rejects if all reject.

> [!abstract] Ex 3.4: Enumerator Definition
> $E = (Q, \Sigma, \Gamma, \delta, q_0, q_{acc}, q_{rej})$ with two tapes. Tape 1: work tape. Tape 2: printer (write-only, moves right only). $L(E) = \{w \mid w \text{ is eventually printed on tape 2}\}$.

> [!abstract] Ex 3.5: Formal TM Properties
> a. **Yes**. $\sqcup \in \Gamma$, TM can write any tape symbol.
> b. **No**. $\Gamma$ must contain $\sqcup$, but $\Sigma$ cannot. So $\Gamma \supset \Sigma$.
> c. **No**. Transition function requires $L$ or $R$ move.
> d. **Yes**, but trivial. Must have at least $q_{acc}$ and $q_{rej}$, so minimum 3 states if distinct.

> [!abstract] Ex 3.6: Why simple enumeration fails
> **Fails because of looping**. If $M$ loops on $s_1$, the algorithm never reaches $s_2$. Correct algorithm uses **dovetailing** to interleave steps across all inputs.

> [!abstract] Ex 3.7: Illegitimate TM Description
> **Not legitimate** because step 1 ("Try all possible settings") is an infinite loop if no solution exists. A decider must halt on all inputs. This describes an unbounded search with no termination guarantee on negative instances.

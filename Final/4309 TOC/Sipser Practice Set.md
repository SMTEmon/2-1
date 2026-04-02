***

**Tags:** #TheoryOfComputation #ExamPrep #SipserExercises #CSE4309
**Source:** Sipser 3rd Ed. Exercises (Ch 2 & 3)
**Mapped To:** Final Exam Pattern (CFG, PDA, TM, Decidability)

---

# Sipser Practice Set: CSE 4309 Final

> [!tip] Exam Mapping
> - **Q1/Q2 Focus:** CFG construction, PDA design, CNF conversion, closure properties.
> - **Q3 Focus:** TM descriptions, configurations, Church-Turing thesis, variants.
> - **Q4 Focus:** True/False justifications, theoretical properties.

---

## 1. CFG Analysis & Language Interpretation
*Pattern: Quiz 3 Q2 / Q2.1*

1. **(Ex 2.3)** Consider grammar $G$:
   - $R \rightarrow XRX \mid S$
   - $S \rightarrow aTb \mid bTa$
   - $T \rightarrow XTX \mid X \mid \epsilon$
   - $X \rightarrow a \mid b$
   
   a. What are the variables and terminals?
   b. Give three strings in $L(G)$ and three not in $L(G)$.
   c. True or False: $T \xRightarrow{*} aba$? $XXX \xRightarrow{*} aba$? $T \xRightarrow{*} XXX$?
   d. Describe $L(G)$ in English.

2. **(Ex 2.13)** Let $G = (V, \Sigma, R, S)$ where $V = \{S, T, U\}$, $\Sigma = \{0, \#\}$, and:
   - $S \rightarrow TT \mid U$
   - $T \rightarrow 0T \mid T0 \mid \#$
   - $U \rightarrow 0U00 \mid \#$
   
   a. Describe $L(G)$ in English.
   b. Prove that $L(G)$ is not regular.

---

## 2. CFG Construction
*Pattern: Q2.2 / Q1.1*

1. **(Ex 2.4)** Give CFGs over $\Sigma = \{0, 1\}$ for:
   a. $\{w \mid w \text{ contains at least three 1s}\}$
   b. $\{w \mid w \text{ starts and ends with the same symbol}\}$
   c. $\{w \mid \text{length of } w \text{ is odd}\}$
   d. $\{w \mid \text{length of } w \text{ is odd and middle symbol is 0}\}$
   e. $\{w \mid w = w^R\}$ (Palindromes)

2. **(Ex 2.6)** Give CFGs for:
   a. Strings over $\{a, b\}$ with more $a$'s than $b$'s.
   b. The complement of $\{a^n b^n \mid n \geq 0\}$.
   c. $\{w \# x \mid w^R \text{ is a substring of } x \text{ for } w, x \in \{0, 1\}^*\}$.

3. **(Ex 2.9)** Give a CFG for $A = \{a^i b^j c^k \mid i = j \text{ or } j = k, i, j, k \geq 0\}$.
   - Is your grammar ambiguous? Why or why not?

4. **(Ex 2.15)** Show that the following construction **fails** to prove CFLs are closed under star:
   - Given $G$ for $A$, add rule $S \rightarrow SS$ to get $G'$.
   - Provide a counterexample where $L(G') \neq A^*$.

---

## 3. PDA Construction & CFG $\leftrightarrow$ PDA
*Pattern: Q1.2 / Q1.3*

1. **(Ex 2.5)** Give informal descriptions and state diagrams of PDAs for the languages in **Section 2, Problem 1** above.

2. **(Ex 2.7)** Give informal English descriptions of PDAs for the languages in **Section 2, Problem 2** above.

3. **(Ex 2.10)** Give an informal description of a PDA that recognizes $A = \{a^i b^j c^k \mid i = j \text{ or } j = k\}$.

4. **(Ex 2.11)** Convert the following CFG to an equivalent PDA using the standard procedure:
   - $E \rightarrow E + T \mid T$
   - $T \rightarrow T \times F \mid F$
   - $F \rightarrow (E) \mid a$

---

## 4. CNF, Ambiguity & Closure Properties
*Pattern: Q2.2 / Q2.4*

1. **(Ex 2.14)** Convert to Chomsky Normal Form:
   - $A \rightarrow BAB \mid B \mid \epsilon$
   - $B \rightarrow 00 \mid \epsilon$

2. **(Ex 2.1)** For grammar $G_4$:
   - $E \rightarrow E + T \mid T$
   - $T \rightarrow T \times F \mid F$
   - $F \rightarrow (E) \mid a$
   
   Give parse trees and leftmost derivations for: `a`, `a+a`, `a+a+a`, `((a))`.

3. **(Ex 2.8)** Show that the string *"the girl touches the boy with the flower"* has two different leftmost derivations in a standard ambiguous grammar. Describe the two meanings.

4. **(Ex 2.2)** Use $A = \{a^m b^n c^n\}$ and $B = \{a^n b^n c^m\}$ to show CFLs are **not closed under intersection**.
   - Use DeMorgan's law to show CFLs are **not closed under complementation**.

5. **(Ex 2.16)** Prove that CFLs are closed under union, concatenation, and star.

---

## 5. TM Constructions & Configurations
*Pattern: Q3.3 / Q3.4*

1. **(Ex 3.8)** Give implementation-level descriptions of TMs that decide:
   a. $\{w \mid w \text{ contains equal number of 0s and 1s}\}$
   b. $\{w \mid w \text{ contains twice as many 0s as 1s}\}$
   c. $\{w \mid w \text{ does NOT contain twice as many 0s as 1s}\}$

2. **(Ex 3.1/3.2)** For a given TM $M$ and input strings (e.g., `0`, `00`, `11`, `1#1`), trace the sequence of configurations step-by-step until halting.

---

## 6. TM Variants, Church-Turing & Theory
*Pattern: Q3.1 / Q3.2 / Q4*

1. **(Ex 3.3)** Modify the NTM $\to$ DTM simulation proof to show: A language is **decidable** iff some NTM decides it. (Hint: Use the tree property: finite branches + finite nodes = finite tree).

2. **(Ex 3.4)** Give a formal definition of an **Enumerator** (as a 2-tape TM). Define the enumerated language.

3. **(Ex 3.5)** Answer based on the formal TM definition:
   a. Can a TM write the blank symbol $\sqcup$?
   b. Can $\Gamma = \Sigma$?
   c. Can the head stay in the same location in two successive steps?
   d. Can a TM have just one state?

4. **(Ex 3.6)** In the proof that T-recognizable $\iff$ enumerable, why does this simpler algorithm fail?
   > $E =$ "Ignore input. For $i = 1, 2, \dots$: Run $M$ on $s_i$. If accepts, print $s_i$."

5. **(Ex 3.7)** Explain why this is **not** a legitimate TM description:
   > $M_{bad} =$ "On input $\langle p \rangle$ (polynomial): Try all integer settings of $x_1, \dots, x_k$. Evaluate $p$. If any equals 0, accept; else reject."

***

**Tags:** #TheoryOfComputation #ExamPrep #PracticeSet #CSE4309
**Syllabus:** CFG, PDA, TM, Decidability, Undecidability
**Source:** Generated from Instructor Guidelines & Lecture Notes

---

# Comprehensive Practice Set: CSE 4309 Final

> [!tip] How to Use This Set
> - **Section 1-2:** Focus on **PDA construction** and **CFG interpretation**. These are high-yield for Q1 and Q2.
> - **Section 3-4:** Drill **CNF conversion** and **CYK algorithm**. The CYK table is worth ~15 marks alone.
> - **Section 7-8:** Memorize the **diagonalization proofs** and **reduction templates**.
> - **Section 9:** Practice **True/False justifications**. Read the instructor's warning: "Deceptively stated."

---

## 1. CFG Language Interpretation
*Pattern: Quiz 3, Question 2. Describe the language in English/Set notation. Give 2 example strings.*

1.  $G_1$: $S \rightarrow 0S1 \mid 1S0 \mid \epsilon$
2.  $G_2$: $S \rightarrow aSb \mid A \mid B$, $A \rightarrow aA \mid \epsilon$, $B \rightarrow bB \mid \epsilon$
3.  $G_3$: $S \rightarrow aSa \mid bSb \mid a \mid b \mid \epsilon$
4.  $G_4$: $S \rightarrow SS \mid aSb \mid bSa \mid \epsilon$
5.  $G_5$: $S \rightarrow aB \mid bA$, $A \rightarrow a \mid aS \mid bAA$, $B \rightarrow b \mid bS \mid aBB$ *(Hint: Compare count of a's vs b's)*

---

## 2. PDA Construction
*Pattern: Q1 (30 marks). Design PDAs (state diagrams or formal 6-tuple).*

1.  **Easy:** $L = \{0^n 1^n \mid n \geq 0\}$
2.  **Medium:** $L = \{w \in \{0,1\}^* \mid w \text{ has more 0s than 1s}\}$
3.  **Hard:** $L = \{a^i b^j c^k \mid i = j \text{ or } j = k, \text{ but not both}\}$
4.  **Classic:** $L = \{ww^R \mid w \in \{0,1\}^*\}$ (Even length palindromes)
5.  **Conversion:** Convert the CFG $S \rightarrow aSb \mid \epsilon$ to an equivalent PDA using the top-down derivation method.

---

## 3. TM Construction & Decidability Proofs
*Pattern: Q1 & Q3. Give high-level TM descriptions. Assume standard encodings $\langle \cdot \rangle$.*

1.  Prove $A_{DFA}$ is decidable.
2.  Prove $E_{DFA}$ is decidable.
3.  Prove $EQ_{DFA}$ is decidable.
4.  Prove $A_{CFG}$ is decidable.
5.  Design a TM that decides $L = \{ \langle G \rangle \mid G \text{ is a CFG that generates at least one string} \}$.
6.  Design a TM that decides $L = \{ \langle M \rangle \mid M \text{ is a TM that accepts exactly 2 strings} \}$. *(Critical Thinking: Is this actually decidable?)*

---

## 4. CNF Conversion & CYK Algorithm
*Pattern: Q2 (41 marks). Show steps clearly. Draw full tables.*

1.  **Convert to CNF:**
    - $S \rightarrow ASA \mid aB$
    - $A \rightarrow B \mid S$
    - $B \rightarrow b \mid \epsilon$
2.  **Convert to CNF:** $S \rightarrow aSb \mid SS \mid \epsilon$
3.  **CYK Practice:**
    Given CNF: $S \rightarrow AB \mid BC$, $A \rightarrow BA \mid a$, $B \rightarrow CC \mid b$, $C \rightarrow AB \mid a$.
    Run CYK on string $w = \texttt{baaba}$. Show the full table.
4.  **CYK Practice:**
    Run CYK on $w = \texttt{abab}$ for grammar: $S \rightarrow AB \mid BC$, $A \rightarrow a$, $B \rightarrow b \mid AB$, $C \rightarrow a$.

---

## 5. Pumping Lemma for CFLs
*Pattern: Q2. Prove the following are NOT context-free.*

1.  $L = \{a^n b^n c^n \mid n \geq 0\}$
2.  $L = \{a^n b^m c^n d^m \mid n, m \geq 0\}$
3.  $L = \{ww \mid w \in \{0,1\}^*\}$ (The "Copy" language)
4.  $L = \{a^{n^2} \mid n \geq 0\}$
5.  $L = \{a^i b^j c^k \mid i < j < k\}$

---

## 6. TM Variants, Church-Turing & Encodings
*Pattern: Q3. Theory and conceptual understanding.*

1.  Explain how a 2-tape TM can be simulated by a standard 1-tape TM. What is the time complexity overhead?
2.  Why does an NTM simulation require **BFS** instead of **DFS**?
3.  Describe how you would encode a directed graph $G$ as a string $\langle G \rangle$ for TM input.
4.  State the **Church-Turing Thesis**. Give 2 examples of "high-level" operations you can safely assume a TM can perform.
5.  What is a **Turing Enumerator**? Prove that a language is T-recognizable iff some enumerator enumerates it.

---

## 7. Undecidability Proofs
*Pattern: Q3. Memorize the logic flow.*

1.  Prove $A_{TM}$ is undecidable using **diagonalization**.
2.  Prove $HALT_{TM}$ is undecidable using **diagonalization**.
3.  Prove $HALT_{TM}$ is undecidable by **reduction from $A_{TM}$**.
4.  Prove $E_{TM} = \{\langle M \rangle \mid L(M) = \emptyset\}$ is undecidable via reduction from $A_{TM}$.
5.  Prove $REGULAR_{TM} = \{\langle M \rangle \mid L(M) \text{ is regular}\}$ is undecidable.

---

## 8. TM Recognizability vs Decidability
*Pattern: Q3 & Q4. Distinguish between halting and looping.*

1.  Prove $A_{TM}$ is Turing-recognizable.
2.  Prove $\overline{A_{TM}}$ is **NOT** Turing-recognizable.
3.  Theorem: If language $A$ and $\overline{A}$ are both Turing-recognizable, prove $A$ is decidable.
4.  Is $HALT_{TM}$ Turing-recognizable? Prove your answer.

---

## 9. True/False with Justification
*Pattern: Q4 (17 marks). Concise 1-2 sentence justifications.*

1.  Every regular language is context-free.
2.  The class of context-free languages is closed under intersection.
3.  If a language is decidable, it must be Turing-recognizable.
4.  There exists a Turing machine that can decide whether any given TM halts on empty input.
5.  All ambiguous CFGs can be converted to unambiguous CFGs.
6.  A deterministic PDA has the same computational power as a nondeterministic PDA.
7.  The language $\{a^n b^n c^n \mid n \geq 0\}$ is Turing-decidable.
8.  If $A \leq_m B$ and $B$ is decidable, then $A$ is decidable.
9.  The CYK algorithm works on any CFG, not just CNF.
10. A language is Turing-recognizable if and only if some enumerator enumerates it.

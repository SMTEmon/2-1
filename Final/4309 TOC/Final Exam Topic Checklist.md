***

**Tags:** #TheoryOfComputation #ExamPrep #Checklist #CSE4309
**Type:** Topic-Based Progress Tracker

---

# Final Exam Topic Checklist: CSE 4309

> [!tip] How to Use
> - Check off each **Problem Type** once you can solve it confidently without looking at notes.
> - This covers **every type of question** that can appear based on your syllabus and exam pointers.

---

## 1. Context-Free Grammars (CFG)

### 1.1 Language Interpretation
- [ ] Given a CFG, describe $L(G)$ in English or Set Notation.
- [ ] Given a CFG, provide 2 example strings that belong to $L(G)$.
- [ ] Given a CFG, provide 2 example strings that do **not** belong to $L(G)$.
- [ ] Identify if a grammar generates Palindromes, Equal Counts, or $\Sigma^*$.

### 1.2 CFG Construction
- [ ] Design CFG for **Matching/Counting** ($a^n b^n$, $a^n b^{2n}$).
- [ ] Design CFG for **Palindromes** ($w = w^R$).
- [ ] Design CFG for **Regular + Context-Free mix** (e.g., odd length with middle 0).
- [ ] Design CFG for **Union/Concatenation** of known CFLs.
- [ ] Design CFG for **Complement** of simple CFLs (e.g., complement of $a^n b^n$).
- [ ] Design CFG for **Substring conditions** (e.g., $w^R$ is substring of $x$).

### 1.3 Ambiguity
- [ ] Prove a grammar is ambiguous by giving **two distinct parse trees** for the same string.
- [ ] Explain why a specific string has two leftmost derivations.
- [ ] Identify inherently ambiguous languages (e.g., $\{a^n b^n c^m\} \cup \{a^n b^m c^m\}$).

### 1.4 Chomsky Normal Form (CNF)
- [ ] Convert any CFG to CNF using the **4-step procedure**:
  1. New Start Symbol
  2. Remove $\epsilon$-rules
  3. Remove Unit rules
  4. Binarize & Replace Terminals

### 1.5 Closure Properties
- [ ] Prove CFLs are **closed** under Union, Concatenation, and Star.
- [ ] Prove CFLs are **NOT closed** under Intersection (using $a^n b^n c^n$).
- [ ] Prove CFLs are **NOT closed** under Complementation (using DeMorgan's Law).
- [ ] Explain why adding $S \to SS$ fails to prove Star closure.

---

## 2. Pushdown Automata (PDA)

### 2.1 PDA Construction
- [ ] Design PDA for **Simple Counting** ($0^n 1^n$).
- [ ] Design PDA for **Multiple Conditions** ($i=j$ or $j=k$).
- [ ] Design PDA for **Palindromes** ($ww^R$) using Nondeterminism.
- [ ] Design PDA for **Comparisons** (More $a$'s than $b$'s).
- [ ] Design PDA that uses the stack as a **Counter** (Push/Pop logic).

### 2.2 CFG $\leftrightarrow$ PDA Equivalence
- [ ] Convert a CFG to an equivalent PDA using the **Top-Down Parser** method.
- [ ] Explain the 3-state standard construction (Push $S$, Replace vars, Match terminals).
- [ ] Explain why NPDA is strictly more powerful than DPDA (give example language).

---

## 3. Turing Machines (TM)

### 3.1 TM Construction
- [ ] Write **High-Level Description** of a TM for a given language.
- [ ] Design TM for **Matching/Crossing off** symbols (e.g., equal 0s and 1s).
- [ ] Design TM that **Simulates** another machine (DFA, PDA, or CFG decider).
- [ ] Design TM for **Decidability Proofs** ($A_{DFA}$, $E_{DFA}$, $EQ_{DFA}$, $A_{CFG}$).

### 3.2 Configurations & Tracing
- [ ] Trace step-by-step configurations ($uqv$) for a given TM and input string.
- [ ] Identify when a TM enters Accept, Reject, or Loop state from a trace.

### 3.3 TM Variants & Theory
- [ ] Explain how **Multi-Tape TM** simulates standard TM (complexity overhead).
- [ ] Explain how **NTM** simulates standard TM (Why BFS is required over DFS).
- [ ] Define **Turing Enumerator** and prove equivalence to Recognizability.
- [ ] State **Church-Turing Thesis** and justify high-level TM descriptions.
- [ ] Describe how to **encode objects** (graphs, automata) as strings $\langle O \rangle$.

---

## 4. Decidability & Undecidability

### 4.1 Decidability Proofs
- [ ] Prove $A_{DFA}$ is decidable (Simulation).
- [ ] Prove $E_{DFA}$ is decidable (Graph Reachability).
- [ ] Prove $EQ_{DFA}$ is decidable (Symmetric Difference + Emptiness).
- [ ] Prove $A_{CFG}$ is decidable (CNF + Finite Derivations).

### 4.2 Recognizability vs Decidability
- [ ] Prove $A_{TM}$ is **Turing-Recognizable** (Universal TM construction).
- [ ] Prove $\overline{A_{TM}}$ is **NOT** Turing-Recognizable.
- [ ] Prove Theorem: If $A$ and $\overline{A}$ are recognizable $\implies$ $A$ is decidable.
- [ ] Determine if a language is Decidable, Recognizable-only, or Unrecognizable.

### 4.3 Undecidability Proofs
- [ ] Prove $A_{TM}$ is **Undecidable** using **Diagonalization** (Paradox machine $D$).
- [ ] Prove $HALT_{TM}$ is **Undecidable** using **Diagonalization**.
- [ ] Prove $HALT_{TM}$ is **Undecidable** via **Reduction** from $A_{TM}$.
- [ ] Prove $E_{TM}$ is **Undecidable** via Reduction from $A_{TM}$.
- [ ] Prove $REGULAR_{TM}$ is **Undecidable** via Reduction from $A_{TM}$.

---

## 5. Algorithms & Lemmas

### 5.1 CYK Algorithm
- [ ] Run CYK algorithm on string $w$ given a CNF grammar.
- [ ] Fill the triangular parsing table correctly (Base case + Recursive splits).
- [ ] Determine if $w \in L(G)$ by checking if Start Variable is in $T[1, n]$.

### 5.2 Pumping Lemma for CFLs
- [ ] Prove a language is **NOT Context-Free** using Pumping Lemma.
- [ ] Correctly choose pumping string $s$ (length $\ge p$).
- [ ] Analyze cases for $vxy$ (spans 1 block, 2 blocks, etc.).
- [ ] Show contradiction by pumping $uv^2xy^2z$ or $uxz$.

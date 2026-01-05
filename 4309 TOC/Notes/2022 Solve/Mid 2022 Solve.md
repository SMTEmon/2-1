[[1.b)]]

# 1. a)differences-dfa-nfa-transition-functions

## 1. Differences between DFA and NFA

| Feature | Deterministic Finite Automaton (DFA) | Nondeterministic Finite Automaton (NFA) |
| :--- | :--- | :--- |
| **Determinism** | For every state and input symbol, there is exactly **one** distinct next state. | For a state and input symbol, there can be **zero, one, or multiple** next states. |
| **Empty Transitions** | $\epsilon$-moves (transitions without input) are **not allowed**. | $\epsilon$-moves are allowed (specifically in $\epsilon$-NFA). |
| **Backtracking** | No backtracking is required. It follows a single path. | Requires backtracking or parallel processing to check all possible paths. |
| **Implementation** | Easier to implement in code (simple state machine), but harder to design the diagram for complex languages. | Easier to design conceptually (allows guessing), but harder to implement in code. |
| **State Count** | Generally requires more states than an equivalent NFA. | Can be much more concise; often has fewer states than the equivalent DFA. |
| **Transition Function** | Returns a single state ($Q$). | Returns a set of states ($2^Q$ or $\mathcal{P}(Q)$). |

---

## 2. Explanation of the Transition Function ($\delta$)

The transition function, denoted by $\delta$ (delta), dictates how the automaton moves from one state to another based on the input.

Let:
* $Q$ be the set of states.
* $\Sigma$ be the alphabet (set of input symbols).
* $2^Q$ (or $\mathcal{P}(Q)$) be the **Power Set** of $Q$ (the set of all possible subsets of states).

### a) $\delta$ for DFA
In a DFA, for a specific state and a specific input symbol, the machine **must** transition to exactly one valid state.
$$\delta: Q \times \Sigma \to Q$$
* **Input:** One current state ($q \in Q$) and one input symbol ($a \in \Sigma$).
* **Output:** Exactly one next state.

### b) $\delta$ for NFA (Standard NFA without $\epsilon$)
In an NFA, for a specific state and input symbol, the machine can move to **multiple** states, or **no** state (empty set).
$$\delta: Q \times \Sigma \to 2^Q$$
* **Input:** One current state and one input symbol.
* **Output:** A subset of states (can be $\emptyset$, $\{q_1\}$, or $\{q_1, q_2, \dots\}$).

### c) $\delta$ for $\epsilon$-NFA
An $\epsilon$-NFA allows transitions on input symbols **OR** on the empty string ($\epsilon$).
$$\delta: Q \times (\Sigma \cup \{\epsilon\}) \to 2^Q$$
* **Input:** One current state and either an input symbol ($a \in \Sigma$) OR the empty string ($\epsilon$).
* **Output:** A subset of states.

# automata-solutions-b-c-d

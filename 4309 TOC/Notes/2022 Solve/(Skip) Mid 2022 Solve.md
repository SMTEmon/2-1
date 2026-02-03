
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



## b) DFA for $L = \{ a^2 b w a^2 \mid w \in \{a, b\}^* \}$

**Analysis:**
The language consists of strings that must start with the prefix **$aab$** ($a^2b$) and must end with the suffix **$aa$** ($a^2$). The middle part $w$ can be any sequence of $a$'s and $b$'s.

**DFA Design:**
1.  **Prefix Check:** We first verify the string starts with `a`, `a`, `b`. If this sequence is broken, we go to a **Dead State**.
2.  **Suffix Tracking:** Once the prefix is satisfied (reaching state $q_3$), we essentially run a pattern matcher for "ends with $aa$".

**Transitions:**
* $q_0 \xrightarrow{a} q_1 \xrightarrow{a} q_2 \xrightarrow{b} q_3$ (Matches Prefix)
* From $q_3$ (Prefix Matched):
    * If we see `b`, we have made no progress towards the suffix `aa`. Stay in $q_3$.
    * If we see `a`, we have the first char of the suffix. Move to $q_4$.
    * From $q_4$: if `a`, we have `aa` (Accept state $q_5$). If `b`, sequence breaks, back to $q_3$.
    * From $q_5$ (Accept): if `a`, we still end in `aa` (stay in $q_5$). If `b`, sequence breaks, back to $q_3$.

```mermaid
graph LR
    %% States
    q0((q0))
    q1((q1))
    q2((q2))
    q3((q3))
    q4((q4))
    q5(((q5)))
    dead((Dead))

    %% Start
    style q0 fill:#f9f,stroke:#333,stroke-width:2px
    style q5 fill:#9f9,stroke:#333,stroke-width:4px
    style dead fill:#ccc,stroke:#333,stroke-width:2px

    %% Prefix Transitions
    q0 -- a --> q1
    q1 -- a --> q2
    q2 -- b --> q3

    %% Dead State Transitions (Prefix Failures)
    q0 -- b --> dead
    q1 -- b --> dead
    q2 -- a --> dead
    dead -- a,b --> dead

    %% Suffix Tracking (Loop)
    q3 -- b --> q3
    q3 -- a --> q4
    q4 -- b --> q3
    q4 -- a --> q5
    q5 -- b --> q3
    q5 -- a --> q5
```


### 1.c) 
```mermaid
stateDiagram-v2
    direction LR
    
    [*] --> CLOSED

    CLOSED --> OPEN: FRONT or BOTH
    CLOSED --> CLOSED: REAR or NEITHER

    OPEN --> OPEN: FRONT or REAR or BOTH
    OPEN --> CLOSED: NEITHER
```

### 1.d)
```mermaid
stateDiagram-v2
    direction LR

    [*] --> Wander

    state "Random Wander" as Wander
    state "Chase Pac-Man" as Chase
    state "Flee (Blue)" as Flee
    state "Return to Base" as Return

    Wander --> Chase: Line of Sight
    Chase --> Wander: Lost Sight

    Wander --> Flee: Power Pellet
    Chase --> Flee: Power Pellet

    Flee --> Return: Ghost Eaten
    Flee --> Wander: Timer Expires

    Return --> Wander: Regenerate
```

### 2a) Applications of Regular Expressions and Finite Automata

1. **Lexical Analysis (Compilers):** Breaking source code (strings) into tokens (keywords, identifiers, literals) using regex.
2. **Text Editors & Search:** Find and replace features (e.g., `grep`) use regex for pattern matching.
3. **Protocol Verification:** Modeling communication protocols (like TCP) to ensure they don't enter invalid states.
4. **Natural Language Processing (NLP):** Simple parsing and morphological analysis.
5. **Hardware Design:** Designing sequential logic circuits and controllers (like the door example above).

### 2b) Password Policy Automata

**Policy:**

1. Start with a symbol ($S = \{!, \#, \$, @, \dots\}$).
2. Contain at least one Uppercase ($U$) **OR** one Digit ($D$).
3. Can contain Lowercase ($L$).
**Alphabet:** $\Sigma = S \cup U \cup D \cup L$

Regular Expression:

$$ S (S \cup L \cup U \cup D)^* (U \cup D) (S \cup L \cup U \cup D)^* $$

(Breakdown: Starts with S, then any characters, then eventually a U or D, then any characters.)

**NFA Design:**
- **q0:** Start state.    
- **q1:** State after seeing the required initial Symbol.
- **q2:** Accepting state (reached after seeing a U or D).

```mermaid
graph LR
    q0((q0)) -- S --> q1((q1))
    
    q1 -- "S, L" --> q1
    q1 -- "U, D" --> q2(((q2)))
    
    q2 -- "S, L, U, D" --> q2
```

### 2c) NFA for Concatenation ($A \circ B$)

**Given:**

- $N_1$ accepts Language $A$ (Final states $F_1$).
- $N_2$ accepts Language $B$ (Start state $q_{start2}$).

**Construction of $N$ for $A \circ B$:**

1. Take the diagram of $N_1$ and $N_2$.    
2. Add **$\epsilon$-transitions** from every Final State in $F_1$ to the Start State of $N_2$.    
3. Mark the original states in $F_1$ as **non-final**.    
4. The new start state is the start state of $N_1$.    
5. The new final states are the final states of $N_2$.    

**Diagram:**

```mermaid
graph LR
    subgraph N1 [NFA for A]
    start1((Start N1)) -.-> end1((End N1))
    end
    
    subgraph N2 [NFA for B]
    start2((Start N2)) -.-> end2(((End N2)))
    end
    
    end1 -- ε --> start2
```

### 2d) Convert Regex to NFA

#### i. $(((00)^*(11)) \cup 01)^*$

**Logic:** A loop that can take two paths:

1. Path A: Any number of `00`s followed by `11`.
2. Path B: The sequence `01`.


```mermaid
graph LR
    start((Start)) --> q0((q0))
    q0 -- ε --> accept(((Accept)))
    accept -- ε --> q0

    %% Path 1: (00)*(11)
    q0 -- ε --> p1_start
    p1_start -- 0 --> p1_a -- 0 --> p1_start
    p1_start -- 1 --> p1_b -- 1 --> p1_end
    p1_end -- ε --> q0

    %% Path 2: 01
    q0 -- ε --> p2_start
    p2_start -- 0 --> p2_mid -- 1 --> p2_end
    p2_end -- ε --> q0
```


#### ii. $(0 \cup 10)^* 010 (0 \cup 1)^*$

**Logic:**
1. **Prefix:** Loop of `0` or `10`.
2. **Core:** Sequence `010`.
3. **Suffix:** Loop of `0` or `1` (anything).
    

```mermaid
graph LR
    q0((q0)) -- 0 --> q0
    q0 -- 1 --> q0_1 -- 0 --> q0
    
    %% Transition to Core
    q0 -- 0 --> q1
    q1 -- 1 --> q2
    q2 -- 0 --> q3(((q3)))
    
    %% Suffix Loop
    q3 -- 0,1 --> q3
```


## Question 3

### 3a) Pumping Lemma Proof

Problem: Show $L = \{ww \mid w \in \{0, 1\}^*\}$ is not regular.
Proof:

1. Assume $L$ is regular. Let $p$ be the pumping length.    
2. Choose string $s = 0^p 1 0^p 1$. Clearly $s \in L$ (where $w = 0^p 1$) and $|s| \ge p$.    
3. According to Pumping Lemma, $s$ can be split into $xyz$ such that:
    
    - $|xy| \le p$        
    - $|y| > 0$        
    - $xy^iz \in L$ for all $i \ge 0$.
        
4. Since $|xy| \le p$, $xy$ lies entirely in the first block of $0$s. Therefore, $y$ consists only of $0$s ($y = 0^k, k > 0$).    
5. Pump $y$ ($i=2$): The string becomes $0^{p+k} 1 0^p 1$.    
6. This new string is not of the form $ww$ because the first half starts with $0^{p+k}$ while the second half (after the midpoint) cannot match this pattern due to the position of the $1$s shifting.
7. Contradiction implies $L$ is not regular.


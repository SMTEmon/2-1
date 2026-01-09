# Comprehensive Pseudo Code Collection

## 1. Linked List Operations

### A. Singly Linked List Traversal
```text
Step 1: SET PTR = START
Step 2: Repeat Steps 3 and 4 while PTR != NULL
Step 3:     Apply Process to PTR -> DATA
Step 4:     SET PTR = PTR -> NEXT
        [END OF LOOP]
Step 5: EXIT
```

### B. Singly Linked List Search
```text
Step 1: SET PTR = START
Step 2: Repeat Steps 3 and 4 while PTR != NULL
Step 3:     IF VAL == PTR -> DATA
                SET POS = PTR
                Go To Step 5
            ELSE
                SET PTR = PTR -> NEXT
            [END OF IF]
        [END OF LOOP]
Step 5: EXIT
```

### C. Singly Linked List Insertion (At End)
```text
Step 1: Initialize NEW_NODE
Step 2: SET NEW_NODE -> NEXT = NULL
Step 3: SET PTR = START
Step 4: Loop while PTR -> NEXT != NULL:
            SET PTR = PTR -> NEXT
Step 5: SET PTR -> NEXT = NEW_NODE
```

### D. Singly Linked List Deletion (Node After `PREPTR`)
```text
FUNCTION DeleteNodeAfter(PREPTR)
    IF PREPTR == NULL OR PREPTR->NEXT == NULL
        RETURN "Error: Nothing to delete"
    
    SET TEMP = PREPTR->NEXT       // The node to be deleted
    SET PREPTR->NEXT = TEMP->NEXT // Bypass TEMP
    FREE TEMP                     // Release memory
END FUNCTION
```

### E. Doubly Linked List Deletion (Node `X`)
```text
Delete(X)
    IF X->NEXT != NULL
        X->NEXT->PREV = X->PREV
    IF X->PREV != NULL
        X->PREV->NEXT = X->NEXT
    FREE X
```

---

## 2. Stack Operations

### A. Push (Array Implementation)
```text
IF TOP == MAX_SIZE - 1
    Print "OVERFLOW"
ELSE
    TOP = TOP + 1
    STACK[TOP] = item
```

### B. Pop (Array Implementation)
```text
IF TOP == -1
    Print "UNDERFLOW"
ELSE
    DATA = STACK[TOP]
    TOP = TOP - 1
    Return DATA
```

### C. Infix to Postfix Conversion
```text
1. Push '(' onto Stack, and add ')' to end of Infix expression.
2. Scan expression from left to right:
    If char is '(': Push to Stack.
    If char is Operand: Add to Postfix string.
    If char is Operator:
        Pop from Stack while Precedence(Top) >= Precedence(Char)
        Push Char to Stack.
    If char is ')': Pop and output until '(' is found.
```

---

## 3. Queue Operations

### A. Circular Queue Enqueue
```text
FUNCTION Enqueue(QUEUE, FRONT, REAR, SIZE, VAL)
    IF (REAR + 1) % SIZE == FRONT
        PRINT "Overflow"
        RETURN
    
    IF FRONT == -1
        SET FRONT = 0
        SET REAR = 0
    ELSE
        SET REAR = (REAR + 1) % SIZE  // Wrap around
        
    SET QUEUE[REAR] = VAL
END FUNCTION
```

---

## 4. Tree Operations

### A. BST Search (Recursive)
```text
FUNCTION Search(NODE, KEY)
    IF NODE == NULL OR NODE->DATA == KEY
        RETURN NODE
    
    IF KEY < NODE->DATA
        RETURN Search(NODE->LEFT, KEY)
    ELSE
        RETURN Search(NODE->RIGHT, KEY)
END FUNCTION
```

### B. Tree Traversals (Recursive)
```text
PRE-ORDER(NODE):
    If NODE == NULL Return
    Visit NODE
    PRE-ORDER(NODE->LEFT)
    PRE-ORDER(NODE->RIGHT)

IN-ORDER(NODE):
    If NODE == NULL Return
    IN-ORDER(NODE->LEFT)
    Visit NODE
    IN-ORDER(NODE->RIGHT)

POST-ORDER(NODE):
    If NODE == NULL Return
    POST-ORDER(NODE->LEFT)
    POST-ORDER(NODE->RIGHT)
    Visit NODE
```

---

## 5. Graph Algorithms

### A. Breadth-First Search (BFS)
```text
BFS(Graph, StartNode)
    Initialize Queue Q
    Initialize Visited Array to False
    
    Enqueue StartNode to Q
    Mark StartNode as Visited
    
    WHILE Q is not Empty
        U = Dequeue Q
        Print U
        
        FOR each neighbor V of U
            IF V is not Visited
                Mark V as Visited
                Enqueue V to Q
```

### B. Depth-First Search (DFS - Recursive)
```text
DFS(Graph, Node, Visited)
    Mark Node as Visited
    Print Node
    
    FOR each neighbor V of Node
        IF V is not Visited
            DFS(Graph, V, Visited)
```

### C. Topological Sort (Kahn's Algorithm)
```text
TopologicalSort(Graph)
    Calculate In-Degree for all nodes
    Enqueue all nodes with In-Degree == 0 to Queue Q
    
    WHILE Q is not Empty
        U = Dequeue Q
        Add U to SortedList
        
        FOR each neighbor V of U
            Decrement In-Degree of V
            IF In-Degree of V == 0
                Enqueue V to Q
```

### D. Topological Sort (DFS Based)
```text
DFS_Topo(U, Visited, Stack)
    Mark U as Visited
    FOR each neighbor V of U
        IF V is not Visited
            DFS_Topo(V, Visited, Stack)
    Push U to Stack

Main:
    FOR each node U
        IF not Visited
            DFS_Topo(U)
    Print Stack (Top to Bottom)
```

### E. Finding Articulation Points (DFS)
```text
DFS_AP(u, p = -1):
    visited[u] = true
    d[u] = low[u] = ++timer
    children = 0
    
    For each neighbor v of u:
        If v == p: Continue
        If v is visited:
            low[u] = min(low[u], d[v]) (Back Edge)
        Else:
            DFS_AP(v, u)
            low[u] = min(low[u], low[v])
            If low[v] >= d[u] AND p != -1:
                is_cutpoint[u] = true
            children++
            
    If p == -1 AND children > 1:
        is_cutpoint[u] = true
```

### F. Finding Bridges (DFS)
```text
DFS_Bridge(u, p = -1):
    visited[u] = true
    d[u] = low[u] = ++timer

    For each neighbor v of u:
        If v == p: Continue
        If v is visited:
            low[u] = min(low[u], d[v])
        Else:
            DFS_Bridge(v, u)
            low[u] = min(low[u], low[v])
            If low[v] > d[u]:
                Print "Bridge found: u - v"
```

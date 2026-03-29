 Lecture Notes: Normalization & Indexing
*Condensed from 200+ pages into essential concepts*

---

## 📋 PART 1: DATABASE DESIGN & NORMALIZATION

### 🎯 Goals of Good Relational Design
```
✅ Store information WITHOUT unnecessary redundancy
✅ Retrieve information EASILY
```

### ⚠️ Problems with "Mega-Schema" Design
| Problem | Description |
|---------|-------------|
| **Redundancy** | Department info repeated for every instructor |
| **Inconsistency** | Update anomalies - must change multiple rows |
| **Bad Business Logic** | Can't add new department without an instructor |

---

## 🔗 Functional Dependencies (FDs)

### Definition
```
α → β means: If we know α, we uniquely know β
Example: dept_name → budget
```

### Types of FDs
| Type | Rule | Example |
|------|------|---------|
| **Trivial** | β ⊆ α | {ID, Name} → ID |
| **Non-Trivial** | α ∩ β = ∅ | StudentID → CGPA |
| **Semi-Trivial** | Partial overlap | {ID, Name} → {Name, CGPA} |
| **Transitive** | α→β and β→γ ⇒ α→γ | ID→Dept, Dept→Budget ⇒ ID→Budget |

---

## ✂️ Decomposition: Lossy vs Lossless

### Lossless Decomposition ✅
```
R decomposed into R1, R2 is LOSSLESS if:
(R1 ∩ R2) → R1  OR  (R1 ∩ R2) → R2

In practice: The common attribute must be a KEY for at least one table
```

### Lossy Decomposition ❌
```
Natural join produces EXTRA (spurious) tuples
Example: Joining on "name" when two people share the same name
```

---

## 🧮 Armstrong's Axioms (Finding Hidden FDs)

### Primary Rules (Foundation)
```
1. Reflexivity: If β ⊆ α, then α → β
   Example: {ID, Name} → ID

2. Augmentation: If α → β, then γα → γβ
   Example: ID→Name ⇒ {ID,Dept}→{Name,Dept}

3. Transitivity: If α→β and β→γ, then α→γ
   Example: ID→Dept, Dept→Budget ⇒ ID→Budget
```

### Secondary Rules (Shortcuts)
```
• Union: α→β AND α→γ ⇒ α→βγ
• Decomposition: α→βγ ⇒ α→β AND α→γ
• Pseudotransitivity: α→β AND γβ→δ ⇒ αγ→δ
• Composition: α→β AND γ→δ ⇒ αγ→βδ
```

---

## 🔑 Finding Candidate Keys: Method 3 (Optimized)

### Phase 1: Discard Process
```
1. Start with ALL attributes: {A,B,C,D,E}
2. For each FD α→β: If α is in your set, remove β (it's derivable)
3. Remaining set = Superkey
4. Check subsets to find minimal = Candidate Key
```

### Phase 2: Replacement Process
```
1. Prime Attributes (PA) = attrs in known Candidate Keys
2. Dependent Attributes (DA) = attrs on RHS of FDs
3. If PA ∩ DA ≠ ∅: Replace overlapping attr using its determining FD
4. Verify new key is minimal → New Candidate Key
5. Repeat until no new keys found
```

### Example
```
R(A,B,C,D), FDs: A→B, B→C, C→A

Phase 1: {A,B,C,D} → discard B,C → {A,D} = CK₁
Phase 2: PA={A,D}, DA={B,C,A}, Intersection={A}
  - C→A, so replace A with C: {C,D} = CK₂
  - B→C, so replace C with B: {B,D} = CK₃

Result: Candidate Keys = {AD, CD, BD}
```

---

## 📊 NORMAL FORMS (Progressive Strictness)

### 1NF: First Normal Form
```
✅ All attribute domains are ATOMIC (indivisible)
✅ Each attribute holds SINGLE value only

❌ Violation: Phone = "0176543, 0176548" (multiple values)
✅ Fix: Create separate Phone table with (ID, PhoneNumber)
```

### 2NF: Second Normal Form
```
Requirements:
1. Must be in 1NF
2. NO Partial Dependencies

Partial Dependency: 
  Proper subset of composite PK → Non-Prime Attribute

Example Violation:
  Table: (StudentID, CourseID, StudentName, Grade)
  PK = {StudentID, CourseID}
  StudentID → StudentName  ❌ (Partial dependency!)

✅ Fix: Decompose
  Students(StudentID, Name)
  Enrollments(StudentID, CourseID, Grade)
```

### 3NF: Third Normal Form
```
Requirements:
1. Must be in 2NF
2. NO Transitive Dependencies on Non-Prime Attributes
   i.e., No FD: α → β where BOTH α and β are Non-Prime

Example Violation:
  Table: (SID, Name, Dept, DeptEst)
  CK = SID, so NonPA = {Dept, DeptEst}
  Dept → DeptEst  ❌ (NonPA → NonPA!)

✅ Fix: Decompose
  Students(SID, Name, Dept)
  Departments(Dept, DeptEst)
```

### BCNF: Boyce-Codd Normal Form (3.5NF)
```
Requirements:
1. Must be in 3NF
2. For EVERY non-trivial FD α → β, α must be a SUPERKEY

Example Violation:
  Table: (SID, CID, TID)  // Student, Course, Teacher
  CK = {SID, CID}
  FD: TID → CID  ❌ (TID is not a superkey!)

✅ Fix: Decompose
  StudentTeacher(SID, TID)
  TeacherCourse(TID, CID)
```

### Normal Forms Quick Reference
```
1NF: Atomic values only
2NF: 1NF + No partial dependencies (PSS of PK → NonPA)
3NF: 2NF + No transitive NonPA → NonPA
BCNF: 3NF + Every determinant is a superkey

💡 Rule of thumb: BCNF is stricter; use 3NF if BCNF causes dependency loss
```

---

## 🗂️ PART 2: INDEXING

### Why Indexing?
```
🎯 Reduce disk I/O by minimizing block reads
🎯 Speed up: exact match, range queries, sorting
```

### Index Evaluation Criteria
| Factor | Consideration |
|--------|--------------|
| Access Types | Point query? Range query? |
| Access Time | How many disk reads? |
| Update Time | Cost of insert/delete on index |
| Space Overhead | Extra storage for index |

---

### Index Classifications

#### By Ordering
```
🔹 Ordered Indices: Keys stored in sorted order (B-Tree, B+ Tree)
🔹 Hash Indices: Keys distributed via hash function (fast exact match only)
```

#### By Data Storage
```
🔹 Clustering (Primary) Index:
   - Data file physically sorted by search key
   - Only ONE per table
   - Leaf nodes contain ACTUAL data records

🔹 Non-Clustering (Secondary) Index:
   - Data NOT sorted by search key
   - Multiple allowed per table
   - Leaf nodes contain POINTERS to data
```

#### By Density
```
🔹 Dense Index: Entry for EVERY search key value
   ✅ Faster lookup  ❌ More space, slower updates

🔹 Sparse Index: Entry for SOME key values (only clustering indices)
   ✅ Less space, faster updates  ❌ Slightly slower lookup
```

---

### Multilevel Indices
```
Problem: Large index doesn't fit in memory → many disk reads

Solution: Build sparse index ON TOP of the index (outer index)

Benefit: Reduces disk reads dramatically
Example (10,000 blocks):
  Binary search (m=2): 14 reads
  m=10: 4 reads
  m=50: 3 reads

💡 Higher fan-out (m) = fewer disk accesses
```

---

## 🌳 B-TREE

### Structure & Properties (Order = m)
```
Node Capacity:
• Max keys: m-1
• Max children: m
• Min keys (non-root): ⌈m/2⌉ - 1
• Min children (non-root): ⌈m/2⌉
• Root: min 1 key, 2 children

Balance: ALL leaves at same level → O(logₘ n) search time
```

### Node Structure
```
[P₀] K₁ [P₁] K₂ [P₂] ... Kₙ [Pₙ]
     ↑    ↑         ↑
   Rp₁  Rp₂       Rpₙ  (Record Pointers to actual data)
```

### Insertion Algorithm
```
1. Search for correct LEAF node
2. Insert key in sorted order
3. If node overflows (has m keys):
   a. Sort all m+1 keys
   b. Promote MIDDLE key to parent
   c. Split remaining into two nodes
   d. If parent overflows, repeat upward (may create new root)
```

### Deletion Algorithm (3 Cases)
```
Case 1a: Leaf has > min keys
  → Simply delete the key ✅

Case 1b: Leaf has = min keys
  Step 1: Try borrow from LEFT sibling (if it has extra)
  Step 2: Try borrow from RIGHT sibling (if it has extra)
  Step 3: If neither can lend → MERGE with sibling + parent key

Case 2: Delete from internal node
  → Replace with predecessor/successor from leaf, then delete from leaf

💡 Borrowing Rule: Parent key BETWEEN your pointer and sibling's pointer comes down
```

---

## 🌲 B+ TREE (Database Favorite)

### Key Differences from B-Tree
```
┌─────────────────┬─────────────────┬─────────────────┐
│ Feature         │ B-Tree          │ B+ Tree         │
├─────────────────┼─────────────────┼─────────────────┤
│ Data Storage    │ Internal + Leaf │ Leaf nodes ONLY │
│ Key Duplication │ Keys unique     │ Keys copied up  │
│ Leaf Links      │ None            │ Linked list ✅  │
│ Range Queries   │ Good            │ EXCELLENT 🚀    │
└─────────────────┴─────────────────┴─────────────────┘
```

### Why B+ Tree for Databases?
```
✅ All data in leaves → uniform access time
✅ Leaf linked list → range queries: find start, then traverse linearly
✅ Internal nodes = more keys/node → higher fan-out → fewer disk reads
✅ Better for sequential access patterns
```

### Insertion (B+ Tree Specific)
```
1. Always insert into LEAF node
2. If leaf overflows:
   a. Sort keys, split into two leaves
   b. COPY middle key to parent (key STAYS in leaf!)
   c. Link new leaf to neighbor via right pointer
3. Propagate splits upward if needed
```

### Deletion (B+ Tree Specific)
```
Similar to B-Tree, BUT:
• When borrowing: parent key comes down, sibling key goes up
• When merging: ensure separator key in parent is updated
• Leaf links must be maintained after splits/merges
```

### Query Performance Comparison
```
Dataset: {1,4,7,10,17,21,31,25,19,20,28,42}, m=4

Point Query: SELECT ... WHERE ID = 21
  BST: 4 comparisons | B-Tree: 2 | B+ Tree: 3

Range Query: SELECT ... WHERE ID BETWEEN 7 AND 21
  BST: 26 comparisons | B-Tree: 10 | B+ Tree: 2 🏆

💡 B+ Tree dominates range queries due to leaf linked list
```

---

## 🎨 BITMAP INDICES

### When to Use
```
✅ Low cardinality attributes (few distinct values)
   Examples: Gender (M/F), Status (Active/Inactive), Rating (1-5)

❌ High cardinality (names, timestamps, IDs)
❌ OLTP systems with frequent updates
```

### Structure
```
For each distinct value → one bit vector
Bit position = record number
1 = record has this value, 0 = doesn't

Example: Income (L1, L2, L3, L4) for 8 records
L1: 1 0 1 1 0 0 0 0
L2: 0 1 0 0 1 0 0 0
L3: 0 0 0 0 0 0 1 1
L4: 0 0 0 0 0 1 0 0
```

### Query Processing (Bitwise Operations)
```
AND Query: gender='M' AND income='L1'
  Gender_M: 1 0 1 0 1 1 0 1
  Income_L1:1 0 1 1 0 0 0 0
  AND:      1 0 1 0 0 0 0 0  → Records 1, 3 match ✅

OR Query: income='L1' OR income='L3'
  L1: 1 0 1 1 0 0 0 0
  L3: 0 0 0 0 0 0 1 1
  OR: 1 0 1 1 0 0 1 1  → Records 1,3,4,7,8 ✅

COUNT(*) Query: Just count 1s in result vector! No disk I/O! 🚀
```

### Advantages & Limitations
```
✅ Extremely fast bitwise operations (CPU-level)
✅ Efficient storage for low-cardinality data
✅ COUNT(*) without accessing records
✅ Easy parallelization

❌ Space = (#distinct values) × (#records) bits
❌ Expensive updates (must modify multiple bitmaps)
❌ Not ideal for OLTP (many writes)
```

---

## 📝 QUICK REVISION CHEAT SHEET

### Normal Forms Decision Tree
```
Is data atomic? → No → Apply 1NF
↓ Yes
Any partial dependency (subset of PK → NonPA)? → Yes → Apply 2NF
↓ No  
Any transitive NonPA → NonPA? → Yes → Apply 3NF
↓ No
Any FD where determinant is NOT superkey? → Yes → Apply BCNF
↓ No
✅ Fully normalized!
```

### B-Tree vs B+ Tree: When to Use
```
Use B-Tree when:
• Mostly point queries (exact match)
• Memory-resident databases

Use B+ Tree when:
• Range queries common (BETWEEN, >, <)
• Sequential access needed
• Disk-based databases (standard choice!)
```

### Finding Candidate Keys: 30-Second Method
```
1. Write all attributes
2. Cross out any attribute that appears on RHS of FD 
   (if its LHS is still in the set)
3. Remaining = minimal superkey = Candidate Key
4. Check for replacements using PA ∩ DA intersection
```

### Index Selection Guide
```
Point queries only? → Hash index
Range queries? → B+ Tree
Low-cardinality filters? → Bitmap index
Need multiple search paths? → Multiple secondary indices
Write-heavy workload? → Fewer indices (update cost!)
```

---

## 🔗 Practice Resources
```
• B-Tree Visualizer: https://www.cs.usfca.edu/~galles/visualization/BTree.html
• B+ Tree Visualizer: https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
💡 Tip: Practice insertion/deletion with m=3,4,5 to internalize splitting logic
```

---

> 🎯 **Final Tip**: Normalization prevents anomalies; Indexing improves performance. Always normalize first, then add indices based on query patterns!

*These notes cover all topics from your lectures in a condensed, exam-ready format. Bookmark this and you won't need to flip through 200 pages!* 🚀
# SQL Logic: Sets, Duplicates, and NULLs

**Tags:** #sql #database #logic #null #postgres

---

## 1. Handling Duplicates in Set Operations

### UNION vs. UNION ALL
When combining results from two queries:
- **`UNION`**: Automatically **eliminates duplicates**.
	- It compares the **entire row** (all selected columns).
	- Slower (needs to sort/hash to find duplicates).
- **`UNION ALL`**: Keeps **everything**.
	- Simply appends the second list to the first.
	- Faster (no processing).

### How "Equality" Works in Sets
SQL is "blind" to columns you do not select.
> [!EXAMPLE] Scenario
> **Row 1:** `ID: 101`, `Semester: Fall`
> **Row 2:** `ID: 101`, `Semester: Spring`

1. **Query:** `SELECT id, semester ... UNION ...`
   - **Result:** Both rows are kept.
   - **Reason:** The rows are *distinct* because "Fall" $\neq$ "Spring".
2. **Query:** `SELECT id ... UNION ...`
   - **Result:** Only one `101` is kept.
   - **Reason:** Since you only selected `id`, the database sees `101` vs `101`. They are identical, so one is removed.

---

## 2. INTERSECT ALL (Bag Semantics)

PostgreSQL supports "Bag Semantics" (allowing duplicates) via the `ALL` keyword.

### The Rule
When performing `(Query A) INTERSECT ALL (Query B)`:
$$ \text{Result Count} = \min(\text{Count in A}, \text{Count in B}) $$

> [!TIP] The "Making Pairs" Analogy
> Think of it as matching cards from Pile A to Pile B.
> - If Pile A has **4** Aces.
> - And Pile B has **2** Aces.
> - You can only make **2 pairs**.
> - Result: The output contains two Aces.

**Syntax (Postgres):**
```sql
(SELECT id FROM ... WHERE ...)
INTERSECT ALL
(SELECT id FROM ... WHERE ...);
```
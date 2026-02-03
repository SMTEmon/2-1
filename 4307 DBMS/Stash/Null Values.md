Three-Valued Logic (The NULL Trap)

In SQL, a boolean expression can result in three states, not just two.
1. **TRUE**
2. **FALSE**
3. **UNKNOWN** (Caused by `NULL`)

### The Comparison Matrix
Assuming `salary > 10000`:

| Value (Salary) | Logic Operation | Boolean Result |
| :--- | :--- | :--- |
| `95000` | `95000 > 10000` | **TRUE** |
| `5000` | `5000 > 10000` | **FALSE** |
| `NULL` | `NULL > 10000` | **UNKNOWN** |

### Filtering "Unknown" Data
Using `WHERE` clauses with explicit Boolean tests treats these buckets differently.

> [!WARNING] UNKNOWN is not FALSE
> If a value is `NULL`, it is **not** True, but it is also **not** False. It exists in a grey area.

#### `WHERE ... IS UNKNOWN`
- **Captures:** Only `NULL` values.
- **Example Result:** Gold, Singh.

#### `WHERE ... IS FALSE`
- **Captures:** Only values where the math explicitly failed.
- **Excludes:** `NULL` (because Unknown $\neq$ False).
- **Example Result:** Mozart (5000).

#### `WHERE ... IS NOT TRUE`
- **Captures:** Both `FALSE` and `UNKNOWN`.
- **Example Result:** Mozart, Gold, Singh.
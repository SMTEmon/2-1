**Tags:** #OOD #SoftwareDesign #Coupling #Cohesion #Architecture

---

# Coupling & Cohesion
*The primary mantra of software design: "High Cohesion, Low Coupling."*

## 1. Coupling (Inter-dependence)
**Coupling** measures the degree of dependency *between* modules (classes, packages, functions). It answers the question: *"If I change Module A, how likely is Module B to break?"*

*   **Goal:** **Low (Loose) Coupling.**
    *   **Analogy:** A plug and a wall socket. You can plug a lamp, a toaster, or a laptop into the same socket because they connect via a standard interface. They are not hardwired into the wall.
*   **Problems with High (Tight) Coupling:**
    *   **Ripple Effect:** A small change in one class causes bugs in five unrelated classes.
    *   **Hard to Test:** You cannot test Class A without also creating instances of Class B, C, and D.
    *   **Hard to Reuse:** You want to use a "User" class in a new app, but it drags in the entire "Database" and "Email" libraries because it's tightly coupled to them.

### Levels of Coupling (Worst to Best)
1.  **Content Coupling (Worst):** One module modifies the internal data of another (e.g., accessing public fields directly).
2.  **Global Coupling:** Modules share global variables.
3.  **Control Coupling:** One module passes a "flag" to control the internal logic of another (e.g., `process(true)` means "save", `process(false)` means "delete").
4.  **Data Coupling (Good):** Modules share data through parameters (e.g., passing an `int` or `String`).
5.  **Message Coupling (Best):** Modules communicate via Interfaces (no implementation details shared).

---

## 2. Cohesion (Intra-dependence)
**Cohesion** measures the strength of the relationship between elements *within* a single module. It answers the question: *"Does this class do one thing, and does it do it well?"*

*   **Goal:** **High Cohesion.**
    *   **Analogy:** A Swiss Army Knife has *low* cohesion (it's a knife, a spoon, a saw, and a toothpick). A Scalpel has *high* cohesion (it does exactly one thing: cut).
*   **Benefits of High Cohesion:**
    *   **Readability:** You know exactly what the class does by looking at its name.
    *   **Maintainability:** All the logic related to "Tax Calculation" is in the `TaxCalculator` class, not scattered across `Invoice` and `PrintManager`.

### Levels of Cohesion (Worst to Best)
1.  **Coincidental (Worst):** Grouping random utilities (e.g., `HelperUtils.java` containing `calculateTax()`, `resizeImage()`, and `encryptPassword()`).
2.  **Logical:** Grouping by category (e.g., `InputHandler` handling Mouse, Keyboard, and Network input—related logically, but different technically).
3.  **Temporal:** Grouping things that happen at the same time (e.g., `SystemStartup`—loads config, connects DB, initializes UI).
4.  **Functional (Best):** Every element in the module contributes to a single, well-defined task (e.g., `XMLParser`—only parses XML).

---

## 3. Comparison Summary
| Metric | Description | Desired State |
| :--- | :--- | :--- |
| **Coupling** | Connections *between* modules. | **Low** (Independent) |
| **Cohesion** | Focus *inside* a module. | **High** (Focused) |

> [!TIP] 
> You want a system made of **Lego bricks** (High cohesion, standard connection interface) rather than a bowl of **Spaghetti** (everything tangled together).

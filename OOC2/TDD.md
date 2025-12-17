---
course: SWE 4301 - Object Oriented Concepts II
lecture: 2
topic: Introduction to TDD
date: 2025-11-24
tags:
---

# Lecture 2: Introduction to Test Driven Development (TDD)

## 1. Introduction to TDD

### Philosophy: Clean & Green Code
*   **Readable Code:** Code that correctly reflects the problem it is solving. Writing clean code is likened to "drawing a picture."
*   **The Goal:** Writing "clean, shamelessly green code."
*   **The Framework:** **TDD** (Test Driven Development) is the primary framework used to achieve this.

### Understanding Testing
Historically, Extreme Programming (XP) practitioners introduced "test first development."
*   **The Norm:** Automated tests are now standard practice.
*   **The Method:** Tests are written *before* the actual code.

#### The "Table Building" Analogy
1.  **Expectation:** Table should be 4ft diameter. -> **Fail** (No table). -> **Action:** Cut wood 4ft round. -> **Pass**.
2.  **Expectation:** Table should be 3ft high. -> **Fail** (Sitting on ground). -> **Action:** Add a leg. -> **Pass**.
3.  **Expectation:** Hold 20lb object. -> **Fail** (Falls over, only 1 leg). -> **Action:** Move leg, add 2 more (tripod). -> **Pass**.

### The TDD Cycle (Red-Green-Refactor)
TDD is a discipline that works in a tight loop:

> [!failure] Red: Write a Test
> Because the code does not exist yet, this test **fails**. Test runners display this in red.

> [!success] Green: Make it Run
> Write the *simplest* code possible to make the test pass. Test runners display this in green.

> [!quote] Refactor: Make it Right
> Once green, refactor the code into better shape, confident that functionality is preserved because tests continue to pass.

---

## 2. Unit Testing

### Definition
**Unit Tests** are automated tests run every time code is changed to ensure new code doesn't break existing functionality.
*   **Scope:** Validates the smallest possible unit of code (function/method).
*   **Isolation:** Tested independently from the rest of the system.
*   **Benefits:** Quick identification of issues, improved quality, reduced later testing time.

### Anatomy of a Test
Every test consists of three distinct parts:
1.  **Setup:** Create the specific environment required.
2.  **Do:** Perform the action to be tested.
3.  **Verify:** Confirm the result is as expected.

### Writing the First Test
*   **The Challenge:** The first test is the hardest because the problem feels like a "big, fuzzy, amorphous blob."
*   **Strategy:** Do not overthink. Pick a starting place. You don't need to know the perfect solution to start; the path will clear as you write tests.
*   **The "Two Hats" Metaphor:**
    *   *Writing Tests Hat:* Focus on the big picture/requirements.
    *   *Writing Code Hat:* Focus *only* on passing the current test (pretend you know nothing else).

---

## 3. TDD In Practice: The `StringSwap` Example

**Goal:** Create a function that swaps the last two characters of a string.

**Requirements:**
1.  "AB" $\to$ "BA"
2.  "ABCD" $\to$ "ABDC"
3.  "SELENIUM" $\to$ "SELENIMU"
4.  "A" $\to$ "A" (Single char returns same)
5.  "" $\to$ "" (Empty returns empty)

### Iteration 1: The Initial Fail (Red)
**Test:**
```java
@Test
public void stringSwap2charsOnly() {
    StringSwapHelper help = new StringSwapHelper();
    Assert.assertEquals("BA", help.swaplasttwochars("AB"));
}
```
*   **Result:** Compilation Error (Class doesn't exist).
*   **Action:** Create class and stub method returning `null`.
*   **Result:** Assertion Error (Expected "BA", got `null`).

### Iteration 2: The Simplest Solution (Green)
**Code:**
```java
public String swaplasttwochars(String string) {
    char firstChar = string.charAt(0);
    char secChar = string.charAt(1);
    return "" + secChar + firstChar; 
}
```
*   **Result:** Passed for input "AB".

### Iteration 3: Generalizing (Refactor/Triangulate)
New Test: Input "ABCD" expects "ABDC".
*   **Result:** Fails with current logic (Logic only swapped indices 0 and 1).
*   **Refactored Code:**
```java
public String swaplasttwochars(String string) {
    int length = string.length();
    String strExceptLast2Chars = string.substring(0, length - 2);
    char secondLastChar = string.charAt(length - 2);
    char lastChar = string.charAt(length - 1);
    return strExceptLast2Chars + lastChar + secondLastChar;
}
```

### Iteration 4: Boundary Conditions (1 Char)
New Test: Input "A" expects "A".
*   **Result:** `StringIndexOutOfBoundsException` (Code tries to access `length - 2`).
*   **Refactored Code:**
```java
if (length == 1) {
    return string;
}
// ... rest of logic
```

### Iteration 5: Boundary Conditions (Empty String)
New Test: Input "" expects "".
*   **Result:** `StringIndexOutOfBoundsException` (Length is 0, logic fails).
*   **Final Refactored Code:**
```java
public String swaplasttwochars(String string) {
    int length = string.length();
    // Combined check for empty and single char
    if (length <= 1) {
        return string;
    }
    String strExceptLast2Chars = string.substring(0, length - 2);
    char secondLastChar = string.charAt(length - 2);
    char lastChar = string.charAt(length - 1);
    return strExceptLast2Chars + lastChar + secondLastChar;
}
```

---

## 4. Kent Beck's "Green Bar Patterns"

Strategies to make tests pass:

1.  **Fake It ("Til You Make It"):** Return a constant (e.g., return "BA"). Gradually replace constants with variables until real code emerges.
2.  **Obvious Implementation:** If the solution is simple, just type the real implementation immediately. If you get stuck, revert to smaller steps.
3.  **Triangulate:**
    *   Conservatively drive abstraction.
    *   Write *several* tests at once that fail.
    *   Write code that solves *all* of them to force the correct abstraction to emerge (avoiding hard-coding for just one specific case).

---

## 5. Best Practices for TDD

1.  **Fail First:** Write small test cases that fail at the start. If a test passes immediately, it's not actually testing the new functionality.
2.  **Independence:** Tests should be self-sufficient. One test should not depend on the state or result of another.
3.  **Execute Regularly:** Run tests before coding, after coding, and after refactoring. Catch regressions immediately.
4.  **Positive & Negative Scenarios:** Test intended behavior (Happy path) AND failure states/edge cases (Robustness).

> [!quote] Robert C. Martin
> "TDD is a discipline for programmers like double-entry bookkeeping is for accountants or sterile procedure is for surgeons."
```
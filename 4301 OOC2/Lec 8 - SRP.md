---
course: SWE 4301 - Object Oriented Concepts II
university: Islamic University of Technology
lecture: 8
topic: Single Responsibility Principle (SRP)
date: 2025-12-05
lecturer: Maliha Noushin Raida
tags:
  - "#SWE4301"
  - "#OOP"
  - "#SOLID"
  - "#SRP"
  - "#Cohesion"
---

# Lecture 8: Single Responsibility Principle (SRP)

## 1. Cohesion

**Definition:** Cohesion refers to the degree to which elements inside a module belong together.
*   It measures the strength of the relationship between methods/data and the unifying purpose of the class.
*   **Goal:** High Cohesion.

> [!INFO] Mental Model
> **High Cohesion:** The module performs one task, has a clear purpose, and nothing else.
> **Low Cohesion:** The module tries to encapsulate more than one purpose or has an unclear purpose.

### Relationship with Coupling
*   High cohesion often correlates with **loose coupling**.
*   Low cohesion often correlates with **tight coupling**.

### Advantages of High Cohesion
1.  **Reduced Complexity:** Simpler modules with fewer operations.
2.  **Increased Maintainability:** Logical changes affect fewer modules; changes in one require fewer changes in others.
3.  **Increased Reusability:** Easier to find and use components with a clear, single purpose.

---

## 2. Single Responsibility Principle (SRP)

**Core Definition:**
> "A class should have only one reason to change."

Alternative definition: Every module, class, interface, or method should have **one job**.

### Why separate responsibilities?
*   **Responsibility = Axis of Change.**
*   If a class has more than one responsibility, the responsibilities become coupled.
*   Changes to one responsibility may impair the ability of the class to meet others.
*   **Result of violation:** Fragile designs that break in unexpected ways.

### What is a "Responsibility"?
In the context of SRP, a responsibility is defined as **"a reason for change."**
*   If you can think of more than one motive for changing a class, that class has >1 responsibility.

---

## 3. Case Studies & Examples

### Example A: The Rectangle (GUI vs. Math)
*   **Scenario:** A `Rectangle` class has two methods: `draw()` and `area()`.
*   **Violation:**
    *   `draw()` is used by a **Graphical Application**.
    *   `area()` is used by a **Computational Geometry App**.
*   **Problem:** The Computational App includes graphical dependencies it doesn't need. Changes to the GUI logic might affect the Math logic.
*   **Solution:** Split into `GeometricRectangle` (Math) and `Rectangle` (UI) or separate classes completely.

### Example B: The Modem (Connection vs. Data)
*   **Scenario:** A `Modem` interface with 4 methods:
    1.  `dial()` (Connection)
    2.  `hangup()` (Connection)
    3.  `send()` (Data Communication)
    4.  `recv()` (Data Communication)
*   **Analysis:** There are two distinct responsibilities here.
    *   *Connection Management*
    *   *Data Communication*
*   **Nuance (Crucial):** Should they be separated?
    *   **YES:** If the application changes in ways that affect connection signatures independently of data signatures (smell of Rigidity).
    *   **NO:** If the application does *not* change in ways that cause these two to change at different times. Splitting them effectively would be "Needless Complexity."

> [!WARNING] Corollary
> An axis of change is only an axis of change if the changes actually occur. Do not apply SRP if there is no symptom.

### Example C: The Resume
*   **Violation:** A `Resume` class containing logic for storing data (`technology`, `yearsOfExperience`) AND logic for searching/viewing (`searchResume()`).
*   **Solution:** Separate the view logic into `RepositoryView` and keep the data model in `Resume`.

---

## 4. Main Reasons to Follow SRP

1.  **Manageable Project:** Keeps the "developer brain" cleaner. You only think about one responsibility at a time.
2.  **Enhances Maintenance & Scalability:** modifying one behavior doesn't inadvertently break unrelated behaviors.
3.  **Better Testability:**
    *   Writing unit tests is easier when a class does only one thing.
    *   Reduces bug fixes and testing time.
4.  **Reduces Coupling:** Methods are independent of each other.
5.  **Facilitates Code Extension:** Enables modular code and Dependency Injection.

---

## 5. Implementation Guide

**Steps to Apply SRP:**
1.  **Identify Responsibilities:** Analyze methods and properties to see what they are used for.
2.  **Separate:** Create new classes for identified responsibilities.
3.  **Delegate:** The original class can delegate tasks to the new classes (Composition).
4.  **Review:** Ensure the resulting classes have only one responsibility.

### Code Refactoring Example (Java)

#### ❌ Before (Violation)
The `Car` class manages driving logic AND fuel calculations/printing.

```java
public class Car {
    private double fuelLevel;

    public void drive(double distance) {
        if (this.fuelLevel >= distance) {
             // Mixed logic: Calculation + Printing
            this.fuelLevel -= distance;
            System.out.printf("Driving %.2f miles...", distance);
        } else {
            System.out.println("Not enough fuel");
        }
    }
    
    public void fillGasTank(double amount) {
        this.fuelLevel += amount;
        // ... print logic
    }
}
```

#### ✅ After (Applied SRP)
Responsibilities are split. `Car` handles driving, `FuelTank` handles fuel logic.

**The FuelTank Class:**
```java
public class FuelTank {
    private double fuelLevel;

    public boolean hasEnoughFuel(double distance) {
        return this.fuelLevel >= distance;
    }

    public void consumeFuel(double distance) {
        this.fuelLevel -= distance;
    }
    
    // Getters...
}
```

**The Car Class:**
```java
public class Car {
    private FuelTank fuelTank;

    public Car(FuelTank fuelTank) {
        this.fuelTank = fuelTank;
    }

    public void drive(double distance) {
        // Delegates logic to FuelTank
        if (this.fuelTank.hasEnoughFuel(distance)) {
            this.fuelTank.consumeFuel(distance);
            System.out.printf("Driving %.2f miles...", distance);
        } else {
            System.out.println("Not enough fuel");
        }
    }
}
```

### Impact on Testing
Because `FuelTank` is isolated, unit tests become simple assertions without needing to instantiate a full Car object or mock print streams.

```java
@Test
void testConsumeFuelMultipleTimes() {
    fuelTank = new FuelTank(50.0);
    fuelTank.consumeFuel(20.0);
    fuelTank.consumeFuel(15.0);
    assertEquals(15.0, fuelTank.getFuelLevel(), 0.001);
}
```
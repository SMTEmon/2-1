***

# Chapter 8: Frameworks and Reuse (Interfaces & Abstract Classes)

**Status:** #study #oo_design #java
**Related:** [[Inheritance]], [[Polymorphism]], [[Composition]]

---

## 1. The Core Problem: Code Reuse
**Goal:** Write code once, reuse it multiple times.
**The Reality:** Simply "copy-pasting" code (e.g., taking code from a Pizza Shop app and pasting it into a Donut Shop app) leads to a maintenance nightmare. If you find a bug in one, you have to fix it in all copies.

**The OO Solution:** Use **Frameworks** and **Contracts** to enforce standardization and reuse.

---

## 2. What is a Framework?
A **Framework** is a standardized structure that allows for "plug-and-play" development. It provides the skeleton of an application, and the developer fills in the specific details.

> [!EXAMPLE] The "Microsoft Office" Analogy
> Word, Excel, and PowerPoint all look similar (same "File", "Edit" menus, same toolbar structure).
> *   **Why?** They share a common framework.
> *   **Benefit:** Users don't have to relearn the UI; Developers don't have to rewrite code for the "Save" dialog or window borders.

**Key Benefits:**
1.  **Consistency:** Similar look and feel.
2.  **Efficiency:** Reuse code that has already been written and tested (e.g., standard Windows buttons).

---

## 3. What is a Contract?
In software design, a **Contract** is a mechanism that *requires* a developer to comply with the specifications of an API (Application Programming Interface).

*   **Enforcement:** If you break the contract (e.g., fail to implement a required method), the compiler throws an error.
*   **Two ways to implement contracts:**
    1.  **Abstract Classes**
    2.  **Interfaces**

---

## 4. Abstract Classes
An **Abstract Class** is a class that cannot be instantiated and usually contains one or more abstract methods.

*   **Rule:** If a class contains an abstract method, the class *must* be abstract.
*   **Rule:** Subclasses *must* implement the abstract methods (unless the subclass is also abstract).
*   **Concept:** Represents a "Strict Inheritance" (Is-A) relationship.

### The "Shape" Example
You cannot draw a generic "Shape." You can only draw a specific shape (Circle, Rectangle). Therefore, `Shape` is abstract.

```java
// The Contract
public abstract class Shape {
    // Abstract method: No implementation allowed here.
    // Children MUST implement this.
    public abstract void draw(); 
    
    // Concrete method: Implementation is shared by all children.
    public void setColor(String color) {
        // code to set color
    }
}

// The Implementation
public class Circle extends Shape {
    public void draw() {
        System.out.println("Draw a Circle");
    }
}

public class Rectangle extends Shape {
    public void draw() {
        System.out.println("Draw a Rectangle");
    }
}
```

> [!NOTE] Polymorphism in Action
> Because of the contract, we can do this:
> `shape.draw();`
> The system knows `draw()` exists because `Shape` guarantees it, but the specific behavior depends on whether the object is a Circle or Rectangle.

---

## 5. Interfaces
An **Interface** is a pure contract. Unlike abstract classes, interfaces usually contain *no* implementation logic (in standard Java/C# design patterns discussed here). They only define **behavior**.

*   **Syntax:** uses `implements` (Java) or `:` (C#).
*   **Why use them?** Java and .NET do **not** support "Multiple Inheritance" (inheriting from two classes). However, a class can implement **multiple interfaces**.
*   **Concept:** "Definition Inheritance" (Behavior) rather than "Implementation Inheritance."

### The "Nameable" Example
Interfaces allow unrelated objects to share behavior. A `Dog` and a `Planet` are not related biologically (no common parent class), but both can be "Named."

```java
// The Interface (The Contract)
public interface Nameable {
    public String getName();
    public void setName(String name);
}

// Class 1
public class Dog extends Mammal implements Nameable {
    // Must implement Nameable methods
    public String getName() { return dogName; }
}

// Class 2 (Totally unrelated to Dog)
public class Planet implements Nameable {
    // Must implement Nameable methods
    public String getName() { return planetName; }
}
```

### Compiler Proof: Is-A Relationship
Even though it's an interface, the compiler treats it as an "Is-A" relationship.
```java
Dog d = new Dog();
Nameable n = d; // This works! A Dog IS-A Nameable thing.
```

---

## 6. Abstract Class vs. Interface (Quiz Critical!)

| Feature | Abstract Class | Interface |
| :--- | :--- | :--- |
| **Methods** | Can have both concrete (code) and abstract (no code) methods. | All methods are abstract (definitions only).* |
| **Inheritance** | Single Inheritance (A class can only extend one). | Multiple Implementation (A class can implement many). |
| **Relationship** | **Strict Is-A** (Related classes). <br> *Ex: Dog is a Mammal.* | **Behavior** (Unrelated classes). <br> *Ex: Dog is Nameable, Car is Nameable.* |
| **State** | Can have member variables (fields). | Usually only constants (static final). |

*(Note: Modern Java allows default methods in interfaces, but for this textbook's context, assume interfaces have no implementation).*

---

## 7. Case Study: The E-Business Framework (Pizza vs. Donut)

**The Scenario:** You build a web system for "Papa's Pizza." Later, "Dad's Donuts" wants a system.

### The Bad Approach (Non-Reuse)
*   Copy `PizzaShop` code, paste it, rename it `DonutShop`.
*   **Result:** Two separate codebases. If `PizzaShop` fixes a bug in the login screen, `DonutShop` still has the bug. This is "divergent."

### The Good Approach (Framework)
Factor out commonalities into a contract.

**The Design:**
1.  **`Shop` (Abstract Class):** Handles inventory logic, tax calculations (things every shop does).
2.  **`Nameable` (Interface):** Handles naming conventions.
3.  **`PizzaShop` / `DonutShop` (Concrete Classes):** Extend `Shop` and implement `Nameable`. They only contain specific items (Pizza names vs Donut names).

**UML Structure:**
*   `Shop` contains `getInventory()` (abstract) and `buyInventory()` (abstract).
*   `Shop` contains `calculateSaleTax()` (concrete/shared).
*   `PizzaShop` inherits from `Shop`.

### Decoupling with Dynamic Loading
The framework allows the application to run *any* shop without changing the main code. The text demonstrates loading the class dynamically using arguments:

```java
// We don't say 'new PizzaShop()'. 
// We let the user tell us which class to load as a String!
String className = args[0]; // e.g., "PizzaShop"

// Dynamically create the object
Shop myShop = (Shop) Class.forName(className).newInstance();

// The rest of the code doesn't care if it's pizza or donuts
myShop.buyInventory("Item 1");
```
*This is the ultimate power of frameworks: The control code never changes; only the plug-in modules (Pizza/Donut classes) change.*

---

## 8. Summary & Key Takeaways for Exam

1.  **Code Reuse:** The primary goal of frameworks. Avoids "reinventing the wheel."
2.  **Abstract Class:** Use when classes are closely related (Dog/Mammal) and share some common implementation code.
3.  **Interface:** Use when classes are unrelated (Dog/Car) but share a behavior, or when you need to bypass the "Single Inheritance" limit.
4.  **Polymorphism:** Both Abstract Classes and Interfaces allow different objects to be treated the same way (e.g., treating a `Circle` and `Rectangle` both as `Shape`).
5.  **Composition:** (Briefly mentioned) `Dog` *has-a* `Head`. This is different from Inheritance (`Dog` *is-a* `Mammal`).
6.  **Compiler Enforcement:** Contracts are not just suggestions; they are enforced by the compiler. If you `implements Nameable`, you **must** write the `getName` method, or the code won't compile.

---

## Quiz Prep Questions
*   **Q:** Why can't I instantiate a class defined as `public abstract class Shape`?
    *   *A: Because it is abstract; it likely contains methods with no body. It is a template, not a concrete object.*
*   **Q:** If Java does not support multiple inheritance, how can a class take on the traits of multiple sources?
    *   *A: By implementing multiple Interfaces.*
*   **Q:** In the Pizza/Donut example, why was `Shop` made an abstract class instead of an interface?
    *   *A: Because `Shop` had some common concrete code (like `calculateSaleTax`) that we wanted to share. Interfaces (in this context) cannot hold shared code.*
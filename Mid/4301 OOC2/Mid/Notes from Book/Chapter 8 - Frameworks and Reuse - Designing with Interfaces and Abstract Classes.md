**Tags:** #ObjectOrientedDesign #Programming #Java #CSharp #Architecture #CodeReuse #Interfaces

---

## 1. Introduction to Code Reuse
Code reuse has been a goal since the dawn of software (e.g., COBOL routines, C libraries), but Object-Oriented (OO) design provides specific mechanisms to facilitate it: **Frameworks** and **Contracts**.

### What is a Framework?
A framework is a system of standardization that allows for "plug-and-play" development.
*   **Analogy:** Office Suites (Word, Excel, PowerPoint).
    *   They share common menus (File, Edit, View) and toolbars.
    *   Result: Users learn faster; developers reuse code and design.
*   **OS Level:** Windows GUI standardizes title bars, minimize/maximize buttons, and close behaviors.
*   **Development Benefit:** Developers use a predetermined interface to create applications. They don't have to rebuild core functionality (like an "Open File" dialog) because it is already written and tested.

---

## 2. Contracts
In this context, a **Contract** is a mechanism that requires a developer to comply with the specifications of an Application Programming Interface (API).

*   **Definition:** An agreement between two or more parties (the framework and the developer) enforceable by "law" (the compiler).
*   **Purpose:** To enforce standards (method names, parameters, return types).
*   **Enforcement:** Without enforcement, rogue developers might reinvent the wheel or break the system.
*   **Implementation:** In Java and .NET, contracts are implemented via:
    1.  **Abstract Classes**
    2.  **Interfaces**

---

## 3. Abstract Classes
An abstract class is a class that contains one or more methods without implementation.

*   **Characteristics:**
    *   Cannot be instantiated directly.
    *   Can contain both abstract methods (no code) and concrete methods (with code).
    *   Used for **Strict Inheritance** ("is-a" relationships).

### Example: The `Shape` Hierarchy
*   **Abstract Concept:** If asked to "draw a shape," one cannot do it without knowing *which* shape.
*   **Polymorphism:**
    *   `Shape` class defines `abstract void draw();`.
    *   `Circle` extends `Shape` and implements `draw()` to make a circle.
    *   `Rectangle` extends `Shape` and implements `draw()` to make a rectangle.
    *   *Benefit:* All shapes use the exact same syntax (`shape.draw()`), reducing errors and manual lookups.
*   **Code Structure:**
    ```java
    public abstract class Shape {
        public abstract void draw(); // The Contract
    }

    public class Circle extends Shape {
        public void draw() { 
            System.out.println("Draw a Circle"); 
        }
    }
    ```
*   **Enforcement:** If `Circle` inherits from `Shape` but fails to implement `draw()`, the compiler throws an error (unless `Circle` is also declared abstract).

---

## 4. Interfaces
An interface is a syntactical contract that defines behavior but provides **no implementation**.

### Why Interfaces? (Java/.NET vs. C++)
*   **C++:** Uses abstract classes with multiple inheritance.
*   **Java/.NET:** Do not support multiple inheritance of classes (to avoid complexity). They use Interfaces to support multiple behaviors.
*   **Definition Inheritance vs. Implementation Inheritance:**
    > [!NOTE] Implementation Inheritance (Code)
    > **Source:** Abstract Classes.
    > *   **What it means:** Inheriting the actual **logic** (the "how-to"). The parent class provides working code that the child "borrows."
    > *   **Goal:** Code Reuse.
    > *   **Analogy:** A "Pre-fabricated House"—the structure is built, you just move in.

    > [!ABSTRACT] Definition Inheritance (Behavior)
    > **Source:** Interfaces.
    > *   **What it means:** Inheriting the **contract** (the "what-to"). The parent provides a "to-do list" without code.
    > *   **Goal:** Polymorphism & Consistency.
    > *   **Analogy:** A "Job Description"—it lists requirements you must fulfill yourself.

### The `Nameable` Example
*   **Scenario:** We want diverse objects (Dogs, Cars, Planets) to be capable of having a name.
*   **The Problem:** Without a contract, developers might use `getDogName()`, `getCarName()`, `getPlanetName()`. This requires looking up documentation for every class.
*   **The Solution:** An interface ensures they all use `getName()`.
    ```java
    public interface Nameable {
        String getName();
        void setName(String name);
    }
    ```

---

## 5. Abstract Classes vs. Interfaces
The decision to use one over the other depends on the relationship between the objects.

| Feature | Abstract Class | Interface |
| :--- | :--- | :--- |
| **Relationship** | Strict "Is-A" | Behavior / Capability |
| **Methods** | Can have concrete & abstract | Abstract only (mostly) |
| **Inheritance** | Single Inheritance | Multiple Implementation |
| **Coupling** | High (Related classes) | Low (Unrelated classes) |

> [!TIP] Understanding Coupling
> **Coupling** refers to the degree of dependency between classes.
> *   **High Coupling (Abstract Classes):** The child class is tightly bound to the parent's implementation. Changing the parent's internal code can ripple through and break child classes. 
>     *   *Analogy:* **DNA.** You are inextricably linked to your ancestry.
> *   **Low Coupling (Interfaces):** The class is loosely connected only by a "contract." There is no shared code, so changes in one class don't affect others.
>     *   *Analogy:* **Uniforms.** Anyone can put on a "Security Guard" uniform; the uniform doesn't care who is inside as long as they perform the duty.

### The "Is-A" Test
*   **Abstract Class:** `Dog` **is a** `Mammal`. `Reptile` **is not a** `Mammal`. They cannot share a `Mammal` abstract class.
*   **Interface:** `Dog` **is** `Nameable`. `Lizard` **is** `Nameable`. `Car` **is** `Nameable`. Even though they are unrelated biologically or mechanically, they share a **behavior**.

> [!INFO] Compiler Proof
> ```java
> Dog d = new Dog();
> Mammal m = d;   // Works (Inheritance)
> Nameable n = d; // Works (Interface is also an is-a relationship)
> Head h = d;     // Fails (Composition/No relation)
> ```

---

## 6. Case Study: E-Business Framework
**Scenario:** A development team builds a website for "Papa's Pizza." Later, "Dad's Donuts" wants a similar site.

### The Non-Reuse Approach (Bad)
*   Copy and paste code from Pizza Shop to Donut Shop.
*   Modify small bits to fit the new context.
*   **Result:**
    *   Code diverges (Version 2.01papa vs Version 2.03dad).
    *   Fixing a bug in one doesn't fix it in the other.
    *   Maintenance nightmare.

### The Framework Approach (Good)
Factor out commonality into a `Shop` framework.

#### 1. The Contract (Abstract Class)
Create an abstract class `Shop` that handles the generic logic (e.g., calculating tax) and forces implementation of specific logic (inventory).
```java
public abstract class Shop {
    CustList customerList; // Composition
    
    public void CalculateSaleTax() {
        System.out.println("Calculate Sales Tax");
    }
    
    // The Contract Methods
    public abstract String[] getInventory();
    public abstract void buyInventory(String item);
}
```

#### 2. The Behavior (Interface)
Ensure all shops can be named standardly.
```java
public interface Nameable {
    public String getName();
    public void setName(String name);
}
```

#### 3. The Implementation (Concrete Classes)
The `PizzaShop` and `DonutShop` classes inherit `Shop` and implement `Nameable`. They only contain the code specific to their products (e.g., "Pizza" vs "Donuts").

```java
public class DonutShop extends Shop implements Nameable {
    String[] menuItems = {"Donuts", "Coffee"};
    
    public String[] getInventory() { return menuItems; }
    // ... implementations for buyInventory, getName, etc.
}
```

#### 4. Dynamic Instantiation
Dynamic instantiation (via **Reflection**) is the "magic" that allows frameworks to load new features without rewriting or recompiling the original core code.

**The Problem: Hardcoding**
```java
Shop myShop = new PizzaShop(); // Hardcoded: You must know the class at compile time.
```
To change to a `DonutShop`, you must edit the source code and recompile.

**The Solution: Runtime Loading**
```java
// 1. Get the class name as a String (from a config file, user input, or command line)
String className = args[0]; 

// 2. Lookup: Find the class file on the disk by its name
// 3. Creation: Create an instance of that class ("newInstance")
// 4. Casting: Treat it as the generic "Shop" type (The Contract)
Shop myShop = (Shop) Class.forName(className).newInstance();
```

> [!INFO] Why is this amazing?
> This is how **Plug-ins** work (e.g., Minecraft Mods, Photoshop Filters). 
> 1. You write the core app once.
> 2. You can add a `TacoShop` next year.
> 3. The core app doesn't need to be changed; it just reads the new "TacoShop" string and loads the new logic dynamically.

### Full Example Code

Here is the complete implementation of the E-Business Framework discussed above.

```java
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

// --- 1. THE CONTRACTS (Framework Layer) ---

// Interface for naming behavior
interface Nameable {
    String getName();
    void setName(String name);
}

// Abstract Class: The Blueprint for ANY Shop
abstract class Shop {
    private CustList customerList; // Composition: Shop has a Customer List
    
    public Shop() {
        customerList = new CustList();
    }
    
    // Concrete Method: Shared Logic (Reuse)
    public void calculateSaleTax() {
        System.out.println("LOG: Calculating General Sales Tax (8.25%)...");
    }
    
    public void addCustomer(String name) {
        customerList.add(name);
    }
    
    public void showCustomers() {
        customerList.display();
    }
    
    // Abstract Methods: Forced Implementation (Customization)
    public abstract String[] getInventory();
    public abstract void buyInventory(String item);
}

// Composition Component
class CustList {
    private List<String> customers = new ArrayList<>();

    public void add(String name) {
        customers.add(name);
        System.out.println("Customer added: " + name);
    }

    public void display() {
        System.out.println("Customer List: " + customers);
    }
}


// --- 2. THE IMPLEMENTATION (Application Layer) ---

// Implementation 1: Pizza Shop
class PizzaShop extends Shop implements Nameable {
    private String shopName;
    private String[] menu = {"Pepperoni", "Cheese", "Veggie"};

    public String getName() { return shopName; }
    public void setName(String name) { this.shopName = name; }

    // Implementing the Shop contract
    public String[] getInventory() {
        return menu;
    }

    public void buyInventory(String item) {
        System.out.println("Buying Pizza Ingredients for: " + item);
    }
}

// Implementation 2: Donut Shop
class DonutShop extends Shop implements Nameable {
    private String shopName;
    private String[] menu = {"Glazed", "Jelly", "Chocolate"};

    public String getName() { return shopName; }
    public void setName(String name) { this.shopName = name; }

    // Implementing the Shop contract
    public String[] getInventory() {
        return menu;
    }

    public void buyInventory(String item) {
        System.out.println("Ordering Flour and Sugar for: " + item);
    }
}


// --- 3. THE DRIVER (Dynamic Loading) ---

public class ShopFrameworkDemo {
    public static void main(String[] args) {
        // In a real app, this comes from a config file
        // Try changing this string to "DonutShop"
        String className = "PizzaShop"; 
        
        System.out.println("Starting Shop Application...");
        
        try {
            // DYNAMIC INSTANTIATION
            // The code doesn't know it's a PizzaShop until runtime!
            Class<?> c = Class.forName(className);
            Object obj = c.getDeclaredConstructor().newInstance();
            
            // Casting to the Contract (Shop)
            Shop myShop = (Shop) obj;
            
            // Using Interface methods (if supported)
            if (myShop instanceof Nameable) {
                ((Nameable) myShop).setName("Best " + className + " in Town");
                System.out.println("Welcome to: " + ((Nameable) myShop).getName());
            }

            // Using Abstract Class methods
            myShop.calculateSaleTax(); // Shared code
            
            // Using the Composition component
            myShop.addCustomer("Alice");
            myShop.addCustomer("Bob");
            myShop.showCustomers();
            
            System.out.println("Menu:");
            for(String item : myShop.getInventory()) {
                System.out.println(" - " + item);
            }

        } catch (Exception e) {
            System.out.println("Failed to load shop: " + e.getMessage());
        }
    }
}
```

> [!ABSTRACT] The "Magic" of Reflection Explained
> Imagine you are building a game console.
> *   **Normal Code:** You solder a specific game cartridge (e.g., *Super Mario*) directly onto the motherboard. If you want to play *Zelda*, you have to unsolder *Mario* and solder *Zelda*.
> *   **Reflection:** You build a "slot." You don't know *what* game will be inserted. The console just knows "whatever fits in this slot, I can run it."

> [!NOTE] Line-by-Line Breakdown of the Dynamic Loading
> 1.  **`Class.forName(className)`**: Looks for the `.class` file on the computer. Usually, the compiler must know a class exists at compile time (`new PizzaShop()`). Here, it only needs a **String**, which could come from a text file or user input at runtime.
> 2.  **`newInstance()`**: Effectively calls `new PizzaShop()`, but blindly. It returns a generic `Object`.
> 3.  **`(Shop) obj` (Casting)**: This is where the **Contract** (Abstract Class) saves the day. We cast the generic object to `Shop`. Because `PizzaShop` extends `Shop`, this is legal, and we can now call any method defined in the `Shop` blueprint.
> 4.  **`instanceof Nameable`**: Since we loaded the class blindly, we use this check to see if the object supports specific optional features (Interfaces).

---

## 7. Summary of Relationships
The chapter concludes with a UML structure for a `Dog` object demonstrating all three key OO relationships:
1.  **Inheritance:** `Dog` extends `Mammal`.
2.  **Interface:** `Dog` implements `Nameable`.
3.  **Composition:** `Dog` has a `Head`.
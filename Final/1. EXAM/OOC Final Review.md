---
tags:
  - OOC/Final
  - Exam/Review
  - SWE4301
date: 2026-04-01
---

# OOC Final Exam Review & Q&A

> [!info] Exam Structure
> Expect 4 Questions covering:
> 1. Web Services
> 2. Multithreading
> 3. SOLID Principles
> 4. Code Smells & Refactoring

---

## 1. SOLID Principles

### A. Dependency Injection (DI) & Inversion of Control (IoC)
**Problem:** Tight coupling when a class creates its own dependencies (e.g., `new CreditCardPayment()` inside `PaymentProcessor`).
**Solution:** Inject dependencies via constructor or setters.

#### Code Example: Constructor Injection
```java
// 1. The Abstraction
interface PaymentType {
    void pay();
}

// 2. Implementations
class CreditCardPayment implements PaymentType {
    public void pay() { /* Logic */ }
}

class PayPalPayment implements PaymentType {
    public void pay() { /* Logic */ }
}

// 3. The Client (Receives dependency)
class PaymentProcessor {
    private final PaymentType pt; // final for immutability

    public PaymentProcessor(PaymentType pt) {
        this.pt = pt;
    }

    public void makePayment() {
        pt.pay();
    }
}

// 4. The Injector (Main)
public class Main {
    public static void main(String[] args) {
        // Dependency is created outside and injected
        PaymentType payment = new PayPalPayment();
        PaymentProcessor processor = new PaymentProcessor(payment);
        processor.makePayment();
    }
}
```

### B. Liskov Substitution Principle (LSP)
**Definition:** Subclasses must be substitutable for their base classes without altering the correctness of the program.

#### The Square-Rectangle Trap
```java
class Rectangle {
    protected int width, height;
    public void setWidth(int w) { this.width = w; }
    public void setHeight(int h) { this.height = h; }
    public int getArea() { return width * height; }
}

class Square extends Rectangle {
    @Override
    public void setWidth(int w) {
        this.width = w;
        this.height = w; // Forces square property
    }
    @Override
    public void setHeight(int h) {
        this.width = h;
        this.height = h; // Forces square property
    }
}
```

**The Violation:**
If a client expects a `Rectangle`, it assumes `setWidth(5)` and `setHeight(4)` results in Area = 20.
If a `Square` is passed:
1. `setWidth(5)` $\to$ width=5, height=5.
2. `setHeight(4)` $\to$ width=4, height=4.
3. Area becomes **16**, not 20. The client's expectation is broken.

**Fix:** Do not use inheritance. Use a common `Shape` interface with `getArea()`.

### C. Interface Segregation Principle (ISP)
**Definition:** Clients should not be forced to depend on interfaces they do not use.
**Smell:** **Refused Bequest** (Subclass throws `UnsupportedOperationException` for inherited methods).

#### Example: The Fat Printer
```java
// ❌ Bad: One fat interface
interface Printer {
    void print();
    void scan();
    void fax();
}

class SimpleInkjet implements Printer {
    public void print() { /* works */ }
    public void scan() { throw new UnsupportedOperationException(); } // Refused Bequest
    public void fax() { throw new UnsupportedOperationException(); }
}
```

**Fix:** Split interfaces into cohesive roles.
```java
interface Printable { void print(); }
interface Scannable { void scan(); }

class SimpleInkjet implements Printable {
    public void print() { /* works */ }
}
```

---

## 2. Multithreading

### A. Race Conditions & Synchronization
**Scenario:** Two threads depositing to the same bank account.
**Problem:** **Lost Update**. Both threads read the same balance (e.g., 0), add their amount, and write back. One update is lost.

**Fix:** Use `synchronized` to ensure atomicity.
```java
// Method level
public synchronized void deposit(int amount) {
    balance += amount;
}

// Block level
public void deposit(int amount) {
    synchronized(this) {
        balance += amount;
    }
}
```

### B. Deadlock
**Cause:** Two threads hold one lock and wait for the other's lock (Circular Wait).
```java
// Thread 1 locks A, then wants B
// Thread 2 locks B, then wants A
// 💀 DEADLOCK
```
**Fix:** **Lock Ordering**. Ensure all threads acquire locks in the same order (e.g., always A then B).

### C. Inter-thread Communication (`wait` & `notify`)
**Pattern:** Producer-Consumer.
*   `wait()`: Releases lock and sleeps. **Must** be called inside `synchronized`.
*   `notify()`: Wakes up a waiting thread.

**Important:** Always use `while` loop for waiting condition to handle **spurious wakeups**.
```java
public synchronized String consume() {
    while (!msgAvailable) { // Check condition
        try { wait(); } catch (InterruptedException e) {}
    }
    msgAvailable = false;
    return msg;
}
```

**`sleep()` vs `wait()`:**
*   `sleep()`: Pauses thread but **keeps the lock**.
*   `wait()`: Pauses thread and **releases the lock**.

---

## 3. Code Smells & Refactoring

### Identifying Smells
1.  **Long Method:** Method does too much (e.g., 200 lines).
    *   *Fix:* **Extract Method**.
2.  **Long Parameter List:** Method has too many arguments (e.g., 6+).
    *   *Fix:* **Introduce Parameter Object** (Group args into a class like `ReportConfig`).
3.  **Large Class:** Class has too many responsibilities/fields.
    *   *Fix:* **Extract Class** (Move related fields to a new class).
4.  **Feature Envy:** Method uses data from another class more than its own.
    *   *Fix:* **Move Method**.
5.  **Switch Statements:** Complex `if/else` or `switch` based on type.
    *   *Fix:* **Replace Switch with Polymorphism**.

---

## 4. Web Services

### A. SOAP Structure
SOAP is an XML-based protocol. Structure is like a Russian Doll:
```xml
<soap:Envelope>
    <soap:Header>
        <!-- Metadata: Auth, Transaction ID -->
        <transactionId>12345</transactionId>
    </soap:Header>
    <soap:Body>
        <!-- Actual Payload -->
        <order id="101">
            <item>Laptop</item>
        </order>
    </soap:Body>
</soap:Envelope>
```

### B. WSDL (Web Services Description Language)
The "Instruction Manual" or Contract for the service.
**5 Key Elements:**
1.  `<types>`: Data types (XSD).
2.  `<message>`: Parameters and return values.
3.  `<portType>`: Operations (Interface).
4.  `<binding>`: Protocol (SOAP over HTTP).
5.  `<service>`: Endpoint URL.

### C. SOAP vs REST
| Feature | SOAP | REST |
| :--- | :--- | :--- |
| **Type** | Protocol | Architectural Style |
| **Format** | XML Only | JSON, XML, HTML, Text |
| **State** | Can maintain state | Strictly Stateless |
| **Performance** | Heavy (High overhead) | Lightweight & Fast |

---

## 5. Generics

### A. PECS Mnemonic
*   **P**roducer **E**xtends: Use `? extends T` if you only need to **read** (get) items.
*   **C**onsumer **S**uper: Use `? super T` if you only need to **write** (add) items.

### B. Type Erasure
Java removes generic type information at runtime for backward compatibility.
*   `List<String>` becomes `List` (raw type).
*   `T` is replaced by `Object` (or its bound).

**Consequences:**
1.  `list1.getClass() == list2.getClass()` is **true** even if types differ.
2.  Cannot create generic arrays (`new T[10]` is illegal).
3.  Cannot use `instanceof` with generics.

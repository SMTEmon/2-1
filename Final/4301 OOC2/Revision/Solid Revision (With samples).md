### 1. Liskov Substitution Principle (LSP)

**Definition:** Subtypes must be substitutable for their base types without altering the correctness of the program.

**Explanation:** LSP ensures that any subclass can stand in for its parent class without causing errors or requiring special handling. A major violation of LSP occurs when you have to use `instanceof` checks to figure out exactly what subclass you are dealing with before executing a method. Another common violation is when a subclass implements a method from its parent but throws an exception (like `UnsupportedOperationException`) because it doesn't actually support that behavior. To follow LSP, you should push specific behaviors behind a unified, polymorphic interface so the client doesn't need to know the exact subtype.

**Code example:**

Java

```java
// ❌ BAD: Violates LSP by using instanceof type-checking
Collection<IPerson> persons = context.getPersons();
for (IPerson person : persons) {
    if (person instanceof Boss) {
        ((Boss) person).doBossStuff();
    } else if (person instanceof Peon) {
        ((Peon) person).doPeonStuff();
    }
}

// ✅ GOOD: Refactored to follow LSP
public interface IPerson {
    // General method pulled up to the interface
    void doStuff(); 
}

public class Boss implements IPerson {
    @Override
    public void doStuff() {
        this.doBossStuff(); // Boss specific logic hidden behind the interface
    }
    private void doBossStuff() { /* ... */ }
}

public class Peon implements IPerson {
    @Override
    public void doStuff() {
        this.doPeonStuff(); // Peon specific logic hidden behind the interface
    }
    private void doPeonStuff() { /* ... */ }
}

// The client no longer needs to know the exact type:
for (IPerson person : persons) {
    person.doStuff(); 
}
```

---

### 2. Interface Segregation Principle (ISP)

**Definition:** Clients should not be forced to depend upon interfaces that they do not use.

**Explanation:** ISP deals with the problem of "fat" or "bulky" interfaces. When an interface contains too many unrelated methods, it lacks cohesion. This leads to "Interface Pollution," where subclasses are forced to inherit methods they don't need, resulting in them writing dummy code or throwing exceptions (a code smell known as Refused Bequest). To fix this, large interfaces should be segregated into smaller, highly cohesive interfaces tailored specifically to what a client actually needs. Java achieves this gracefully because while a class can only extend one base class, it can implement multiple segregated interfaces.

**Code example:**

Java

```java
// ❌ BAD: Bulky interface forces simple doors to implement timer logic they don't need
public interface Door {
    void lock();
    void unlock();
    boolean isDoorOpen();
    void timeout(); // Only TimedDoor needs this!
}

// ✅ GOOD: Segregated interfaces using multiple inheritance of interfaces
public interface Door {
    void lock();
    void unlock();
    boolean isDoorOpen();
}

public interface TimerClient {
    void timeout();
}

// SimpleDoor only depends on what it uses
public class SimpleDoor implements Door {
    private boolean isLocked;
    
    @Override public void lock() { isLocked = true; }
    @Override public void unlock() { isLocked = false; }
    @Override public boolean isDoorOpen() { return !isLocked; }
}

// TimedDoor explicitly implements both interfaces it needs
public class TimedDoor implements Door, TimerClient {
    private boolean isLocked;
    
    @Override public void lock() { isLocked = true; }
    @Override public void unlock() { isLocked = false; }
    @Override public boolean isDoorOpen() { return !isLocked; }
    
    @Override 
    public void timeout() { 
        this.lock(); 
    }
}
```

---

### 3. Dependency Inversion Principle (DIP)

**Definition:** High-level modules should not depend on low-level modules; both should depend on abstractions. Furthermore, abstractions should not depend on details; details should depend on abstractions.

**Explanation:** DIP is the principle that drives the design pattern known as Dependency Injection (DI) and the concept of Inversion of Control (IoC). In a tightly coupled system, a high-level class directly instantiates its low-level dependencies (e.g., using the `new` keyword), making it rigid and hard to test. DIP flips this paradigm: the high-level class relies on an abstract interface, and the concrete dependencies are provided (injected) from the outside. This allows you to easily swap implementations (like changing a real database for a mock database during testing) without altering the core logic of the high-level class.

**Code example:**

Java

```java
// ❌ BAD: Tightly coupled. NotificationService strictly depends on a specific EmailSender.
public class NotificationService {
    private EmailSender emailSender;

    public NotificationService() {
        // High-level module creates the low-level module directly
        this.emailSender = new EmailSender(); 
    }

    public void notifyUser(String message) {
        emailSender.sendEmail(message);
    }
}

// ✅ GOOD: Decoupled via Dependency Injection. Both depend on the MessageService abstraction.
public interface MessageService {
    void sendMessage(String message);
}

public class EmailSender implements MessageService {
    @Override
    public void sendMessage(String message) {
        System.out.println("Sending email: " + message);
    }
}

public class NotificationService {
    private MessageService messageService;

    // Constructor Injection: The dependency is injected from the outside
    public NotificationService(MessageService messageService) {
        this.messageService = messageService; 
    }

    public void notifyUser(String message) {
        messageService.sendMessage(message);
    }
}
```
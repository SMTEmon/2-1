
---

# Clean Code (Java Edition)

Source: [[Clean Code Book]] (Robert C. Martin) / Adapted from jbarroso/clean-code

[[Clean Code - 2  | Free Code Camp Version]]

Tags: #java #clean-code #best-practices #programming #solid

---

## 1. Variables

### Use Meaningful and Pronounceable Names

Names should reveal intent. Avoid abbreviations or single letters that require mapping in your head.

> [!failure] Bad
> 
> Java
> 
> ```
> String yyyymmdstr = new SimpleDateFormat("YYYY/MM/DD").format(new Date());
> ```

> [!success] Good
> 
> Java
> 
> ```
> String currentDate = new SimpleDateFormat("YYYY/MM/DD").format(new Date());
> ```

### Use Searchable Names

Avoid "Magic Numbers". Extract them into named constants.

> [!failure] Bad
> 
> Java
> 
> ```
> // What is 86400000?
> setTimeout(blastOff, 86400000);
> ```

> [!success] Good
> 
> Java
> 
> ```
> public static final int MILLISECONDS_IN_A_DAY = 86400000;
> setTimeout(blastOff, MILLISECONDS_IN_A_DAY);
> ```

### Avoid Mental Mapping

Don't use variables like `i`, `j`, `k` in large scopes or `l` (which looks like `1`).

> [!failure] Bad
> 
> Java
> 
> ```
> List<String> l = Arrays.asList("Austin", "New York", "San Francisco");
> for (String s : l) {
>     doStuff(s);
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> List<String> locations = Arrays.asList("Austin", "New York", "San Francisco");
> for (String location : locations) {
>     doStuff(location);
> }
> ```

---

## 2. Functions

### Function Arguments (2 or fewer ideally)

Limiting arguments makes testing easier. If you need more than 2 or 3 arguments, your function might be doing too much, or you should wrap the arguments in a class.

> [!failure] Bad
> 
> Java
> 
> ```
> public void createMenu(String title, String body, String buttonText, boolean cancellable) {
>     // ...
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> public void createMenu(MenuConfig config) {
>     // ...
> }
> ```

### Functions Should Do One Thing

This is the most important rule. If a function does more than one thing, it is hard to compose, test, and reason about.

> [!failure] Bad
> 
> Java
> 
> ```
> public void emailClients(List<Client> clients) {
>     for (Client client : clients) {
>         if (client.isActive()) {
>             email(client);
>         }
>     }
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> public void emailActiveClients(List<Client> clients) {
>     clients.stream()
>         .filter(this::isActiveClient)
>         .forEach(this::email);
> }
> ```

> private boolean isActiveClient(Client client) {
> 
> return client.isActive();
> 
> }

### Function Names Should Say What They Do

Avoid generic names.

> [!failure] Bad
> 
> Java
> 
> ```
> private void addToDate(Date date, int month) {
>     // ...
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> private void addMonthToDate(Date date, int month) {
>     // ...
> }
> ```

---

## 3. Classes

### Single Responsibility Principle (SRP)

A class should have one, and only one, reason to change.

> [!failure] Bad
> 
> Java
> 
> ```
> class UserSettings {
>     private User user;
> ```

> ```
> public void changeSettings(Settings settings) {
>     if (verifyCredentials()) {
>         // ...
>     }
> }
> ```

> ```
> public boolean verifyCredentials() {
>     // ...
> }
> ```
> 
> }

> [!success] Good
> 
> Java
> 
> ```
> class UserAuth {
>     private User user;
>     
>     public boolean verifyCredentials() {
>         // ...
>     }
> }
> ```

> class UserSettings {
> 
> private User user;
> 
> private UserAuth auth;

> ```
> public void changeSettings(Settings settings) {
>     if (auth.verifyCredentials()) {
>         // ...
>     }
> }
> ```
> 
> }

### Composition over Inheritance

Inheritance often leads to tight coupling. Prefer using interfaces and composition.

> [!example] Concept
> 
> Instead of extending a Logger class, inject a Logger interface into your class.

---

## 4. Objects and Data Structures

### Getter and Setters

Don't just add getters and setters to every variable. Think about if the object should expose its internals.

### Law of Demeter

A module should not know about the innards of the objects it manipulates.

Don't talk to strangers.

> [!failure] Bad
> 
> Java
> 
> ```
> String outputDir = ctxt.getOptions().getScratchDir().getAbsolutePath();
> ```

> [!success] Good
> 
> Java
> 
> ```
> // Ask the object to do the work rather than asking for its internals
> String outputDir = ctxt.createScratchFileStream(classFileName);
> ```

---

## 5. SOLID Principles

### S - Single Responsibility Principle

As mentioned in Classes: _A class should have one reason to change._

### O - Open/Closed Principle

Software entities should be **open for extension**, but **closed for modification**.

> [!failure] Bad
> 
> Java
> 
> ```
> public void drawShape(Object shape) {
>     if (shape instanceof Circle) {
>         drawCircle((Circle) shape);
>     } else if (shape instanceof Square) {
>         drawSquare((Square) shape);
>     }
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> // Use polymorphism
> public void drawShape(Shape shape) {
>     shape.draw();
> }
> ```

### L - Liskov Substitution Principle

Subtypes must be substitutable for their base types.

### I - Interface Segregation Principle

Clients should not be forced to depend upon interfaces that they do not use. Break large interfaces into smaller ones.

> [!failure] Bad
> 
> Java
> 
> ```
> interface Shape {
>     void draw();
>     void volume(); // Not all shapes have volume (e.g. 2D squares)
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> interface Shape {
>     void draw();
> }
> interface ThreeDimensionalShape {
>     void volume();
> }
> ```

### D - Dependency Inversion Principle

Depend on abstractions, not on concretions. High-level modules should not depend on low-level modules.

> [!failure] Bad
> 
> Java
> 
> ```
> class PasswordReminder {
>     private MySQLConnection dbConnection; // Dependent on specific DB implementation
> ```

> ```
> public PasswordReminder(MySQLConnection dbConnection) {
>     this.dbConnection = dbConnection;
> }
> ```
> 
> }

> [!success] Good
> 
> Java
> 
> ```
> class PasswordReminder {
>     private DBConnectionInterface dbConnection; // Dependent on abstraction
> ```

> ```
> public PasswordReminder(DBConnectionInterface dbConnection) {
>     this.dbConnection = dbConnection;
> }
> ```
> 
> }

---

## 6. Error Handling

### Use Exceptions rather than Return Codes

Return codes clutter the caller. Exceptions allow error handling to be separated from main logic.

> [!failure] Bad
> 
> Java
> 
> ```
> if (deletePage(page) == E_OK) {
>     if (registry.deleteReference(page.name) == E_OK) {
>         // ...
>     } else {
>         logger.log("Reference missing");
>     }
> } else {
>     logger.log("Page not deleted");
> }
> ```

> [!success] Good
> 
> Java
> 
> ```
> try {
>     deletePage(page);
>     registry.deleteReference(page.name);
> } catch (Exception e) {
>     logger.log(e.getMessage());
> }
> ```

### Don't Return Null

Returning `null` forces the caller to check for nulls, increasing the risk of `NullPointerException`. Use `Optional<T>` or return empty collections.

> [!success] Good
> 
> Java
> 
> ```
> public List<Employee> getEmployees() {
>     if (noEmployeesFound) {
>         return Collections.emptyList(); // Instead of null
>     }
>     return employees;
> }
> ```

---

## 7. Comments

### Comments Do Not Make Up for Bad Code

> "Don't comment bad code—rewrite it." — _Brian W. Kernighan_

### Explain "Why", not "What"

Good comments explain the intent or the reason for a specific decision (e.g., specific algorithm choice for performance), not what the syntax is doing.

> [!failure] Bad
> 
> Java
> 
> ```
> // Check if employee is eligible for full benefits
> if ((employee.flags & HOURLY_FLAG) && (employee.age > 65))
> ```

> [!success] Good
> 
> Java
> 
> ```
> if (employee.isEligibleForFullBenefits())
> ```
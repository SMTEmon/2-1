Here are the additional notes based on the **FreeCodeCamp Clean Code Guide**, adapted for Java. You can append this to your existing Obsidian note or create a linked note.

---

# Clean Code (Supplementary Guide)

Source: [[FreeCodeCamp Guide]] (German Cocca)

Tags: #java #clean-code #refactoring #efficiency

---

## 1. Core Pillars

The guide identifies three pillars for evaluating code quality:

1. **Effectiveness**: Does it solve the problem? (The baseline).
    
2. **Efficiency**: Does it use resources (time/space) wisely? Use clear algorithms.
    
3. **Simplicity**: Is it readable, maintainable, and modular?
    

### Efficiency Example

Using built-in methods (like Streams) can often be more readable and efficient than manual iteration, provided the team understands them.

> [!failure] Verbose & Manual
> 
> Java
> 
> ```
> public int sumArrayInefficient(int[] array) {
>     int sum = 0;
>     for (int i = 0; i < array.length; i++) {
>         sum += array[i];
>     }
>     return sum;
> }
> ```

> [!success] Efficient & Expressive (Java Streams)
> 
> Java
> 
> ```
> public int sumArrayEfficient(int[] array) {
>     return Arrays.stream(array).sum();
> }
> ```

---

## 2. Conciseness vs. Clarity

Don't sacrifice _clarity_ just to make code shorter ("one-liners"). If a complex logic (like Regex) is crammed into one line, it becomes "write-only" code.

> [!failure] Too Concise (Hard to Read)
> 
> Java
> 
> ```
> // Counting vowels - cryptic one-liner
> public long countVowels(String s) {
>     return s.chars().filter(c -> "AEIOUaeiou".indexOf(c) != -1).count();
> }
> ```

> [!success] Clear & Maintainable
> 
> Java
> 
> ```
> public long countVowels(String input) {
>     if (input == null) return 0;
>     
>     // Extract logic into variables or helper methods for clarity
>     return input.chars()
>         .filter(this::isVowel)
>         .count();
> }
> ```

> private boolean isVowel(int character) {
> 
> return "AEIOUaeiou".indexOf(character) != -1;
> 
> }

---

## 3. Re-usability (DRY)

Avoid hardcoding logic that is repeated. Use polymorphism or helper methods to handle variations.

> [!failure] Repetitive (Bad)
> 
> Java
> 
> ```
> public double calculateCircleArea(double radius) {
>     return 3.14 * radius * radius;
> }
> public double calculateRectangleArea(double length, double width) {
>     return length * width;
> }
> ```

> [!success] Reusable (Polymorphism)
> 
> Java
> 
> ```
> // Define an interface
> interface Shape {
>     double calculateArea();
> }
> ```

> class Circle implements Shape {
> 
> private double radius;
> 
> public Circle(double radius) { this.radius = radius; }
> 
> ```
> @Override
> public double calculateArea() {
>     return Math.PI * radius * radius;
> }
> ```
> 
> }

> // Usage
> 
> public void printArea(Shape shape) {
> 
> System.out.println(shape.calculateArea());
> 
> }

---

## 4. Project Structure

Organize your code by **Feature**, not just by technical role. This makes it easier to locate all files related to a specific domain concept.

> [!example] Feature-Based Structure (Recommended)
> 
> Plaintext
> 
> ```
> └── src/
>     ├── auth/
>     │   ├── AuthController.java
>     │   ├── AuthService.java
>     │   └── User.java
>     ├── payment/
>     │   ├── PaymentController.java
>     │   └── Transaction.java
>     └── Main.java
> ```

> [!failure] Layer-Based Structure (Traditional but often harder to navigate)
> 
> Plaintext
> 
> ```
> └── src/
>     ├── controllers/
>     │   ├── AuthController.java
>     │   └── PaymentController.java
>     ├── models/
>     │   ├── User.java
>     │   └── Transaction.java
>     └── services/
> ```

---

## 5. Documentation

- **Self-Documenting Code**: Prefer good naming over comments.
    
- **Inline Documentation**: Use Javadoc for public APIs.
    
- **API Documentation**: Tools like Swagger/OpenAPI are part of "Clean Code" for external consumers.
    

> [!tip] Rule of Thumb
> 
> If you feel the need to write a comment to explain what the code is doing, try renaming the variable or method first. Use comments to explain why (business logic, weird constraints).
> 
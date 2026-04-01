**3(a) Liskov Substitution Principle (LSP)**

- LSP states that subtypes must be substitutable for their base types.
    
- Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program.
    
- In the delivery fleet analogy, Bob expects all vehicles to start an engine, drive, and stop.
    
- If Bob is given a bicycle that cannot start an engine, it violates the expectations he has from all vehicles in his fleet.
    
- The `Bicycle` class violates LSP because it inherits from `Vehicle` but throws an exception when the `startEngine()` method is called, breaking the contract established by the parent class.
    
- To refactor and adhere to LSP, you ensure that the `Bicycle` class doesn't inherit methods it cannot fulfill.
    
- This is done by creating an abstract `Vehicle` class with only `drive()` and `stop()` methods, and then creating a `MotorVehicle` subclass that adds the `startEngine()` method. `Truck` extends `MotorVehicle`, while `Bicycle` directly extends `Vehicle`.
    

**3(b) Interface Segregation Principle (ISP)**

- ISP states that clients should not be forced to depend upon interfaces that they do not use.
    
- Interface Pollution occurs when an interface is forced to incorporate methods it does not require solely for the benefit of one of its subclasses.
    
- For example, forcing the base `Door` class (and all its derivatives) to inherit from `TimerClient` just so a specific `TimedDoor` subclass can use timeouts is a form of interface pollution.
    
- To fix this using delegation, you create a separate adapter class (e.g., `DoorTimerAdapter`) that implements the `TimerClient` interface.
    
- The `TimedDoor` class then delegates the timer functionality to this `DoorTimerAdapter` object rather than inheriting the polluted interface directly.
    

**3(c) Dependency Inversion Principle (DIP)**

- DIP states that high-level modules should depend on abstractions, not concrete implementations.
    
- Inversion of Control (IoC) is the concept that a class should not configure its dependencies statically internally, but should receive its dependencies from an external source.
    
- **Constructor Injection:** Involves passing dependencies as parameters to a class's constructor. It should be used when dependencies are essential for the proper functioning of the object and must be provided during object creation.
    
- **Property-Based (Setter) Injection:** Involves adding a property/setter method to your class that can be set to a valid instance of the dependency. It should be used when a class can function with optional dependencies or when dependencies may change dynamically during the object's lifecycle.
    
- **Method Injection:** Involves injecting a dependency right at the point of use as a method parameter. It should be used when the dependency could change with every use, or when you aren't sure which specific dependency implementation will be needed at the point of use
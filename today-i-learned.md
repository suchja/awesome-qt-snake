# Today I learned
While working on this project I (re-) learned a lot about C++, Qt, TDD and more. Recently I came across the approach Today I Learned (TIL) as defined by [Josh Branchaud](https://github.com/jbranchaud/til). To me it seems like a great way to *learn in public*. I'm not totally clear on whether somebody else could learn from my postings here, but for my own learning it is essential and it shows part of my working and thinking. 

Therefore I try to write one or the other learnings I during this project. In the future I would like to have a dedicated part of my blog, where i post these TIL. So without further ado here are my learnings!

## Is a class without functionality still OOP?

In an interview I had recently, I came across a tendency that data and functionality might be different concerns. From what I understood, the interviewer suggested that this is an valid approach even on class level. This idea gave me quite a hard time, because usually I see encapsulation as one of the corner stones of OOP (and [[Separation of Concerns (SOLID)]] as another).

After recovering from the shock about this I did some research and came across [this stackoverflow post](https://stackoverflow.com/questions/11389948/object-oriented-programming-separation-of-data-and-behavior). It raises the problem with a good example:

```csharp
class Person
{
    string Name;
    DateTime BirthDate;

    //constructor
    Person(string Name, DateTime BirthDate)
    {
        this.Name = Name;
        this.BirthDate = BirthDate;
    }
}

class PersonService
{
    Person personObject;

    //constructor
    PersonService(string Name, DateTime BirthDate)
    {
        this.personObject = new Person(Name, BirthDate);
    }

    //overloaded constructor
    PersonService(Person personObject)
    {
        this.personObject = personObject;
    }

    int GetAge()
    {
        return personObject.Today - personObject.BirthDate; //for illustration only
    }
}
```

From my understanding of OOP this goes against:
- Encapsulation - The `PersonService` requires data (internal state) from the `Person` to offer its services. So it violates encapsulation.
- Coupling - The `PersonService` highly depends on the `Person`. So we have a high coupling here, which makes it difficult to use the one class without the other.
- Cohesion - Thinking in objects as a way of [[Divide and Conquer]] appeals to me, because you have core aspects about one single "problem" in one class. However, if I look into the `Person` above, even its interface doesn't tell me anything about what problem it might solve. I always have to look into both classes to get the understanding about the solved problem. So this seems to me like the cohesion is either too high or not existing at all.

### Did I kill myself ...
**BUT** reading further through the answers, I came across [this](https://stackoverflow.com/a/14949756/5258906):

> I agree, the separation as you implemented is cumbersome. But there are other options. What about an ageCalculator object that has method getAge(person p)? Or person.getAge(IAgeCalculator calc). Or better yet calc.getAge(IAgeble a)
> 
> There are several benefits that accrue from separating these concerns. Assuming that you intended for your implementation to return years, what if a person / baby is only 3 months old? Do you return 0? .25? Throw an exception? What if I want the age of a dog? Age in decades or hours? What if I want the age as of a certain date? What if the person is dead? What if I want to use Martian orbit for year? Or Hebrew calendar?

Even though I would still say that the age is intrinsic to a person, I wouldn't implement functionality like calculating the age in different calendars into the class `Person` (low cohesion!). This is because I would argue that it is against separation of concerns. But wait, wasn't that the idea I'm fighting? So, did I kill myself?

### ... or was it just a KISS?
As ~~always~~ usual, we probably have to say: **it (heavily) depends**. First of all I would argue that it depends on the requirements. If there is **no** requirement to have the age in different calendar types, why do we bother in the first place? Although I long enough was fond of the idea to prepare my code for "anything" that might happen in the future, I lately came across [[Test Driven Development (TDD)]] as well as [[Extreme Programming]].

Both argue that we really should only implement that, what is currently required. I guess this is one of the key aspects of [[Agile Development]] and properly fits [[Keep It Simple and Stupid (KISS)]] quite nicely. More than that it also supports my experience. The additional effort I put into thinking of (more or less likely) future changes and preparing my code for that, seldomly paid out. Usually the requirement in such situations was a little bit (most times largely) different than I had anticipated.

Anyhow, what happens if there is the requirement to support different calendars? I probably still would have a `Person` with a `getAgeInHebrewCalender` (or something else) method. In addition, I would suggest to have some kind of converter between the required calendars. This way we have separation of concerns as well.

However, I have to admit that it would be difficult for me to decide, which calendar is used to store the age in a `Person`. In addition such a converter class would offer functionality, but has no (long-term) data, or does it?

Phew, still not clear on how to deal with this!

### The one answer to rule them all

> If you can't find an answer, simply quote an expert. - *Quote from either Konfuzius or myself ;-)!*

[Another answer](https://stackoverflow.com/a/11390053/5258906) referred to the [Anemic Domain Model](https://martinfowler.com/bliki/AnemicDomainModel.html) from [[Martin Fowler]]:
> The basic symptom of an Anemic Domain Model is that at first blush it looks like the real thing. There are objects, many named after the nouns in the domain space, and these objects are connected with the rich relationships and structure that true domain models have. The catch comes when you look at the behavior, and you realize that there is hardly any behavior on these objects, making them little more than bags of getters and setters.
> [...]
> 
> The fundamental horror of this anti-pattern is that it's so contrary to the basic idea of object-oriented design; which is to combine data and process together. The anemic domain model is really just a procedural style design, exactly the kind of thing that object bigots like me (and Eric) have been fighting since our early days in Smalltalk. What's worse, many people think that anemic objects are real objects, and thus completely miss the point of what object-oriented design is all about.

So, if mister OOP himself says its bad, than it probably is. Isn't it?

My gut feeling is still that classes should (usually) consist of data and functionality. However, if the requirements ask for certain features and a team decides to use a more functional oriented architecture, go for separating data and behavior. To me there is no single right or wrong decision. It simply depends on the circumstances and the trade-offs. The latter is also nicely explained [here](https://monospacedmonologues.com/2016/01/why-couple-data-to-behaviour/).

**But**, however you decide to go ahead, insisting that it is the only possible or maybe even the best solution seems to me pretty wrong!

PS: Learning from my interview: I really should ask for clarification, if I'm unsure what is meant by a question. Even if this takes a little more time.

## Mark methods with `noexcept` to improve code (or not?)
With C++11 the keyword `noexcept` was introduced. Its general idea is to clearly state the intend of a method to **not** throw any `Exception`. This does not only help the compiler to improve performance, but it also clearly communicates the intended behavior of a method.

Although the keyword can be used in different contexts (e.g. as operator to check whether a method is `noexcept` or not), it is used like this to indicate that a method does not throw any `Exception`:

```cpp
void myFunction() noexcept;
```

It seems like the usefullness of this keyword is questioned. I haven't read enough so far, but before using it in all code, I should do so.

### Resources
- [IsoCpp](https://isocpp.org/wiki/faq/exceptions) provides a great FAQ on the topic *exception and error handling*.
- [noexcept — what for?](https://akrzemi1.wordpress.com/2014/04/24/noexcept-what-for/) by Andrzej Krzemieński - provides critical question whether it is usefull and how it might benefit.


## Parameterized Tests with QTest
Using parameterized tests is one of the *Test Patterns* described in the book *xUnit Test Patterns - Refactoring Test Code* by *Gerard Meszaros*. Its intention is to reduce *Test Code Duplication*.

*QTest* supports this with some specific methods and macros. The general idea is to create a method (`private slot`), with the same name like the test that should be parameterized, and add the `_data` suffix. In this method the different data-sets used to run the test case are defined. In the test case the parameters can be included via the `QFETCH` macro. A complete example might then look like this:

```cpp
#include <QtTest/QtTest>

class MyTest : public QObject {
    Q_OBJECT

private slots:
    void myTestFunction();
    void myTestFunction_data();
};

void MyTest::myTestFunction_data() {
    QTest::addColumn<int>("input");
    QTest::addColumn<int>("expectedOutput");

    QTest::newRow("simple case 1") << 1 << 2;
    QTest::newRow("another simple case") << 2 << 4;
    QTest::newRow("complex case with spaces") << 3 << 6;
}

void MyTest::myTestFunction() {
    QFETCH(int, input);
    QFETCH(int, expectedOutput);

    // Replace the following line with the actual function you want to test.
    int actualOutput = input * 2;

    QCOMPARE(actualOutput, expectedOutput);
}

QTEST_MAIN(MyTest)
#include "mytest.moc"
```

In context of the *AwesomeQtSnake*, [this data-method](https://github.com/suchja/awesome-qt-snake/blob/14cca1eb55135ce2c0b5720d5149fe9554c10f80/tests/auto/snakecore/test_game.cpp#L97) and its [test-method](https://github.com/suchja/awesome-qt-snake/blob/14cca1eb55135ce2c0b5720d5149fe9554c10f80/tests/auto/snakecore/test_game.cpp#L109) is a real-life example.

## Rule of Five (Memory Management / Resource Ownership)
C++11 introduced performance improvements with regards to the copying of "heavy" objects (those requiring deep copy due to the handling of dynamic memory allocation/handling). These improvements are usually referred to as *move semantics*. The general idea is, that dynamically allocated ressources are not copied between two objects of the same type, but instead *"moved"*. This (usually?) includes that the object containing the resources before releases them.

The *Rule of Five* states:

> Extends the Rule of Three to include the move constructor and move assignment operator, accommodating move semantics.

To handle this properly a new type of reference was introduced (see RValue Reference). With this the *move constructor* as well as the *move assignment operator* can do their job. Following is a complete example:

```cpp
#include <iostream>
#include <utility> // for std::move

class Resource {
public:
    Resource(size_t size) : size(size), data(new int[size]) {
        std::cout << "Resource acquired\n";
    }

    // Destructor
    ~Resource() {
        delete[] data;
        std::cout << "Resource destroyed\n";
    }

    // Copy Constructor
    Resource(const Resource& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Resource copied\n";
    }

    // Copy Assignment Operator
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data; // Release old resource
            size = other.size;
            data = new int[other.size];
            std::copy(other.data, other.data + other.size, data);
            std::cout << "Resource assigned\n";
        }
        return *this;
    }

    // Move Constructor
    Resource(Resource&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        std::cout << "Resource moved\n";
    }

    // Move Assignment Operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data; // Release old resource
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
            std::cout << "Resource move-assigned\n";
        }
        return *this;
    }

private:
    size_t size;
    int* data;
};

int main() {
    Resource res1(10);            // Acquires resource
    Resource res2(std::move(res1)); // Moves resource

    Resource res3(20);
    res3 = std::move(res2);       // Moves resource

    return 0;
}
```

### Why the Rule of Five?
1. Avoiding Deep Copies: Move operations transfer ownership of resources rather than copying them. This is especially beneficial for classes that manage large amounts of data or resources, such as dynamic arrays, file handles, or network connections.
2. Efficiency: Move operations are typically constant time (O(1)), while copy operations are linear time (O(n)), where n is the number of elements or the size of the resource.
3. Temporary Objects: Move semantics are particularly useful for managing temporary objects (rvalues) created during expression evaluation. They allow for the efficient transfer of temporary resources without unnecessary allocations and deallocations.

*Hint: I need to learn more about temporary objects and expression evaluation*!

## Rule of Three (Memory Management / Resource Ownership)
*For using C++11 and newer see [Rule of Five](#rule-of-five-memory-management--resource-ownership) as well*!

Probably since the beginning or early start of C++ the *Rule of Three* exists. Generally speaking it applies in cases where an instance of a class handles dynamic memory (e.g. instantiates new objects via `new` or takes ownership - via some kind of pointer - of objects allocated dynamically). It states that

> If a class needs a user-defined destructor, copy constructor, or copy assignment operator, it likely needs all three. - Probably "defined" by Bjarne Stroustrup.

### Why the Rule of Three?
- **Resource Management:** Ensures that resources are managed correctly. If you implement one of these special functions, it's likely because your class manages resources that need to be properly copied and destroyed.
- **Preventing Issues:** Helps prevent resource leaks, double deletions, and undefined behavior that can result from improper handling of resources.

### Personal Comment
Even though I know the general approach (e.g. using a *destructor*, applying deep copies by *copy constructor* and/or *assignment operator*, ...), I wasn't aware or couldn't remeber this rule!

## Short-Circuit Evaluation
C++ was designed from the beginning to support short-circuit evaluation in the logical operators `&&` (logical AND) and `||` (logical OR). That means:

```cpp
bool a = false;
bool b = (a && someFunction());
```
If `a` is `false`, `someFunction()` will not be called due to short-circuit evaluation.

```cpp
bool a = true;
bool b = (a || someFunction());
```

If `a` is `true`, `someFunction()` will not be called due to short-circuit evaluation.

Especially in cases where one of the condition fails frequently or one of the conditions has a "high" cost of evaluation, the order is important!

**General Rule of Thumb**
- Place the condition that is cheaper to evaluate and/or more likely to determine the result of the logical operation first.

## I got TDD (totally?) wrong
I would say, that I use unit tests since at least 17 years. It was one of the first larger C# projects I worked on as lead developer. In this context I learned a lot about unit testing and I also came across TDD.

Unfortunately I never applied it rigorously in any project. While working on AwesomeQtSnake I somehow got inspired to look into it again and came across the wonderful article [Canon TDD](https://tidyfirst.substack.com/p/canon-tdd) by Kent Beck.
Here it occurred to me that
- TDD has an analysis phase (we **don't** start immediately in code). The first step in TDD is to write a list of tests (without any implementation detail) for the change in behavior that should be realized. This list will have the happy path(s) as well as any edge cases of the intended behavior. It guides the development and might frequently change as new tests are detected during the next steps or the next iterations.
- Software design should differentiate between interface design and implementation design. I guess this is one of my weak points. As soon as I'm thinking about the interface my mind starts to spin off and goes wild on how the interface might be implemented.
- Although I know that progress in small steps is essential, I seldomly act according to this. When working on the spike for AwesomeQtSnake, I immediately thought about patterns to apply, interfaces and their pros and cons, ... So it took me a really long time and I made so many iterations, before I ended up with an idea that seems to be good enough. What might have happened, if I simply started with much smaller tasks and increments? I really should remember *divide and conquer*!

To keep it short. Applying TDD means the following:
1. Analyse the intended behavior by creating a list of tests that describe the behavior.
2. Select **ONE** test from the list, create an automated test from it that fails. This usually involves defining key aspects of an interface. The test needs to call something.
3. Implement the behavior only so far that the created test passes. The focus here is on creating a very simple solution. Now we have another description of the behavior (this time in code). Remember the first description is the test as defined in step 1. If both ways of describing the behavior match, there is a good chance that we got it right (a concept Kent Beck calls double checking).
4. If necessary, apply some refactoring. In this step we think in detail about how the implementation could be improved. In its book *Test Driven Development* Kent Beck focuses especially on avoiding any duplication (let it be within the code, but also between test and code)!
5. Keep iterating until all tests from the lists are crossed out!

### Resources
During research I stumbled upon and (partially) used the following resources:
- [Canon TDD](https://tidyfirst.substack.com/p/canon-tdd) by Kent Beck - is really a MUST read!
- [Test Driven Development](https://martinfowler.com/bliki/TestDrivenDevelopment.html) article by Martin Fowler - TDD in a nutshell
- [Let's Play: Test Driven Development](https://www.jamesshore.com/v2/projects/lets-play-tdd) by James Shore - 200 short episodes showing James applying TDD to a side project.
- [Incremental Test Driven Development](https://www.youtube.com/watch?v=nlGSDUuK7C4) video by James Shore - James implements a version of the ROT13 algorithm in a TDD way. Except that the test list and analysis phase is not explicitly mentioned, this is a really good example.

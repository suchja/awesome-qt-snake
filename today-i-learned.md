# Today I learned
While working on this project I (re-) learned a lot about C++, Qt, TDD and more. Recently I came across the approach Today I Learned (TIL) as defined by [Josh Branchaud](https://github.com/jbranchaud/til). To me it seems like a great way to *learn in public*. I'm not totally clear on whether somebody else could learn from my postings here, but for my own learning it is essential and it shows part of my working and thinking. 

Therefore I try to write one or the other learnings I during this project. In the future I would like to have a dedicated part of my blog, where i post these TIL. So without further ado here are my learnings!

## Rule of three (Memory Management / Resource Ownership)
*For using C++11 and newer see Rule of Five as well*!

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

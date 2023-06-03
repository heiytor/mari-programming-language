<h1 align="center">Overview</h1>

**Mari** is a simple interpreted language created for study purposes. It is built using standard C, with plans to incorporate assembly optimization in the future.

While I acknowledge that this language will never be used for production purposes, I would like to utilize this space to discuss the development process and architectural choices made during its creation.

<h1 align="center">Syntax</h1>

One of my primary motivations for creating the **Mari** programming language is to develop my own ideal syntax while also learning and growing as a programmer. Personally, I place a strong emphasis on syntax as it significantly impacts the readability and enjoyability of a language.

In **Mari**, I've strived to design a syntax that is clear, concise, and easy to read. I believe that code should be as readable as a text, bringing ease and understanding to the development process. While contemplating the syntax, I drew inspiration from my favorite languages — Rust, C, and Python. For instance, I truly appreciate the concept of immutability in Rust and the use of the "mut" keyword to define mutable variables. However, the ubiquitous "let" keyword found in many languages has always bothered me, and I've always loved the "def" keyword in Python.

By default, all variables in **Mari** are constants. In my experience, spanning about a year and a half as of mid-2023, developers rarely need to change the value of a variable once it's defined.

```
def x = 5; -- This is a constant variable
def mut y = 10; -- This is a mutable variable
```

You can simply read these statements as "define x equals 5" and "define mutable y equals 10."

Another example is that functions are defined using the "func" keyword, which is inspired by JavaScript.

```
def func add_numbers(x, y) { x + y; } -- implicit return

-- anonymous functions
def square = func(x) {
    return x ** 2;
}
```

Once again, you can read these statements as "define function add_numbers ..." and "define square function ...".

(I like Lua comments)

<h1 align="center">Testing</h1>

As I couldn't find a suitable testing package, I built my own testing framework. You can find all unit tests in files with names ending in `_test.c` and `_test.h`.

To run all tests, use the following command:

```bash
make test && ./run_tests
```

If all tests pass, the output will be something like:

![Test results - All Pass](https://example.com/test_results_all_pass.png)

On the other hand, if any test fails, the program will exit, and the output will be something like:

![Test results - Failures](https://example.com/test_results_failures.png)

<h1 align="center">Development</h1>

## Lexer:

***In computer science, lexical analysis, lexing or tokenization is the process of converting a sequence of characters (such as in a computer program or web page) into a sequence of lexical tokens (strings with an assigned and thus identified meaning). A program that performs lexical analysis may be termed a lexer, tokenizer,[1] or scanner, although scanner is also a term for the first stage of a lexer. A lexer is generally combined with a parser, which together analyze the syntax of programming languages, web pages, and so forth.***
> [wikipedia](https://en.wikipedia.org/wiki/Lexical_analysis)

under construction

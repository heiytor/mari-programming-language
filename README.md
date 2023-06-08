<h1 align="center">Overview</h1>

**Mariana** is a simple interpreted language created using standard C. It came about from my desire to design something with "perfect" syntax (in my opinion). It's developed purely for learning purposes.

Being aware that this language will never be used in production, and is merely a small personal project, this README will be used as a discussion platform during the development process, such as, for instance, architectural decisions concerning syntax.

<h1 align="center">Getting Started</h1>

I plan to develop an installation script. For now, you can clone the source code and compile it directly:

1. Clone the repository:
    ```bash
    git clone https://github.com/heiytor/mari-programming-language && cd mari-programming-language
    ```

2. Compile the source code:

    ```bash
    make dev
    ```

    During the project development, I personally chose to build my own testing "framework" to stick to the idea of using only standard C. You can run all the tests with:
    ```bash
    make test
    ```
    
    If all tests pass, the output will look something like:

    ![image](https://github.com/heiytor/mari-programming-language/assets/107213601/62583e37-9fde-4c85-988b-bd43f3290aa8)

    
    On the other hand, if any test fails, the program will exit, and the output will look something like:

    ![image](https://github.com/heiytor/mari-programming-language/assets/107213601/b742dfb6-84ba-4cfd-a1cf-44d012ad43b4)

With that done, within the project folder you can run the following command:

```
./program
```

This will start a small REPL.

<h1 align="center">Syntax</h1>

```mariana
// Function definition
def func add(def x, def y) {
    return x + y;
}

def x = 5; // Variable definition. All variables are constants by default.
def mut y = 10; // Mutable variable definition

def result = add(x, y);
x = 0; // This will throw an error.
y = 0; // This will pass.

println("{x} + {y} = {result}");
```

<h1 align="center">Developer Notes</h1>

## Comments

One of my primary goals in this project is readability and comprehensibility (mainly for myself). Therefore, if you decide to review the source code, you'll encounter numerous comments like this one:

```c
/**
 * As in other languages, some special characters are allowed to create variable names,
 * but you are not allowed to start with these characters.
 *
 * Let's take "!" for example:
 * 
 * ! is an operator character, if the lexer sees a !, it must
 * create a specific token for it. Even so, if the language considers "!" as a letter
 * (to create var names), so the lexer will tokenize it as a variable. Because of this,
 * some languages must block these special characters to be the first letter of the var.
 * 
 * So if the lexer sees any of these special characters, it must create two tokens:
 * !my_var: one for "!" and other for "my_var"
 * 
 * If the lexer sees any of these characters after a letter, the lexer must create a single token:
 * my_!var: "my_!var"
*/
bool is_allowed_as_first_char(byte ch) {
    return ch != '.' && ch != '?' &&

 ch != '!';
}
```

I'm striving to incorporate all the insights and learnings I found during the development process into the project.

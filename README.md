<h1 align="center">Overview</h1>

**Mariana** is a simple interpreted language created using C. It came about from my desire to design something with "perfect" syntax (in my opinion). It's developed purely for learning purposes.

Being aware that this language will never be used in production, and is merely a small personal project, this README will be used as a discussion platform during the development process, such as, for instance, architectural decisions concerning syntax.

<h1 align="center">Getting Started</h1>

"I am in the process of developing an installation script. However, for now, you can clone the source code and compile it manually. Follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/heiytor/mari-programming-language && cd mari-programming-language
    ```

2. Compile the source code:

    ```bash
    make
    ```

    This command will first run all [tests](). If all tests pass, the source code will then be compiled. If you want to only compile the source code without running the tests, you can use `make dev`.

Once you've done that, navigate to the project folder and execute the following command:

```bash
./program
```

This will launch a simple Read-Eval-Print Loop (REPL)."

<h1 align="center">Syntax</h1>

```mariana
// Function definition
var add_numbers = fn(def x, def y) {
    return x + y;
}

var x = 5; // Variable definition. All variables are constants by default.
var mut y = 10; // Mutable variable definition

var result = add(x, y);
x = 0; // This will throw an error.
y = 0; // This will pass.

println("${x} + ${y} = ${result}");
```

<h1 align="center">Tests</h1>

During the course of this project's development, I considered several testing frameworks, such as [Check](https://libcheck.github.io/check/). However, my evaluation led me to the conclusion that introducing such a framework could potentially overcomplicate things.

As a result, I decided to implement my own testing "lib". Running these tests is simple, just execute the following command:

```
make test
```

If all tests pass successfully, the console will display a message similar to the following:

...

However, if a test fails, the program will halt execution at the point of failure, allowing for easier debugging.

You can find the definitions for all tests in the files that end with the ***_test.h*** suffix, while the ***_test.c*** files contain the implementations of these tests. The ***./src/main_test.c*** file serves as the test runner, executing all test implementations.

Tests are named following the pattern "`test_should_pass_if_\[condition]`". For example:
1. `test_should_pass_if_var_statement_to_string_is_equal_to_expected` (***src/ast/ast_test.h***)
2. `test_should_pass_if_bool_assignments_are_equal_to_expected` (******src/token/token_test.h******)**

Each ***_test.c*** file contains local helper functions that assist in performing specific tasks within the file, but are not accessible for other tests. For this reason, I would categorize this as a library, rather than a framework. For instance, in ***src/ast/ast_test.c***, you'll find the `create_program` function:

```C
struct Program* create_program(char* input) {
    struct Lexer* lexer = new_lexer(input);
    struct Parser* parser = new_parser(lexer);
    struct Program* program = parser->parse_program(parser);

    return program;
}
```

This function assists us in creating new programs within tests:

```C
void test_should_pass_if_program_to_string_is_equal_to_expected() {
    char* input = "var x = ;\n" // var statement
                  "var mut y = ;\n" // mutable var statement
                  "return ;"; // return statement

    struct Program* prg = create_program(input);

    // [...]
}
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
 * 
 * @param ch The current character being evaluated.
 * 
 * @return 1 if is number, 0 otherwise.
 */
int is_allowed_as_first_char(byte ch) {
    return ch != '.' &&
        // ch != '-' && // uncomment to allow kebab-case
           ch != '?' &&
           ch != '!';
}
```

I'm striving to incorporate all the insights and learnings I found during the development process into the project.

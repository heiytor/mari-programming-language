# Lexer

This project contains the implementation of a lexer, also known as a scanner, which is an important part of many compilers and interpreters. The lexer takes a sequence of characters as input and outputs a sequence of tokens, which are categorizable sequences that have been grouped together.

## File Structure

The structure of the project's directories and files is as follows:

```
├── lexer
    │   ├── ch.c
    │   ├── ch.h
    │   ├── def.h
    │   ├── init.c
    │   ├── init.h
    │   ├── nav.c
    │   ├── nav.h
    │   ├── tokenization.c
    │   └── tokenization.h
```

## File Descriptions

### def.h
This file contains the definition of the lexer struct, which holds all the important information the lexer needs to function, such as the current position in the input, the current character, the current line and column, and more.

### init.h & init.c
These files contain functions related to the initialization of the lexer, like creating a new lexer.

### nav.h & nav.c
These files contain functions that enable the lexer to navigate through the input, including consuming characters, skipping whitespace, and peeking at the next character.

### ch.h & ch.c
These files include utility functions to handle the lexer's current and next characters.

### tokenization.h & tokenization.c
These files define functions to tokenize the input into meaningful sequences based on certain rules.

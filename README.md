# Minishell

Minishell is a custom Unix shell implementation designed for educational purposes. It provides a simplified shell environment that supports command parsing, execution, environment variable management, and basic built-in commands.

---

## Purpose

The goal of Minishell is to offer a hands-on understanding of how shells work internally, including process management, input parsing, and environment handling. It is built as part of the 42 school curriculum to reinforce knowledge of system programming in C.

---

## Functionality

- **Command Parsing:** Supports splitting input into commands and tokens, handling pipes (`|`), and redirections (`<`, `>`, `>>`, `<<`).
- **Built-in Commands:** Implements built-ins such as `cd`, `pwd`, `echo`, `env`, `export`, `unset`, and `exit`.
- **Environment Management:** Duplicates and manages environment variables, including custom handling of `SHLVL` and `PWD`.
- **Signal Handling:** Custom signal handlers for parent and child processes, including heredoc input.
- **Prompt Generation:** Displays a colored prompt with user and current directory information.
- **Error Handling:** Provides detailed error messages for syntax errors, invalid filenames, and failed system calls.

---

## Techniques Used

- **Custom Parsing:** Uses manual parsing functions to split input, respecting quotes and special characters.
- **Memory Management:** Implements safe allocation and freeing routines to avoid leaks.
- **Redirection Handling:** Manages file descriptors for input/output/appending and heredoc operations.
- **Process Control:** Forks and executes commands, manages pipes, and handles child/parent process signals.
- **Environment List:** Maintains environment variables in a linked list for efficient updates and lookups.
- **Heredoc Implementation:** Handles heredoc input with custom signal handling and expansion logic.

---

## Custom Approach

Minishell is built from scratch without relying on external parsing libraries or shell frameworks. All parsing, environment management, and execution logic are implemented manually, providing full control over shell behavior. The project emphasizes:

- **Manual Tokenization:** Custom logic for splitting commands and handling edge cases.
- **Linked List Environment:** Environment variables are managed in a linked list, allowing dynamic updates.
- **Signal Safety:** Signals are handled with custom handlers to ensure robust user interaction.
- **Resource Management:** Careful allocation and freeing of resources to prevent leaks and undefined behavior.

---

## Getting Started

To build and run Minishell:

```sh
make
./minishell
```

---

## Project Structure

- `src` — Source files for execution, parsing, builtins, and utilities.
- `include` — Header files and custom libft library.
- `Makefile` — Build instructions.

---

## Authors

- dchrysov
- jbrandt

---

Minishell is a learning project and not intended for production use. For more details, see the source code
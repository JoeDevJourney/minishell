<div align="center">
  <img src="https://www.dieter-schwarz-stiftung.de/files/Projects/Project%20logos/Logo_42HN-min.jpg" alt="Logo"/>
</div>

<br>
<div align="center">

### 🛠 C (Programming Language)
### 🛠 Bash (Linux)

</div>
<br>


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
- `include` — Header files and dependencies (libft, getnextline).
- `Makefile` — Build instructions.

---

## Custom Data Structures

Minishell uses several custom structs to organize its internal state and operations. Below is an overview of the main structures:

### `t_env`
Represents an environment variable as a node in a linked list.

**Purpose:**  Allows dynamic management of environment variables, supporting efficient updates, lookups, and deletions.

| <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/b4df8802-b8eb-4196-8312-2b130729bb32" /> | <div align="left">- `char *name` — The name of the environment variable.<br>- `char *value` — The value of the environment variable.<br>- `struct s_env *next` — Pointer to the next environment variable node.</div>|
|-------------------------------|----------------------------------|

---

### `t_redir_op`
Handles redirection and piping operations.

**Purpose:** Encapsulates all data needed for handling pipes and redirections, making parsing and execution modular and manageable.

| <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/8e282bf7-87e0-4fae-9ff9-737bac01aab2" /> | <div align="left">- `char **cmd` — Array of commands split by a delimeter (e.g., '\|').<br>- `int num_cmd` — Number of commands in the array.<br>- `int **fd` — Array of file descriptors for managing input/output redirections.</div>|
|-------------------------------|----------------------------------|

---

### `t_data`
Central structure holding the shell's runtime state.

**Purpose:** Acts as the main context for the shell, storing all relevant information for parsing, execution, environment management, and error handling.

| <img width="400" height="500" alt="image" src="https://github.com/user-attachments/assets/06e6a463-87f3-4d70-be51-7d95038a1914" /> | <div align="left">- `pid_t pid` — Process ID of the shell.<br>- `char *home_dir` — Path to the home directory.<br>- `t_env *env` — Linked list of environment variables.<br>- `char *input` — Raw user input string.<br>- `char *cmd` — Current command being processed.<br>- `char **tok` — Tokenized command arguments.<br>- `t_redir_op pipe` — Pipe operation data.<br>- `t_redir_op inp_op` — Input redirection data.<br>- `t_redir_op out_op` — Output redirection data.<br>- `t_redir_op app_op` — Append redirection data.<br>- `t_redir_op hdoc_op` — Heredoc operation data.<br>- `int ret_val` — Return value/status of the last executed command.<br></div>|
|-------------------------------|----------------------------------|

---

## Authors

This project was a collaboration with [dchrysov](https://github.com/chrisov), as part of the 42 Programming School Core curriculum.<br>
Thanks for the awesome work!

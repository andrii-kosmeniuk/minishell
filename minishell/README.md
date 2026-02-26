*This project has been created as part of the 42 curriculum by milija-h, akosmeni.*

# Minishell — As beautiful as a shell

## Description

Minishell is a 42 School project that challenges students to build a functional Unix shell from scratch in C, inspired by Bash. The goal is to gain deep, hands-on understanding of how a shell works under the hood — including process creation, file descriptors, signal handling, and command parsing.

The shell supports interactive use with a prompt, command history, pipes, redirections, environment variable expansion, and a set of built-in commands. It handles quoted strings, special characters, and signals in a manner consistent with Bash behavior.

## Features

- Interactive prompt with command history
- Executable lookup via `PATH`, relative, or absolute paths
- Single (`'`) and double (`"`) quote handling
- Environment variable expansion (`$VAR`, `$?`)
- Redirections: `<`, `>`, `<<` (heredoc), `>>`
- Pipes (`|`) — chaining multiple commands
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Instructions

### Requirements

- GCC compiler
- GNU Make
- Readline library (`libreadline-dev` on Debian/Ubuntu)

### Compilation

```bash
git clone <your-repo-url> minishell
cd minishell
make
```

This will produce the `minishell` executable.

### Running

```bash
./minishell
```

You will be presented with an interactive prompt. Type commands just as you would in Bash.

### Cleanup

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Full recompile
```

## Usage Examples

```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42

minishell$ ls -la | grep src
minishell$ cat < input.txt > output.txt

minishell$ cat << EOF
> line1
> line2
> EOF

minishell$ echo $?
```

## Resources

### Documentation & References

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the primary reference for expected behavior
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for the readline interface used for input and history
- [The Linux Programming Interface — Michael Kerrisk](https://man7.org/tlpi/) — comprehensive reference for syscalls, processes, and file descriptors
- [fork(2), execve(2), pipe(2), dup2(2) man pages](https://man7.org/) — essential syscall documentation
- [Signal handling in C — signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Writing Your Own Shell — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — introductory walkthrough for shell implementation in C

### How AI Was Used

AI tools (primarily Claude) were used during this project for **research and conceptual understanding**, not for code generation. Specifically:

- **Understanding function behavior**: AI was used to explain the behavior and edge cases of system calls such as `execve`, `dup2`, `fork`, `waitpid`, and `sigaction` — particularly when the man pages were unclear or ambiguous.
- **Bash behavior clarification**: When the expected behavior of the shell was unclear (e.g., how Bash handles unclosed quotes, nested expansions, or heredoc without history update), AI was queried to clarify and cross-reference with the Bash manual.
- **Debugging guidance**: AI was occasionally consulted to understand error patterns (e.g., zombie processes, signal propagation in pipelines) at a conceptual level.

All code was written, understood, and tested by the project authors. AI-generated content was never copy-pasted directly into the project. Every suggestion was reviewed, questioned, and validated — first individually, then with peer review.

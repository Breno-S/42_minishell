# 42_minishell 🐚

*This project was developed as part of the 42 curriculum by **[Breno Silva](https://github.com/Breno-S/)** and **[Ronaldo Gomes](https://github.com/Norethx)**.*

## Description

This project consists of a shell application written in C. Its goal is to reproduce a subset of the behavior of the [Bash](https://www.gnu.org/software/bash/) shell, while being restricted to a limited set of allowed system calls and functions, in addition to our custom implementation of parts of the C Standard Library (`libft`).

The project emphasizes a deep understanding of several core topics of Unix systems programming, such as:

- Command parsing.
- Shell lifecycle.
- Unix files and file descriptors.
- Process creation and management.
- Pipes, signals and inter-process communication.

### What is a shell?

A shell is an interactive, text-based program that allows users to execute and orchestrate other programs within an operating system by typing commands. It acts as an interface between the user and the kernel.

There are many widely used shell implementations, such as `sh`, `bash`, `zsh`, and `fish`. Among them, Bash is one of the most common and is often used as a reference due to its POSIX compliance and widespread availability across Unix-like systems. For portability reasons, many shell scripts are written targeting Bash or POSIX `sh`.

### Minishell features

| Feature | Example |
| ------- | ------- |
| Single and double quoting | `echo 'single quoted $HOME'` <br> `echo "double quoted $HOME"` |
| Variables | `export var="42"` <br> `echo $var` |
| Pipelining | `echo "foo bar" \| tr ' ' \n' ` |
| Redirections | `<`, `>`, `>>`, `<<` |
| Signals | `Ctrl-C`, `Ctrl-D`, `Ctrl-\` |
| Builtin commands | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| Filename expansion | `echo *.md` |

> [!IMPORTANT]
> There are some limitations to our project:
> - Listing commands with `;` or `&` is not possible. They are both treated as invalid tokens.
> - Filename expansions (`*`) target only the current directory and its subdirectories.
> - There is no brace (`{start..end}`), tilde (`~`), parameter (`${parameter}`) or arithmetic (`$((expression))`) expansions.
> - There is no command (`$(command)`) or process (`>(command)`, `<(command)`) substitution.

## Instructions

1. Clone the repository:

	```bash
	git clone https://github.com/Breno-S/42_minishell.git
	```

2. Move into the project directory:

	```bash
	cd 42_minishell
	```

3. Compile the project:

	```bash
	make
	```

4. Run the program:

	```bash
	./minishell
	```

You can now type commands at the prompt and interact with the shell. Press `Ctrl-d` or type `exit` to quit.

## Resources

Some of the main references used during the development of this project:

* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
* [Shell Command Language (POSIX)](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
* [Shell Code Explained](https://youtube.com/playlist?list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq&si=nOBAoxPgcI911upE)
* [Military Grade C/C++ Lexer from Scratch](https://youtu.be/AqyZztKlSGQ?si=mKJNNsJD_HAbHYYe)


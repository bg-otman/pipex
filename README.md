# 👨‍💻 Pipex

## 📌 Introduction
Pipex is a project that replicates the behavior of the shell's piping mechanism. It allows executing multiple commands in sequence while passing output from one command as input to the next. This project is implemented in C, following the constraints of the 1337 School curriculum.

## ✨ Features
- ✅ Handles simple pipes (mandatory part)
- ✅ Supports multiple commands (bonus part)
- ✅ Works with absolute and relative paths
- ✅ Handles errors gracefully
- ✅ Implements file redirection for input and output
- ✅ Manages edge cases such as invalid commands and permissions

## 🔨 Compilation
To compile the project, use the provided Makefile:
```sh
make
```
This will generate the `pipex` executable.

## 🚀 Usage
### 🔹 Mandatory Part
```sh
./pipex infile cmd1 cmd2 outfile
```
Equivalent to:
```sh
< infile cmd1 | cmd2 > outfile
```

### 🔹 Bonus Part
Supports multiple pipes:
```sh
./pipex infile cmd1 cmd2 cmd3 ... cmdN outfile
```
Equivalent to:
```sh
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```
Supports here_doc mode:
```sh
./pipex here_doc LIMITER cmd1 cmd2 outfile
```
Equivalent to:
```sh
cmd1 << LIMITER | cmd2 >> outfile
```

## ⚠️ Error Handling
- ❌ Checks if files are accessible
- ❌ Validates command paths
- ❌ Handles permission errors
- ❌ Manages invalid input gracefully
- ❌ Handles exit status

## 📜 Allowed Functions
- 🔹 open, close, read, write
- 🔹 malloc, free
- 🔹 perror, strerror
- 🔹 dup, dup2, execve
- 🔹 fork, wait, waitpid
- 🔹 access, unlink, pipe

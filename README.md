# Minishell - As beautiful as a shell

## 🎯 Project Overview

**Minishell** is a project that involves creating your own simple shell - your own version of bash! You'll learn extensively about processes, file descriptors, and command-line interpretation while building a functional shell from scratch.

> **Summary:** This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.

## 💻 What is a Shell?

A shell is a command-line interpreter that provides a user interface for accessing an operating system's services. Shells were created because communicating with computers using binary switches was impractical, and developers needed a more human-friendly way to interact with systems.

## ⚙️ Technical Specifications

### Program Requirements
| Component | Specification |
|-----------|---------------|
| **Program Name** | `minishell` |
| **Language** | C |
| **Compilation** | `cc` with `-Wall -Wextra -Werror` |
| **External Functions** | Extensive list including `readline`, `fork`, `execve`, `pipe`, `dup2`, etc. |
| **Libft** | Authorized |

### Key Constraints
- ✅ **Only one global variable allowed** (for signals)
- ✅ **No memory leaks** (except readline's inherent leaks)
- ✅ **Norm-compliant code**
- ✅ **No unexpected crashes**
- ❌ **No interpretation of unclosed quotes or unnecessary special characters**
- ❌ **Limited to subject requirements**

## 🔧 Core Features

### Basic Functionality
- **Display a prompt** when waiting for commands
- **Working command history**
- **Executable search** (PATH, relative, absolute paths)
- **Signal handling** (ctrl-C, ctrl-D, ctrl-\)

### Quote Handling
- **Single quotes ('')** - prevent interpretation of all meta-characters
- **Double quotes ("")** - prevent interpretation except for `$` (dollar sign)

### Redirections
- **<** - Redirect input
- **>** - Redirect output
- **<<** - Here document (read input until delimiter)
- **>>** - Redirect output in append mode

### Pipes and Variables
- **Pipes (|)** - Connect command output to next command's input
- **Environment variables ($VAR)** - Expand to their values
- **$?** - Expand to last command's exit status

## 🛠️ Built-in Commands

Your shell must implement these built-in commands:

- **echo** with `-n` option
- **cd** with relative or absolute path
- **pwd** with no options
- **export** with no options
- **unset** with no options
- **env** with no options or arguments
- **exit** with no options

## 🛠️ Technical Implementation

### Process Management
- **Forking** for command execution
- **Process waiting** (`wait`, `waitpid`, `wait3`, `wait4`)
- **Signal handling** (`signal`, `sigaction`, `kill`)

### File Descriptor Management
- **Redirection handling** (`dup`, `dup2`)
- **Pipe implementation** (`pipe`)
- **File operations** (`open`, `close`, `read`, `write`)

### Memory & Input
- **Readline library** for input and history
- **Proper memory management** (`malloc`, `free`)
- **Environment variable handling** (`getenv`)

## 🎯 Learning Objectives

- **Process Management**: Forking, execution, waiting
- **File Descriptors**: Redirection, piping, duplication
- **Signal Handling**: Interrupts and process control
- **Command Parsing**: Lexical analysis and interpretation
- **Memory Management**: Allocation and cleanup
- **System Programming**: Low-level OS interactions  
More info at `Infor` folder

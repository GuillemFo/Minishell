*****AI used to explain this project*****
# Minishell — As Beautiful as a Shell

## 🎯 Project Overview

**Minishell** is a system programming project that consists of building a **simple Unix shell** from scratch.

The goal is to recreate the core behavior of a standard shell such as **bash**, including command execution, environment variable handling, pipes, and redirections.

Through this project, you gain practical experience with:

* **process management**
* **file descriptor manipulation**
* **command parsing**
* **Unix signals**
* **system calls**

By implementing a shell yourself, you gain a deeper understanding of how operating systems execute programs and manage processes.

---

## 💻 What is a Shell?

A **shell** is a command-line interpreter that allows users to interact with the operating system by entering commands.

Instead of interacting directly with the kernel, users type commands into the shell, which then:

1. Parses the command
2. Locates the corresponding executable
3. Creates a process
4. Executes the program
5. Returns the result to the user

Shells such as **bash**, **zsh**, and **sh** are essential tools in Unix-based systems and are widely used for system administration, development, and automation.

---

## ⚙️ Technical Specifications

### Program Requirements

| Component              | Specification                                                 |
| ---------------------- | ------------------------------------------------------------- |
| **Program Name**       | `minishell`                                                   |
| **Language**           | C                                                             |
| **Compilation**        | `cc -Wall -Wextra -Werror`                                    |
| **Authorized Library** | `libft`                                                       |
| **External Functions** | `readline`, `fork`, `execve`, `pipe`, `dup2`, `waitpid`, etc. |

---

### Key Constraints

* ✅ Only **one global variable** allowed (used for signal handling)
* ✅ **No memory leaks** (except those caused internally by `readline`)
* ✅ Code must follow the **42 Norm**
* ✅ The program must **not crash under normal usage**
* ❌ No interpretation of **unclosed quotes**
* ❌ Only features required by the subject are implemented

---

## 🔧 Core Features

### Basic Shell Behavior

* Display a **prompt** when waiting for user input
* Maintain a **command history**
* Execute binaries using:

  * absolute paths
  * relative paths
  * executables found via `$PATH`
* Proper **signal handling**

  * `Ctrl + C` — interrupt command
  * `Ctrl + D` — exit shell
  * `Ctrl + \` — ignored

---

## 🧾 Quote Handling

The shell must correctly interpret quotes:

| Quote Type        | Behavior                                              |
| ----------------- | ----------------------------------------------------- |
| `'single quotes'` | Prevent interpretation of all special characters      |
| `"double quotes"` | Allow `$` expansion but prevent other interpretations |

---

## 🔁 Redirections

The shell supports the following redirection operators:

| Operator | Description                                  |
| -------- | -------------------------------------------- |
| `<`      | Redirect input from a file                   |
| `>`      | Redirect output to a file                    |
| `>>`     | Append output to a file                      |
| `<<`     | Here-document (read input until a delimiter) |

---

## 🔗 Pipes & Variables

### Pipes

Pipes (`|`) allow chaining commands by redirecting the output of one command to the input of another.

Example:

```
ls -l | grep minishell
```

---

### Environment Variables

The shell must expand environment variables using `$`.

Examples:

```
echo $HOME
echo $PATH
```

Special variable:

```
$?
```

Expands to the **exit status of the last executed command**.

---

## 🛠 Built-in Commands

The shell implements the following built-in commands:

* `echo` (with `-n`)
* `cd` (with relative or absolute paths)
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

These commands are executed **directly by the shell**, without calling external programs.

---

## 🛠 Technical Implementation

### Process Management

* Command execution using **`fork()`**
* Program execution using **`execve()`**
* Process synchronization using:

  * `wait()`
  * `waitpid()`

---

### File Descriptor Management

* **Redirections** handled using `dup()` and `dup2()`
* **Pipes** implemented using `pipe()`
* File handling using:

  * `open()`
  * `close()`
  * `read()`
  * `write()`

---

### Input & Memory Management

* **Readline library** used for command input and history
* Dynamic memory allocation using:

  * `malloc`
  * `free`
* Environment variable handling through `getenv`

---

## 🎯 Learning Objectives

This project focuses on core concepts in **Unix system programming**:

* **Process creation and control**
* **File descriptor manipulation**
* **Signal handling**
* **Command parsing and tokenization**
* **Memory management**
* **Low-level operating system interaction**

---

## 📚 Additional Information

More implementation details and documentation can be found in the **`Infor`** folder.

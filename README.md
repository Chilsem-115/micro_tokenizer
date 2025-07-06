
# 🦦 micro\_tokenizer

> A malloc-free, lightweight tokenizer for microcontrollers and minimalist shells.

---

## 🧠 Overview

**micro\_tokenizer** is a lightweight shell-style tokenizer built specifically for **resource-constrained systems** like the ESP32.
It avoids dynamic memory allocation and heavy dependencies, making it ideal for microcontroller shells and embedded interpreters.

---

## ✨ Features

* ✅ **Zero heap allocation** — all stack/static memory
* ✅ **Supports common shell tokens**:

  * Words, quoted strings
  * Operators: `|`, `||`, `&&`
  * Redirections: `<`, `>`, `<<`, `>>`
  * Environment variables: `$VAR`, `$?`
* ✅ **Written in pure ANSI C**
* ✅ **Fast and compact** — tuned for microcontrollers
* 🛠️ Extensible: easy to port to a linked list backend later

---

## 📦 Project Structure

```
tokenizer/
        ├── tokenize.c
        ├── tokenize.h
        └── handle_events/
            ├── control.c
            ├── quote.c
            ├── redirect.c
            ├── word.c
            └── errors/
                └── err_handler.c
```

* `local_lib/`: optional libraries (optional)
* `Makefile`: build system for the shell/tokenizer

---

## 🚀 Usage

Include the tokenizer in your project:

```c
#include "tokenize.h"

char *line = "echo $USER && cat < file.txt";
char **tokens = tokenize(line);

// Do something with the tokens...
```

---

## 🧪 Token Types

Each token is classified under a `t_tokentype` enum:

```c
TOK_WORD         // Bare word
TOK_SQUOTE       // 'single quoted string'
TOK_DQUOTE       // "double quoted string"
TOK_PIPE         // |
TOK_OR           // ||
TOK_AND          // &&
TOK_REDIR_IN     // <
TOK_REDIR_OUT    // >
TOK_HEREDOC      // <<
TOK_REDIR_APPEND // >>
TOK_ENV_VAR      // $VARIABLE
TOK_EXIT_STATUS  // $?
```

---

## 🔧 Building

Use the provided `Makefile`:

```bash
make
./mesh
```

Make sure you have `libreadline` installed if you're compiling the full shell example.

---

## 💡 Future Plans

* [ ] Replace static token array with linked list (optional mode)
* [ ] Add support for grouped commands (e.g., `(cmd1 && cmd2)`)
* [ ] Optional escaping support for special characters
* [ ] CI tests and tokenizer fuzzing

---

## 🛡️ License

MIT License — do whatever you want, just don’t claim you wrote it first.

---

## 👤 Author

Built with embedded sanity by \[@chilsem].

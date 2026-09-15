*This project was created as part of the 42 curriculum by difortez.*

# get_next_line

## Description

`get_next_line` returns one line at a time from a file descriptor (a file or the standard input).
Each call returns the next line, including its `\n`, or `NULL` when there is nothing left to read
or an error occurs.

```c
char *get_next_line(int fd);
```

The project is about **static variables**: keeping the data that was read but not returned yet
between calls, whatever the `BUFFER_SIZE` is. Mandatory part only (no bonus).

## Instructions

Compile the function with your program. `BUFFER_SIZE` defaults to `42`.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I. get_next_line.c get_next_line_utils.c tests/main.c -o gnl
./gnl tests/normal.txt          # read from a file
printf 'a\nb\nc' | ./gnl        # read from stdin
```

Every returned line must be freed by the caller.

## Algorithm

The static variable is a **linked list**: each node holds one chunk as returned by `read`.
Between calls it only keeps the leftover after the last `\n` (or `NULL`).

Each call:

1. **Read** chunks into new nodes until the last node contains a `\n` or `read` returns `0`.
2. **Build** the line: measure up to the `\n`, allocate once and copy.
3. **Clean**: copy the leftover to a new node and free the rest of the list.

Example with `BUFFER_SIZE=4` and `"linea uno\nlinea dos\n"`:

```
read:   ["line"] -> ["a un"] -> ["o\nli"]
build:  "linea uno\n"
clean:  ["li"]
```

**Why a list:** chunks are only linked while reading, so each line is copied once instead of
joining strings on every `read`. Buffers live on the heap, so a huge `BUFFER_SIZE` does not
overflow the stack.

**Errors:** if `read` returns `-1` or a `malloc` fails, the whole list is freed and the function
returns `NULL`.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C](https://en.cppreference.com/w/c/language/storage_duration)
- [Valgrind Quick Start](https://valgrind.org/docs/manual/quick-start.html)

### AI usage

AI was used as a tutor to understand the underlying C concepts and to find bugs in
code I had written myself; the project files (`get_next_line.c`, `get_next_line_utils.c`,
`get_next_line.h`) are my own work.

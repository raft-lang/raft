## Standard library

### `std.fs`

This module contains methods for manipulating the contents of the local file system.

Example:

```rust
use std;

file = "test.txt";
data = "some data";

// Write and read.
std.fs.write_string(file, data);
assert std.fs.read_to_string(file) == data;

// Remove file.
std.fs.remove(file);
```

### `std.io`

This module provides support for various I/O types.

Example:

```rust
use std;

// Write to stderr.
std.io.stderr.write("some data");

// Create bytes stream in memory.
b = std.io.BytesIO(b"\x00\x01");

// Change 2nd byte.
b.getbuffer()[1] = 0xff;
assert b.getvalue() == b"\x00\xff";

// Close stream.
// `b.getvalue()` will panic from now.
b.close();
```

### `std.thread`

This module provides support for threads.

Example:

```rust
use std;

/// Maps list on 4 threads.
fn parallel_map(f: Callable, x: list) -> list {
    x = list(x);
    n = int(len(x) / 4);
    result = [None] * 4;

    fn func(i: int, a: list) {
        result[i] = list(map(f, a));
    }

    // Spawn threads.
    threads = [];
    threads.append(std.thread.spawn(func(3, x[n*3:])));
    threads.append(std.thread.spawn(func(2, x[n*2:n*3])));
    threads.append(std.thread.spawn(func(1, x[n:n*2])));
    threads.append(std.thread.spawn(func(0, x[:n])));

    // Join all threads.
    for t in threads {
        t.join();
    }
    
    return sum(result, []);
}

fn inc(n: int) -> int { return n + 1; }
assert parallel_map(inc, range(0x8000)) == list(map(inc, range(0x8000)));
```

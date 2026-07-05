# eva_explorer

A simple C CLI tool that opens any file, reads its raw bytes, and displays them in a readable hex + ASCII format.

## What it does

`eva_explorer` lets you inspect the binary contents of any file directly from the terminal.

It displays:

* **Offset** – the byte position inside the file.
* **Bytes** – the raw file data shown in hexadecimal.
* **ASCII** – the printable text representation of those bytes.

Non-printable characters are shown as `.`.

## Current Features

* Opens any file in binary mode.
* Finds the full file size.
* Reads file contents into memory.
* Prints a formatted hex dump.
* Shows 16 bytes per row.
* Groups bytes with extra spacing every 4 bytes.
* Displays ASCII output beside the hex bytes.
* Supports reading from a specific offset.
* Supports limiting how many bytes are read.
* Handles invalid flags.
* Handles file open errors.
* Handles memory allocation failure.
* Handles `fseek`, `ftell`, `fread`, and `fclose` errors.
* Frees allocated memory after use.
* Reads only the required bytes when `--offset` and `--limit` are used.

## Usage

```bash
./eva_explorer <file_path>
```

Example:

```bash
./eva_explorer main.c
```

With offset and limit:

```bash
./eva_explorer <file_path> --offset <start_in_hex> --limit <bytes>
```

Example:

```bash
./eva_explorer main.c --offset 20 --limit 64
```

This starts reading from offset `0x20` and reads `64` bytes.

## Output Format

```text
OFFSET             BYTES                                                                            ASCII
----------------------------------------------------------------------------------------------------------------

00000000          2F  2A  20  42    69  6E  61  72    79  20  65  78    70  6C  6F  72         /* Binary explor
```

Each row contains:

* The offset in hexadecimal.
* Up to 16 bytes in hexadecimal.
* The ASCII version of those bytes.

## Why I built this

The goal of this project is to understand files at the byte level.

Before working on bigger systems programming projects, game engine internals, memory systems, asset loaders, or binary formats, I wanted to first build a tool that shows what files actually look like in memory.

This project helped me practice:

* File handling in C.
* Binary reading.
* Pointers.
* Dynamic memory allocation.
* Error handling.
* Hex formatting.
* ASCII interpretation.
* Command-line arguments.
* Offset-based file inspection.

## Build

Using GCC:

```bash
gcc main.c -o eva_explorer
```

Run:

```bash
./eva_explorer main.c
```

## Current Limitations

* The flag order must currently be:

```bash
--offset <value> --limit <value>
```

* Offset is read as hexadecimal.
* Limit is read as decimal.
* The tool currently prints output only to the terminal.
* No search or interactive navigation yet.

## Status

This is the first working version of `eva_explorer`.

It can open a file, read bytes, apply offset and limit, and print a clean hex + ASCII dump.

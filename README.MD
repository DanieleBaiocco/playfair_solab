# Playfair Cipher in C

This project is a command-line implementation of the **Playfair cipher**, a classical encryption technique that works on pairs of letters rather than on single characters.

The program reads a configurable key file, builds a **5×5 Playfair grid**, and uses that grid to encrypt or decrypt one or more text files. The project is written in **C99** and is intended as an educational implementation of the main ideas behind the Playfair cipher: key-based grid construction, digraph processing, substitution rules, preprocessing, and file-based input/output.

## How the project works

The Playfair cipher works on **digraphs**, meaning pairs of characters.

A 5×5 matrix is built from a key. Because the English alphabet contains 26 letters while the matrix contains only 25 cells, one letter must be omitted and mapped to another one. In the example included with this project, the alphabet omits `J`, which is replaced by `I`.

For each pair of letters, the program applies the standard Playfair geometric rules:

- if both letters are on the same row, each letter is replaced by the letter to its right;
- if both letters are in the same column, each letter is replaced by the letter below it;
- otherwise, the two letters form the corners of a rectangle and are replaced by the letters on the other two corners of the same rows.

Decryption applies the inverse rules.

Before encryption, the implementation also performs some preprocessing. Spaces are encoded so that they can be restored after decryption, the missing alphabet character is replaced according to the key-file configuration, and a special character is used for padding and repeated-character handling.

Encrypted output is written to a file with the `.pf` extension, while decrypted output is written to a `.dec` file.

## Project structure

The most relevant files are:

```text
.
├── main.c
├── playfair.c
├── playfair.h
├── utility.c
├── utility.h
├── deallocate.c
├── deallocate.h
├── CMakeLists.txt
└── example/
    ├── key.txt
    ├── message.txt
    └── results/
        ├── message.pf
        └── message.dec
```

The repository already contains a complete runnable example in the `example/` directory.

## Requirements

You need a C compiler with C99 support, such as **GCC**.

On Windows, one convenient option is GCC through **MSYS2 / MinGW-w64**. On Linux, GCC is usually available through the system package manager. The project can also be built with CMake.

## Build with GCC

From the root directory of the project:

### Windows / MSYS2

```bash
gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair.exe
```

### Linux / macOS

```bash
gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair
```

## Build with CMake

Alternatively:

```bash
cmake -S . -B build
cmake --build build
```

The exact location and name of the generated executable may depend on the operating system and CMake generator.

## Command-line usage

The program uses the following syntax:

```text
playfair (encode|decode) <keyfile> <output_directory> <file> [additional_files...]
```

The output directory must already exist.

### Encode

On Windows / MSYS2:

```bash
./playfair.exe encode <keyfile> <output_directory> <input_file>
```

On Linux / macOS:

```bash
./playfair encode <keyfile> <output_directory> <input_file>
```

The generated encrypted file has the same base name as the input file and the `.pf` extension.

For example:

```text
message.txt -> message.pf
```

### Decode

On Windows / MSYS2:

```bash
./playfair.exe decode <keyfile> <output_directory> <encrypted_file>
```

On Linux / macOS:

```bash
./playfair decode <keyfile> <output_directory> <encrypted_file>
```

The generated decrypted file uses the `.dec` extension.

For example:

```text
message.pf -> message.dec
```

The program writes its result to files rather than printing the encrypted or decrypted message directly to the terminal.

## Key-file format

The key file is not just a plain key phrase. It contains the configuration used to build the Playfair grid.

The example `example/key.txt` contains:

```text
ABCDEFGHIKLMNOPQRSTUVWXYZ
I
X
INTERESTING AND DIFFICULT KEY
```

The lines have the following meaning:

1. `ABCDEFGHIKLMNOPQRSTUVWXYZ` — the 25-character alphabet used by the 5×5 matrix;
2. `I` — the replacement character for the missing letter (`J` in this example);
3. `X` — the special character used by the preprocessing logic;
4. `INTERESTING AND DIFFICULT KEY` — the key used to construct the Playfair grid.

Duplicate key characters do not need to be removed manually: the grid-construction logic handles them while building the matrix.

## Included terminal example

The repository includes a ready-to-run example in `example/`.

The plaintext in:

```text
example/message.txt
```

is:

```text
THIS IS AN IMPORTANT MESSAGE BE CAREFULL
```

The output directory is:

```text
example/results/
```

### 1. Encrypt the example

After compiling, run:

```bash
./playfair.exe encode example/key.txt example/results example/message.txt
```

On Linux/macOS, use `./playfair` instead of `./playfair.exe`.

The program creates:

```text
example/results/message.pf
```

For the included key and message, the encrypted content is:

```text
NM SC QV SC QV GT QV TB BP IE GT RW WB ID GD DN QV OI QV LS IR GY KW
```

You can inspect it from the terminal with:

```bash
cat example/results/message.pf
```

### 2. Decrypt the encrypted file

Run:

```bash
./playfair.exe decode example/key.txt example/results example/results/message.pf
```

The program creates:

```text
example/results/message.dec
```

Its content is:

```text
THIS IS AN IMPORTANT MESSAGE BE CAREFUL
```

You can inspect it with:

```bash
cat example/results/message.dec
```

A complete terminal session therefore looks like:

```bash
$ gcc -std=c99 main.c playfair.c utility.c deallocate.c -o playfair.exe

$ ./playfair.exe encode example/key.txt example/results example/message.txt

$ cat example/results/message.pf
NM SC QV SC QV GT QV TB BP IE GT RW WB ID GD DN QV OI QV LS IR GY KW

$ ./playfair.exe decode example/key.txt example/results example/results/message.pf

$ cat example/results/message.dec
THIS IS AN IMPORTANT MESSAGE BE CAREFUL
```

No console output after `encode` or `decode` is necessarily an error: during a normal run, the program primarily communicates its result by creating the corresponding `.pf` or `.dec` file.

## Input notes

The current implementation is intended primarily for uppercase alphabetic text and spaces.

With the example configuration:

- `J` is converted to `I`;
- spaces are internally represented in a reversible form and restored during decryption;
- `Z` is escaped internally so it can coexist with the space marker;
- `X` is used as the special/padding character.

For predictable results, use uppercase text and avoid unsupported punctuation or arbitrary symbols.

This is an educational implementation, and some edge cases involving repeated letters and the special character may not round-trip byte-for-byte. For example, the bundled plaintext ends with `CAREFULL`, while the bundled decrypted result is `CAREFUL`.

## Multiple files

The program can process more than one file in a single command.

For example:

```bash
./playfair.exe encode key.txt output file1.txt file2.txt file3.txt
```

Each input file is processed independently and written to the selected output directory.

## Notes

The project is intended mainly for learning and experimentation with classical cryptography and C programming. The Playfair cipher is historically interesting, but it is **not secure for modern cryptographic use** and should not be used to protect sensitive information.

# [Assignment-1: File Operation [Building a FTP]][def1]

## File Operation in C

A file is a container in computer storage devices which is used for storing output or information permanently in the form of a sequence of bytes on the disk.

In C, you can perform various file handling operations like creating a file, deleting a file, opening a file, reading a file or you can even manipulate the data inside of a file. You can also work with the data in your program code by fetching it from a file. You can perform various file handling operations in C. In C, we can use file handling functions for various types of file manipulation like create, update, read or delete the files on the local file system. Below are the operations that you can perform on a file:-

- Creating a new file.
- Opening an existing file.
- Reading from a file.
- Writing to a file.
- Deleting a file.

### Assignment-1: Copy the one file from one location to another location using binary mode that is Binary File Handling

Binary File Handling is a process in which we create a file and store data in its original format. It means that if we stored an integer value in a binary file, the value will be treated as an integer rather than text.

Binary files are mainly used for storing records just as we store records in a database. It makes it easier to access or modify the records easily.

> **Hints:**
>
> ```c
> #include <stdint.h>
> #include <stdio.h>
> int main() {
>     FILE *input_file, *output_file;
>     input_file = fopen("XXXXX", "rb");
>     output_file = fopen("YYYYY", "wb");
>     int buffer;
>     while (!feof(input_file)) {
>         fread();
>         fwrite();
>     }
>     fclose("XXXXX");
>     fclose("YYYYY");
>     printf("\n done\n");
>     return 0;
> }
> ```

---

## Solution

- Go to the directory and open the terminal.

- Run the [`copy.c`][def2] file using the below command:

  ```bash
  gcc copy.c -o copy
  ```

- Run the `copy` file using the below command:

  ```bash
  ./copy
  ```

- To compare the below code, run the [`compare.c`][def3] file using the velow command:

  ```bash
  gcc compare.c -o compare
  ```

- Run the `compare` file using the below command:

  ```bash
  ./compare
  ```

- Alternatively, you can use the `diff` command to compare the two files:

  ```bash
  diff source.bin destination.bin
  ```

  or,

  ```bash
  cmp source.bin destination.bin
  ```

  If you show no output, then there is no difference in [`source.bin`][def4] and `destination.bin` file. Your programme have successfully copied the content of the code.

[def1]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-1
[def2]: ./copy.c
[def3]: ./compare.c
[def4]: ./source.bin

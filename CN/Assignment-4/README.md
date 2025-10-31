# [Assignment-4: TCP/UDP Client-Server Implementation with String Manipulation, Online Calculator & Heterogeneous File transfer][def1]

## Part-1: String Manipulation & Online Calculator

### Objective

There are a number of objectives to this assignment beyond just a simple socket programming assignment. First, if you have not ever programmed sockets before, it is relatively straightforward, but still an effort. It is worthwhile to have everyone on the same page in terms of experience, at least in this respect. Second, it will help you "tune up" your programming skills and prepare you for other upper-division networking courses. Third, because you can use the Internet to look for examples, this assignment will help you see just how many network programming aids are out in the Internet. And finally, having some practical experience will put a lot of the protocol concepts we learn into perspective.

### Assignment

The goal of this assignment is to implement a TCP client and server, and a UDP client and server (that’s four different programs all told).

Your TCP or UDP client/server will communicate over the network (same machine using local loop) and exchange data.

The server will start in passive mode listening for a transmission from the client. The client will then start and contact the server (on a given IP address and port number). The client will pass the server a string (eg: `network`) up to $80$ characters in length.

**1. String Operation in Server Side:** The client will pass the server a string (eg: `network`) up to $100$ characters in length.

On receiving a string from a client, the server should:

- reverse all the characters
- reverse the capitalization of the strings (`network` would now become `KROWTEN`).

The server should then send the string back to the client. The client will display the received string and exit.

**2. Online Calculator:** The client will pass the server a string (example `a+b*c/d`) with values (example $a=10$,$b=15$, $c=5$ and $d=3$ etc.)

On receiving data/string from the client the server calculate the value and result will send to client side. The client will display the received result and exit.

```txt
43
Turned in
1
Assigned
```

## Part-2: Multiple File Transfers from the Server using TCP & UDP Protocol

[![Image][def2]][def2]

---

## Solution

### Part-1

#### String Manipulation

- Go to the directory and open the terminal.

- Run the [`tcp_server.c`][def7] file using the below command:

  ```bash
  gcc tcp_server.c -o tcp_server
  ```

- Run the `tcp_server` file using the below command:

  ```bash
  ./tcp_server
  ```

- Open another terminal and run the [`tcp_client.c`][def8] file using the below command:

  ```bash
  gcc tcp_client.c -o tcp_client
  ```

- Run the `tcp_client` file using the below command:

  ```bash
  ./tcp_client
  ```

- The server will ask for the string to be manipulated. Write the input string in the client terminal. An example string given below:

  ```txt
  Enter a string (max 256 characters): network
  ```

  [![Client terminal][def10]][def10]

- The resulted manipulated string has been shown in client terminal.

  [![Server terminal][def9]][def9]

The above string manipulation is implemented using TCP protocol. Now, we are implementing the UDP protocol.

- Run the [`udp_server.c`][def11] file using the below command:

  ```bash
  gcc udp_server.c -o udp_server
  ```

- Run the `udp_server` file using the below command:

  ```bash
  ./udp_server
  ```

- Open another terminal and run the [`udp_client.c`][def12] file using the below command:

  ```bash
  gcc udp_client.c -o udp_client
  ```

- Run the `udp_client` file using the below command:

  ```bash
  ./udp_client
  ```

- The server will ask for the string to be manipulated. Write the input string in the client terminal. An example string given below:

  ```txt
  Enter a string (max 256 characters): network
  ```

  [![Client terminal][def14]][def14]

- The resulted manipulated string has been shown in client terminal.

  [![Server terminal][def13]][def13]

#### Online Calculator

- Go to the directory and open the terminal.

- Run the [`tcp_calc_server.c`][def3] file using the below command:

  ```bash
  gcc tcp_calc_server.c -o tcp_calc_server
  ```

- Run the `tcp_calc_server` file using the below command:

  ```bash
  ./tcp_calc_server
  ```

- Open another terminal and run the [`tcp_calc_client.c`][def4] file using the below command:

  ```bash
  gcc tcp_calc_client.c -o tcp_calc_client
  ```

- Run the `tcp_calc_client` file using the below command:

  ```bash
  ./tcp_calc_client
  ```

- Now give the expression and the variables. A sample expresion and variable is given below.

  ```txt
  Expression: a+b*c/d
  Variables: a=10,b=15,c=5,d=3
  ```

  [![Server terminal][def5]][def5]

- The server will return the results.

  [![Client terminal][def6]][def6]

### Part-2

- Go to the directory and open the terminal.

- Run the [`server.c`][def15] file using the below command:

  ```bash
  gcc server.c -o server
  ```

- Run the `server` file using the below command:

  ```bash
  ./server
  ```

- Open another terminal and run the [`client.c`][def16] file using the below command:

  ```bash
  gcc client.c -o client
  ```

- Run the `client` file using the below command:

  ```bash
  ./client
  ```

- Now give the folder names that you want to be compared.

  - [`folder1`][def19] before comparison.

    [![Folder-1][def17]][def17]

  - [`folder2`][def20] before comparison.

    [![Folder-2][def18]][def18]

  Here is the sample command for comparison and transfer of folders.

  ```txt
  Enter path of folder-1: folder1
  Enter path of folder-2: folder2
  Enter filename/folder to request: folder2
  ```

- The client is requested for the files.

  [![Client terminal][def22]][def22]

- The server will transfer the files.

  [![Server terminal][def21]][def21]

- [`folder1`][def19] after transfer (added the files of folder2).

  [![Folder-1][def23]][def23]

- [`folder2`][def20] after transfer (remains same).

  [![Folder-2][def24]][def24]

[def1]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-4
[def2]: ../images/img_17.png
[def3]: ./tcp_calc_server.c
[def4]: ./tcp_calc_client.c
[def5]: ../images/img_20.png
[def6]: ../images/img_21.png
[def7]: ./tcp_server.c
[def8]: ./tcp_client.c
[def9]: ../images/img_22.png
[def10]: ../images/img_23.png
[def11]: ./udp_server.c
[def12]: ./udp_client.c
[def13]: ../images/img_24.png
[def14]: ../images/img_25.png
[def15]: ./server.c
[def16]: ./client.c
[def17]: ../images/img_26.png
[def18]: ../images/img_27.png
[def19]: ./folder1/
[def20]: ./folder2/
[def21]: ../images/img_28.png
[def22]: ../images/img_29.png
[def23]: ../images/img_30.png
[def24]: ../images/img_31.png

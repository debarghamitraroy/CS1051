# [Assignment-5: Reliable File Transfer using UDP Protocol][def1]

Implement naive flow control mechanism using **(a)** stop & wait protocol and **(b)** Selective and Repeat Protocol. Transfer files (Text, Image, Audio, Video) using UDP protocol. If during the connection suddenly connection is terminated then you have start ones again, it simply resume the process not start from beginning.

Write a socket program in C for Multimodal File Transmission using UDP with Full-Duplex Stop and Wait protocol. The program/protocol should support the following properties/mechanism

1. The protocol will send any type of files

2. Each packet should consist of the file name, sequence number/Acknowledgement number

3. A log file should be generated with some information like,

List of uncommon files in server and client which are to be transferred, Start time, If the connection is broken then the $\%$ of the file already uploaded, How many times connections were established during the complete transmission, End time (when the file is fully transmitted), How many packets are lost, How many time-outs are occurred, etc.

## Objective

Implement a reliable file transfer system over the UDP protocol. Since UDP itself is unreliable (packets may be lost, duplicated, or arrive out of order), you must design a mechanism to ensure reliability using techniques such as segmentation, sequencing, acknowledgments, and retransmission.

## Tasks

- ### File Segmentation

  Divide the file into fixed-size segments (e.g., $1$ KB each). Each segment should contain metadata:

  - Sequence Number
  - File Name / File Identifier
  - Data Payload

- ### Stop-and-Wait Protocol

  Implement a Stop-and-Wait ARQ (Automatic Repeat Request) mechanism:

  - Sender transmits one segment at a time.
  - Sender waits for an acknowledgment (ACK) from the receiver.
  - If the ACK is not received within a timeout, retransmit the segment.
  - Receiver sends ACK for each correctly received segment (use sequence number to handle duplicates).

- ### Acknowledgment Handling

  Receiver must send back an ACK containing:

  - Sequence Number of the successfully received segment
  - File identifier (to handle multiple file transfers, if extended later)

- ### Reassembly of File

  Receiver collects all the received segments in order. Write them back into the original file format after successful transfer.

> Follow this link: [https://sites.google.com/view/sscomputernetworks/class-notes][def2]

---

## Solution

- Go to the [server][def12] directory and open the terminal.

- Run the [`server.c`][def10] file using the below command:

  ```bash
  cd server
  gcc server.c -o server
  ```

- Run the `server` file using the below command:

  ```bash
  ./server
  ```

- Now go to the [client][def13] directory and open another terminal and run the [`client.c`][def11] file using the below command:

  ```bash
  gcc client.c -o client
  ```

- Run the `client` file using the below command:

  ```bash
  ./client
  ```

- Now give the folder names that you want to be compared.

  - [`server`][def12] folder before transfer content.

    [![server folder][def14]][def14]

  - [`client`][def13] folder before transfer content.

    [![client folder][def15]][def15]

- The client is requested for the files.

  [![client terminal][def17]][def17]

- The server will transfer the files.

  [![Server terminal][def16]][def16]

- [`client`][def13] after transfer (added the files of folder2).

  [![client folder][def18]][def18]

---

> - Open [WireShark][def3] and click on `Loopback: lo` to capture the packets.
>
>   [![WireShark Capture][def4]][def4]
>
> - Now go to the [WireShark][def3] window and filter the packets by typing below command in the filter bar.
>
> ```ini
> udp.port == 8080
> ```
>
> - Go to the directory and open the terminal.
>
> - Open another terminal and build the [`sender.c`][def5] and [`receiver.c`][def6] by running the below command:
>
> ```bash
> make
> ```
>
> - Open the terminal and start the receiver (listen on all interfaces on `port 8080`, no simulated loss).
>
> ```bash
> ./receiver 127.0.0.1 8080 ./output 0
> ```
>
> - Open another terminal and Run the sender (send [`test.txt`][def7] to receiver at `127.0.0.1:8080`; no simulated loss).
>
> ```bash
> ./sender 127.0.0.1 8080 ./output/test.txt 0
> ```
>
> [![Data Folder][def8]][def8]
>
> - After completion, the receiver writes `received_test.txt`.
>
> [![Output Folder][def9]][def9]
>
> - **Testing Retransmissions**
>
> - Open a terminal and run the below command.
>
>   ```bash
>   ./sender 127.0.0.1 8080 ./data/test.txt 20
>   ```
>
> - Open another terminal and run below comman.
>
>   ```bash
>   ./receiver 0.0.0.0 8080 ./output 20
>   ```

[def1]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-5
[def2]: https://sites.google.com/view/sscomputernetworks/class-notes
[def3]: https://www.wireshark.org/
[def4]: ../images/img_01.png
[def5]: ./sender.c
[def6]: ./receiver.c
[def7]: ./data/test.txt
[def8]: ../images/img_18.png
[def9]: ../images/img_19.png
[def10]: ./server/server.c
[def11]: ./client/client.c
[def12]: ./server/
[def13]: ./client/
[def14]: ../images/img_32.png
[def15]: ../images/img_33.png
[def16]: ../images/img_34.png
[def17]: ../images/img_35.png
[def18]: ../images/img_36.png

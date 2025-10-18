# Assignment-4: Reliable File Transfer over UDP

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

---

## Solution

- Open [WireShark][def1] and click on `Loopback: lo` to capture the packets.

  [![WireShark Capture][def2]][def2]

- Now go to the [WireShark][def1] window and filter the packets by typing below command in the filter bar.

  ```ini
  udp.port == 9999
  ```

- Go to the directory and open the terminal.

- Open another terminal and build the [`sender.c`][def3] and [`receiver.c`][def4] by running the below command:

  ```bash
  make
  ```

- Open the terminal and start the receiver (listen on all interfaces on `port 9999`, no simulated loss).

  ```bash
  ./receiver 0.0.0.0 9999 . 0
  ```

- Open another terminal and Run the sender (send [`source.bin`][def5] to receiver at `127.0.0.1:9999`; no simulated loss).

  ```bash
  ./sender 127.0.0.1 9999 source.bin 0
  ```

- After completion, the receiver writes `received_source.bin`.

- **Testing Retransmissions**

  - Open a terminal and run the below command.

    ```bash
    ./sender 127.0.0.1 9999 source.bin 20
    ```

  - Open another terminal and run below comman.

    ```bash
    ./receiver 0.0.0.0 9999 . 20
    ```

  [![WireShark Packet Capture][def6]][def6]

[def1]: https://www.wireshark.org/
[def2]: ../images/img_01.png
[def3]: ./sender.c
[def4]: ./receiver.c
[def5]: ./source.bin
[def6]: ../images/img_17.png

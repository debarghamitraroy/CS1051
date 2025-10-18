# [Assignment 2: Analysis of TCP/IP Protocol Stack][def1]

1. Write simple TCP and UDP program using socket API which will transfer simple text messages, and check TCP and UDP packets using [WireShark][def2] (Check Annexure I, Copy the codes and execute it in `gcc`)

2. Using [WireShark][def2], capture the TCP headers while connecting your computer to the server of [`nitdgp.ac.in`][def3].

3. (a) Show how the six flags (`SYN`, `ACK`, `PUSH`, `URGENT`, `RST`, `FIN`) are working in TCP protocol?

   (b) What is the IP address of [`nitdgp.ac.in`][def3]? On what port number is it sending and receiving TCP segments for this connection?

   (c) Write a small socket program for the `URGENT` pointer and `URGENT` flag.

   (d) What is the sequence number of the TCP `SYN` segment that is used to initiate the TCP connection between the client computer and [`nitdgp.ac.in`][def3]?

   (e) What is it in the segment that identifies the segment as a `SYN` segment?

   (f) What is the sequence number of the `SYN-ACK` segment sent by [`nitdgp.ac.in`][def3] to the client computer in reply to the `SYN`?

   (g) What is the value of the Acknowledgement field in the `SYN-ACK` segment?

   (h) How did [`nitdgp.ac.in`][def3] determine that value?

   (i) What is it in the segment that identifies the segment as a `SYN-ACK` segment?

---

## Solution

### Solution-1

- Open [WireShark][def2] and click on `Loopback: lo` to capture the packets.

  [![WireShark Capture][def4]][def4]

- Go to the directory and open the terminal.

- Run the [`udpserver.c`][def5] file using the below command:

  ```bash
  gcc udpserver.c -o udpserver
  ```

- Run the `udpserver` file using the below command:

  ```bash
  ./udpserver
  ```

- Open another terminal and run the [`udpclient.c`][def6] file using the below command:

  ```bash
  gcc udpclient.c -o udpclient
  ```

- Run the `udpclient` file using the below command:

  ```bash
  ./udpclient
  ```

- Try to send some messages from the client terminal.

- You can see the UDP packets in the [WireShark][def2] window.

  [![UDP Packet Capture][def9]][def9]

- Now, stop the UDP server and client by pressing `Ctrl + C`.

- Now, run the [`tcpserver.c`][def7] file using the below command:

  ```bash
  gcc tcpserver.c -o tcpserver
  ```

- Run the `tcpserver` file using the below command:

  ```bash
  ./tcpserver
  ```

- Open another terminal and run the [`tcpclient.c`][def8] file using the below command:

  ```bash
  gcc tcpclient.c -o tcpclient
  ```

- Run the `tcpclient` file using the below command:

  ```bash
  ./tcpclient
  ```

- Try to send some messages from the client terminal.

- You can see the TCP packets in the [WireShark][def2] window.

  [![TCP Packet Capture][def10]][def10]

### Solution-2

- Open [WireShark][def2] and click on `wlo1` to capture the packets.

  [![WireShark Capture][def22]][def22]

- To find the IP address of [`nitdgp.ac.in`][def3], run the below command in terminal:

  ```bash
  nslookup nitdgp.ac.in
  ```

  [![IP Address Capture][def11]][def11]

- Install `telnet` and `curl` if not installed.

  ```bash
  sudo apt install telnet curl
  ```

- Open terminal and run the below command to connect to the server of [`nitdgp.ac.in`][def3]:

  ```bash
  telnet nitdgp.ac.in 80
  ```

  or,

  ```bash
  curl http://nitdgp.ac.in
  ```

  or,

  Alternatively, you can also open any browser and go to [`nitdgp.ac.in`][def3].

  [![WireShark Capture][def12]][def12]

- Now go to the [WireShark][def2] window and filter the packets by typing below command in the filter bar.

  ```ini
  ip.addr == 14.139.221.27 && tcp
  ```

- You can see the TCP packets in the [WireShark][def2] window.

  [![TCP Packet Capture][def13]][def13]

### Solution-3 (a)

|  Flag  |                     Description                     |
| :----: | :-------------------------------------------------: |
| `SYN`  |             Used to start a connection.             |
| `ACK`  |             Acknowledges received data.             |
| `PUSH` |     Forces delivery of data without buffering.      |
| `URG`  | Marks urgent data, indicated by the urgent pointer. |
| `RST`  |             Resets a broken connection.             |
| `FIN`  |            Finishes/closes a connection.            |

### Solution-3 (b)

- To find the IP address of [`nitdgp.ac.in`][def3], run the below command in terminal:

  ```bash
  nslookup nitdgp.ac.in
  ```

  The output will show the IP address as:

  ```bash
  Server: 127.0.0.53
  Address: 127.0.0.53#53

  Non-authoritative answer:
  Name: nitdgp.ac.in
  Address: 14.139.221.27
  ```

  So, the IP address of [`nitdgp.ac.in`][def3] is $14.139.221.27$.

- The port number used for HTTP is $80$ and for HTTPS is $443$.

### Solution-3 (c)

- Open [WireShark][def2] and click on `Loopback: lo` to capture the packets.

  [![WireShark Capture][def4]][def4]

- Type the below filter in the filter bar to filter the TCP packets with URG flag set.

  ```ini
  tcp.flags.urg == 1 && tcp.port == 8080
  ```

  [![URG Flag Filter][def14]][def14]

- Go to the directory and open the terminal.

- Run the [`urgentserver.c`][def15] file using the below command:

  ```bash
  gcc urgentserver.c -o urgentserver
  ```

- Run the `urgentserver` file using the below command:

  ```bash
  ./urgentserver
  ```

- Open another terminal and run the [`urgentclient.c`][def16] file using the below command:

  ```bash
  gcc urgentclient.c -o urgentclient
  ```

- Run the `urgentclient` file using the below command:

  ```bash
  ./urgentclient
  ```

### Solution-3 (d)

- Open [WireShark][def2] and click on `wlo1` to capture the packets.

  [![WireShark Capture][def22]][def22]

- Open terminal and run the below command to connect to the server of [`nitdgp.ac.in`][def3]:

  ```bash
  telnet nitdgp.ac.in 80
  ```

  or,

  ```bash
  curl http://nitdgp.ac.in
  ```

  or,

  Alternatively, you can also open any browser and go to [`nitdgp.ac.in`][def3].

  [![WireShark Capture][def17]][def17]

- Now go to the [WireShark][def2] window and filter the packets by typing below command in the filter bar.

  ```ini
  ip.addr == 14.139.221.27 && tcp
  ```

- You can see the TCP packets in the [WireShark][def2] window.

  [![TCP Packet Capture][def18]][def18]

- In the top packet list, look for the **first TCP packet** from your IP $\rightarrow 14.139.221.27$ with Info column showing `SYN`.

- Click on that packet to see the details in the middle pane.

  [![SYN Packet][def19]][def19]

- Expand the `Transmission Control Protocol` section. The Sequence Number (raw) field shows the sequence number of the TCP `SYN` segment.

  [![SYN Packet Details][def20]][def20]

  In this case, the sequence number (raw) is $2805640763$.

  > The sequence number of the TCP `SYN` segment sent by the client computer to [`nitdgp.ac.in`][def3] was $2805640763$ (this value is chosen randomly by the client’s TCP stack). In Wireshark, it is displayed as $0$ in relative terms.

### Solution-3 (e)

- In the same `Transmission Control Protocol` section, look for the `Flags` field.

  [![SYN Packet Flags][def21]][def21]

So, The thing that identifies the segment as a `SYN` segment is:

- The `SYN` flag is set to $1$ in the TCP header’s Flags field, while
- The `ACK` flag is $0$ (since this is the very first packet from the client).

  > The segment is identified as a `SYN` segment because the `SYN` flag is set in the TCP header (Flags field). In Wireshark, this appears as `Flags: 0x002` (`SYN`).

### Solution-3 (f)

- Open [WireShark][def2] and click on `wlo1` to capture the packets.

  [![WireShark Capture][def22]][def22]

- Open terminal and run the below command to connect to the server of [`nitdgp.ac.in`][def3]:

  ```bash
  telnet nitdgp.ac.in 80
  ```

  or,

  ```bash
  curl http://nitdgp.ac.in
  ```

  or,
  Alternatively, you can also open any browser and go to [`nitdgp.ac.in`][def3].

  [![WireShark Capture][def17]][def17]

- Now go to the [WireShark][def2] window and filter the packets by typing below command in the filter bar.

  ```ini
  ip.addr == 14.139.221.27 && tcp
  ```

- You can see the TCP packets in the [WireShark][def2] window.

  [![TCP Packet Capture][def23]][def23]

- In the top packet list, look for the **second TCP packet** from your IP $\rightarrow 14.139.221.27$ with Info column showing `SYN, ACK`.

- Click on that packet to see the details in the middle pane.

  [![SYN-ACK Packet][def24]][def24]

So, The Sequence Number of the `SYN-ACK` segment is the server’s own Initial Sequence Number (ISN).

> The sequence number of the `SYN-ACK` segment sent by [`nitdgp.ac.in`][def3] was $3427571096$ (server’s Initial Sequence Number). Wireshark shows this as $0$ in relative numbering for readability.

### Solution-3 (g)

> The value of the Acknowledgement field in the `SYN-ACK` segment is equal to the client’s Initial Sequence Number plus $1$. In our capture, Wireshark displayed it as $1$ (relative), corresponding to the client’s `ISN + 1` ie. $3549778751$ i this case.

[![SYN-ACK Acknowledgement][def24]][def24]

### Solution-3 (h)

> [`nitdgp.ac.in`][def3] determined the value of the Acknowledgement field by taking the Initial Sequence Number (ISN) from the client’s `SYN` segment and adding $1$. This is required because the `SYN` flag consumes one sequence number, so the next expected byte from the client is `ISN + 1`.

[![SYN-ACK Acknowledgement][def24]][def24]

### Solution-3 (i)

> The segment is identified as a `SYN-ACK` segment because in the TCP header, both the `SYN` flag and the `ACK` flag are set (`SYN = 1`, `ACK = 1`). This distinguishes it from the initial `SYN` (which has `ACK = 0`) and from later pure `ACK` packets (which have `SYN = 0`, `ACK = 1`).

[![SYN-ACK Packet Flags][def24]][def24]

[def1]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-2
[def2]: https://www.wireshark.org/
[def3]: https://nitdgp.ac.in/
[def4]: ../images/img_01.png
[def5]: ./udpserver.c
[def6]: ./udpclient.c
[def7]: ./tcpserver.c
[def8]: ./tcpclient.c
[def9]: ../images/img_02.png
[def10]: ../images/img_03.png
[def11]: ../images/img_04.png
[def12]: ../images/img_05.png
[def13]: ../images/img_06.png
[def14]: ../images/img_07.png
[def15]: ./urgentserver.c
[def16]: ./urgentclient.c
[def17]: ../images/img_08.png
[def18]: ../images/img_09.png
[def19]: ../images/img_10.png
[def20]: ../images/img_11.png
[def21]: ../images/img_12.png
[def22]: ../images/img_13.png
[def23]: ../images/img_14.png
[def24]: ../images/img_15.png

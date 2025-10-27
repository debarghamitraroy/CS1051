# [Assignment-3: Wireshark Analysis of TCP/UDP Communication and Protocol Behavior][def6]

## Data Transmission Under the Microscope: Wireshark's Watchful Eye

1. Install Wireshark on your computer: Begin by downloading and installing Wireshark, a network protocol analyzer, to monitor and capture network traffic.

2. **Run a simple TCP Client and Server code:** Create and execute a basic TCP client-server code to establish a connection between two devices, allowing data exchange.

3. Examine how data packets traverse the five communication layers: Utilize Wireshark to analyze the journey of data packets through the five TCP/IP layers, including physical, data link, network, transport, and application layers.

4. Observe the three-way handshake process, data transmission, and acknowledgment procedures: Investigate the TCP three-way handshake, which involves SYN, SYN-ACK, and ACK packets. Monitor the transmission of data packets and the acknowledgment process that ensures reliable data delivery.

5. **Execute a basic UDP server code:** Develop and run a simple UDP (User Datagram Protocol) server code to facilitate communication via a connectionless protocol.

6. **Investigate how UDP packets travel through the TCP/IP protocol stack:** Use Wireshark to track the path of UDP packets as they navigate through the layers of the TCP/IP protocol stack, which includes the network and transport layers.

7. **Analyze the use of the DHCP protocol for handling UDP packets:** Explore the role of the DHCP (Dynamic Host Configuration Protocol) in assigning IP addresses and other network configuration parameters to devices, which often involves the use of UDP packets for communication.

By following these steps and leveraging Wireshark's capabilities, you can gain valuable insights into network communication, protocols, and packet behavior.

---

## Solution

- Open [WireShark][def2] and click on `Loopback: lo` to capture the packets.

  [![WireShark Capture][def3]][def3]

- Go to the directory and open the terminal.

- Run the [`server.c`][def5] file using the below command:

  ```bash
  gcc server.c -o server
  ```

- Run the `server` file using the below command:

  ```bash
  ./server
  ```

- Open another terminal and run the [`client.c`][def6] file using the below command:

  ```bash
  gcc client.c -o client
  ```

- Run the `client` file using the below command:

  ```bash
  ./client
  ```

- Now, you can see the packets being captured in WireShark and the audio file is transferred from the client to the server.

  [![WireShark Capture][def4]][def4]

- There will be a new file named `received_audio.wav` in the directory.

  [![Received Audio][def5]][def5]

[def1]: ./audio.wav
[def2]: https://www.wireshark.org/
[def3]: ../images/img_01.png
[def4]: ../images/img_16.png
[def5]: ../images/img_17.png
[def6]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-3

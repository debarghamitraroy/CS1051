# Networking Lab

## Course Overview

- **Assignment-1**: File Operation (Building a FTP)

  | Sl. No. | Task Description                                                                                        |  Problem Statement Link   |  Solution Link   |
  | :-----: | :------------------------------------------------------------------------------------------------------ | :-----------------------: | :--------------: |
  |   1 .   | Copy the one file from one location to another location using binary mode that is Binary File Handling. | [Problem Statement][def1] | [Solution][def2] |

- **Assignment-2**: Analysis of TCP/IP Protocol Stack

  | Sl. No. | Task Description                                                                                                                                 |  Problem Statement Link   |   Solution Link   |
  | :-----: | :----------------------------------------------------------------------------------------------------------------------------------------------- | :-----------------------: | :---------------: |
  |   1 .   | Write simple TCP and UDP program using socket API which will transfer simple text messages, and check TCP and UDP packets using WireShark.       | [Problem Statement][def3] | [Solution][def4]  |
  |   2.    | Using WireShark, capture the TCP headers while connecting your computer to the server of `nitdgp.ac.in`                                          | [Problem Statement][def3] | [Solution][def5]  |
  | 3. (a)  | Show how the six flags (`SYN`, `ACK`, `PUSH`, `URGENT`, `RST`, `FIN`) are working in TCP protocol?                                               | [Problem Statement][def3] | [Solution][def6]  |
  | 3. (b)  | What is the IP address of `nitdgp.ac.in`? On what port number is it sending and receiving TCP segments for this connection?                      | [Problem Statement][def3] | [Solution][def7]  |
  | 3. (c)  | Write a small socket program for the `URGENT` pointer and `URGENT` flag?                                                                         | [Problem Statement][def3] | [Solution][def8]  |
  | 3. (d)  | What is the sequence number of the TCP `SYN` segment that is used to initiate the TCP connection between the client computer and `nitdgp.ac.in`? | [Problem Statement][def3] | [Solution][def9]  |
  | 3. (e)  | What is it in the segment that identifies the segment as a `SYN` segment?                                                                        | [Problem Statement][def3] | [Solution][def10] |
  | 3. (f)  | What is the sequence number of the `SYN-ACK` segment sent by `nitdgp.ac.in` to the client computer in reply to the `SYN`?                        | [Problem Statement][def3] | [Solution][def11] |
  | 3. (g)  | What is the value of the Acknowledgement field in the `SYN-ACK` segment?                                                                         | [Problem Statement][def3] | [Solution][def12] |
  | 3. (h)  | How did `nitdgp.ac.in` determine that value?                                                                                                     | [Problem Statement][def3] | [Solution][def13] |
  | 3. (i)  | What is it in the segment that identifies the segment as a `SYN-ACK` segment?                                                                    | [Problem Statement][def3] | [Solution][def14] |

- **Assignment-3:** Transfer an audio file (audio.wav) from a client to a server using UDP.

  | Sl. No. | Task Description                                                        |   Problem Statement Link   |   Solution Link   |
  | :-----: | :---------------------------------------------------------------------- | :------------------------: | :---------------: |
  |   1 .   | Transfer an audio file (audio.wav) from a client to a server using UDP. | [Problem Statement][def15] | [Solution][def16] |

- **Assignment-4:** Reliable File Transfer over UDP.

  | Sl. No. | Task Description                                                                                                                                                                                                                                                                                     |   Problem Statement Link   |   Solution Link   |
  | :-----: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :------------------------: | :---------------: |
  |   1 .   | Implement a reliable file transfer system over the UDP protocol. Since UDP itself is unreliable (packets may be lost, duplicated, or arrive out of order), you must design a mechanism to ensure reliability using techniques such as segmentation, sequencing, acknowledgments, and retransmission. | [Problem Statement][def17] | [Solution][def18] |

## Installation Instructions

### Download [WireShark][def19]

- Enter the following command in your terminal to download WireShark:

  ```bash
  sudo apt update
  sudo apt install gcc wireshark
  ```

- During the installation, you will be prompted with a question: **`"Should non-superusers be able to capture packets?"`** Select **`Yes`** to allow non-superusers to capture packets.

  ```bash
  sudo usermod -a -G wireshark $USER
  sudo dpkg-reconfigure wireshark-common
  sudo chmod +x /usr/bin/dumpcap
  ```

- After installation, you can launch WireShark by typing `wireshark` in your terminal.

  ```bash
  wireshark
  ```

### Video Tutorial

If you need help with the installation or want to learn how to use WireShark, you can watch the following video tutorial.

**Video link:** [Wireshark Tutorial for Beginners | Network Scanning Made Easy](https://www.youtube.com/watch?v=qTaOZrDnMzQ)

[![Watch the video][def20]][def21]

## Useful Websites and YouTube Videos

- [sscomputernetworks][def22]
- [Stop & Wait Protocol Implementation using Socket Programming][def23]

[def1]: ./Assignment-1/README.md#assignment-1-copy-the-one-file-from-one-location-to-another-location-using-binary-mode-that-is-binary-file-handling
[def2]: ./Assignment-1/README.md#solution
[def3]: ./Assignment-2/README.md#assignment-2-analysis-of-tcpip-protocol-stack
[def4]: ./Assignment-2/README.md#solution-1
[def5]: ./Assignment-2/README.md#solution-2
[def6]: ./Assignment-2/README.md#solution-3-a
[def7]: ./Assignment-2/README.md#solution-3-b
[def8]: ./Assignment-2/README.md#solution-3-c
[def9]: ./Assignment-2/README.md#solution-3-d
[def10]: ./Assignment-2/README.md#solution-3-e
[def11]: ./Assignment-2/README.md#solution-3-f
[def12]: ./Assignment-2/README.md#solution-3-g
[def13]: ./Assignment-2/README.md#solution-3-h
[def14]: ./Assignment-2/README.md#solution-3-i
[def15]: ./Assignment-3/README.md#assignment-3-udp-audio-file-transfer
[def16]: ./Assignment-3/README.md#solution
[def17]: ./Assignment-4/README.md#tasks
[def18]: ./Assignment-4/README.md#solution
[def19]: https://www.wireshark.org/
[def20]: https://img.youtube.com/vi/qTaOZrDnMzQ/hqdefault.jpg
[def21]: https://www.youtube.com/watch?v=qTaOZrDnMzQ
[def22]: https://sites.google.com/view/sscomputernetworks/home
[def23]: https://youtu.be/I03WOU266d0

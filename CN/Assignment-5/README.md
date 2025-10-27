# [Assignment-5: Reliable File Transfer using UDP Protocol][def1]

Implement naive flow control mechanism using **(a)** stop & wait protocol and **(b)** Selective and Repeat Protocol. Transfer files (Text, Image, Audio, Video) using UDP protocol. If during the connection suddenly connection is terminated then you have start ones again, it simply resume the process not start from beginning.

Write a socket program in C for Multimodal File Transmission using UDP with Full-Duplex Stop and Wait protocol. The program/protocol should support the following properties/mechanism

1. The protocol will send any type of files

2. Each packet should consist of the file name, sequence number/Acknowledgement number

3. A log file should be generated with some information like,

List of uncommon files in server and client which are to be transferred, Start time, If the connection is broken then the $\%$ of the file already uploaded, How many times connections were established during the complete transmission, End time (when the file is fully transmitted), How many packets are lost, How many time-outs are occurred, etc.

Follow this link: [https://sites.google.com/view/sscomputernetworks/class-notes][def2]

---

## Solution

[def1]: https://sites.google.com/view/sscomputernetworks/assignments/2024-25/assignment-5
[def2]: https://sites.google.com/view/sscomputernetworks/class-notes

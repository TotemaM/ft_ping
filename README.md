*This project has been created as part of the 42 curriculum by mmichele*
# ft_ping

This projects aims to reproduce the `ping` command from `inetutils`.

- [Instruction](#instruction)
- [Ressources](#ressources)
- [Documentation](#documentation)

## Instruction
```
apt remove iputils-ping
sudo apt-get install inetutils-ping
ping -V
```

| Command       | Description                                                                |
| :------------ | :------------------------------------------------------------------------- |
| `make`        | Compile main program and test environment                                  |
| `make clean`  | Delete only intermediate compile files                                     |
| `make fclean` | Delete all previous compiled files                                         |
| `make lsan`   | Compile main and test environment with address and memory leak sanitizers  |

It's recommended to `make clear` before compiling with different flags to avoid *bad linkings*.

`sudo` is needed to execute the program due to the protocol used on the socket.

## Ressources
1) https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
2) https://www.rfc-editor.org/info/rfc792/
3) https://en.wikipedia.org/wiki/Fully_qualified_domain_name
4) https://en.wikipedia.org/wiki/Domain_Name_System
5) https://en.wikipedia.org/wiki/Checksum
6) https://www.rfc-editor.org/info/rfc1071/

## Documentation

1) Parse input
2) [Resolve hostname](#resolve-hostname)
3) [Create ICMP socket](#create-icmp-socket)
4) Build ICMP `echo` request
5) Add timestamp and payload
6) Compute checksum
7) Send packet
8) Wait for reply
9) Validate response
10) Compute RTT
11) Display stats

### Resolve hostname

The function `gethostbyname` could've been used for simplicity, however this project uses 
`getaddrinfo` which is a bit harder to use and complete but more modern, and POSIX compliant.

Parameters of the `getaddrinfo` function :
| parameter                    | description           |
| -                            | -                     |
| const char *node             | hostname / IP address |
| const char *service          | port                  |
| const struct addrinfo *hints | result filtering      |
| struct addrinfo **res        | results               |

### Create ICMP socket

`ping` command uses [Internet Control Message Protocol](https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol), shortened ICMP.  
On the [IP Suite](https://en.wikipedia.org/wiki/Internet_protocol_suite) it can be found on the [transport layer](https://en.wikipedia.org/wiki/Transport_layer), like TCP or UDP.

So the socket transport protocol has to be defined as `IPPROTO_ICMP`.

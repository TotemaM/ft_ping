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
- https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
- https://en.wikipedia.org/wiki/Fully_qualified_domain_name

## Documentation
`ping` command uses [Internet Control Message Protocol](https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol), shortened ICMP.

The function `gethostbyname` could've been used for simplicity, however this project uses 
`getaddrinfo` which is a bit harder to use and complete but more modern, and POSIX compliant.

Parameters of the `getaddrinfo` function :
| parameter                    | description           |
| -                            | -                     |
| const char *node             | hostname / IP address |
| const char *service          | port                  |
| const struct addrinfo *hints | result filtering      |
| struct addrinfo **res        | results               |

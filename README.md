# INTERPROCESS COMMUNICATION

3 different methods of interprocess communication is implemented in 6(of 3 pairs of files) c files. Each file has the same code to generate the 50 random
strings and have the same index encoding. The index of a string is encapsulated behind the null terminating charecter of the string and is read by 
specifically pointing to index in the string, without interfering in the string handelling.
The index are ascii encapusated, the charecter correspoding to 40 in ascii table is the reference 0 index and other index mapped one to one from 40 to 90.

in all of the ipc files p1 denotes the main file, which generates the string and sends to the respective p2 file which prints and send the highest index in intervals of 5 strings, for p1 to send more strings. p1 is timed from after the random string generation and only around the read write blocks in p1.
both programs of pair can be run on seperate shell windows or suing an & between them.

## Run P1 and P2 simultaneously

After make run following command for different ipc methods

To run Named pipes 

```gcc
  ./ipc_fifo_p1 & ./ipc_fifo_p2
```

To run Named pipes after make run the following command

```gcc
  ./ipc_shm_p1 & ./ipc_shm_p2
```

To run Named pipes after make run the following command

```gcc
  ./ipc_socket_p1 & ./ipc_socket_p2
```


## Acknowledgements

 - [Lecture 5 (Sambuddho Chakravarty)](https://drive.google.com/file/d/1Rb3mEzsDxChImM1L72_5yoOQ6acMSByi/view)
 - [Xoviabcs IPC](https://www.youtube.com/watch?v=G2vwkBZy894&t=1063s)
 - [Jacob Sorber ](https://www.youtube.com/watch?v=dhFkwGRSVGk)

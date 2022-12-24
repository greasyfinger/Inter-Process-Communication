all: clean ipc_fifo_p1 ipc_fifo_p2 ipc_shm_p2 ipc_shm_p1 ipc_socket_p2 ipc_socket_p1

ipc_socket_p2: ipc_socket_p2.c
	gcc ipc_socket_p2.c -o ipc_socket_p2 -pthread

ipc_socket_p1: ipc_socket_p1.c
	gcc ipc_socket_p1.c -o ipc_socket_p1 -pthread 

ipc_shm_p2: ipc_shm_p2.c
	gcc ipc_shm_p2.c -o ipc_shm_p2 -pthread 

ipc_shm_p1: ipc_shm_p1.c
	gcc ipc_shm_p1.c -o ipc_shm_p1 -pthread 

ipc_fifo_p2: ipc_fifo_p2.c
	gcc ipc_fifo_p2.c -o ipc_fifo_p2 -pthread 

ipc_fifo_p1: ipc_fifo_p1.c
	gcc ipc_fifo_p1.c -o ipc_fifo_p1 -pthread 

clean :
	rm -f fifo_p1 fifo_p2 ipc_socket ipc_fifo_p2 ipc_fifo_p1 ipc_shm_p1 ipc_shm_p2 ipc_socket_p2 ipc_socket_p1
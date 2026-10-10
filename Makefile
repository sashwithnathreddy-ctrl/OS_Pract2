CC = gcc
CFLAGS = -Wall -Wextra -g
PTHREAD = -pthread

all: prog1 prog2 prog3 prog4 prog5 prog6_fifo_server prog6_fifo_client \
     signal_handler memory_layout memory_demo dynamic_memory cow_demo \
     copy_lowlevel copy_stdio redirect_output redirect_input \
     mmap_file race_counter safe_counter pc_semaphore \
     deadlock_demo deadlock_prevention

prog1: src/prog1.c
	$(CC) $(CFLAGS) -o src/prog1 src/prog1.c

prog2: src/prog2.c
	$(CC) $(CFLAGS) -o src/prog2 src/prog2.c

prog3: src/prog3.c
	$(CC) $(CFLAGS) -o src/prog3 src/prog3.c

prog4: src/prog4.c
	$(CC) $(CFLAGS) -o src/prog4 src/prog4.c

prog5: src/prog5.c
	$(CC) $(CFLAGS) -o src/prog5 src/prog5.c

prog6_fifo_server: src/prog6_fifo_server.c
	$(CC) $(CFLAGS) -o src/prog6_fifo_server src/prog6_fifo_server.c


signal_handler: src/signal_handler.c
	$(CC) $(CFLAGS) -o src/signal_handler src/signal_handler.c

memory_layout: src/memory_layout.c
	$(CC) $(CFLAGS) -o src/memory_layout src/memory_layout.c

memory_demo: src/memory_demo.c
	$(CC) $(CFLAGS) -o src/memory_demo src/memory_demo.c

dynamic_memory: src/dynamic_memory.c
	$(CC) $(CFLAGS) -o src/dynamic_memory src/dynamic_memory.c

cow_demo: src/cow_demo.c
	$(CC) $(CFLAGS) -o src/cow_demo src/cow_demo.c

copy_lowlevel: src/copy_lowlevel.c
	$(CC) $(CFLAGS) -O2 -o src/copy_lowlevel src/copy_lowlevel.c

copy_stdio: src/copy_stdio.c
	$(CC) $(CFLAGS) -O2 -o src/copy_stdio src/copy_stdio.c

redirect_output: src/redirect_output.c
	$(CC) $(CFLAGS) -o src/redirect_output src/redirect_output.c

redirect_input: src/redirect_input.c
	$(CC) $(CFLAGS) -o src/redirect_input src/redirect_input.c

mmap_file: src/mmap_file.c
	$(CC) $(CFLAGS) -o src/mmap_file src/mmap_file.c

race_counter: src/race_counter.c
	$(CC) $(CFLAGS) $(PTHREAD) -o src/race_counter src/race_counter.c

safe_counter: src/safe_counter.c
	$(CC) $(CFLAGS) $(PTHREAD) -o src/safe_counter src/safe_counter.c

pc_semaphore: src/pc_semaphore.c
	$(CC) $(CFLAGS) -O2 $(PTHREAD) -o src/pc_semaphore src/pc_semaphore.c

deadlock_demo: src/deadlock_demo.c
	$(CC) $(CFLAGS) $(PTHREAD) -o src/deadlock_demo src/deadlock_demo.c

deadlock_prevention: src/deadlock_prevention.c
	$(CC) $(CFLAGS) -O2 $(PTHREAD) -o src/deadlock_prevention src/deadlock_prevention.c

clean:
	rm -f src/prog1 src/prog2 src/prog3 src/prog4 src/prog5
	rm -f src/prog6_fifo_server src/prog6_fifo_client src/signal_handler
	rm -f src/memory_layout src/memory_demo src/dynamic_memory src/cow_demo
	rm -f src/copy_lowlevel src/copy_stdio src/redirect_output src/redirect_input
	rm -f src/mmap_file src/race_counter src/safe_counter src/pc_semaphore
	rm -f src/deadlock_demo src/deadlock_prevention

.PHONY: all clean

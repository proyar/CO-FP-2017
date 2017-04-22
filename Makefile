CC	= ../I-love-CO/bin/riscv64-unknown-elf-gcc
CC-HOST	= gcc
TARGET	= dip-riscv
TARGET-HOST	= dip
SPIKE	= ../I-love-CO/bin/spike
SPIKE-OPTION	= pk
#SPIKE-OPTION	=--ic=64:1:64 --dc=64:1:64 pk   (for part I example)   

CHECKER	= inspector


.PHONY: clean host run run-host
clean:
	rm -fr $(TARGET) $(TARGET-HOST) ./Output/*

host: dip.c bmp.h cnv.h 
	$(CC-HOST) -o $(TARGET-HOST) $<
riscv: dip.c bmp.h cnv.h
	$(CC) -o $(TARGET) $<



riscv-run: 
	$(SPIKE) $(SPIKE-OPTION) $(TARGET)
	./$(CHECKER)

host-run: 
	./$(TARGET-HOST)
	./$(CHECKER)

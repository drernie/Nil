#**********************************************************************
# Nil Makefile
#
# Copyright 2009-2010 by Dustin Laurence.  Distributed under the terms of
# the LGPLv3.
#
#**********************************************************************

LPPFLAGS = # -D NDEBUG

%.s : %.bc
	llc -f $<

%.dis.ll : %.bc
	llvm-dis -f $< -o $@

%.bc : %.ll
	llvm-as $<

%.ll : %.llm
	cpp $(LPPFLAGS) -nostdinc -P -x assembler-with-cpp -I. $< $@

all : nil

nil : nil.o system_c.o system_ll.o lex.o exp.o memory.o

nil.ll :    system.llh c_defs.llh nil.llh lex.llh exp.llh

lex.ll :    system.llh c_defs.llh nil.llh lex.llh

exp.ll :                          nil.llh exp.llh memory.llh

memory.ll : system.llh c_defs.llh nil.llh memory.llh exp.llh

system_ll.ll : system.llh c_defs.llh

c_defs.llh : c_defs
	./c_defs > c_defs.llh

clean :
	rm -f nil c_defs c_defs.llh *.bc *.ll *.s *.o


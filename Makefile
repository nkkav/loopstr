PASS =		loopstr

OBJS =		loopstr.o suif_pass.o
MAIN_OBJ =	suif_main.o
CPPS =		$(OBJS:.o=.cpp) $(MAIN_OBJ:.o=.cpp)
HDRS =		$(OBJS:.o=.h)

NWHDRS =
NWCPPS =

LIBS =		-lmachine -lcfg -lcfa

include $(MACHSUIFHOME)/Makefile.common

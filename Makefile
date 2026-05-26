
MFILE = $(FILE).cpp
MCFILE= $(FILE).c
GCC = g++-14
GC = gcc-14
GCCFLAGS = -Wall -Wextra -Werror -Wpedantic -Wnull-dereference  -Wshadow -mavx2 -Wconversion -Wduplicated-branches -Wlogical-op -O3  -Wformat=2   -pthread -mavx2 -march=native 
CPP23 = -std=c++23
C23 = -std=c23 
INCLUDES = -I includes -I src 
COMPILE.cc = $(GCC) $(GCCFLAGS) $(INCLUDES) $(CPP23)
COMPILE.c = $(GC) $(GCCFLAGS) $(INCLUDES) $(C23)
vpath %.c src 
vpath %.cc src 
vpath %.cpp src 
vpath %.h includes 

run : $(MFILE) $(HARGS)
	$(COMPILE.cc) $<  -o $(FILE) && ./$(FILE)  

runc : $(MCFILE) $(HARGS)
	$(COMPILE.c) $<  -o $(FILE) && ./$(FILE)  
create: 
	touch src/$(MFILE) && touch src/$(MCFILE)
pp: 
	git add . && git commit -m "letsg"
online: 
	git commit origin main 
push : 
	git add  . && git commit -m "mesas" && git push origin main

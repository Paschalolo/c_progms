
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
OBJ_DIR = src
OBJS = $(wildcard $(OBJ_DIR)/*.o)
vpath %.c src 
vpath %.cc src 
vpath %.cpp src 
vpath %.h includes 


runc : $(MCFILE) $(HARGS)
	$(COMPILE.c) $<  -o $(FILE) && ./bin/$(FILE)  
run : $(MCFILE)
	$(COMPILE.c) $<   -o ./bin/ch $(HFILE) && ./bin/ch 
clean : 
	rm -rf *.o
object : $(MCFILE) $(HARGS)
	$(COMPILE.c) -c  $< -o ./src/$(FILE).o

special : 
	@echo "Here we are"
	@echo "wassup "
oshared: $(MFILE) $(HARGS)
	$(COMPILE.c) -fPIC -c  $< -o ./src/$(FILE).o
create: 
	touch src/$(MCFILE)
push : 
	git add . && git commit -m"message " && git push origin main 

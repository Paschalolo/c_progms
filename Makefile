MFILE = $(FILE).c
PFILE = $(FILE).cpp
GCC = gcc-14
GPP = g++-14
GCCFLAGS = -Wall -Wextra -Werror -Wpedantic -Wnull-dereference  -Wshadow -Wconversion -Wduplicated-branches -Wlogical-op -O3  -Wformat=2   -pthread -Wuse-after-free=3  -Wdangling-pointer=2 -Winit-self
C23 = -std=c23
CPP23 = -std=c++23
INCLUDES = -I includes -I src 
COMPILE.c = $(GCC) $(GCCFLAGS) $(INCLUDES) $(C23)
COMPILE.cc = $(GPP) $(GCCFLAGS) $(INCLUDES) $(CPP23)
OBJ_DIR = src
OBJS = $(wildcard $(OBJ_DIR)/*.o)
vpath %.c src 
vpath %.cc src 
vpath %.cpp src 
vpath %.h includes 

run : $(MFILE) $(HARGS)
	$(COMPILE.c) $< $(HARGS)  -o ./bin/ch && ./bin/ch
exec : $(OBJS) 
	$(COMPILE.c) $(OBJS)  -o bin && ./bin  	
object : $(MFILE) $(HARGS)
	$(COMPILE.c) -c  $< -o ./src/$(FILE).o

oshared: $(MFILE) $(HARGS)
	$(COMPILE.c) -fPIC -c  $< -o ./src/$(FILE).o
create: 
	touch src/$(MFILE)
create1: 
	touch src/$(PFILE)
push : 
	git add . && git commit -m"message " && git push origin main 

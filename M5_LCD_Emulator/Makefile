# sudo apt install libopencv-dev opencv-data

PROG=m5hello
SRCS=main.cpp M5Stack.cpp M5Emulator.cpp
CVLIBS=-lopencv_core -lopencv_highgui -lopencv_imgproc

OBJS=$(SRCS:.cpp=.o)

CPPFLAGS=-g -O3

all: $(PROG)

$(PROG): $(OBJS)
	g++ -o $@ $? $(CVLIBS)

%.o:%.cpp
	g++ -c $(CPPFLAGS) -DLINUX $< -o $@

clean:
	rm *.o $(PROG)



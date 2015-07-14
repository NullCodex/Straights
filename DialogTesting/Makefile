CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = helloworld.o MyDialogBox.o main.o TurnDialog.o
EXEC = hello

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

helloworld.o: helloworld.h helloworld.cc
main.o: helloworld.h main.cc TurnDialog.h
MyDialogBox.o: MyDialogBox.h MyDialogBox.cc
TurnDialog.o: TurnDialog.h TurnDialog.cc

clean:
	rm $(EXEC) $(OBJS)

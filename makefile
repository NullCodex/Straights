CXX= g++
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = subject.o model.o controller.o DeckGUI.o view.o main.o GameDialog.o
EXEC = mvc

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

DeckGUI.o: DeckGUI.h DeckGUI.cpp
model.o: subject.h model.h model.cpp
subject.o: subject.h subject.cpp
controller.o: controller.h model.h controller.cpp
view.o: view.h observer.h controller.h model.h subject.h DeckGUI.h view.cpp
main.o: view.h controller.h model.h main.cpp
GameDialog.o: GameDialog.h GameDialog.cpp


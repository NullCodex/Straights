CXX= g++
CXXFLAGS = -Wall -MMD -O -g `pkg-config gtkmm-2.4 --cflags` -std=c++0x
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = Card.o Deck.o Player.o Human.o Computer.o Table.o Command.o Game.o subject.o model.o controller.o DeckGUI.o view.o main.o GameDialog.o
EXEC = mvc

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)
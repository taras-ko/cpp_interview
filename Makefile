CXXFLAGS += -std=c++0x -g -Wl,--no-as-needed -Wall

%:
	$(CXX) $@.cpp $(CXXFLAGS) $(LDFLAGS)
#$(CXX) $@.cpp $(CXXFLAGS) $(LDFLAGS) $(shell pkg-config --libs --cflags glib-2.0)

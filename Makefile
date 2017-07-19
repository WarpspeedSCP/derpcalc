src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CXXFLAGS = -DDEBUG -g
LDFLAGS = -lncurses

calculator: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

derpcalc: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) derpcalc


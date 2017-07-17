src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

DBGFLAGS = -DDEBUG -g
LDFLAGS = -lncurses

derpcalc-debug: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(DBGFLAGS)

derpcalc: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) derpcalc


src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lncurses

derpcalc: $(obj)
    $(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
    rm -f $(obj) derpcalc


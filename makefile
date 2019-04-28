CXX = g++
CXXFLAGS = -Wall -g -std=c++11

src = $(wildcard src/*.cc) \
		$(wildcard src/driver/*.cc) \
		$(wildcard src/pager/*.cc) \
		$(wildcard src/io/*.cc) \
		$(wildcard src/memref/*.cc)

obj = $(src:.cc=.o)

exec: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) exec

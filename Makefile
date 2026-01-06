BINNAME   =   pr1_IA_lds

SRCDIR		     =		src

CXX				=		g++
CXXFLAGS	=		-g -std=c++17

SRCS = $(shell find $(SRC_DIR) -name '*.cc')

all: $(BINNAME)

$(BINNAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

clean:
	rm -f ./$(BINNAME)
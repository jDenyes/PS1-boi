NAME = emu
CXX = g++
RM = rm
DEBUG = no

LIB = -l m
INCLUDE = -I include

LDFLAGS = $(LIB)

ifeq ($(DEBUG), no)
LDFLAGS += -s
endif

SRC = main.cpp \
	addr.cpp \
	BIOS.cpp \
	bus.cpp \
	cpu.cpp \
	op_code.cpp \

DPD = $(SRC:.cpp=.dpd)
OBJ     =   $(SRC:.cpp=.o)
all : $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(DPD)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) -C .

%.dpd : %.cpp
	$(CXX) -MM $(<) -o $(@) $(CXXFLAGS) -MT $(<:.cpp=.o)

%.o : %.cpp
	$(CXX) -c $(<) -o $(@) $(CXXFLAGS)

.PHONY : all clean fclean re %.dpd %.o

.SUFFIXES : .o.cpp .dpd.cpp

include $(DPD)
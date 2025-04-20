NAME = libft_json.a

SRCS = JSON.cpp

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MD -I$(INC_DIR)

AR = ar
ARFLAGS = -crs

RM = rm -rf
MKDIR = mkdir -p

OBJ = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEP = $(OBJ:.o=.d)

.DEFAULT_GOAL = all

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	@$(MKDIR) $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEP)

.PHONY: all bonus clean fclean re

all: $(NAME)

clean:
	$(RM) $(BUILD_DIR)

fclean:
	$(RM) $(BUILD_DIR) $(NAME)

re: fclean
	@$(MAKE)

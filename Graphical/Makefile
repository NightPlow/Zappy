##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile of the source file
##

ROOT		=	..

CURRENT_DIR	=	Graphical

SRC_DIR		=	sources

TEST_DIR	=	tests

CXX	    	=	g++

NAME		=	zappy_graphical

TEST		=	tests_run

BUILD		=	build

MAIN		:=	main.cpp	\

SRC			:=	protocol/ServerInteraction.cpp	\
				InputParser.cpp	\
				Errors.cpp	\
				App.cpp	\

TEST_SRC	:=	test_InputParser.cpp	\
				test_Game.cpp

INCLUDES	=	-I includes

CXXFLAGS	=	$(INCLUDES) $(WARN) -pipe -march=native -std=c++17

LDFLAGS		=	-L ./GraphicalAPI/ -lGraphicalAPI -lsfml-graphics -lsfml-system -lsfml-window

TESTFLAGS	=	$(CXXFLAGS)

WARN		=	-Wall -Wextra

LIB		?=	1

DEB		?=	0

G		=	-g -D DEBUG

V		?=	@


MAIN_PREFIXED		:=	$(addprefix $(SRC_DIR)/, $(MAIN))
SRC_PREFIXED		:=	$(addprefix $(SRC_DIR)/, $(SRC))
TEST_SRC_PREFIXED	:=	$(addprefix $(TEST_DIR)/, $(TEST_SRC))

MAIN_OBJ		:=	$(patsubst $(SRC_DIR)/%.cpp, $(BUILD)/%.o, $(MAIN_PREFIXED))
OBJS			:=	$(patsubst $(SRC_DIR)/%.cpp, $(BUILD)/%.o, $(SRC_PREFIXED))
TEST_OBJS		:=	$(patsubst $(TEST_DIR)/%.cpp, $(BUILD)/%.o, $(TEST_SRC_PREFIXED))

#COLOR

GREEN		=	\e[1;32m

WHITE		=	\e[0m

ORANGE		=	\e[1;33m

RED		 	=	\e[1;35m

BLUE		=	\e[1;34m


debug:			CXXFLAGS += $(G)

##
## Directives
##

all:		$(NAME)

$(NAME):	OBJS += $(MAIN_OBJ)
$(NAME):	$(BUILD)/$(NAME)
			$(V)printf "$(GREEN)Duping binary.$(WHITE)\n"
			$(V)cp $(BUILD)/$(NAME) $(NAME)

build_tests:		CXXFLAGS += --coverage
build_tests:		LDFLAGS	+= -lcriterion --coverage
build_tests:		OBJS +=	$(TEST_OBJS)
build_tests:		fclean graphic_api $(BUILD)/$(TEST) #find a solution to remove fclean rule
					$(V)printf "$(GREEN)Duping binary.$(WHITE)\n"
					$(V)cp $(BUILD)/$(TEST) $(TEST)

$(TEST): build_tests
		$(V)printf "$(GREEN)Executing tests for $(NAME):$(WHITE)\n"
		$(V)./tests_run -f

debug:			 echo_d $(NAME)

release:		 fclean echo_r $(NAME)

$(BUILD)/$(NAME):	graphic_api $(MAIN_OBJ) $(OBJS)
			$(V)printf "$(GREEN)Compile sources.$(WHITE)\n"
			$(V)$(CXX) -o $(BUILD)/$(NAME) $(OBJS) $(LDFLAGS)
			$(V)printf "$(GREEN)Linking obj and Libraries.$(WHITE)\n"

$(BUILD)/$(TEST):	$(OBJS) $(TEST_OBJS)
					$(V)printf "$(GREEN)Compile sources.$(WHITE)\n"
					$(V)$(CXX) -o $(BUILD)/$(TEST) $(OBJS) $(LDFLAGS)
					$(V)printf "$(GREEN)Linking obj and Libraries.$(WHITE)\n"

$(BUILD)/%.o:		$(SRC_DIR)/%.cpp
			$(V)mkdir -p $(dir $@)
			$(V)printf "$(BLUE)Compiling [$(GREEN)$(notdir $<)$(BLUE) -> $(RED)$(notdir $@)$(BLUE)]\n$(WHITE)"
			$(V)$(CXX) -o $@ -c $< $(CXXFLAGS)

$(BUILD)/%.o:		$(TEST_DIR)/%.cpp
			$(V)mkdir -p $(dir $@)
			$(V)printf "$(BLUE)Compiling [$(GREEN)$(notdir $<)$(BLUE) -> $(RED)$(notdir $@)$(BLUE)]\n$(WHITE)"
			$(V)$(CXX) -o $@ -c $< $(TESTFLAGS)

graphic_api:
			$(V)make --no-print-directory -C $(ROOT)/$(CURRENT_DIR)/GraphicalAPI

clean:
			$(V)make clean --no-print-directory -C $(ROOT)/$(CURRENT_DIR)/GraphicalAPI
			$(V)rm -f $(OBJS)
			$(V)rm -f $(TEST_OBJS)
			$(V)rm -f $(MAIN_OBJ)
			$(V)rm -rf $(BUILD)
			$(V)printf "$(ORANGE)Removing object files.$(WHITE)\n"

fclean:		clean
			$(V)make fclean --no-print-directory -C $(ROOT)/$(CURRENT_DIR)/GraphicalAPI
			$(V)rm -f $(BUILD)/$(NAME)
			$(V)rm -f $(BUILD)/$(TEST)
			$(V)rm -f $(NAME)
			$(V)rm -f $(TEST)
			$(V)printf "$(ORANGE)Removing binary file.$(WHITE)\n"

re:			fclean all

echo_build:
			$(V)printf "$(GREEN)Begin of the build !\n$(ORANGE)Warnings : \n$(WHITE)"

echo_d:
			$(V)printf "$(RED)DEBUG MODE initialized.$(WHITE)\n";

echo_r:
			$(V)printf "$(RED)RELEASE MODE initialized.$(WHITE)\n";

.PHONY:		 clean fclean debug all re echo_debug buildrepo build_tests

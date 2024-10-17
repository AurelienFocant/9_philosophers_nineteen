#-------------------------PROGRAM NAME------------------------#
NAME							=	philo
all:							$(NAME)

MAKEFLAGS						=	--no-print-directory

#---------------------------COMPILER--------------------------#
CC								=	cc
CFLAGS							=	-Wall -Wextra -Werror
CFLAGS							+=	-g3

LINK	=	$(shell ld -v 2>&1 | grep --quiet GNU && gold -v)
ifneq ($(LINK),)
	LDFLAGS			=	-fuse-ld=gold
else
	LDFLAGS			=	-fuse-ld=ld
endif

COMPILER						=	$(CC) $(CFLAGS)
LINKER							=	$(CC) $(LDFLAGS) $(CFLAGS)
ARCHIVER						=	ar -rcs

#-------------------------SOURCE FILES------------------------#
SRC_DIR							=	src
SRC_SUBDIRS						=	$(shell find $(SRC_DIR)/* -type d)
SRC_FILES						=	$(shell find $(SRC_DIR) -type f -name "*.c")

#-------------------------OBJECT FILES------------------------#
OBJ_DIR							=	.build
OBJ_SUBDIRS						=	$(SRC_SUBDIRS:$(SRC_DIR)%=$(OBJ_DIR)%)
OBJ_FILES						=	$(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) $(CPPFLAGS) -c $< -o $@

#--------------------------DEPENDENCIES-----------------------#
DEPS							=	$(OBJ_FILES:.o=.d)
-include $(DEPS)
CPPFLAGS						=	-MMD -MP

#----------------------------HEADERS--------------------------#
INC_DIR							=	include
CPPFLAGS						+=	-I$(INC_DIR)
CPPFLAGS						+=	-I$(LIBFT_DIR)/$(INC_DIR)

#---------------------------LINKING---------------------------#
$(NAME):	$(OBJ_FILES)
	$(LINKER) $(OBJ_FILES) -o $@

#---------------------------CLEANING--------------------------#
clean:
	@rm -rf $(OBJ_DIR)

fclean:		clean
	@rm -rf $(NAME)
	@echo  "$(NAME) fully cleaned"

re:		fclean all

.PHONY: all clean fclean re
#-------------------------------------------------------------#

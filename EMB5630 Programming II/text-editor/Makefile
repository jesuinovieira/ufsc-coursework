TARGET = Editor
CC = gcc

CFLAGS = -std=c99 -Wall -I.

LINKER = gcc
LFLAGS = -g -Wall -Werror -Wextra -I.

SRCDIR = sources
OBJDIR = obj
BINDIR = bin
LIBDIR = header

SOURCES	:= $(wildcard $(SRCDIR)/*.c)
LIB	:= $(wildcard $(LIBDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC	:= $($(BINDIR)/$(TARGET))
rm	= rm -f

all: $(BINDIR)/$(TARGET)
	$(info EDITOR DE TEXTO - por Jesuino Vieira Filho)
	$(info Universidade Federal de Santa Catarina (Campus Joinville) - 2017/1)
	$(info Programacao II)
	$(info --------------------------------------------------------)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Arquivos gerados com sucesso!"
	@echo "--------------------------------------------------------"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(LIB)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Gerando arquivo objeto "$@

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Arquivos objetos apagados."

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Arquivo executavel apagado."

run: $(EXEC)
	@cd bin; ./$(TARGET)

TARGET = BatalhaNaval
CC = g++

CCFLAGS = -std=c++14 -Wall -Wextra -g -Os

LINKER = g++
LFLAGS = -g -Wall -Werror -Wextra 

SRCDIR = sources
OBJDIR = obj
BINDIR = bin
LIBDIR = header

SOURCES	:= $(wildcard $(SRCDIR)/*.cpp)
LIB	:= $(wildcard $(LIBDIR)/*.hpp)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC	:= $($(BINDIR)/$(TARGET))
rm	= rm -f

all: $(BINDIR)/$(TARGET)
	$(info Batalha Naval - por Jesuino Vieira Filho)
	$(info Universidade Federal de Santa Catarina (Campus Joinville) - 2017/2)
	$(info Programacao III)
	$(info ------------------------------------------------------------------)
	$(info Para escolher o tipo de jogo:)
	$(info Jogador contra Jogador:			$$ make ARGS="JxJ" run;)
	$(info Jogador contra Ambiente [Facil]:	$$ make ARGS="JxA F" run;)
	$(info Jogador contra Ambiente [Dificil]:	$$ make ARGS="JxA D" run;)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Arquivos gerados com sucesso!"
	@echo "------------------------------------------------------------------"
	@echo 

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(LIB)
	@$(CC) $(CCFLAGS) -c $< -o $@
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
	@cd bin; ./$(TARGET) ${ARGS}

# Compilador C++
CXX = g++

# Opções de compilação
CXXFLAGS = -std=c++11 -Wall

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Obtenha o nome do arquivo de entrada da linha de comando
ifeq ($(strip $(file)),)
    $(error Usage: make file=arquivo.cpp)
endif

# Nome do arquivo de saída baseado no nome do arquivo de entrada
OUTPUT = $(BUILD_DIR)/$(basename $(notdir $(file)))

all: $(OUTPUT)

$(OUTPUT): $(file)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: all run clean

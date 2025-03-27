# Makefile fusionado: funcionalidades del usuario y generador

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Ilib
LDFLAGS =
TARGET = make

# Carpetas
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = trash

# Crear carpeta para los archivos objeto si no existe
$(shell mkdir -p $(OBJ_DIR))
# Archivos fuente y objetos
SRC = $(wildcard $(SRC_DIR)/*.cc)
LIB = $(wildcard $(LIB_DIR)/*.h)
OBJ = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC))

# Compilación del proyecto
all: build

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Reglas para compilar cada archivo fuente a objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Eliminación del archivo comprimido
tar_clean:
	@if [ -z "$(DIR)" ]; then \
	    echo "Error: Debes especificar un directorio usando 'make tar_clean DIR=<directorio>'"; \
	    exit 1; \
	fi
	rm -f "$(DIR).tgz"

# Formateo de archivos según la guía de estilo de Google
format:
	@files=$$(find -type f \( -name '*.cc' -o -name '*.h' \)); \
	if [ -n "$$files" ]; then \
	    echo "Formateando los siguientes archivos:"; \
	    echo "$$files"; \
	    clang-format -i --style=Google $$files; \
	else \
	    echo "No hay archivos para formatear en $(SRC_DIR) o $(LIB_DIR)."; \
	fi

# Creación de un archivo comprimido de un directorio específico
tar:
	@read -p "Introduce el directorio a comprimir: " dir; \
	if [ ! -d "$$dir" ]; then \
	    echo "Error: El directorio $$dir no existe."; \
	    exit 1; \
	fi; \
	BASE_DIR=$$(dirname "$$dir"); \
	ARCHIVE_NAME=$$(basename "$$dir").tgz; \
	echo "Creating archive $$BASE_DIR/$$ARCHIVE_NAME"; \
	tar --exclude="$$dir/$$ARCHIVE_NAME" -czvf "$$BASE_DIR/$$ARCHIVE_NAME" "$$dir"

# Commit y push a git con un mensaje personalizado
git:
	@read -p "Introduce el mensaje del commit: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push

# Regla para limpiar el comprimido
distclean: clean tar_clean

# Alias para construir y formatear
build_and_format: format build

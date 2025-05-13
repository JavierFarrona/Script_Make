# Makefile para TypeScript

# Variables
TSC = tsc
SRC_DIR = src
DIST_DIR = dist
FILES = $(wildcard $(SRC_DIR)/*.ts)
OUT_FILES = $(patsubst $(SRC_DIR)/%.ts,$(DIST_DIR)/%.js,$(FILES))

# Directorios
$(shell mkdir -p $(DIST_DIR))

# Regla principal para compilar el proyecto
all: build

# Compilar los archivos TypeScript en JavaScript
build: $(OUT_FILES)

$(DIST_DIR)/%.js: $(SRC_DIR)/%.ts
	$(TSC) --outDir $(DIST_DIR) $<

# Limpiar los archivos compilados
clean:
	rm -rf $(DIST_DIR)

# Formateo con Prettier (opcional, si tienes Prettier instalado)
format:
	prettier --write $(SRC_DIR)/**/*.ts

# Crear un archivo comprimido con el código fuente y los archivos compilados
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

# Regla para generar un archivo README.md (opcional)
readme:
	@read -p "Nombre de la práctica: " practica; \
	read -p "Asignatura: " asignatura; \
	read -p "Curso: " curso; \
	read -p "Cuatrimestre: " cuatri; \
	read -p "Autor: " autor; \
	echo "# 🧪 Práctica $$practica" > README.md; \
	echo "**Asignatura:** $$asignatura" >> README.md; \
	echo "**Grado:** Nombre del grado o carrera" >> README.md; \
	echo "**Curso:** $$curso" >> README.md; \
	echo "**Cuatrimestre:** $$cuatri" >> README.md; \
	echo "**Autor:** $$autor" >> README.md; \
	echo "" >> README.md; \
	echo "---" >> README.md; \
	echo "## 📄 Descripción" >> README.md; \
	echo "Breve descripción de la práctica y sus objetivos." >> README.md; \
	echo "" >> README.md; \
	echo "---" >> README.md; \
	echo "## 📁 Estructura del proyecto" >> README.md; \
	echo "- \`src/\`: Archivos fuente (.ts)" >> README.md; \
	echo "- \`dist/\`: Archivos compilados (.js)" >> README.md; \
	echo "- \`Makefile\`: Script de construcción" >> README.md; \
	echo "- \`README.md\`: Este documento" >> README.md; \
	echo "" >> README.md; \
	echo "---" >> README.md; \
	echo "## ⚙️ Compilación y ejecución" >> README.md; \
	echo '```bash' >> README.md; \
	echo "make       # Compila el proyecto" >> README.md; \
	echo "node dist/main.js       # Ejecuta el binario generado" >> README.md; \
	echo '```' >> README.md; \
	echo "" >> README.md; \
	echo "---" >> README.md; \
	echo "## 🔍 Detalles técnicos" >> README.md; \
	echo "- Lenguaje: TypeScript" >> README.md; \
	echo "- Compilador: tsc" >> README.md; \
	echo "- Formato: Prettier (opcional)" >> README.md; \
	echo "" >> README.md; \
	echo "---" >> README.md; \
	echo "## 📝 Conclusiones" >> README.md; \
	echo "Aquí puedes escribir reflexiones personales, problemas encontrados o ideas de mejora." >> README.md; \
	echo "" >> README.md; \
	echo "README.md generado correctamente." >> README.md
# Regla para eliminar todo
distclean: clean
	rm -f README.md

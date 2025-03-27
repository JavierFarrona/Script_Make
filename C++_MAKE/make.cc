#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

/**
 * @brief
 *
 * @param path
 * @return true
 * @return false
 */
bool directoryExists(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) return false;  // El directorio no existe
  return (info.st_mode & S_IFDIR) != 0;
}

/**
 * @brief Create a Directories object
 *
 * @param path
 */
void createDirectories(const std::string& path) {
  std::string command = "mkdir -p " + path;
  if (system(command.c_str()) != 0) {
    std::cerr << "Error: No se pudieron crear los directorios en la ruta: "
              << path << std::endl;
  }
}

/**
 * @brief
 *
 * @param path
 * @return std::string
 */
std::string ensureMakefilePath(const std::string& path) {
  if (path.back() == '/')
    return path + "Makefile";
  else if (path.size() < 9 || path.substr(path.size() - 9) != "/Makefile")
    return path + "/Makefile";
  return path;
}

/**
 * @brief
 *
 * @param outputPath
 * @param targetName
 */
void generateMakefile(const std::string& outputPath,
                      const std::string& targetName) {
  std::ofstream makefile(outputPath);

  if (!makefile) {
    std::cerr << "Error: No se pudo crear el archivo Makefile en la ruta "
              << outputPath << std::endl;
    std::cerr
        << "Verifica si el archivo ya existe o los permisos del directorio."
        << std::endl;
    perror("Detalles del error");
    return;
  }

  makefile
      << "# Makefile fusionado: funcionalidades del usuario y generador\n\n"

      << "CXX = g++\n"
      << "CXXFLAGS = -std=c++17 -Wall -Wextra -g -Ilib\n"
      << "LDFLAGS =\n"
      << "TARGET = " << targetName << "\n\n"

      << "# Carpetas\n"
      << "SRC_DIR = src\n"
      << "LIB_DIR = lib\n"
      << "OBJ_DIR = trash\n\n"

      << "# Crear carpeta para los archivos objeto si no existe\n"
      << "$(shell mkdir -p $(OBJ_DIR))\n"
      << "# Archivos fuente y objetos\n"
      << "SRC = $(wildcard $(SRC_DIR)/*.cc)\n"
      << "LIB = $(wildcard $(LIB_DIR)/*.h)\n"
      << "OBJ = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC))\n\n"

      << "# Compilación del proyecto\n"
      << "all: build\n\n"

      << "build: $(OBJ)\n"
      << "\t$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)\n\n"

      << "# Reglas para compilar cada archivo fuente a objeto\n"
      << "$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc\n"
      << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n"

      << "# Limpieza de archivos generados\n"
      << "clean:\n"
      << "\trm -rf $(OBJ_DIR) $(TARGET)\n\n"

      << "# Eliminación del archivo comprimido\n"
      << "tar_clean:\n"
      << "\t@if [ -z \"$(DIR)\" ]; then \\\n"
      << "\t    echo \"Error: Debes especificar un directorio usando 'make "
         "tar_clean DIR=<directorio>'\"; \\\n"
      << "\t    exit 1; \\\n"
      << "\tfi\n"
      << "\trm -f \"$(DIR).tgz\"\n\n"

      << "# Formateo de archivos según la guía de estilo de Google\n"
      << "format:\n"
      << "\t@files=$$(find $(SRC_DIR) $(LIB_DIR) -type f \\( -name '*.cc' -o "
         "-name '*.h' \\)); \\\n"
      << "\tif [ -n \"$$files\" ]; then \\\n"
      << "\t    echo \"Formateando los siguientes archivos:\"; \\\n"
      << "\t    echo \"$$files\"; \\\n"
      << "\t    clang-format -i --style=Google $$files; \\\n"
      << "\telse \\\n"
      << "\t    echo \"No hay archivos para formatear en $(SRC_DIR) o "
         "$(LIB_DIR).\"; \\\n"
      << "\tfi\n\n"

      << "# Creación de un archivo comprimido de un directorio específico\n"
      << "tar:\n"
      << "\t@read -p \"Introduce el directorio a comprimir: \" dir; \\\n"
      << "\tif [ ! -d \"$$dir\" ]; then \\\n"
      << "\t    echo \"Error: El directorio $$dir no existe.\"; \\\n"
      << "\t    exit 1; \\\n"
      << "\tfi; \\\n"
      << "\tBASE_DIR=$$(dirname \"$$dir\"); \\\n"
      << "\tARCHIVE_NAME=$$(basename \"$$dir\").tgz; \\\n"
      << "\techo \"Creating archive $$BASE_DIR/$$ARCHIVE_NAME\"; \\\n"
      << "\ttar --exclude=\"$$dir/$$ARCHIVE_NAME\" -czvf "
         "\"$$BASE_DIR/$$ARCHIVE_NAME\" \"$$dir\"\n\n"

      << "# Commit y push a git con un mensaje personalizado\n"
      << "git:\n"
      << "\t@read -p \"Introduce el mensaje del commit: \" msg; \\\n"
      << "\tgit add .; \\\n"
      << "\tgit commit -m \"$$msg\"; \\\n"
      << "\tgit push\n\n"
      << "# Regla para limpiar el comprimido\n"
      << "distclean: clean tar_clean\n\n"
      << "# Alias para construir y formatear\n"
      << "build_and_format: format build\n";

  makefile.close();
  std::cout << "Makefile generado exitosamente en " << outputPath << std::endl;
}


void generateMakefileTS(const std::string& outputPath) {
std::ofstream makefile(outputPath);

if (!makefile) {
std::cerr << "Error: No se pudo crear el archivo Makefile en la ruta "
<< outputPath << std::endl;
std::cerr
<< "Verifica si el archivo ya existe o los permisos del directorio."
<< std::endl;
perror("Detalles del error");
return;
}
makefile
<< "# Makefile fusionado: funcionalidades del usuario y generador\n\n"
<< "# Definir el compilador TypeScript\n"
<< "TSC = npx tsc\n\n"
<< "# Carpetas\n"
<< "SRC_DIR = src\n"
<< "DIST_DIR = dist\n\n"
<< "# Crear carpeta para los archivos de salida si no existe\n"
<< "$(shell mkdir -p $(DIST_DIR))\n\n"
<< "# Archivos fuente\n"
<< "SRC = $(wildcard $(SRC_DIR)/*.ts)\n"
<< "OUT = $(patsubst $(SRC_DIR)/%.ts,$(DIST_DIR)/%.js,$(SRC))\n\n"
<< "# Compilación del proyecto\n"
<< "all: build\n\n"
<< "# Regla para compilar todos los archivos\n"
<< "build: $(OUT)\n\n"
<< "# Regla para compilar cada archivo TypeScript\n"
<< "$(DIST_DIR)/%.js: $(SRC_DIR)/%.ts\n"
<< "\t$(TSC) --outDir $(DIST_DIR) --noEmitOnError --strict --esModuleInterop --module commonjs $<\n\n"
<< "# Limpieza de archivos generados\n"
<< "clean:\n"
<< "\trm -rf $(DIST_DIR)\n\n"
<< "# Formateo de archivos TypeScript con Prettier\n"
<< "format:\n"
<< "\tnpx prettier --write $(SRC_DIR)/**/*.ts\n\n"
<< "# Creación de un archivo comprimido de un directorio específico\n"
<< "tar:\n"
<< "\t@read -p \"Introduce el directorio a comprimir: \" dir; \\\n"
<< "\tif [ ! -d \"$$dir\" ]; then \\\n"
<< "\t    echo \"Error: El directorio $$dir no existe.\"; \\\n"
<< "\t    exit 1; \\\n"
<< "\tfi; \\\n"
<< "\tBASE_DIR=$$(dirname \"$$dir\"); \\\n"
<< "\tARCHIVE_NAME=$$(basename \"$$dir\").tgz; \\\n"
<< "\techo \"Creando archivo comprimido $$BASE_DIR/$$ARCHIVE_NAME\"; \\\n"
<< "\ttar --exclude=\"$$dir/$$ARCHIVE_NAME\" -czvf \"$$BASE_DIR/$$ARCHIVE_NAME\" \"$$dir\"\n\n"
<< "# Commit y push a git con un mensaje personalizado\n"
<< "git:\n"
<< "\t@read -p \"Introduce el mensaje del commit: \" msg; \\\n"
<< "\tgit add .; \\\n"
<< "\tgit commit -m \"$$msg\"; \\\n"
<< "\tgit push\n\n"
<< "# Regla para limpiar el comprimido\n"
<< "distclean: clean tar_clean\n\n"
<< "# Alias para construir y formatear\n"
<< "build_and_format: format build\n";

makefile.close();
std::cout << "Makefile generado exitosamente en " << outputPath << std::endl;
}

/**
 * @brief
 *
 * @param path
 */
void deleteMakefile(const std::string& path) {
  std::string makefilePath = ensureMakefilePath(path);
  if (std::remove(makefilePath.c_str()) == 0) {
    std::cout << "Makefile eliminado exitosamente de la ruta: " << makefilePath
              << std::endl;
  } else {
    std::cerr << "Error: No se pudo eliminar el Makefile en la ruta: "
              << makefilePath << std::endl;
    perror("Detalles del error");
  }
}

/**
 * @brief Create a Path With Subfolders object
 *
 * @param path
 */
void createPathWithSubfolders(const std::string& path) {
  try {
    // Crear la ruta completa si no existe
    if (!directoryExists(path)) {
      std::cout << "Creando la ruta completa: " << path << std::endl;
      fs::create_directories(path);
    }

    // Crear las subcarpetas 'src' y 'lib'
    fs::create_directories(path + "/src");
    fs::create_directories(path + "/lib");

    std::cout << "Se creó el directorio " << path
              << " junto con las subcarpetas 'src' y 'lib'.\n";
  } catch (const std::exception& e) {
    std::cerr << "Error al crear los directorios: " << e.what() << std::endl;
  }
}

/**
 * @brief
 *
 * @return int
 */
int main() {
  int option;

  do {
    std::cout << "\nSeleccione una opción:\n";
    std::cout << "1. Generar Makefile\n";
    std::cout << "2. Eliminar Makefile\n";
    std::cout << "3. Crear directorios necesarios\n";
    std::cout << "4. Generar Makefile TypeScript\n";
    std::cout << "0. Salir\n";
    std::cout << "Opción: ";
    std::cin >> option;
    std::cin.ignore();  // Para manejar el salto de línea que queda en el buffer

    switch (option) {
      case 1: {
        std::string outputPath, targetName;
        std::cout
            << "Introduce la ruta donde se generará el Makefile (directorio): ";
        std::getline(std::cin, outputPath);
        std::cout << "Introduce el nombre del ejecutable objetivo (TARGET): ";
        std::getline(std::cin, targetName);

        // Asegurar que la ruta termina con "/Makefile"
        outputPath = ensureMakefilePath(outputPath);

        generateMakefile(outputPath, targetName);
        break;
      }
      case 2: {
        std::string deletePath;
        std::cout << "Introduce la ruta del directorio donde se encuentra el "
                     "Makefile: ";
        std::getline(std::cin, deletePath);

        // Intentar eliminar el Makefile en la ruta especificada
        deleteMakefile(deletePath);
        break;
      }
      case 3: {
        std::string path;
        std::cout << "Introduce la ruta donde se crearán las carpetas 'src' y "
                     "'lib': ";
        std::getline(std::cin, path);
        createPathWithSubfolders(path);
        break;
      }
      case 4: {
        std::string outputPath, targetName;
        std::cout
            << "Introduce la ruta donde se generará el Makefile (directorio): ";
        std::getline(std::cin, outputPath);

        // Asegurar que la ruta termina con "/Makefile"
        outputPath = ensureMakefilePath(outputPath);

        generateMakefileTS(outputPath);
        break;
      }
      case 0:
        std::cout << "Saliendo del programa..." << std::endl;
        break;
      default:
        std::cerr << "Opción no válida. Por favor, intenta de nuevo."
                  << std::endl;
    }
  } while (option != 0);

  return 0;
}
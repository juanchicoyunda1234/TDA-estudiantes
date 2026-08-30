# TDA Estudiante

## Descripcion
TDA Estudiante. Modela un estudiante (cedula, nombres, apellidos, fecha de nacimiento y calificaciones) y un curso que administra la coleccion de estudiantes. Permite registrar, modificar y eliminar calificaciones, calcular edad y promedios, e insertar, eliminar, buscar y listar estudiantes. El proyecto se implementa en Java y C++.

## Estructura del proyecto
Arquitectura modular en 3 paquetes/carpetas (implementada en Java y C++):
- `modelo/`  -> Clase del dominio (`Estudiante`) con datos personales y calificaciones.
- `negocio/` -> TDA `Curso` que administra la coleccion de estudiantes.
- `app/`     -> Punto de entrada (`Main.java` / `main.cpp`) del programa.

## Diagrama de clases
Ver `diagramas/diagrama-clases.md`

## Como ejecutar

### Java
Desde la carpeta `Java`:
```bash
# Compilar todas las clases
javac -d bin src/modelo/*.java src/negocio/*.java src/app/*.java

# Ejecutar
java -cp bin app.Main
```

### C++
> **Nota:** Este proyecto no utiliza archivos de cabecera `.h`. Cada clase contiene su declaracion e implementacion en su archivo `.cpp` con guardas `#ifndef`, incluyendose automaticamente en cadena. Por lo tanto, solo debe compilarse `app/main.cpp`.

Desde la carpeta `CPP`:
```bash
# Compilar
g++ -std=c++17 app/main.cpp -o programa

# Ejecutar (Linux / macOS)
./programa

# Ejecutar (Windows)
programa.exe
```

## Equipo
| Rol | Integrante |
|---|---|
| Lider | Juan Chico |
| Documentacion - Diagramas | Jeremy Torosina |
| Documentacion - Informe | Jullisa Altamirano |
| Backend - Modelo | Joseph Romo |
| Backend - Negocio | Andres Yamuca |
| Frontend - Integracion | Noemi Tuza |

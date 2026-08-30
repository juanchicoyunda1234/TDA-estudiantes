# TDA Estudiante

## Descripcion
TDA Estudiante. Modela un estudiante (cédula, nombres, apellidos, fecha de nacimiento y calificaciones) y un curso que administra la colección de estudiantes.

### Especificaciones del sistema:
- **Capacidad por estudiante:** Máximo 7 calificaciones por estudiante.
- **Capacidad por curso:** Máximo 20 estudiantes por curso.
- **Búsqueda:** Se realiza mediante el número de cédula del estudiante.
- **Eliminación y modificación:** Se despliega una lista numerada con el ID/índice de cada registro para seleccionar el elemento a modificar o eliminar.
- **Operaciones:** Permite registrar, modificar y eliminar calificaciones, calcular edad y promedios individuales y generales, e insertar, eliminar, buscar y listar estudiantes. Implementado en Java y C++.

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

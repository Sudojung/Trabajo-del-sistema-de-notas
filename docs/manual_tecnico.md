# Manual Técnico

## Sistema de Notas - UNMSM

Este documento describe el procedimiento para descargar, compilar y ejecutar el Sistema de Notas desarrollado en C++.

---

# Requisitos

Antes de ejecutar el proyecto es necesario contar con:

- Windows 10 u 11
- Visual Studio 2026 Community (o superior)
- Compilador Microsoft C++ (MSVC)
- Símbolo del sistema (CMD)

---

# Estructura del proyecto

```text
Trabajo-del-sistema-de-notas/
│
├── src/
│   └── main.cpp
│
├── data/
│   └── alumnos.txt
│
├── output/
│   └── alumnos.txt 
├── docs/
│
└── web/
```

La carpeta **web/** corresponde a un prototipo de la futura versión web del sistema y no es necesaria para ejecutar la aplicación en C++.

---

# Descarga del proyecto

## Opción 1 (recomendada)

Descargar el repositorio desde GitHub.

```
Code
↓
Download ZIP
```

Descomprimir el archivo.

Mover la carpeta:

```
Trabajo-del-sistema-de-notas
```

al Escritorio de Windows.

La ruta debería quedar similar a:

```
C:\Users\Usuario\Desktop\Trabajo-del-sistema-de-notas
```

---

# Compilación del proyecto

## Paso 1

Abrir **Símbolo del sistema (CMD)**.

---

## Paso 2

Cargar el entorno de compilación de Visual Studio.

Ejecutar:

```cmd
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat"
```

Si la instalación de Visual Studio se encuentra en otra ubicación, deberá modificarse la ruta correspondiente.

---

## Paso 3

Verificar que el compilador esté disponible.

Ejecutar:

```cmd
cl
```

Si aparece la información del compilador Microsoft C/C++, la configuración es correcta.

---

## Paso 4

Ingresar a la carpeta del proyecto.

Si el proyecto fue colocado en el Escritorio:

```cmd
cd %USERPROFILE%\Desktop\Trabajo-del-sistema-de-notas
```

---

## Paso 5

Compilar el programa.

```cmd
cl /EHsc src\main.cpp /Fe:sistema.exe
```

Al finalizar correctamente se generará:

```
sistema.exe
```

---

# Ejecución

Ejecutar:

```cmd
sistema.exe
```

El sistema mostrará:

```text
========================================
        SISTEMA DE NOTAS - UNMSM
========================================

Usuario:
Contraseña:
```

Ingresar las credenciales configuradas en el código fuente.

---

# Uso del sistema

Una vez autenticado aparecerá el menú principal.

```text
1. Listar alumnos
2. Buscar alumno
3. Registrar alumno
4. Editar notas
5. Eliminar alumno
6. Generar reportes
7. Ver estadísticas
8. Salir
```

Desde este menú es posible administrar completamente la información de los alumnos.

---

# Archivos utilizados

## data/alumnos.txt

Almacena permanentemente los registros de los alumnos.

Formato:

```text
Codigo|Nombre|Practica|Parcial
```

---

## output/aprobados.txt

Se genera al seleccionar la opción:

```
6. Generar reportes
```

Contiene únicamente los alumnos aprobados.

---

## output/desaprobados.txt

Se genera al seleccionar la opción:

```
6. Generar reportes
```

Contiene únicamente los alumnos desaprobados.

---

# Solución de problemas

## El comando `cl` no existe

Verifique que Visual Studio tenga instalado el componente:

```
Desktop development with C++
```

y ejecute previamente:

```cmd
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat"
```

---

## No se encuentra `alumnos.txt`

Verifique que exista la carpeta:

```
data/
```

El programa creará automáticamente el archivo si no existe.

---

## No se generan los reportes

Verifique que exista la carpeta:

```
output/
```

---

# Versión web

El proyecto incluye una carpeta:

```
web/
```

que contiene una implementación preliminar del sistema mediante HTML, CSS y JavaScript.

Actualmente esta versión corresponde únicamente a un prototipo y no forma parte de la ejecución del sistema desarrollado en C++.

---

# Autor

**Renzo Cienfuegos** - Computación Científica - Universidad Nacional Mayor de San Marcos

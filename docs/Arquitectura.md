# Arquitectura del Sistema

## Descripción

El Sistema de Notas - UNMSM está desarrollado en C++ siguiendo una arquitectura modular basada en funciones. Cada módulo realiza una tarea específica, facilitando el mantenimiento, la reutilización del código y futuras ampliaciones del sistema.

La persistencia de los datos se realiza mediante archivos de texto (`.txt`), simulando una base de datos sencilla para almacenar la información académica de los alumnos.

---

# Arquitectura general

```text
                     ┌────────────────────────┐
                     │  Inicio del programa   │
                     └────────────┬───────────┘
                                  │
                                  ↓
                     ┌────────────────────────┐
                     │ Cargar alumnos.txt     │
                     └────────────┬───────────┘
                                  │
                                  ↓
                     ┌────────────────────────┐
                     │ Login del administrador│
                     └────────────┬───────────┘
                                  │
                     ┌────────────┴────────────┐
                     │ ¿Credenciales válidas?  │
                     └───────┬─────────┬───────┘
                             │Sí       │No
                             ↓         ↓
                  ┌────────────────┐  Fin
                  │ Menú principal │
                  └───────┬────────┘
                          │
                          ▼
        ┌────────────────────────────────────────────┐
        │ 1. Listar alumnos                          │
        │ 2. Buscar alumno                           │
        │ 3. Registrar alumno                        │
        │ 4. Editar notas                            │
        │ 5. Eliminar alumno                         │
        │ 6. Generar reportes                        │
        │ 7. Ver estadísticas                        │
        │ 8. Salir                                   │
        └────────────────────────────────────────────┘
```

---

# Flujo del sistema

```text
                                                                                           ┌──────────────┐
                                                                                           │    Inicio    │
                                                                                           └──────┬───────┘
                                                                                                  │
                                                                                                  ▼
                                                                                    ┌────────────────────────────┐
                                                                                    │ Cargar archivo alumnos.txt │
                                                                                    └─────────────┬──────────────┘
                                                                                                  │
                                                                                                  ▼
                                                                                    ┌───────────────────────────┐
                                                                                    │  Login del administrador  │
                                                                                    └─────────────┬─────────────┘
                                                                                                  │
                                                                                ┌─────────────────┴──────────────────┐
                                                                                │   ¿Credenciales                    │
                                                                                │                      válidas?      │
                                                                                └─────┬───────────────────────┬──────┘
                                                                                      │ Sí                    │ No
                                                                                      ▼                       ▼
                                                                                ┌────────────┐           ┌───────────┐
                                                                                │    Menú    │           │    Fin    │
                                                                                │  principal │           │  programa │
                                                                                └──────┬─────┘           └───────────┘
                                                                                       │
                                                                                       ▼
                                                                                ┌───────────────────────────────────┐
                                                                                │       Seleccionar una opción      │
                                                                                └───────────────────┬───────────────┘                                                             
                                                                                                    │                                                                             
           ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐  
           │                         │                           │                       │                                  │                         │                         │                     │ 
           ▼                         ▼                           ▼                       ▼                                  ▼                         ▼                         ▼                     ▼
    ┌────────────┐             ┌───────────┐             ┌──────────────┐           ┌───────────┐                    ┌────────────┐          ┌────────────────┐         ┌───────────────┐       ┌──────────┐
    │ Listar     │             │ Buscar    │             │  Registrar   │           │  Editar   │                    │ Eliminar   │          │   Generar      │         │      Ver      │       │   Salir  │
    │     Alumno │             │    Alumno │             │      Alumno  │           │    Notas  │                    │     Alumno │          │      reportes  │         │  Estadísticas │       └──────────┘
    └────────────┘             └───────────┘             └──────────────┘           └───────────┘                    └────────────┘          └────────────────┘         └───────────────┘             │
           │                         │                           │                        │                                 │                         │                         │                     │
         ¿Hay                      ¿Hay                       Digitar                  Digitar                           Digitar                  ¿Existen                  ¿Existen                  │
        alumnos?                  alumnos?                    Código                   Código                            Código                    alumnos?                  alumnos?                 │
           │                         │                           │                        │                                 │                         │                         │                     │
   ┌──────────────┐           ┌──────────────┐              ¿Es único?                 ¿Existe?                          ¿Existe?              ┌──────────────┐          ┌──────────────┐             │
  Sí              No         Sí              No                  │                        │                                 │                 Sí              No        Sí              No            │
   │              │           │              │           ┌──────────────┐          ┌──────────────┐                ┌────────────────┐          │              │          │              │             │
   │              │           │              │          Sí              No        Sí              No              Sí                No      Genera          Mostrar   Mostrar        Mostrar          │
Mostrar        Mostrar     Buscar         Mostrar        │              │          │              │                │                │       (+ / -)         mensaje    Datos         mensaje          │
 tabla         mensaje     Código         mensaje     Digitar         Mostrar   Cambiar         Mostrar         ¿Deseas           Mostrar                                                             │
                              │              ▲         Alumno         mensaje   Practica        mensaje        Eliminarlo?        mensaje                                                             │
                              │              │           │                         │                               │                                                                                  │
                           ¿Existe?          │           │                         │                         ┌───────────┐                                                                            │ 
                              │              │        Digitar                   Cambiar                     Sí           No                                                                           │
                      ┌──────────────┐       │        Prctica                   Parcial                      │           │                                                                            │
                     Sí              No ─────┘           │                         │                    Eliminación    Mostrar                                                                        │
                      │                               Digitar                Actualización                Exitosa      mensaje                                                                        │
                      │                               Parcial                   Exitosa                                                                                                               │
                   Mostrar                               │                                                                                                                                            │
                    Datos                             Registro                                                                                                                                        │
                                                      Exitoso                                                                                                                                         │
                                                                                                                                                                                                      ▼
                                                                                                                                                                                               ┌────────────┐
                                                                                                                                                                                               │    Fin     │
                                                                                                                                                                                               └────────────┘


```
# Tecnologías utilizadas

- Lenguaje C++17
- Standard Template Library (STL)
- Programación modular
- Archivos de texto (.txt)
- Microsoft Visual C++ Compiler (MSVC)

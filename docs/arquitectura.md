# Arquitectura del Sistema

## Descripción

El Sistema de Notas - UNMSM está desarrollado en C++ siguiendo una arquitectura modular basada en funciones. Cada módulo realiza una tarea específica, facilitando el mantenimiento, la reutilización del código y futuras ampliaciones del sistema.

La persistencia de los datos se realiza mediante archivos de texto (`.txt`), simulando una base de datos sencilla para almacenar la información académica de los alumnos.

---

# Arquitectura general

El sistema está organizado en cuatro componentes principales:

```text
 ┌────────────────────────────────────────────┐
 │           Usuario / Administrador          │
 │        Interactúa mediante consola         │
 └─────────────────────┬──────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────┐
│              Interfaz de consola             │
│ Login, menú principal y mensajes del sistema │
└──────────────────────┬───────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────┐
│              Lógica del sistema             │
│ Registrar, listar, buscar, editar, eliminar │
│ calcular promedios y generar estadísticas   │
└──────────────────────┬──────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────┐
│              Persistencia de datos          │
│ data/alumnos.txt                            │
│ output/aprobados.txt                        │
│ output/desaprobados.txt                     │
└─────────────────────────────────────────────┘
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
┌─────────────────────────────────────────────────────────────────────────────→ │       Seleccionar una opción      │
│                                                                               └───────────────────┬───────────────┘                                                             
│                                                                                                   │                                                                             
│          ┌─────────────────────────┬───────────────────────────┬───────────────────────┬──────────────────────────────────┬─────────────────────────┬─────────────────────────┬─────────────────────┐  
│          │                         │                           │                       │                                  │                         │                         │                     │ 
│          ▼                         ▼                           ▼                       ▼                                  ▼                         ▼                         ▼                     ▼
│   ┌────────────┐             ┌───────────┐             ┌──────────────┐           ┌───────────┐                    ┌────────────┐          ┌────────────────┐         ┌───────────────┐       ┌──────────┐
│   │ Listar     │             │ Buscar    │             │  Registrar   │           │  Editar   │                    │ Eliminar   │          │   Generar      │         │      Ver      │       │   Salir  │
│   │     Alumno │             │    Alumno │             │      Alumno  │           │    Notas  │                    │     Alumno │          │      reportes  │         │  Estadísticas │       └──────────┘
│   └────────────┘             └───────────┘             └──────────────┘           └───────────┘                    └────────────┘          └────────────────┘         └───────────────┘             │
│          │                         │                           │                        │                                 │                         │                         │                     │
│        ¿Hay                      ¿Hay                      Ingresar                 Ingresar                          Ingresar                  ¿Existen                  ¿Existen                  │
│       alumnos?                  alumnos?                    Código                   Código                            Código                    alumnos?                  alumnos?                 │
│          │                         │                           │                        │                                 │                         │                         │                     │
│   ┌─────────────┐           ┌──────────────┐            Validar código            Validar código                    Validar código            ┌─────────────┐           ┌─────────────┐             │
│  Sí             No         Sí              No                  │                        │                                 │                  Sí             No         Sí             No            │
│   │             │           │              │               ¿Existe?                 ¿Existe?                          ¿Existe?                │             │           │             │             │
│   │             │           │              │                   │                        │                                 │                   │             │           │             │             │
│   │             │           │              │           ┌──────────────┐          ┌──────────────┐                ┌────────────────┐           │             │           │             │             │
│   │             │           │              │          Sí              No        Sí              No              Sí                No        Crear          No hay    Mostrar        No hay          │
│Mostrar       No existe    Buscar        No existe      │              │          │              │                │                │        aprobados     datos para   Datos       datos para        │
│tabla          registro    Código        el alumno    Usar         Ingresar    Cambiar        No existe        ¿Deseas          No existe      ↓           reportar      │           mostrar         │
│   │             │           │              ▲ │      editar         nombre      notas         el alumno       Eliminarlo?       el alumno     Crear          │           │             │             │
│   │             │           │              │ │       notas            │          │              │                │                │       desaprobados      │           │             │             │
│   │             │        ¿Existe?          │ │         │              │          │              │          ┌───────────┐          │           │             │           │             │             │ 
│   │             │           │              │ │         │           Ingresar  Recalcular         │         Sí           No         │        Alojar en        │           │             │             │
│   │             │   ┌──────────────┐       │ │         │            notas     promedio          │          │           │          │         \output         │           │             │             │
│   │             │  Sí              No ─────┘ │         │              │          │              │     Eliminar      Operación     │           │             │           │             │             │
│   │             │   │                        │         │           Calcular  Guardar en         │     Registro      cancelada     │           │             │           │             │             │
│   │             │   │                        │         │           Promedio  alumnos.txt        │          │           │          │           │             │           │             │             │
│   │             │Mostrar                     │         │              │          │              │     Guardar en       │          │           │             │           │             │             │
│   │             │ Datos                      │         │          Guardar en     │              │     alumnos.txt      │          │           │             │           │             │             │
│   │             │   │                        │         │          alumnos.txt    │              │          │           │          │           │             │           │             │             │
│   │             │   │                        │         │              │          │              │          │           │          │           │             │           │             │             ▼
│   │             │   │                        │         │              │          │              │          │           │          │           │             │           │             │      ┌────────────┐
│   │             │   │                        │         │              │          │              │          │           │          │           │             │           │             │      │    Fin     │
└───┴─────────────┴───┴────────────────────────┴─────────┴──────────────┴──────────┴──────────────┴──────────┴───────────┴──────────┴───────────┴─────────────┴───────────┴─────────────┘      └────────────┘
```
# Archivos utilizados

### alumnos.txt

Almacena toda la información de los alumnos.

Formato:

```
Codigo|Nombre|Practica|Parcial
```

---

### aprobados.txt

Contiene únicamente los alumnos aprobados.

---

### desaprobados.txt

Contiene únicamente los alumnos desaprobados.

# Lógica de negocio

El sistema calcula automáticamente el promedio académico de cada alumno utilizando las notas de práctica y examen parcial.

## Fórmula del promedio

```text
Promedio = (Práctica + Parcial) / 2
```

## Criterio de aprobación

```text
Promedio >= 12.00 → Aprobado
Promedio < 12.00  → Desaprobado
```

El estado académico se determina automáticamente después del cálculo del promedio y es utilizado para:

- Mostrar el estado del alumno en el listado.
- Mostrar el estado al consultar un alumno.
- Clasificar los alumnos en los reportes de aprobados y desaprobados.
- Calcular las estadísticas generales del sistema.


# Tecnologías utilizadas

- Lenguaje C++17
- Standard Template Library (STL)
- Programación modular
- Archivos de texto (.txt)
- Microsoft Visual C++ Compiler (MSVC)

# Mejoras futuras

Esta versión corresponde a una implementación funcional inicial del sistema. Entre las posibles mejoras se consideran:

- Integración con una base de datos (SQLite o MySQL).
- Gestión de múltiples cursos.
- Registro de docentes.
- Exportación de reportes en formato PDF.
- Interfaz gráfica de usuario.
- Integración completa con la versión web desarrollada en HTML, CSS y JavaScript.

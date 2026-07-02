# Sistema de Notas - UNMSM

Proyecto académico desarrollado en **C++** inspirado en el Sistema Único de Matrícula (SUM) de la **Universidad Nacional Mayor de San Marcos (UNMSM)**.

---

# Descripción

El Sistema de Notas - UNMSM es una aplicación de consola que permite gestionar la información académica de los alumnos mediante una interfaz sencilla.

El sistema permite al administrador autenticarse mediante credenciales, registrar alumnos, consultar información académica, editar notas, eliminar registros, generar reportes y visualizar estadísticas, utilizando archivos de texto como mecanismo de almacenamiento.

---

# Funcionalidades

- Inicio de sesión mediante credenciales del administrador.
- Registro de alumnos.
- Listado de alumnos.
- Búsqueda de alumnos por código.
- Edición de notas.
- Eliminación de alumnos.
- Validación de códigos únicos.
- Validación de nombres.
- Validación de notas.
- Cálculo automático del promedio.
- Determinación automática del estado académico.
- Generación de reportes de alumnos aprobados.
- Generación de reportes de alumnos desaprobados.
- Estadísticas generales del curso.
- Arquitectura preparada para una futura versión web.

---

# Tecnologías utilizadas

- C++17
- Standard Template Library (STL)
- Microsoft Visual C++ (MSVC)
- Archivos de texto (.txt)
- HTML
- CSS
- JavaScript

---

# Estructura del proyecto

```text
Trabajo-del-sistema-de-notas/
│
├── README.md
├── LICENSE
│
├── src/
│   └── main.cpp
│
├── data/
│   └── alumnos.txt
│
├── output/
│   ├── aprobados.txt
│   └── desaprobados.txt
│
├── docs/
│   ├── arquitectura.md
│   ├── manual_tecnico.md
│   └── capturas/ (opcional)
│
└── web/
    ├── index.html
    ├── login.html
    ├── panel.html
    ├── notas.html
    ├── reporte.html
    ├── css/
    │   └── styles.css
    └── js/
        └── app.js
```

---

# Estado del proyecto

**Versión actual:** `v1.0 Beta`

Estado de los módulos:

- ✅ Sistema de consola completamente funcional.
- ✅ Gestión de alumnos.
- ✅ Generación de reportes.
- ✅ Estadísticas.
- 🚧 Versión web en desarrollo.

---

# Documentación

La documentación técnica del proyecto se encuentra en la carpeta **docs/**.

- **arquitectura.md** → Arquitectura del sistema y flujo de ejecución.
- **manual_tecnico.md** → Instalación, compilación y ejecución del proyecto.
- **capturas/** → Evidencias del funcionamiento del sistema. (opcional)

---

# Autor

**Renzo Cienfuegos**

Estudiante de Computación Científica  
Universidad Nacional Mayor de San Marcos (UNMSM)

---

# Licencia

Proyecto desarrollado con fines académicos.

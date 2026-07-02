# Sistema de Notas - UNMSM

Proyecto académico desarrollado en C++ inspirado en el Sistema Único de Matrícula de la UNMSM.

## Descripción

El sistema simula una intranet académica básica para alumnos. Permite iniciar sesión con usuario y contraseña, consultar notas registradas, calcular el promedio final y mostrar el estado académico del alumno.

## Funcionalidades

- Login de alumno.
- Validación de usuario y contraseña.
- Lectura de usuarios desde usuarios.txt.
- Lectura de notas desde alumnos.txt.
- Cálculo automático del promedio.
- Estado final: Aprobado o Desaprobado.
- Generación de reporte en resultados.txt.
- Arquitectura preparada para una futura versión web.

## Estructura del proyecto

```txt
Trabajo-del-sistema-de-notas/
│
├── README.md
├── LICENSE
│
├── src/
│    └── main.cpp
│      
├── data/
│    ├── usuarios.txt
│    └── alumnos.txt
│
├── output/
│    ├── aprobados.txt
│    └── desaprobados.txt
│    
├── docs/
│    ├── arquitectura.md
│    └── manual_usuario.md    
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

## Autor:
```
Renzo Cienfuegos - Universidad Nacional Mayor de San Marcos
```


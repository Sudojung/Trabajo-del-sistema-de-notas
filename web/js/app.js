const ADMIN_USER = "benito04";
const ADMIN_PASS = "12341234";

const alumnosBase = [
  { codigo: "20260001", nombre: "Juan Perez", practica: 15, parcial: 14 },
  { codigo: "20260002", nombre: "Maria Lopez", practica: 10, parcial: 12 },
  { codigo: "20260003", nombre: "Pedro Ramos", practica: 18, parcial: 17 },
  { codigo: "20260004", nombre: "Ana Torres", practica: 8, parcial: 11 },
  { codigo: "20260005", nombre: "Luis Garcia", practica: 13, parcial: 15 }
];

function obtenerAlumnos() {
  const guardados = localStorage.getItem("alumnosWeb");
  if (!guardados) {
    localStorage.setItem("alumnosWeb", JSON.stringify(alumnosBase));
    return alumnosBase;
  }
  return JSON.parse(guardados);
}

function guardarAlumnosWeb(alumnos) {
  localStorage.setItem("alumnosWeb", JSON.stringify(alumnos));
}

function calcularPromedio(practica, parcial) {
  return (Number(practica) + Number(parcial)) / 2;
}

function obtenerEstado(promedio) {
  return promedio >= 12 ? "Aprobado" : "Desaprobado";
}

function normalizarCodigo(codigo) {
  codigo = String(codigo).trim();
  if (!/^\d{1,8}$/.test(codigo)) return null;
  return codigo.padStart(8, "0");
}

function nombreValido(nombre) {
  return /^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$/.test(nombre.trim());
}

function notaValida(nota) {
  const n = Number(nota);
  return !Number.isNaN(n) && n >= 0 && n <= 20;
}

function verificarSesion() {
  if (localStorage.getItem("adminActivo") !== "true") {
    window.location.href = "login.html";
  }
}

function loginWeb() {
  const usuario = document.getElementById("usuario").value.trim();
  const password = document.getElementById("password").value.trim();
  const mensaje = document.getElementById("mensaje");

  if (usuario === ADMIN_USER && password === ADMIN_PASS) {
    localStorage.setItem("adminActivo", "true");
    window.location.href = "panel.html";
    return;
  }

  mensaje.textContent = "Usuario o contraseña incorrectos.";
}

function cargarPanel() {
  verificarSesion();
  document.getElementById("bienvenida").textContent = "Bienvenido, administrador";
}

function cerrarSesion() {
  localStorage.removeItem("adminActivo");
  window.location.href = "login.html";
}

function cargarGestionAlumnos() {
  verificarSesion();
  mostrarTablaAlumnos();

  const seccion = location.hash ? location.hash.replace("#", "") : "listar";
  mostrarSeccion(seccion);
}

function mostrarSeccion(id) {
  document.querySelectorAll(".section").forEach(sec => sec.classList.add("hidden"));
  const seccion = document.getElementById(id);
  if (seccion) seccion.classList.remove("hidden");
  if (id === "listar") mostrarTablaAlumnos();
}

function crearTabla(alumnos) {
  if (alumnos.length === 0) return "<p>No existen alumnos registrados.</p>";

  let filas = alumnos.map(a => {
    const promedio = calcularPromedio(a.practica, a.parcial);
    const estado = obtenerEstado(promedio);
    const clase = estado === "Aprobado" ? "aprobado" : "desaprobado";

    return `
      <tr>
        <td>${a.codigo}</td>
        <td>${a.nombre}</td>
        <td>${Number(a.practica).toFixed(2)}</td>
        <td>${Number(a.parcial).toFixed(2)}</td>
        <td>${promedio.toFixed(2)}</td>
        <td class="${clase}">${estado}</td>
      </tr>
    `;
  }).join("");

  return `
    <table>
      <thead>
        <tr>
          <th>Código</th>
          <th>Alumno</th>
          <th>Práctica</th>
          <th>Parcial</th>
          <th>Promedio</th>
          <th>Estado</th>
        </tr>
      </thead>
      <tbody>${filas}</tbody>
    </table>
  `;
}

function mostrarTablaAlumnos() {
  const contenedor = document.getElementById("tablaAlumnos");
  if (!contenedor) return;
  contenedor.innerHTML = crearTabla(obtenerAlumnos());
}

function buscarAlumnoWeb() {
  const codigo = normalizarCodigo(document.getElementById("buscarCodigo").value);
  const resultado = document.getElementById("resultadoBusqueda");

  if (!codigo) {
    resultado.innerHTML = "<p class='mensaje'>Código inválido. Debe tener máximo 8 números.</p>";
    return;
  }

  const alumno = obtenerAlumnos().find(a => a.codigo === codigo);
  if (!alumno) {
    resultado.innerHTML = "<p class='mensaje'>No se encontró al alumno.</p>";
    return;
  }

  resultado.innerHTML = crearTabla([alumno]);
}

function registrarAlumnoWeb() {
  const mensaje = document.getElementById("mensajeRegistro");
  const codigo = normalizarCodigo(document.getElementById("regCodigo").value);
  const nombre = document.getElementById("regNombre").value.trim();
  const practica = document.getElementById("regPractica").value;
  const parcial = document.getElementById("regParcial").value;

  if (!codigo) {
    mensaje.textContent = "Código inválido. Solo números y máximo 8 dígitos.";
    return;
  }
  if (!nombreValido(nombre)) {
    mensaje.textContent = "Nombre inválido. Solo letras y espacios.";
    return;
  }
  if (!notaValida(practica) || !notaValida(parcial)) {
    mensaje.textContent = "Notas inválidas. Deben estar entre 0 y 20.";
    return;
  }

  const alumnos = obtenerAlumnos();
  if (alumnos.some(a => a.codigo === codigo)) {
    mensaje.textContent = "El código ya existe.";
    return;
  }

  alumnos.push({ codigo, nombre, practica: Number(practica), parcial: Number(parcial) });
  guardarAlumnosWeb(alumnos);

  mensaje.className = "success";
  mensaje.textContent = `Alumno registrado correctamente. Código guardado: ${codigo}`;
  mostrarTablaAlumnos();
}

function editarAlumnoWeb() {
  const mensaje = document.getElementById("mensajeEdicion");
  const codigo = normalizarCodigo(document.getElementById("editCodigo").value);
  const practica = document.getElementById("editPractica").value;
  const parcial = document.getElementById("editParcial").value;

  if (!codigo) {
    mensaje.textContent = "Código inválido.";
    return;
  }
  if (!notaValida(practica) || !notaValida(parcial)) {
    mensaje.textContent = "Notas inválidas. Deben estar entre 0 y 20.";
    return;
  }

  const alumnos = obtenerAlumnos();
  const alumno = alumnos.find(a => a.codigo === codigo);

  if (!alumno) {
    mensaje.textContent = "No se encontró al alumno.";
    return;
  }

  alumno.practica = Number(practica);
  alumno.parcial = Number(parcial);
  guardarAlumnosWeb(alumnos);

  mensaje.className = "success";
  mensaje.textContent = "Notas actualizadas correctamente.";
  mostrarTablaAlumnos();
}

function eliminarAlumnoWeb() {
  const mensaje = document.getElementById("mensajeEliminacion");
  const codigo = normalizarCodigo(document.getElementById("delCodigo").value);

  if (!codigo) {
    mensaje.textContent = "Código inválido.";
    return;
  }

  let alumnos = obtenerAlumnos();
  const alumno = alumnos.find(a => a.codigo === codigo);

  if (!alumno) {
    mensaje.textContent = "No se encontró al alumno.";
    return;
  }

  if (!confirm(`¿Seguro que desea eliminar a ${alumno.nombre}?`)) {
    mensaje.textContent = "Operación cancelada.";
    return;
  }

  alumnos = alumnos.filter(a => a.codigo !== codigo);
  guardarAlumnosWeb(alumnos);

  mensaje.className = "success";
  mensaje.textContent = "Alumno eliminado correctamente.";
  mostrarTablaAlumnos();
}

function mostrarReporte() {
  verificarSesion();

  const alumnos = obtenerAlumnos();
  const aprobados = alumnos.filter(a => calcularPromedio(a.practica, a.parcial) >= 12);
  const desaprobados = alumnos.filter(a => calcularPromedio(a.practica, a.parcial) < 12);
  const porcentaje = alumnos.length ? (aprobados.length * 100) / alumnos.length : 0;

  document.getElementById("estadisticas").innerHTML = `
    <div class="stat-card"><strong>${alumnos.length}</strong>Total alumnos</div>
    <div class="stat-card"><strong>${aprobados.length}</strong>Aprobados</div>
    <div class="stat-card"><strong>${desaprobados.length}</strong>Desaprobados</div>
    <div class="stat-card"><strong>${porcentaje.toFixed(2)}%</strong>Aprobación</div>
  `;

  document.getElementById("tablaAprobados").innerHTML = crearTabla(aprobados);
  document.getElementById("tablaDesaprobados").innerHTML = crearTabla(desaprobados);
}

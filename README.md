# Gestor de Estudiantes — C++

Aplicacion de consola desarrollada en C++ para gestionar los datos y calificaciones de los estudiantes matriculados en un curso. Proyecto academico de tercer semestre de Ingenieria en Software.

---

## Tabla de contenidos

- [Descripcion](#descripcion)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Clases](#clases)
- [Menu de opciones](#menu-de-opciones)
- [Compilacion y ejecucion](#compilacion-y-ejecucion)
- [Ejemplo de uso](#ejemplo-de-uso)
- [Consideraciones tecnicas](#consideraciones-tecnicas)

---

## Descripcion

El sistema permite registrar hasta **20 estudiantes** por curso. Cada estudiante puede tener hasta **7 calificaciones**. Desde la consola se pueden ingresar, modificar y eliminar tanto los datos de los estudiantes como sus notas, y calcular promedios individuales o generales del curso.

---

## Estructura del proyecto

```
gestor-estudiantes/
├── Estudiante.h          # Clase con los datos personales y notas de un estudiante
├── GestorEstudiante.h    # Clase que administra el vector de estudiantes y los menus
├── Main.cpp              # Menu principal e instancia del gestor
└── README.md
```

---

## Clases

### `Estudiante` — `Estudiante.h`

Representa a un unico estudiante dentro del sistema.

**Atributos privados**

| Atributo | Tipo | Descripcion |
|---|---|---|
| `cedula` | `string` | Numero de cedula de identidad |
| `nombres` | `string` | Nombres del estudiante |
| `apellidos` | `string` | Apellidos del estudiante |
| `fechaNacimiento` | `string` | Fecha en formato dd/mm/aaaa |
| `notas` | `vector<float>` | Calificaciones (maximo 7) |
| `MAX_NOTAS` | `static const int` | Limite de notas (valor: 7) |

**Constructores**

```cpp
Estudiante();                                                    // crea un objeto vacio
Estudiante(string ced, string nom, string ape, string fNac);    // con todos los datos
```

**Metodos principales**

| Metodo | Retorna | Descripcion |
|---|---|---|
| `agregarNota(float)` | `bool` | Agrega una nota con `push_back`, falla si ya hay 7 |
| `modificarNota(int, float)` | `bool` | Cambia una nota por indice |
| `eliminarNota(int)` | `bool` | Borra una nota con `erase(begin() + indice)` |
| `calcularPromedio()` | `float` | Suma y divide con for clasico; retorna 0 si no hay notas |
| `notasLlenas()` | `bool` | Dice si ya se llego al maximo de 7 notas |
| `tieneNotas()` | `bool` | Dice si hay al menos una nota registrada |
| `mostrarDatos()` | `void` | Imprime cedula, nombres, apellidos y fecha |
| `mostrarNotas()` | `void` | Lista las notas con numeracion desde 1 |

---

### `GestorEstudiante` — `GestorEstudiante.h`

Administra el vector de estudiantes y concentra toda la logica de los menus y la lectura de datos por consola.

**Atributos privados**

| Atributo | Tipo | Descripcion |
|---|---|---|
| `estudiantes` | `vector<Estudiante>` | Lista principal de estudiantes |
| `MAX_ESTUDIANTES` | `static const int` | Cupo maximo del curso (valor: 20) |

**Metodos de lectura (privados)**

| Metodo | Descripcion |
|---|---|
| `leerEntero(string)` | Lee un entero con validacion; repite si el usuario escribe letras |
| `leerFloat(string)` | Igual pero para decimales |
| `leerTexto(string)` | Lee una linea completa con `getline` |
| `limpiarBuffer()` | Limpia el buffer con `cin.ignore` |

**Metodos publicos**

| Metodo | Descripcion |
|---|---|
| `buscar(string cedula)` | Recorre el vector y retorna el indice del estudiante o -1 |
| `mostrarListado()` | Lista todos los estudiantes con su autonumerico |
| `menuEstudiantes()` | Submenu para insertar, modificar y eliminar estudiantes |
| `insertarEstudiante()` | Agrega estudiante(s) con opcion de repetir |
| `modificarEstudiante()` | Edita datos de un estudiante por autonumerico |
| `eliminarEstudiante()` | Elimina un estudiante con confirmacion |
| `menuCalificaciones()` | Busca por cedula y gestiona las notas de ese estudiante |
| `promedioEstudiante()` | Busca por cedula y muestra el promedio individual |
| `promedioCurso()` | Calcula y muestra el promedio general del curso |

---

### `Main.cpp`

Contiene unicamente el menu principal y la instancia del gestor. No tiene logica de negocio.

```cpp
GestorEstudiante gestor; // unica instancia, vive durante toda la ejecucion

// menu en do-while; delega cada opcion al metodo correspondiente del gestor
```

El `cin.ignore()` despues de leer la opcion del menu es clave: limpia el salto de linea que deja `cin >>` para que el primer `getline()` dentro de cualquier submenu funcione correctamente.

---

## Menu de opciones

```
=== GESTOR DE PERSONAS ===
1. Estudiantes
2. Registro de calificaciones
3. Determinar el promedio de notas de un estudiante
4. Determinar el promedio de notas del curso
0. Salir
Teclee su opcion (0-4):
```

### Opcion 1 — Estudiantes

Muestra el listado actual y da acceso a un submenu:

- **Insertar**: pide los datos del nuevo estudiante; pregunta si se quiere agregar otro. No permite insertar si el curso ya tiene 20 estudiantes.
- **Modificar**: el usuario elige por autonumerico; dejar un campo en blanco mantiene el valor actual.
- **Eliminar**: pide confirmacion antes de borrar; no permite intentarlo si no hay estudiantes.

### Opcion 2 — Registro de calificaciones

El usuario ingresa la cedula del estudiante. Si existe, se muestran sus datos y se puede:

- Agregar notas (hasta completar 7).
- Modificar o eliminar una nota existente por numero.
- Cuando se llega a 7 notas el sistema lo notifica y cierra el ingreso automaticamente.

Si la cedula no existe, se ofrece intentar con otra o volver al menu principal.

### Opcion 3 — Promedio de un estudiante

Busca al estudiante por cedula y muestra nombre, apellidos, fecha de nacimiento y su promedio de notas. Si no tiene notas, lo indica.

### Opcion 4 — Promedio del curso

Calcula el promedio general sumando los promedios de todos los estudiantes que tienen al menos una nota. Si ninguno tiene notas, muestra el mensaje correspondiente.

---

## Compilacion y ejecucion

Requiere un compilador compatible con **C++11** o superior.

```bash
# Linux / macOS
g++ -o gestor Main.cpp
./gestor

# Windows con MinGW
g++ -o gestor.exe Main.cpp
gestor.exe
```

Los tres archivos (`Main.cpp`, `Estudiante.h`, `GestorEstudiante.h`) deben estar en la misma carpeta al compilar.

---

## Ejemplo de uso

```
=== GESTOR DE PERSONAS ===
1. Estudiantes
...
Teclee su opcion (0-4): 1

--- LISTADO DE ESTUDIANTES ---
  No hay estudiantes registrados.

-- SUBMENU ESTUDIANTES --
1. Insertar estudiante
...
Opcion: 1

-- NUEVO ESTUDIANTE --
Cedula          : 1804567890
Nombres         : Ana
Apellidos       : Torres
Fecha de nac.   : 15/03/2003
  Estudiante registrado correctamente.
Deseas registrar otro estudiante? (s/n): n
```

---

## Consideraciones tecnicas

- Los datos se almacenan en memoria durante la ejecucion; al cerrar el programa se pierden (no hay archivo ni base de datos).
- Se usan `vector` de la STL con metodos tradicionales: `push_back`, `erase`, `empty`, `size`.
- La busqueda por cedula es lineal (recorre el vector de inicio a fin).
- La lectura de enteros y decimales tiene validacion de tipo; si el usuario escribe texto, el programa lo detecta, limpia el buffer y vuelve a pedir el dato.
- No se usan librerias externas; todo corre con la biblioteca estandar de C++.

---

## Autor

Proyecto desarrollado como ejercicio academico — Tercer semestre, Ingenieria en Software.

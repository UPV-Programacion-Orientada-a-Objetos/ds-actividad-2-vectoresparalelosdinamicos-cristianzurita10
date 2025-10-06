[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/aWT1eIpo)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20921189)
# Problema: Sistema de Despacho Logístico con Prioridad Dinámica

## Vectores paralelos nidámicos

### Definición del Problema

La empresa de distribución logística "MegaEnvío" necesita optimizar la carga y el despacho de paquetes en su almacén principal. Los paquetes llegan constantemente y deben ser procesados en orden de llegada (FIFO), pero la capacidad de la flota de camiones y la prioridad de los paquetes varían dinámicamente. Necesitamos un sistema que simule la cola de despacho y la gestión de paquetes en espera.

El sistema debe utilizar vectores paralelos dinámicos (asignados con new[]) para almacenar la información de todos los paquetes en el sistema (tanto los despachados como los que esperan). La estructura de Cola (FIFO) se implementará utilizando los índices de estos vectores paralelos para gestionar el orden de despacho.

Los datos clave del paquete a manejar son:

  * ID de Paquete: Identificador único del paquete.
  * Peso (kg): Peso del paquete.
  * Destino: Cadena que indica la ciudad de destino.
  * Prioridad: Nivel de prioridad (1 = Alta, 2 = Media, 3 = Baja).
  * Estado: Estado actual ('E' = En cola, 'D' = Despachado).

El desafío principal radica en manejar la memoria dinámicamente y reubicar o "despachar" los elementos de la cola sin liberar la memoria del paquete hasta que el sistema se cierre.

---

### Requisitos Funcionales y No Funcionales

**Requisitos Funcionales**

1. Inicialización Dinámica: Al iniciar, el programa debe asignar un conjunto inicial de memoria para los cinco vectores paralelos para un tamaño inicial máximo de 50 paquetes.
2. Manejo de Cola (FIFO):
    * **Encolar (Agregar Paquete)**: Simular la llegada de un nuevo paquete. Si los vectores paralelos están llenos, el programa debe duplicar la capacidad actual de todos los vectores.
    * **Desencolar (Despachar Paquete)**: Simular el despacho del paquete que ha estado más tiempo en la cola (FIFO). En lugar de eliminar el paquete de los arreglos, solo se debe cambiar su campo Estado a 'D' (Despachado) y actualizar los índices de inicio de la cola.
3. **Inspección de la Cola**: Permitir al usuario ver la información completa del paquete que está actualmente al frente de la cola (el próximo a ser despachado).
4. **Búsqueda y Reporte**: El usuario puede ingresar un destino y el programa debe listar:
   * El total de paquetes con ese destino que están 'E' (En cola).
   * El peso promedio de todos los paquetes 'E' (En cola) que tienen ese destino.
5. **Terminación Segura**: Antes de salir, el programa debe liberar correctamente toda la memoria asignada dinámicamente para cada vector paralelo y sus contenidos.

**Requisitos No Funcionales**

1. **Asignación Manual**: El crecimiento de los vectores paralelos (si se llena la capacidad) debe ser implementado manualmente utilizando punteros.
2. **Complejidad**: La simulación de la cola debe ser eficiente, evitando la reubicación física de los datos del paquete en la memoria al desencolar. Solo los índices deben ser modificados.
3. **Robustez**: El programa debe manejar la escasez de memoria al intentar expandir los arreglos y reportar errores apropiadamente.

---

### Ejemplo de Salida del Sistema

```bash
--- Sistema de Despacho Logístico MegaEnvío (Modo Punteros) ---

Inicializando sistema con capacidad para 50 paquetes...
Capacidad actual: 50. Paquetes en cola: 0.

Seleccione una operación:
1. Agregar Paquete (Encolar)
2. Despachar Paquete (Desencolar)
3. Inspeccionar Frente de Cola
4. Reporte por Destino
5. Salir (Liberar Memoria)

Opción seleccionada: 1
Ingrese ID: 101, Peso: 5.5, Destino: New York, Prioridad (1-3): 1
Paquete 101 encolado. Capacidad utilizada: 1/50.

Opción seleccionada: 1
Ingrese ID: 102, Peso: 12.0, Destino: Miami, Prioridad (1-3): 2
Paquete 102 encolado. Capacidad utilizada: 2/50.

Opción seleccionada: 3
Frente de la cola:
  ID: 101 | Peso: 5.5 kg | Destino: New York | Prioridad: Alta

Opción seleccionada: 2
Despachando paquete...
Paquete 101 despachado con éxito. Estado: 'D'.

Opción seleccionada: 4
Ingrese el destino para el reporte: Miami
Reporte para destino 'Miami':
  Paquetes En Cola: 1
  Peso Promedio: 12.00 kg

Opción seleccionada: 5
Liberando 50 bloques de memoria asignada...
Sistema cerrado. ¡Memoria libre!
```
# Sistemas Embebidos
Repositorio para el seminario de sistemas embebidos 66.48

- Diego Luna
- Juan C. Suárez

# Documentación del TP3
**Objetivo**

- Uso del IDE (edición, compilación y depuración de programas).
- Uso de GPIO & FreeRTOS (manejo de Salidas y de Entradas Digitales en Aplicaciones).
- Documentar lo que se solicita en c/ítems.

# Contenidos

- [**IDE**](#IDE)
- [**Análisis del proyecto del proyecto freertos_examples_1_to_9**](#freertosexamples1to9 )
- [**Análisis del proyecto del proyecto freertos_examples_10_to_16**](#freertosexamples10to16)
- [**Implementación 1: Tarea 1 periódica**](#punto4)
- [**Implementación 2: Intercambio de las palabras semáforo <--> cola**](#punto5)
- [**Implementación 3: Tareas de secuencia fija**](#punto6)
- [**Hoja de ruta**](#HojadeRuta)

# 1 IDE <a name=IDE></a>

### 1.a Instalacion de software
Se utilizó **MCUXpresso** somo **IDE**. Se creó un Workspace de nombre *workspace-EDU_CIAA_NXP-TP3*. Se importó la carpeta descomprimida de *LPCXpresso-FreeRTOS-Examples.zip* mediante la opción *import project(s) from file system*. Dicha carpeta contiene los proyectos:

- lpc_chip_43xx (librería p/chips LPC43xx de NXP).
- lpc_board_nxp_lpcxpresso_4337 (librería p/placas NXP).
- freertos_examples_1_to_9 (ejemplos de aplicación). 
- freertos_examples_10_to_16 (ejemplos de aplicación).


![importProject](Imagenes/importProject.jpeg)


# 2 Análisis del proyecto del proyecto **freertos_examples_1_to_9* <a freertosexamples1to_9></a>

Para cada uno de los ejemplos 1 a 9, se analizó el comportamiento de sus tareas involucradas a través del desarrollo de un  diagrama temporal, para plasmar la distribución del tiempo de CPU entre tareas, Kernel e interrupciones.

### Example 1
El ejemplo 1 consta de dos tareas (*Task1* y *Task2*) de prioridad *tskIDLE_PRIORITY + 1UL*. *Task1* enciende el LED3 y *Task2* apaga lo apaga. 

![Example1_1](Imagenes/Example1_1.png)


### Example 2
El ejemplo 2 consta de dos tareas (*Task1* y *Task2*) de prioridad *tskIDLE_PRIORITY + 1UL* que comparten la ejecución de la función *vTaskFunction*. Esta función hace destellar el LED3 con la instrucción *Board_LED_Toggle(LED3)*. La ejecución de las tareas hace que el destello del led sea muy corto sin que el periodo sea fijo. El diagrama temporal es similar al del ejemplo2. 

![Example2](Imagenes/Example2.png)

### Example 3
El ejemplo 3 consta de dos tareas (*Task1* y *Task2*), de prioridades tskIDLE_PRIORITY + 1UL*  y *tskIDLE_PRIORITY + 2UL*, respectivamente. Las dos tareas comparten la ejecución de la función *vTaskFunction*. Esta función hace destellar el LED3 con la instrucción *Board_LED_Toggle(LED3)*. La tarea 2 tiene una prioridad más alta que la tarea 1 y será la única tarea en ejecutarse (estado *RUNNING*) debido a que el *scheduler* siempre seleccionará la tarea de mayor prioridad para ejecutar. Como la Tarea 1 nunca entra en el estado *RUNNING*, nunca imprime su string (*Task 1 is running*). El destello del *LED3* se puede ver mejor que en el ejemplo2. 

![Example3](Imagenes/Example3.png)

### Example 4
El ejemplo 4 consta de dos tareas (*Task1* y *Task2*),de prioridades tskIDLE_PRIORITY + 1UL*  y *tskIDLE_PRIORITY + 2UL*, respectivamente.
Las dos tareas comparten la ejecución de la función *vTaskFunction*. Esta función hace destellar el LED3 con la instrucción*Board_LED_Toggle(LED3)*. A su vez, al ser *Task2* de mayor prioridad, hace que se imprima primero el mensaje (*Task 2 is running*) y en la siguiente lìnea (*Task 1 is running*). El orden de ejecuciòn: *Task1*-*Task2* hace que el led destelle por intervalos cortos y luego las tareas pasan a estado *Blocked*, ejecutàndose la *Idle task* durante el periodo de 250 ms definido por *vTaskDelay(250 / portTICK_RATE_MS)*

![Example4](Imagenes/Example4.png)

### Example 5

El diagrama temporal del ejemplo 5 es el mismo del ejemplo 4, salvo que con el uso de *xLastWakeTime = xTaskGetTickCount()* y *vTaskDelayUntil(&xLastWakeTime, (250 / portTICK_RATE_MS))* se garantiza el tiempo en que las tareas salen del estado *Blocked*.

![Example5](Imagenes/Example5.png)

### Example 6

El ejemplo 6 consta de tres tareas (*Task1*, *Task2* y *Task3*)
*Task1* , *Task2* de *tskIDLE_PRIORITY + 1UL* y *Task3* de prioridad *tskIDLE_PRIORITY + 2UL*
![Example6](Imagenes/Example6.png)

### Example 7

Se imprime  el mensaje de contador *DEBUGOUT("Idle ulCycleCount %d %s", ulIdleCycleCount, pcTaskName)* durante el periodo inexacto definido por
*vTaskDelay(250 / portTICK_RATE_MS)*. *Idle ulCycleCount* incrementa su valor a través de la función *vApplicationIdleHook()* ejecutando *Idle Task Hook*.
![Example7](Imagenes/Example7.png)

### Example 8
*Task1* tiene mayor prioridad que *Task2*  y a través de *uxTaskPriorityGet()* y *vTaskPrioritySet((xTaskHandle)NULL, (uxPriority - 2))* se invierten las prioridades. 

![Example8](Imagenes/Example8.png)

### Example 9
La *Task1* tiene prioridad 1 y al ejecutarse crea a *Task2* con prioridad 2, luego *Task2* tiene mayor prioridad y pasa a ejecutarse inmediatamente. La *Task2* no hace algo salvo usar *vTaskDelete(xTask2Handle)* para borarse a sí misma. 

![Example9](Imagenes/Example9.png)
# 3 Análisis del proyecto **freertos_examples_10_to_16* <a freertosexamples10to_16></a>

### Example 10

![Example10](Imagenes/Example10.png)

### Example 11
El ejemplo 11 es similar al ejemplo 10, pero las prioridades de la tarea se invierten, por lo que la tarea de recepción tiene una prioridad menor que las tareas de envío. También la cola se usa para pasar estructuras entre las tareas en lugar de simples enteros largos.
En el ejemplo 11, las tareas de envío tienen la mayor prioridad, por lo que la cola normalmente estará llena. Esto se debe a que tan pronto como la tarea de recepción elimine un elemento de la cola, será reemplazado por una de las tareas de envío que luego volverá a llenar la cola. La tarea de envío volverá a ingresar al estado *Blocked* para esperar a que el espacio vuelva a estar disponible en la cola.

En el tiempo t5, *Sender2* intenta escribir datos en la cola. Debido a que la cola ya está llena, *Sender2* ingresa al estado bloqueado para esperar a que haya espacio disponible, lo que permite que *Sender1* se ejecute una vez más.
![Example11](Imagenes/Example11.png)

### Example 12

![Example12](Imagenes/Example12.png)

### Example 13

![Example13](Imagenes/Example13.png)

### Example 14

![Example14](Imagenes/Example14.png)


### Example 15

![Example15](Imagenes/Example15.png)

### Example 16

![Example16](Imagenes/Example16.png)


# 4 Implementación 1 <a Implementación1></a>

# 5 Implementación 2 <a Implementación2></a>

# 6 Implementación 3 <a Implementación2></a>

# 7 Hoja de ruta <a name=HojadeRuta></a>
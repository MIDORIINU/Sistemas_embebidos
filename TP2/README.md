# TP2
**Objetivo**
- **Uso del IDE** edición, compilación y depuración de programas.
- **Uso de GPIO & Diagrama de Estado** manejo de Salidas y Entradas Digitales en Aplicaciones.
- **Documentar lo que se solicita en c/ítems** 

# 1 IDE

### 1.a.1 Instalacion de software
Se insatalaron los complementos de OpenOCD, eGit y Yakindu StateChart  siguiendo los pasos de la instalación y configuración del *IDE* enunciados en la [guía de instalación de herramientas](https://campus.fi.uba.ar/pluginfile.php/307047/mod_resource/content/5/Sistemas_Embebidos-2019_2doC-Instalacion_de_Herramientas-Cruz.pdf)


### 1.a.2 Instalacion del plugin de Yakindu SCT
Dentro de Eclipse, se agregó el plug-in Yakindu StateChart Tools Menú Help → Install New Software … Work with: http://updates.yakindu.org/sct/mars/releases/. Se selecciono el plug-in y luego se sigio las instrucciones del asistente. 


### 1.a.3 Edición de código y debug 

Para el proceso de *edición de código* y *debug* se iguieron los siguientes pasos:

- 1.  Se Selecciono como nombre de Workspace: workspace-SE-2019-TPs (el mismo que utilizó para el TP1).

- 2. En el archivo project.mk se configuro el proyecto, el procesador y la placa a utilizar:

> -  PROJECT = sapi_examples/edu-ciaa-nxp/statecharts/statecharts_bare_metal	
> -  TARGET = lpc4337_m4
> -  BOARD = edu_ciaa_nxp


- 3.  Se copiaron en la carpeta sapi_examples/edu-ciaa-nxp/statcharts/statecharts_bare_metal/gen/ los archivos:

> - a. prefix.sct. Se copio y pego Blinky.-sct y  se renombro como: prefix.sct
> - b. pregix.sgen

Los cambios se pueden visualizar en la siguiente figura:

![renombrar_prefix_sct.png](Imagenes/renombrar_%20prefix_sct.png)

- 4. Para Simular el modelo se hizo clic derecho sobre *prefix.sct -> Run Us -> 1 Satechart Simulation*. Para ver los cambios en los estados (de APAGADO a ENCENDIDO) se hizo clic sobre la opción evTick en la ventana *Simulation* :

![simulacion_statecharts_bare_metal](Imagenes/simulacion_statecharts_bare_metal.png)


- 5. Para Generar el código del modelo se dió clic derecho sobre *pregix.sgen -> Generate Code Artifacts (Artifacts => Prefix.c, Prefix.h, PrefixRequired.h y sc_types.h)*


- 6. Luego se Compilo y debugeo firmware_v2 cambiando la ruta de debug por C:\firmware_v2\out\lpc4337_m4\statecharts_bare_metal.axf


Dentro de la carpeta *gen* se se encuentran los archivos: *Prefix.c, Prefix.h, PrefixRequired.h, sc_types.h, prefix.sct, prefix.sgen*. Su descripción se detalla a continuación:

| Nombre del archivo | Descripción |
| ------ | ----------- |
|Prefix.c| Fuente con el nombre del statechart Prefix.sct |
|Prefix.h | Fuente con el nombre del statechart Prefix.sct |
|PrefixRequired.h|Prototipos de funciones)  |
|sc_types.h| Prototipos de variables) |
|prefix.sct | Yakindu SCT Statechart Model file |
|prefix.sgen|  Yakindu SCT Code Generator Model file |


- 7. Para probar la función de debug se puso un breakpoint en la funcion que cambia de estado el led para ver el cambio de estado debido a que la frecuencia de interrupcion seteada en el programa es demasiado rapida para ver el cambio a simple vista:

![1a7_breackpoint_breakpoint.png](Imagenes/1a7_breackpoint_breakpoint.png)

## 1.b funciones 

En la siguiente tabla se puede visualizar las siguientes funciones:


| Nombre | Descripción |
| ------ | ----------- |
|  boardConfig(); | configura los pines de entrada y salida    |
|  tickConfig( TICKRATE_MS );  | configura la frecuencia de la interrupciones    |
|  tickCallbackSet( myTickHook, (void*)NULL );  | configura la funcion que se ejecutara con cada interrupcion    |
|  InitTimerTicks(ticks, NOF_TIMERS); | incializa la frecuencia del timer   |
|  prefix_init(&statechart);  | inicializa la maquina de estados    |
|  prefix_enter(&statechart);   |  cambia el estado de la maquina de estados   |
|  UpdateTimers(ticks, NOF_TIMERS);  | actualiza la frecuencia del timer    |
|  prefixIface_raise_evTick(&statechart);| activa el evento etick |
|  IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid)       | devuelve true si se cumplio el tiempo de eventos dado por NOF_TIMERS|
|  prefix_raiseTimeEvent(&statechart, ticks[i].evid);   |  activa el evento etick   |
|  MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);   |  setea el evento pendiente en false  |
|  prefix_runCycle(&statechart);   | cambia el estado de la maquina de estados  |


![1b1_funciones.png](Imagenes/1b1_funciones.png)

![1b2_funciones.png](Imagenes/1b2_funciones.png)


## 1.c Constantes y variables.

En la siguiente tabla se puede visualizar las siguientes constantes:

| Nombre | Descripción |
| ------ | ----------- |
|  TICKRATE_MS   |  setea la frecuencia de interrupciones   |
|  USE_TIME_EVENTS  | flag utilizado para decididir si se ejecutan eventos por tiempo o no    |
|  NOF_TIMERS  |  constante utilizada para definir el tiempo de cada evento  |
|  SysTick_Time_Flag  |  flag utilizado para saber si se produjo una interrupcion  |

![Constantes_Variables.png](Imagenes/Constantes_Variables.png)

## 2. Uso del IDE (Integrated Development Environment) Eclipse 2019 & plug-in Yakindu SCT


## 2.a Migrar proyecto
Se migró el proyecto sapi_examples/edu-ciaa-nxp/statchart/statechart_bare_metal (parpadeo del LEDs c/sAPI & Yakindu SCT) 
a: projects/TP2 dentro firmware_v2.

## 2.b Generacion de códigos con statecharts
Para cada caso se copio los archivos Blinky.-sct,BlinkyTimeEvent.-sct,Button.-sct,ldelBlinky.-sct, Application.-sct,Porton.-sct y se los renombro como prefix.sct cada uno por separado. .Luego se genero el codigo de cada uno por separado. Para generar los codigos fuentes correspondientes de cada maquina de estado se usaron los archivos de prefix.sgen -> generate code artifacts.Como se puede visualizar en la siguiente figura:

![2b_codigo_generado.png](Imagenes/2b_codigo_generado.png)


*Global-Makefile*


### 2.c Prueba de simulaciones

Con los codigos generados en el punto anterior se modifico el #define TEST (SCT_?) con ? ={1,2,3,4,5} en el main.c para seleccionar entre los diferentes casos de las maquinas de estado como se puede visualizar en la siguiente figura:

![2c_Simulaciones.png](Imagenes/2c_Simulaciones.png)




# Implementacion de las máquinas de estados finitos (MEF)

Para la implementacion de la maquina de estados para cada uno de los casos propuestos,se realizaron los diagramas de estado,se generaron los codigos fuente(prefix.sgen -> generate code artifacts) y se modifico el archivo makefile, añadiendo la opción de compilación paralela:

## 3. Panel de control de un generador de señales
Las diferentes MEFs utilizadas, dado que se trata de una MEF compuesta son: 
*SHAPE*, *MODE*, *BUTTONS*

*SHAPE*
![GeneradorSenales_Shape.png](Imagenes/GeneradorSenales_Shape.png)

*MODE*
![GeneradorSenales_Mode.png](Imagenes/GeneradorSenales_Mode.png)

*BUTTONS*
![GeneradorSenales_Buttons.png](Imagenes/GeneradorSenales_Buttons.png)

![GeneradorSenalesPrefix.png](Imagenes/GeneradorSenalesPrefix.png)

## 4. Puerta corrediza

## 5. Portón de cochera

## 6. Escalera mecánica 

## 7. Horno microondas
Para el caso de horno microondas se tuvo en cuenta: 3 modos de cocción seleccionable por botón de modo, botón de comenzar/terminar y sensor de apertura de puerta.

A continuación se muestran las diferentes MEFs utilizadas, dado que se trata de una MEF compuesta: *MODE*, *BUTTONS*, *SENSORS* y *OVEN* 

*MODE*
![HornoMicroondas_Mode.png](Imagenes/HornoMicroondas_Mode.png)

*BUTTONS*
![HornoMicroondas_Buttons.png](Imagenes/HornoMicroondas_Buttons.png)

*SENSORS* 
![HornoMicroondas_Sensors.png](Imagenes/HornoMicroondas_Sensors.png)

*OVEN*
![HornoMicroondas_Oven.png](Imagenes/HornoMicroondas_Oven.png)

![HornoPrefix.png](Imagenes/HornoPrefix.png)
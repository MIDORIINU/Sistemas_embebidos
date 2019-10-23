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

![renombrar_prefix_sct.png](https://github.com/MIDORIINU/Sistemas_embebidos/blob/master/TP2/Imagenes/renombrar_%20prefix_sct.png)

- 4. Para Simular el modelo se hizo clic derecho sobre *prefix.sct -> Run Us -> 1 Satechart Simulation*. Para ver los cambios en los estados (de APAGADO a ENCENDIDO) se hizo clic sobre la opción evTick en la ventana *Simulation* :

![simulacion_statecharts_bare_metal](https://github.com/MIDORIINU/Sistemas_embebidos/blob/master/TP2/Imagenes/simulacion_statecharts_bare_metal.png)


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

![1a7_breackpoint_breakpoint.png](https://github.com/MIDORIINU/Sistemas_embebidos/blob/master/TP2/Imagenes/1a7_breackpoint_breakpoint.png)


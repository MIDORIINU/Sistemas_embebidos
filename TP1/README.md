# Sistemas Embebidos
Repositorio para el seminario de sistemas embebidos 66.48

- Diego Luna
- Daniel Romero
- Juan C. Suárez

# Documentación del TP1
**Objetivo**
- **Uso del IDE** edición, compilación y depuración de programas.
- **Uso de GPIO** manejo de Salidas y Entradas Digitales.
- **Documentar lo que se solicita en c/ítems** 

# 1 IDE
Se descargó LPCXpresso 8.2.0 y se insatalaron los complementos de OpenOCD, eGit y Yakindu StateChart Tools siguiendo los pasos de la [hoja de ayuda](https://campus.fi.uba.ar/pluginfile.php/307047/mod_resource/content/5/Sistemas_Embebidos-2019_2doC-Instalacion_de_Herramientas-Cruz.pdf) de la materia.


![](Imagenes/Im00_Instalacion_Activacion.png)
<SUB>**Registro del IDE en la página de NXP**




Otras opciones de IDE, son el **MCUXPRESSO**, también de **NXP** o el **ECLIPSE** original, los anteriores son versiones modificadaas de este último. Para estos otros IDE los pasos son similares, ya que los plugins son plugins de Eclipse, pero no es necesario el paso de registro que **NXP** exige para **LPCXpresso**.

## 1.1 Firmware
Utilizando git se descargó el repositorio *firmware_v2* y se copió el archivo *project.mk.template* a *project.mk* utilizando los siguientes comandos:
```sh
$ git clone https://github.com/ciaa/firmware_v2.git
$ cd firmware_v2
$ git status -s
$ git checkout master
$ cp project.mk.template project.mk
```
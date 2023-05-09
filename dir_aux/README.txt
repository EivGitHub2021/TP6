Para el TP4:
git submodule init -> copia la direccion del repositorio
git submodule update -> descarga el repositorio
Labredes18
se modifica al archivo launch.json en muju/.vscode
./external/base/mcu/lpc4337-m4/openocd/openocd.cfg
para programar la placa se sustituye el archivo openocd.cfg de la carpeta de dir_aux en la direccion mencionada en la linea superior
make -> para compilar
make download -> para programar la placa
configuracion del virtual box: configuracion->usb->agregar dispo->FTDI
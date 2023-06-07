/************************************************************************************************
Copyright (c) 2023, Pablo Rivas

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** \brief Implementacion del modulo de alumnos
 **
 ** \addtogroup alumno Alumno
 ** \brief Modulo para gestion de aulumno
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "digital.h"
#include "chip.h"
#include <stdint.h>

/* === Macros definitions ====================================================================== */
// define un parametro que determina el tamaño de la estructura de las salidas, si no esta definido antes
#ifndef OUTPUT_INSTANCES
#define OUTPUT_INSTANCES 4
#endif
// define un parametro para determinar el tamaño de la estructura de las entradas, si no esta difinido antes
#ifndef INPUT_INSTANCES
#define INPUT_INSTANCES 4
#endif
/* === Private data type declarations ========================================================== */

//! Estructura para almacenar el descriptor de una salida digital
struct digital_output_s {
    uint8_t port;   //!< Puerto GPIO
    uint8_t pin;    //!< Terminal del puerto GPIO de la salida digital
    bool allocated; //!< Bnadera para indicar el uso
    bool inverted;  //!< Determina si usa logica activa en alta o baja
};

//! Estructura para almacenar entradas digitales
struct digital_input_s {
    uint8_t port;    //!< Almacena el numero del puerto de entrada
    uint8_t pin;     //!< Almacena el numero de la terminal de entrada
    bool allocated;  //!< Bandera para indicar el uso
    bool inverted;   //!< Determina si usa logica activa en alta o baja
    bool last_state; //!< Almacena el estado de la tecla
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */
digital_output_t DigitalOutputAllocate(void);

digital_input_t DigitalInputAllocate(void);
/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
// busca un lugar en el arreglo de estructuras de SALIDAS creado, lo reserva y envia su puntero
digital_output_t DigitalOutputAllocate(void) {
    digital_output_t output = NULL;

    static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

    for (int i = 0; i < OUTPUT_INSTANCES; i++) {
        if (!instances[i].allocated) {
            instances[i].allocated = true;
            output = &instances[i];
            break;
        }
    }
    return output;
}
// busca un lugar en el arreglo de estructuras de ENTRADAS creado, lo reserva y envia su puntero
digital_input_t DigitalInputAllocate(void) {
    digital_input_t input = NULL;

    static struct digital_input_s instancias[INPUT_INSTANCES] = {0};

    for (int i = 0; i < INPUT_INSTANCES; i++) {
        if (!instancias[i].allocated) {
            instancias[i].allocated = true;
            input = &instancias[i];
            break;
        }
    }
    return input;
}

/* === Public function implementation ========================================================== */
// completa la una estructura de SALIDA con los valores en el puntero solicitado si el punero no es null
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted) {
    digital_output_t output = DigitalOutputAllocate();

    if (output) {
        output->port = port;
        output->pin = pin;
        output->inverted = inverted;

        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
    }
    return output;
}
// activa una SALIDA
void DigitalOutputActivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);

    return;
}
// desactiva una SALIDA
void DigitalOutputDesactivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);

    return;
}
// cambia de estado una SALIDA
void DigitalOutputToggle(digital_output_t output) {
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);

    return;
}
// completa la una estructura de ENTRADA con los valores en el puntero solicitado si el punero no es null
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted) {
    digital_input_t input = DigitalInputAllocate();

    if (input) {
        input->port = port;
        input->pin = pin;
        input->inverted = inverted;

        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->port, input->pin, false);
    }

    return input;
}
// obtiene el estado de la tecla y la invierte si inverted esta activo
bool DigitalInputGetState(digital_input_t input) {
    return (!input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin));
}
// lee el estado actual de la ENTRADA, determina si cambio y almacena el nuevo estado
bool DigitalInputHasChange(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (state != input->last_state);

    input->last_state = state;

    return result;
}
// determina si la ENTRADA fue activada y almacene el estado actual
bool DigitalInputHasActivate(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (state && !input->last_state);

    input->last_state = state;

    return result;
}
// determina si la ENTRADA fue desactivada y almacena el estado actual
bool DigitalInputHasDesactivate(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (!state && input->last_state);

    input->last_state = state;

    return result;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */

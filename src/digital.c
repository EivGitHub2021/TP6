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
//define un parametro que determina el tamaño de la estructura si no esta definido antes
#ifndef OUTPUT_INSTANCES
   #define OUTPUT_INSTANCES 4
#endif
/* === Private data type declarations ========================================================== */

//! Estructura para almacenar el descriptor de una salida digital
struct digital_output_s{
   uint8_t port;  //!< Puerto GPIO
   uint8_t pin;   //!< Terminal del puerto GPIO de la salida digital
   bool allocated;   //!< Bnadera para indicar el uso
};


/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */
digital_output_t DigitalOutputAllocate(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
//busca un lugar en el arreglo de estructuras creado, lo reserva y envia su puntero
digital_output_t DigitalOutputAllocate(void){
   digital_output_t output = NULL;

   static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

   for (int i = 0; i < OUTPUT_INSTANCES; i++){
      if (!instances[i].allocated){
         instances[i].allocated = true;
         output = &instances[i];
         break;         
      }
      
   }
   return output;
}

/* === Public function implementation ========================================================== */
//completa la una estructura con los valores en el puntero solicitado si el punero no es null
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin){
   digital_output_t output = DigitalOutputAllocate();

   if (output)
   {
      output->port = port;
      output->pin = pin;

      Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
      Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);

   }
   // output.port = port;
   // output.pin = pin;

   // Chip_GPIO_SetPinState(LPC_GPIO_PORT, output.port, output.pin, false);
   // Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output.port, output.pin, true);

   // return &output;
   return output;
}
void DigitalOutputActivate(digital_output_t output){
   Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);
   return;
}
void DigitalOutputDesactivate(digital_output_t output){
   Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
   return;
}
void DigitalOutputToggle(digital_output_t output){
   Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);
   return;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */

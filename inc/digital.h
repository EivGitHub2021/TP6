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

#ifndef DIGITAL_H
#define DIGITAL_H

/** \brief Declaraciones publicas del modulo de alumnos
 **
 ** \addtogroup alumno Alumno
 ** \brief Modulo para gestion de aulumno
 ** @{ */

/* === Headers files inclusions ================================================================ */
#include "define.h"
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */
//! Referencia para gestionar la salida digital
typedef struct digital_output_s * digital_output_t;

//! Referencia para gestionar las entradas digitales
typedef struct digital_input_s * digital_input_t;

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */
/**
 * @brief Modo para crear una salida digital
 *
 * @param port Puerto GPIO que contiene la salida
 * @param pin Numero de terminal del puerto
 * @return digital_output_t Puntero a la salida creada
 */
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted);

/**
 * @brief Modo para activar la salida
 *
 * @param output puntero al descrptor de la salida
 */
void DigitalOutputActivate(digital_output_t output);

/**
 * @brief Modo para desactivar la salida
 *
 * @param output puntero al descrptor de la salida
 */
void DigitalOutputDesactivate(digital_output_t output);

/**
 * @brief Modo para cambiar de estado la salida
 *
 * @param output puntero al descrptor de la salida
 */
void DigitalOutputToggle(digital_output_t output);

/**
 * @brief Crea una entrada digital
 *
 * @param port Numero del puerto de la entrada GPIO
 * @param pin Numero del termial del puerto
 * @return digital_input_t Puntero de refencia de la salida
 */
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted);

/**
 * @brief Obtiene el estado del boton
 *
 * @param tecla Puntero al boton designado
 * @return true Estado actual del boton
 * @return false Estado actual del boton
 */
bool DigitalInputGetState(digital_input_t input);

/**
 * @brief Detecta cuando hay un cambio en el estdo de la tecla
 *
 * @param tecla Puntero al objeto tecla
 * @return true
 * @return false
 */
bool DigitalInputHasChange(digital_input_t input);

/**
 * @brief Detecta cuando la tecla se activa
 *
 * @param tecla Puntero al objeto tecla
 * @return true
 * @return false
 */
bool DigitalInputHasActivate(digital_input_t input);

/**
 * @brief Detecta cuando la tecla se desactiva
 *
 * @param tecla Puntero al objeto tecla
 * @return true
 * @return false
 */
bool DigitalInputHasDesactivate(digital_input_t input);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* DIGITAL_H */
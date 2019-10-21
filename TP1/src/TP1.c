/*
        TP1

        Diego Luna
        Daniel Romero
        Juan C. Su�rez

*/


/*==================[inclusions]=============================================*/

#include "TP1.h"   // <= own header (optional)
#include "sapi.h"       // <= sAPI header

/*==================[macros and definitions]=================================*/
#define TP1_1 1
#define TP1_2 2
#define TP1_3 3


#define TP1_PROJECT TP1_3

/*      The DEBUG* functions are sAPI debug print functions.
        Code that uses the DEBUG* functions will have their I/O routed to
        the sAPI DEBUG UART. */
DEBUG_PRINT_ENABLE;


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
#if (TP1_PROJECT == TP1_3)
        /* FUNCION que se ejecuta cada vez que ocurre un Tick. */
        static void myTickHook(void* ptr);
#endif



/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{
        /* ------------- INICIALIZACIONES ------------- */
        /* Inicializar la placa */
        boardConfig();
        /* UART for debug messages. */
        debugPrintConfigUart(UART_USB, 115200);
        #if (TP1_PROJECT == TP1_2)
        gpioConfig(GPIO0, GPIO_INPUT);
        gpioConfig(GPIO1, GPIO_OUTPUT);
        /* Variable para almacenar el valor de tecla leido */
        bool_t valor;
        #elif (TP1_PROJECT == TP1_3)
        /*      Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
                periodicamente una interrupcion cada 50ms que incrementa un contador de
                Ticks obteniendose una base de tiempos). */
        tickConfig(50);
        /*      Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
                simplemente una funcion que se ejecutara peri�odicamente con cada
                interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
                a una interrupcion.
                El segundo parametro es el parametro que recibe la funcion myTickHook
                al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
        */
        tickCallbackSet(myTickHook, (void*)LEDR);
        delay(1000);
        #endif
        debugPrintString("DEBUG c/sAPI\r\n");
        /* ------------- REPETIR POR SIEMPRE ------------- */
        while(1)
        {
                #if (TP1_PROJECT == TP1_1)
                /* Prendo el led azul */
                gpioWrite(LEDB, ON);
                delay(500);
                /* Apago el led azul */
                gpioWrite(LEDB, OFF);
                delay(500);
                #elif (TP1_PROJECT == TP1_2)
                valor = !gpioRead(TEC1);
                gpioWrite(LEDB, valor);
                valor = !gpioRead(TEC2);
                gpioWrite(LED1, valor);
                valor = !gpioRead(TEC3);
                gpioWrite(LED2, valor);
                valor = !gpioRead(TEC4);
                gpioWrite(LED3, valor);
                valor = !gpioRead(GPIO0);
                gpioWrite(GPIO1, valor);
                #elif (TP1_PROJECT == TP1_3)
                tickCallbackSet(myTickHook, (void*)LEDG);
                debugPrintString("LED RGB G\n");
                delay(1000);
                tickCallbackSet(myTickHook, (void*)LEDB);
                debugPrintString("LED RGB B\n");
                delay(1000);
                tickCallbackSet(myTickHook, (void*)LED1);
                debugPrintString("LED 1\n");
                delay(1000);
                tickCallbackSet(myTickHook, (void*)LED2);
                debugPrintString("LED 2\n");
                delay(1000);
                tickCallbackSet(myTickHook, (void*)LED3);
                debugPrintString("LED 3\n");
                delay(1000);
                tickCallbackSet(myTickHook, (void*)LEDR);
                debugPrintString("LED RGB R\n");
                delay(1000);
                #endif
        }
        /*      NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
                por ningun S.O. */
        return 0 ;
}


/*==================[internal functions definition]==========================*/


#if (TP1_PROJECT == TP1_3)
/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook(void* ptr)
{
        static bool_t ledState = OFF;
        gpioMap_t led = (gpioMap_t)ptr;
        if(ledState)
        {
                ledState = OFF;
        }
        else
        {
                ledState = ON;
        }
        gpioWrite(led, ledState);
}
#endif



/*==================[end of file]============================================*/

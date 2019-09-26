/*
        TP1
*/


/*==================[inclusions]=============================================*/

#include "TP1.h"   // <= own header (optional)
#include "sapi.h"       // <= sAPI header

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


#define TP1_1 1
#define TP1_2 2
#define TP1_3 3


#define TP1_PROJECT TP1_3



#if (TP1_PROJECT == TP1_3)
/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

   static bool_t ledState = OFF;

   gpioMap_t led = (gpioMap_t)ptr;

   if( ledState ){
      ledState = OFF;
   }
   else{
      ledState = ON;
   }
   gpioWrite( led, ledState );
}
#endif


/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{
        /* ------------- INICIALIZACIONES ------------- */
        /* Inicializar la placa */
        boardConfig();

#if (TP1_PROJECT == TP1_2)
        gpioConfig(GPIO0, GPIO_INPUT);
        gpioConfig(GPIO1, GPIO_OUTPUT);
        /* Variable para almacenar el valor de tecla leido */
        bool_t valor;

#elif (TP1_PROJECT == TP1_3)
        /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
           periodicamente una interrupcion cada 50ms que incrementa un contador de
           Ticks obteniendose una base de tiempos). */
        tickConfig( 50 );

        /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
           simplemente una funcion que se ejecutara peri­odicamente con cada
           interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
           a una interrupcion.
           El segundo parametro es el parametro que recibe la funcion myTickHook
           al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
        */
        tickCallbackSet( myTickHook, (void*)LEDR );
        delay(1000);
#endif
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
                tickCallbackSet( myTickHook, (void*)LEDG );
                delay(1000);
                tickCallbackSet( myTickHook, (void*)LEDB );
                delay(1000);
                tickCallbackSet( myTickHook, (void*)LED1 );
                delay(1000);
                tickCallbackSet( myTickHook, (void*)LED2 );
                delay(1000);
                tickCallbackSet( myTickHook, (void*)LED3 );
                delay(1000);
                tickCallbackSet( myTickHook, (void*)LEDR );
                delay(1000);
#endif
        }
        /*      NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
                por ningun S.O. */
        return 0 ;
}

/*==================[end of file]============================================*/

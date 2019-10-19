

/*==================[inclusions]=============================================*/

#include "main.h"
#include "sapi.h"       // <= sAPI header

/*      Include statechart header file. Be sure you run the statechart C code
        generation tool!
*/

#include "Prefix.h"
#include "TimerTicks.h"


/*==================[macros and definitions]=================================*/
/* Compilation choices */
#define SCT_TP2_1 (1)
/*
        TP2 Statechart EDU-CIAA-NXP - Generador de se�ales
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp GeneradorSenales.-sct prefix.sct
*/

#define SCT_TP2_2 (2)
/*
        TP2 Statechart EDU-CIAA-NXP - Puerta corrediza
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp PuertaCorrediza.-sct prefix.sct
*/

#define SCT_TP2_3 (3)
/*
        TP2 Statechart EDU-CIAA-NXP - Port�n cochera
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp PortonCochera.-sct prefix.sct
*/

#define SCT_TP2_4 (4)
/*
        TP2 Statechart EDU-CIAA-NXP - Escalera mec�nica
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp EscaleraMecanica.-sct prefix.sct
*/

#define SCT_TP2_5 (5)
/*
        TP2 Statechart EDU-CIAA-NXP - Horno microondas
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp HornoMicroondas.-sct prefix.sct
*/


#define TICKRATE_1MS    (1)                     /* 1000 ticks per second */
#define TICKRATE_MS             (TICKRATE_1MS)  /* 1000 ticks per second */


/* Select active statechart. */
#define ACTIVE_ST (SCT_TP2_2)

/*==================[internal macro declaration]==============================*/

#if (ACTIVE_ST == SCT_TP2_1)

/* Select a TimeEvents choice   */
#define __USE_TIME_EVENTS (true)

#define __USE_BUTTONS_STATE_CHART (true)

/*      The DEBUG* functions are sAPI debug print functions.
        Code that uses the DEBUG* functions will have their I/O routed to
        the sAPI DEBUG UART. */
DEBUG_PRINT_ENABLE;

#elif (ACTIVE_ST == SCT_TP2_2)

/* Select a TimeEvents choice   */
#define __USE_TIME_EVENTS (true)

#define __USE_BUTTONS_STATE_CHART (true)

/*      The DEBUG* functions are sAPI debug print functions.
        Code that uses the DEBUG* functions will have their I/O routed to
        the sAPI DEBUG UART. */
DEBUG_PRINT_ENABLE;

#endif


/*==================[internal data declaration]==============================*/

static volatile bool SysTick_Time_Flag = false;

/*! This is a state machine */
static Prefix statechart;



/*! This is a timed state machine that requires timer services */
#if (__USE_TIME_EVENTS == true)
#define NOF_TIMERS (sizeof(PrefixTimeEvents)/sizeof(sc_boolean))
#else
#define NOF_TIMERS 0
#endif

TimerTicks ticks[NOF_TIMERS];


/*==================[internal functions declaration]=========================*/

#if (__USE_BUTTONS_STATE_CHART)

static void ImplementButtons(const sc_integer Btn);

static bool RepeatButtons(const sc_integer Btn);

#endif


/**
        @brief       Check for pending time events and raise them.
        @return      none.
*/
static void CheckTimeEvents(void);


#if (__USE_TIME_EVENTS)

/**
        @brief       Hook on Handle interrupt from SysTick timer
        @return      Nothing
*/
static void myTickHook(void* ptr);

#endif

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[main function]===============================*/


/**
        @brief       main routine for statechart TPS.
        @return      Function should not exit.
*/
int main(void)
{
        /* Generic Initialization */
        boardConfig();

        /* UART for debug messages. */
        debugPrintConfigUart(UART_USB, 115200);

        /* Initiate Ticks counter => TICKRATE_MS */
        tickConfig(TICKRATE_MS);

        /* Add Tick Hook */
        tickCallbackSet(myTickHook, (void*)NULL);

        /* Statechart Initialization */
#if (__USE_TIME_EVENTS)
        InitTimerTicks(ticks, NOF_TIMERS);
#endif

        prefix_init(&statechart);

        prefix_enter(&statechart);

#if (ACTIVE_ST == SCT_TP2_1)

        while(1)
        {

                prefix_runCycle(&statechart);

                CheckTimeEvents();

        } //while

#elif (ACTIVE_ST == SCT_TP2_2)

        while(1)
        {

                prefix_runCycle(&statechart);

                CheckTimeEvents();

        } //while


#elif (ACTIVE_ST == SCT_TP2_3)


#elif (ACTIVE_ST == SCT_TP2_4)


#elif (ACTIVE_ST == SCT_TP2_5)


#endif

} //main



/*==================[internal functions definition]==========================*/

#if (ACTIVE_ST == SCT_TP2_1)

static void ImplementButtons(const sc_integer Btn)
{
        switch(Btn)
        {

        case 1: // TEC1
                prefixIface_raise_evSHAPE(&statechart);
                break;
        case 2: // TEC2
                prefixIface_raise_evMODE(&statechart);
                break;
        case 4: // TEC3
                prefixIface_raise_evINCREMENT(&statechart);
                break;
        case 8: // TEC4
                prefixIface_raise_evDECREMENT(&statechart);
                break;

        }
}


static bool RepeatButtons(const sc_integer Btn)
{
        return ((4 == Btn) || (8 == Btn));
}

#elif (ACTIVE_ST == SCT_TP2_2)

static void ImplementButtons(const sc_integer Btn)
{
        switch(Btn)
        {

        case 1: // TEC1

                break;
        case 2: // TEC2
                prefixIface_raise_eBtnClosed(&statechart);
                break;
        case 4: // TEC3
                prefixIface_raise_eBtnOpen(&statechart);
                break;
        case 8: // TEC4
                prefixIface_raise_eBtnPresence(&statechart);
                break;

        }
}


static bool RepeatButtons(const sc_integer Btn)
{
        return false;
}

#endif

/**
        @brief       Check for pending time events and raise them.
        @return      none.
*/
static void CheckTimeEvents(void)
{
        if(SysTick_Time_Flag == true)
        {
                SysTick_Time_Flag = false;
#if (__USE_TIME_EVENTS)
                UpdateTimers(ticks, NOF_TIMERS);

                int i;

                for(i = 0; i < NOF_TIMERS; i++)
                {
                        if(IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true)
                        {
                                prefix_raiseTimeEvent(&statechart, ticks[i].evid); // Event -> Ticks.evid => OK
                                MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
                        }
                }
#else
                prefixIface_raise_evTick(&statechart);                             // Event -> evTick => OK
#endif
                prefix_runCycle(&statechart);                                      // Run Cycle of Statechart
        }
}


#if (__USE_TIME_EVENTS)

/**
        @brief       Hook on Handle interrupt from SysTick timer
        @return      Nothing
*/
static void myTickHook(void* ptr)
{
        SysTick_Time_Flag = true;
}

#endif

/*==================[external functions definition]==========================*/

/*!
        This is a timed state machine that requires timer services
*/


#if (__USE_TIME_EVENTS)
/*! This function has to set up timers for the time events that are required by the state machine. */
/*!
        This function will be called for each time event that is relevant for a state when a state will be entered.
        \param evid An unique identifier of the event.
        \time_ms The time in milli seconds
        \periodic Indicates the the time event must be raised periodically until the timer is unset
*/
void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
        SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}


/*! This function has to unset timers for the time events that are required by the state machine. */
/*!
        This function will be called for each time event that is relevant for a state when a state will be left.
        \param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
        UnsetTimerTick(ticks, NOF_TIMERS, evid);
}

#endif


#if (__USE_BUTTONS_STATE_CHART)

/**     state machine user-defined external function (action)

        @param handle state machine instance
        @param sc_integer state
*/
sc_integer prefixIface_aReadButtons(const Prefix* handle)
{
        uint8_t ret = 0;
        uint8_t idx;

        for(idx = 0; idx < 4; ++idx)
        {
                if(gpioRead(TEC1 + idx) == 0)
                {
                        ret |= 1 << idx;
                }
        }

        return (sc_integer)ret;
}


void prefixIface_aButtons(const Prefix* handle, const sc_integer Btn)
{
        ImplementButtons(Btn);

        prefix_runCycle(&statechart);

}


sc_boolean prefixIface_aRepeatButtons(const Prefix* handle, const sc_integer Btn)
{
        return RepeatButtons(Btn);
}

#endif


#if (ACTIVE_ST == SCT_TP2_1)

void prefixIface_aSetShape(const Prefix* handle, const sc_integer cSHAPE)
{
        if(PREFIX_PREFIXIFACE_CTRIANG == cSHAPE)
        {
                gpioWrite(LEDR, true);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, false);

                stdioPrintf(UART_USB, "SHAPE: TRIANGULAR.\n");
        }
        else if(PREFIX_PREFIXIFACE_CSQUARE == cSHAPE)
        {
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, true);
                gpioWrite(LEDB, false);

                stdioPrintf(UART_USB, "SHAPE: SQUARE.\n");
        }
        else if(PREFIX_PREFIXIFACE_CSINUSOID == cSHAPE)
        {
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, true);

                stdioPrintf(UART_USB, "SHAPE: SINUSOIDAL.\n");
        }

}


void prefixIface_aSetMode(const Prefix* handle, const sc_integer cMODE)
{

        if(PREFIX_PREFIXIFACE_CFREQ == cMODE)
        {
                gpioWrite(LED1, true);
                gpioWrite(LED2, false);
                gpioWrite(LED3, false);

                stdioPrintf(UART_USB, "MODE: FREQUENCY.\n");
        }
        else if(PREFIX_PREFIXIFACE_CVOLT == cMODE)
        {
                gpioWrite(LED1, false);
                gpioWrite(LED2, true);
                gpioWrite(LED3, false);

                stdioPrintf(UART_USB, "MODE: VOLTAGE.\n");
        }
}



void prefixIface_aIncrement(const Prefix* handle, const sc_integer cMODE)
{
        gpioWrite(LED3, true);
        delay(25);
        gpioWrite(LED3, false);

        stdioPrintf(UART_USB, "INCREMENT: %s.\n", (cMODE == PREFIX_PREFIXIFACE_CFREQ)?"frequency":"voltage");

}


void prefixIface_aDecrement(const Prefix* handle, const sc_integer cMODE)
{
        gpioWrite(LED3, true);
        delay(25);
        gpioWrite(LED3, false);

        stdioPrintf(UART_USB, "DECREMENT: %s.\n", (cMODE == PREFIX_PREFIXIFACE_CFREQ)?"frequency":"voltage");

}

#elif (ACTIVE_ST == SCT_TP2_2)

void prefixIface_aSensClosed(const Prefix* handle)
{
        gpioWrite(LED1, true);
        delay(25);
        gpioWrite(LED1, false);

        stdioPrintf(UART_USB, "Puerta cerrada.\n");

        prefixIface_raise_evClosed(&statechart);

        prefix_runCycle(&statechart);

}


void prefixIface_aSensOpen(const Prefix* handle)
{
        gpioWrite(LED2, true);
        delay(25);
        gpioWrite(LED2, false);

        stdioPrintf(UART_USB, "Puerta abierta.\n");

        prefixIface_raise_evOpen(&statechart);

        prefix_runCycle(&statechart);

}


void prefixIface_aSensPresence(const Prefix* handle, const sc_boolean Pres)
{
        gpioWrite(LED3, Pres);

        stdioPrintf(UART_USB, "Presencia: %s.\n", Pres?"SI":"NO");

}


void prefixIface_aControl(const Prefix* handle, const sc_integer cACTION, const sc_boolean cOPEN)
{
        if(PREFIX_PREFIXIFACE_COPEN == cACTION)
        {
                gpioWrite(LEDR, true);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, false);

                stdioPrintf(UART_USB, "MOTOR: ABRIENDO.\n");
        }
        else if(PREFIX_PREFIXIFACE_CCLOSE == cACTION)
        {
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, true);
                gpioWrite(LEDB, false);

                stdioPrintf(UART_USB, "MOTOR: CERRANDO.\n");
        }
        else if(PREFIX_PREFIXIFACE_CSTOP == cACTION)
        {
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, true);

                stdioPrintf(UART_USB, "MOTOR: DETENIDO (%s).\n", cOPEN?"ABIERTO":"CERRADO");
        }

}


#endif

/*==================[end of file]============================================*/

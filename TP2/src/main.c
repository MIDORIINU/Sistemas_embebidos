

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
#define SCT_1 (1)       /* Test Statechart EDU-CIAA-NXP - Blink LED3
                                                #define __USE_TIME_EVENTS (false)
                                                rm prefix.sct
                                                cp Blink.-sct prefix.sct                                                         */
#define SCT_1 (1)       /* Test Statechart EDU-CIAA-NXP - Blink TimeEvent LED3
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp BlinkTimeEvent.-sct prefix.sct                                        */
#define SCT_2 (2)       /* Test Statechart EDU-CIAA-NXP - Idle Blink LED3
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp IdleBlink.-sct prefix.sct                                             */
#define SCT_2 (2)       /* Test Statechart EDU-CIAA-NXP - Button
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp Button.-sct prefix.sct                                                        */
#define SCT_3 (3)       /* Test Statechart EDU-CIAA-NXP - IDE LPCXpresso - Application
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp app.-sct prefix.sct                                                          */
#define SCT_3 (3)       /* Test Statechart EDU-CIAA-NXP - IDE LPCXpresso - Portón
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp Porton.-sct prefix.sct                                                                       */

#define SCT_4 (4)







#define TICKRATE_1MS    (1)                             /* 1000 ticks per second */
#define TICKRATE_MS             (TICKRATE_1MS)  /* 1000 ticks per second */

/*==================[internal data declaration]==============================*/

volatile bool SysTick_Time_Flag = false;

/*! This is a state machine */
static Prefix statechart;


/* Select a TimeEvents choise   */
//#define __USE_TIME_EVENTS (false)       /* "false" without TimeEvents */
#define __USE_TIME_EVENTS (true)      /* or "true" with TimerEvents */

#define TEST (SCT_4)

/*! This is a timed state machine that requires timer services */
#if (__USE_TIME_EVENTS == true)
#define NOF_TIMERS (sizeof(PrefixTimeEvents)/sizeof(sc_boolean))
#else
#define NOF_TIMERS 0
#endif

TimerTicks ticks[NOF_TIMERS];


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*!     \file This header defines prototypes for all functions that are required by the state machine implementation.

        This is a state machine uses time events which require access to a timing service. Thus the function prototypes:
        - prefix_setTimer and
        - prefix_unsetTimer
        are defined.

        This state machine makes use of operations declared in the state machines interface or internal scopes. Thus the function prototypes:
        - prefixIface_opLED
        are defined.

        These functions will be called during a 'run to completion step' (runCycle) of the statechart.
        There are some constraints that have to be considered for the implementation of these functions:
        - never call the statechart API functions from within these functions.
        - make sure that the execution time is as short as possible.

*/
/**     state machine user-defined external function (action)

        @param handle state machine instance
        @param LEDNumber number of LED
        @param onoff state machine operation parameter
*/
void prefixIface_opLED(Prefix* handle, sc_integer LEDNumber, sc_boolean State)
{
        gpioWrite((LEDR + LEDNumber), State);
}


/*!
        This is a timed state machine that requires timer services
*/

#if (__USE_TIME_EVENTS == true)
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
        This function will be called for each time event taht is relevant for a state when a state will be left.
        \param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
        UnsetTimerTick(ticks, NOF_TIMERS, evid);
}
#endif


/**
        @brief       Hook on Handle interrupt from SysTick timer
        @return      Nothing
*/
void myTickHook(void* ptr)
{
        SysTick_Time_Flag = true;
}


#if (TEST == SCT_1)     /* Test Statechart EDU-CIAA-NXP - Blink LED3
                                                #define __USE_TIME_EVENTS (false)
                                                rm prefix.sct
                                                cp Blink.-sct prefix.sct                                                         */
/*      Test Statechart EDU-CIAA-NXP - Blink TimeEvent LED3
        #define __USE_TIME_EVENTS (true)
        rm prefix.sct
        cp BlinkTimeEvent.-sct prefix.sct                                        */
/**
        @brief       main routine for statechart example
        @return      Function should not exit.
*/
int main(void)
{
#if (__USE_TIME_EVENTS == true)
        uint32_t i;
#endif
        /* Generic Initialization */
        boardConfig();
        /* Init Ticks counter => TICKRATE_MS */
        tickConfig(TICKRATE_MS);
        /* Add Tick Hook */
        tickCallbackSet(myTickHook, (void*)NULL);
        /* Statechart Initialization */
#if (__USE_TIME_EVENTS == true)
        InitTimerTicks(ticks, NOF_TIMERS);
#endif
        prefix_init(&statechart);
        prefix_enter(&statechart);
        /* LEDs toggle in main */
        while(1)
        {
                __WFI();
                if(SysTick_Time_Flag == true)
                {
                        SysTick_Time_Flag = false;
#if (__USE_TIME_EVENTS == true)
                        UpdateTimers(ticks, NOF_TIMERS);
                        for(i = 0; i < NOF_TIMERS; i++)
                        {
                                if(IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true)
                                {
                                        prefix_raiseTimeEvent(&statechart, ticks[i].evid);      // Event -> Ticks.evid => OK
                                        MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
                                }
                        }
#else
                        prefixIface_raise_evTick(&statechart);                         // Event -> evTick => OK
#endif
                        prefix_runCycle(&statechart);                                  // Run Cycle of Statechart
                }
                delay(1500);
        }
}
#endif


#if (TEST == SCT_2)     /* Test Statechart EDU-CIAA-NXP - Idle Blink LED3
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp IdleBlink.-sct prefix.sct                                             */
/*      Test Statechart EDU-CIAA-NXP - Button
        #define __USE_TIME_EVENTS (true)
        rm prefix.sct
        cp Button.-sct prefix.sct                                                        */


uint32_t Buttons_GetStatus_(void)
{
        uint8_t ret = false;
        if(gpioRead(TEC1) == 0)
                ret = true;
        return ret;
}

/**
        @brief       main routine for statechart example
        @return      Function should not exit.
*/
int main(void)
{
#if (__USE_TIME_EVENTS == true)
        uint32_t i;
#endif
        uint32_t BUTTON_Status;
        /* Generic Initialization */
        boardConfig();
        /* Init Ticks counter => TICKRATE_MS */
        tickConfig(TICKRATE_MS);
        /* Add Tick Hook */
        tickCallbackSet(myTickHook, (void*)NULL);
        /* Statechart Initialization */
#if (__USE_TIME_EVENTS == true)
        InitTimerTicks(ticks, NOF_TIMERS);
#endif
        prefix_init(&statechart);
        prefix_enter(&statechart);
        /* LEDs toggle in main */
        while(1)
        {
                __WFI();
                if(SysTick_Time_Flag == true)
                {
                        SysTick_Time_Flag = false;
#if (__USE_TIME_EVENTS == true)
                        UpdateTimers(ticks, NOF_TIMERS);
                        for(i = 0; i < NOF_TIMERS; i++)
                        {
                                if(IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true)
                                {
                                        prefix_raiseTimeEvent(&statechart, ticks[i].evid);      // Event -> Ticks.evid => OK
                                        MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
                                }
                        }
#else
                        prefixIface_raise_evTick(&statechart);                                  // Event -> evTick => OK
#endif
                        BUTTON_Status = Buttons_GetStatus_();
                        if(BUTTON_Status != 0)
                                prefixIface_raise_evTECXOprimido(&statechart);          // Event -> evTECXOprimodo => OK
                        else
                                prefixIface_raise_evTECXNoOprimido(&statechart);        // Event -> evTECXNoOprimido => OK
                        prefix_runCycle(&statechart);                                                   // Run Cycle of Statechart
                }
        }
}
#endif


#if (TEST == SCT_3)     /* Test Statechart EDU-CIAA-NXP - IDE LPCXpresso - Application
                                                #define __USE_TIME_EVENTS (true)
                                                rm prefix.sct
                                                cp Application.-sct prefix.sct                                                          */
/*      Test Statechart EDU-CIAA-NXP - IDE LPCXpresso - Portón
        #define __USE_TIME_EVENTS (true)
        rm prefix.sct
        cp Porton.-sct prefix.sct                                                                       */


uint32_t Buttons_GetStatus_(void)
{
        uint8_t ret = false;
        uint32_t idx;
        for(idx = 0; idx < 4; ++idx)
        {
                if(gpioRead(TEC1 + idx) == 0)
                        ret |= 1 << idx;
        }
        return ret;
}

/**
        @brief       main routine for statechart example
        @return      Function should not exit.
*/
int main(void)
{
#if (__USE_TIME_EVENTS == true)
        uint32_t i;
#endif
        uint32_t BUTTON_Status;
        /* Generic Initialization */
        boardConfig();
        /* Init Ticks counter => TICKRATE_MS */
        tickConfig(TICKRATE_MS);
        /* Add Tick Hook */
        tickCallbackSet(myTickHook, (void*)NULL);
        /* Statechart Initialization */
#if (__USE_TIME_EVENTS == true)
        InitTimerTicks(ticks, NOF_TIMERS);
#endif
        prefix_init(&statechart);
        prefix_enter(&statechart);
        /* LEDs toggle in main */
        while(1)
        {
                __WFI();
                if(SysTick_Time_Flag == true)
                {
                        SysTick_Time_Flag = false;
#if (__USE_TIME_EVENTS == true)
                        UpdateTimers(ticks, NOF_TIMERS);
                        for(i = 0; i < NOF_TIMERS; i++)
                        {
                                if(IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true)
                                {
                                        prefix_raiseTimeEvent(&statechart, ticks[i].evid);      // Event -> Ticks.evid => OK
                                        MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
                                }
                        }
#else
                        prefixIface_raise_evTick(&statechart);                                  // Event -> evTick => OK
#endif
                        BUTTON_Status = Buttons_GetStatus_();
                        if(BUTTON_Status != 0)                                                                  // Event -> evTECXOprimodo => OK
                                prefixIface_raise_evTECXOprimido(&statechart, BUTTON_Status);   // Value -> Tecla
                        else                                                                                                    // Event -> evTECXNoOprimido => OK
                                prefixIface_raise_evTECXNoOprimido(&statechart);
                        prefix_runCycle(&statechart);                                                   // Run Cycle of Statechart
                }
        }
}
#endif

#if (TEST == SCT_4)


/**     state machine user-defined external function (action)

        @param handle state machine instance
        @param sc_integer state
*/

enum {sCUAD = 0, sTRIA, sSEN} stype;

enum {mFREC = 0, mMAGN} mmagfrec;


sc_integer Buttons_GetStatus_(void)
{
        int8_t ret = false;
        uint32_t idx;
        for(idx = 0; idx < 4; ++idx)
        {
                if(gpioRead(TEC1 + idx) == 0)
                        ret |= 1 << idx;
        }
        return ret;
}

void prefixIface_aSetForma(const Prefix* handle, const sc_integer cFORMA)
{

        switch(cFORMA)
        {
        case sCUAD:
                gpioWrite(LEDR, true);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, false);
                break;
        case sTRIA:
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, true);
                gpioWrite(LEDB, false);
                break;
        case sSEN:
                gpioWrite(LEDR, false);
                gpioWrite(LEDG, false);
                gpioWrite(LEDB, true);
                break;

        }

}

void prefixIface_aSetMode(const Prefix* handle, const sc_integer cMODE)
{
        switch((int)(cMODE))
        {
        case mFREC:
                gpioWrite(LED1, false);
                gpioWrite(LED2, true);
                gpioWrite(LED3, false);
                break;

        case mMAGN:
                gpioWrite(LED1, true);
                gpioWrite(LED2, false);
                gpioWrite(LED3, false);
                break;
        }


}

void prefixIface_aTeclas(const Prefix* handle, const sc_integer But)
{
        switch(But)
        {

        case 1: // TEC1
                prefixIface_raise_eFORMA(&statechart);
                break;
        case 2: // TEC2
                prefixIface_raise_eMODE(&statechart);
                break;
        case 4: // TEC3
                prefixIface_raise_eINCREMENT(&statechart);
                break;
        case 8: // TEC4
                prefixIface_raise_eDECREMENT(&statechart);
                break;

        }

        prefix_runCycle(&statechart);

}

void prefixIface_aIncrement(const Prefix* handle, const sc_integer cMODE)
{
        gpioWrite(LED3, true);
        delay(25);
        gpioWrite(LED3, false);
}

void prefixIface_aDecrement(const Prefix* handle, const sc_integer cMODE)
{
        gpioWrite(LED3, true);
        delay(25);
        gpioWrite(LED3, false);

}

/**
        @brief       main routine for statechart example
        @return      Function should not exit.
*/
int main(void)
{

        sc_integer BUTTON_Status;

        /* Generic Initialization */
        boardConfig();
        /* Init Ticks counter => TICKRATE_MS */
        tickConfig(TICKRATE_MS);
        /* Add Tick Hook */
        tickCallbackSet(myTickHook, (void*)NULL);
        /* Statechart Initialization */
#if (__USE_TIME_EVENTS)
        InitTimerTicks(ticks, NOF_TIMERS);
#endif
        prefix_init(&statechart);

        prefix_enter(&statechart);


        while(1)
        {
                BUTTON_Status = Buttons_GetStatus_();


                if(prefix_isStateActive(&statechart, Prefix_TECS_NO_OPRIMIDO) &&
                                (0 != BUTTON_Status))
                {
                        prefixIface_set_buttons(&statechart, BUTTON_Status);

                        prefixIface_raise_evTECSDOWN(&statechart);
                }
                else if(prefix_isStateActive(&statechart, Prefix_TECS_OPRIMIDO) &&
                                (0 == BUTTON_Status))
                {
                        prefixIface_set_buttons(&statechart, 0);

                        prefixIface_raise_evTECSUP(&statechart);

                }
                else if(prefix_isStateActive(&statechart, Prefix_TECS_VALIDACION))
                {
                        if(prefixIface_get_buttons(&statechart) == Buttons_GetStatus_())
                        {
                                prefixIface_raise_evTECSVALID(&statechart);
                        }
                        else
                        {
                                prefixIface_raise_evTECSNOVALID(&statechart);
                        }
                }


                if(
                        prefix_isStateActive(&statechart, Prefix_magnitud_region_INC_FREC) ||
                        prefix_isStateActive(&statechart, Prefix_magnitud_region_DEC_FREC) ||
                        prefix_isStateActive(&statechart, Prefix_magnitud_region_INC_TENS) ||
                        prefix_isStateActive(&statechart, Prefix_magnitud_region_DEC_TENS))
                {
                        prefixIface_raise_eDONE(&statechart);
                }




                prefix_runCycle(&statechart);

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
                                        prefix_raiseTimeEvent(&statechart, ticks[i].evid);      // Event -> Ticks.evid => OK
                                        MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
                                }
                        }
#else
                        prefixIface_raise_evTick(&statechart);                         // Event -> evTick => OK
#endif
                        prefix_runCycle(&statechart);                                  // Run Cycle of Statechart
                }




        }


}

#endif


/** @} doxygen end group definition */

/*==================[end of file]============================================*/

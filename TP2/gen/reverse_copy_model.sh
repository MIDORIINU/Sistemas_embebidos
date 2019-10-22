#!/bin/bash

if [ -z "$1" ] ; then
        echo "Error: Missing model number."
        exit 1
fi

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

cd "${SCRIPTPATH}"

if [ "$1" -eq 1 ] ; then
        echo "Copying GeneradorSenales.-sct"
        rm ./GeneradorSenales.-sct
        cp ./prefix.sct ./GeneradorSenales.-sct
elif [ "$1" -eq 2 ] ; then
        echo "Copying PuertaCorrediza.-sct"
        rm ./PuertaCorrediza.-sct
        cp ./prefix.sct ./PuertaCorrediza.-sct
elif [ "$1" -eq 3 ] ; then
        echo "Copying PortonCochera.-sct"
        rm ./PortonCochera.-sct
        cp ./prefix.sct ./PortonCochera.-sct
elif [ "$1" -eq 4 ] ; then
        echo "Copying EscaleraMecanica.-sct"
        rm ./EscaleraMecanica.-sct
        cp ./prefix.sct ./EscaleraMecanica.-sct
elif [ "$1" -eq 5 ] ; then
        echo "Copying HornoMicroondas.-sct"
        rm ./HornoMicroondas.-sct
        cp ./prefix.sct ./HornoMicroondas.-sct
else
        echo "Error: Invalid model number."
        exit 2
fi

exit 0





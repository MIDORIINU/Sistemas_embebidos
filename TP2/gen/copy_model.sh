#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

if [ -z "$1" ] ; then
        echo "Error: Missing model number."
        exit 1
fi

cd "${SCRIPTPATH}"

if [ "$1" -eq 1 ] ; then
        echo "Copying GeneradorSenales.-sct"
        rm ./prefix.sct
        cp ./GeneradorSenales.-sct ./prefix.sct
elif [ "$1" -eq 2 ] ; then
        echo "Copying PuertaCorrediza.-sct"
        rm ./prefix.sct
        cp ./PuertaCorrediza.-sct ./prefix.sct
elif [ "$1" -eq 3 ] ; then
        echo "Copying PortonCochera.-sct"
        rm ./prefix.sct
        cp ./PortonCochera.-sct ./prefix.sct
elif [ "$1" -eq 4 ] ; then
        echo "Copying EscaleraMecanica.-sct"
        rm ./prefix.sct
        cp ./EscaleraMecanica.-sct ./prefix.sct
elif [ "$1" -eq 5 ] ; then
        echo "Copying HornoMicroondas.-sct"
        rm ./prefix.sct
        cp ./HornoMicroondas.-sct ./prefix.sct
else
        echo "Error: Invalid model number."
        exit 2
fi

exit 0





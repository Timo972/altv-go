# CMakeList.txt: progetto CMake per altv-capi-golang. Includere l'origine e definire
# qui la logica specifica del progetto.
#
cmake_minimum_required (VERSION 3.8)
project(altv-go-capi)

# Aggiungere l'origine all'eseguibile di questo progetto.
add_library (altv-capi-golang STATIC "capi.c" "capi.h")

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.

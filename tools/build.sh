#! /bin/bash

# Build the program

# usage:
#   ./build.sh usage
#   ./build.sh [OPTION] [EXEC_DIRECORY]
#   ./build.sh clean [EXEC_DIRECTORY]

#   OPTION:
#       -l[ce]
#           set initial language: Chinese / English

#       -d
#           enter debug option

#       [EXEC_DIRECTORY]
#           set the dirctory of the EXEC

usage() {
    tab="   "
    echo "usage:"
    echo "$tab./build.sh usage"
    echo "$tab./build.sh [OPTION] [EXEC_DIRECORY]"
    echo "$tab./build.sh clean [EXEC_DIRECTORY]"
    echo ""
    echo "OPTION"
    echo "$tab-l[ce]$tab set initial language: Chinese / English"
    echo "$tab-b    $tab enable debugging mode"
    echo ""
    echo "OPTION need to be unique in type"
    echo "$tab(for example, do not execute build.sh with both -lc and -le)"
    exit 1
}

if [ $# -ge 1 ] && [ $1 == "clean" ]; then
    make clean
    if [ $# -eq 2 ]; then
        rm $2/*.exe
    fi
    exit 0
fi

if [ $# -ge 1 ] && [ $1 == "usage" ]; then
    usage
fi


language=0
debug=""
exec="中国象棋"
dirctory=".."


for arg in $@; do
    case $arg in
        ("-l"*)
            if [ $language -ne 0 ]; then
                usage
            fi
            case $arg in
                (-lc)
                    language=1
                    ;;
                (-le)
                    language=2
                    exec="Chinese_Chess"
                    ;;
                (*)
                    usage
                    ;;
            esac
            ;;
        ("-d")
            if [ ! $debug == "" ]; then
                usage
            fi
            debug="-DDEBUG -g"
            ;;
        (*)
            if [ ! $dirctory == ".." ]; then
                usage
            fi
            dirctory=$arg
            ;;
    esac
done

variables=""
if [ $language -ne 0 ]; then
    variables="$variables-DINIT_LANGUAGE=$language "
fi

if [ ! "$debug" == "" ]; then
    exec=${exec}_debug
fi


make "PREPROCESSOR=$variables" "DEBUG=$debug" "EXEC_DIRECTORY=$dirctory/" "EXEC=${exec}.exe"

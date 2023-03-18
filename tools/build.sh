#! /bin/bash

# usage: build.sh [OPTION]

# Build the program
#   OPTION:
#       -l[ce]
#           set initial language: Chinese / English

#       [OUTPUT_DIRECTORY]
#           set the dirctory of the EXEC

usage() {
    echo "usage: build.sh [OPTION]"
    echo "OPTION must has unique type"
    exit -1
}

language=0
exec="中国象棋.exe"
dirctory=".."


for arg in $@; do
    case $arg in
        ("-l"*)
            if [ $language -ne 0 ]; then
                usage
                exit -1 
            fi
            case $arg in
                (-lc)
                    language=1
                    ;;
                (-le)
                    language=2
                    ;;
                (*)
                    usage
                    ;;
            esac
            ;;
        (*)
            if [ ! $dirctory == ".." ]; then
                usage
                exit -1 
            fi
            dirctory=$arg
            ;;
    esac
done

variables=""
if [ $language -ne 0 ]; then
    variables="$variables-DINIT_LANGUAGE=$language "
    if [ $language -eq 2 ]; then
        exec="Chinese_Chess.exe"
    fi
fi

echo $variables $dirctory $exec
make $(echo CPPFLAGS=$variables EXEC_DIRECTORY=$dirctory/ EXEC=$exec)

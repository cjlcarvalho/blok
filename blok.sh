#! /bin/bash

setRootDir () {
    cwd="${PWD##*/}"
    if [[ $cwd != "blok" ]]; then
        cd ..
    fi
}

clean () {
    setRootDir
    cd blok-images
    make clean
    cd ../snow
    make clean
    cd ../starwars
    make clean
    cd ../default
    make clean
    cd ../blok-qt
    make clean
    cd ../images_lib
    rm -f *.so
    cd ../images_plugins
    rm -f *.so
}

compileBlokImages () {
    setRootDir
    cd blok-images
    qmake-qt4
    make -j 5
}

compileBlokSimulator () {
    setRootDir
    cd blok-simulator
    qmake-qt4
    make -j 5
}

compileSnowPlugin () {
    setRootDir
    cd snow
    qmake-qt4
    make -j 5
}

compileDefaultPlugin () {
    setRootDir
    cd default
    qmake-qt4
    make -j 5
}

compileStarWarsPlugin () {
    setRootDir
    cd starwars
    qmake-qt4
    make -j 5
}

compileBox2DSimulatorPlugin () {
    setRootDir
    cd box2dsimulator
    qmake-qt4
    make -j 5
}

setLDLibraryPath () {
    if [[ $LD_LIBRARY_PATH != *"$PWD/images_lib"* ]]; then
        echo ""
        echo "LD_LIBRARY_PATH variable set"
        echo ""
        LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/images_lib:$PWD/simulator_lib
        export LD_LIBRARY_PATH
    fi
}

compileBlokQt () {
    setRootDir
    setLDLibraryPath
    cd blok-qt
    qmake-qt4
    make -j 5
}

changeSimulatorPlugin () {
    setRootDir
    cd simulator_plugins
    rm -f *.so
    if [[ $1 == "box2d" ]]; then
        echo "Compiling Box 2D Simulator plugin..."
        compileBox2DSimulatorPlugin
    else
        echo "Wrong choice. Please try again."
        exit
    fi
}

changeImagePlugin () {
    setRootDir
    cd images_plugins
    rm -f *.so
    if [[ $1 == "default" ]]; then
	    echo "Compiling Default image plugin..."
        compileDefaultPlugin
    elif [[ $1 == "snow" ]]; then
	    echo "Compiling Snow image plugin..."
	    compileSnowPlugin
    elif [[ $1 == "starwars" ]]; then
	    echo "Compiling Star Wars image plugin..."
	    compileStarWarsPlugin
    else
	    echo "Wrong choice. Please try again."
	    exit
    fi
}

compile () {
    clean
    
    compileBlokSimulator
    echo ""
    echo "Select your simulator plugin:"
    echo "[1] - BOX 2D SIMULATOR"
    read -p "Option: " plugin
    if [[ $plugin == "1" ]]; then
        echo "Compiling Box 2D Simulator plugin..."
        compileBox2DSimulatorPlugin
    else
        echo "Wrong choice. Please try again."
        exit
    fi

    compileBlokImages
    echo ""
    echo "Select your image plugin:"
    echo "[1] - DEFAULT"
    echo "[2] - SNOW"
    echo "[3] - STAR WARS"
    read -p "Option: " plugin
    if [[ $plugin == "1" ]]; then
        echo "Compiling Default plugin..."
        compileDefaultPlugin
    elif [[ $plugin == "2" ]]; then
        echo "Compiling Snow plugin..."
        compileSnowPlugin
    elif [[ $plugin == "3" ]]; then
        echo "Compiling Star Wars plugin..."
        compileStarWarsPlugin
    else
        echo "Wrong choice. Please try again."
        exit
    fi
    
    compileBlokQt
    echo ""
    read -p "Do you want to run Blok? [Y/N] " yn
    case $yn in
        [Yy]* ) run;;
        [Nn]* ) exit;;
    esac
}

run () {
    setRootDir
    if [[ $LD_LIBRARY_PATH == "" ]]; then
        echo "Setting LD_LIBRARY_PATH environment variable"
        setLDLibraryPath
    fi
    ./blok-qt/blok
}

main () {
    
    echo "###################"
    echo "##### Blok Qt #####"
    echo "###################"
    echo ""

    if [[ "$1" == "compile" ]]; then
        compile
    elif [[ "$1" == "run" ]]; then
        run
    elif [[ "$1" == "clean" ]]; then
        echo "Cleaning directories..."
        clean
    elif [[ "$1" == "changeImage" ]]; then
	    changeImagePlugin $2
    elif [[ "$1" == "changeSimulator" ]]; then
        changeSimulatorPlugin $2
    else
        echo "Wrong parameter"
        echo "Usage: ./blok.sh [compile/run/clean]"
        exit
    fi
}

main $1 $2

# blok

- Running:
    
    - Execute blok.sh script with compile/run/clean option

- In case of problems:

    - Compile blok-simulator

    - Compile your simulator plugin (only Box2D for a while)

    - Compile blok-images

    - Compile your image plugin (default or snow)

    - Export LD_LIBRARY_PATH variable:

        `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/images_lib`

        `export LD_LIBRARY_PATH`

    - Compile blok-qt

    - Run

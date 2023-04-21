# listDirectoriesJSON

Este programa en C++ genera un archivo JSON que contiene información sobre los archivos encontrados en un directorio y sus subdirectorios de manera recursiva.
Utiliza la biblioteca JSONcpp y la biblioteca de manejo de archivos. El programa está hecho para C++17, para poder usar el filesystem.

El programa recibe del usuario una cadena con la dirección del directorio a analizar y escribirá en un JSON los archivos contenidos, junto a su peso.
Si se encuentra un subdirectorio, se aplicará el mismo algoritmo recursivamente para abarcar todos los archivos contenidos.
Finalmente, si el programa termina con éxito, se generará un archivo JSON con la información en la carpeta del proyecto.

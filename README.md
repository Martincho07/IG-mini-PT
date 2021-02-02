# Path Tracer y Tone Mapper
* Autor: Fernando Peña Bes (NIA: 756012)
* Autor: Jose Daniel Subías Sarrato (NIA: 759533)

*Informática Gráfica - Universidad de Zaragoza, curso 2020-21*

# Descripción
Este repositorio contiene un Path Tracer y un Tone Mapper capaz de convertir
las imágenes HDR PPM que genera el Path Tracer a LDR PPM.

# Compilación
Se ha utilizado cmake como sistema de compilación. Para construir los
Makefiles del proyecto ir al directorio raíz y ejecutar

    cmake -B build

Este comando creará un directorio llamado `build` con todos los ficheros
necesarios para la compilación.

A continuación, acceder a dicho directorio y ejecutar `make` para compilar
tanto el Path Tracer como el Tone Mapper. Si se quieren compilar por
separado, se puede ejecutar `make path_tracer` y `make tone_mapper`
respectivamente.

# Ejecución
Una vez que se ha completado la compilación, en el directorio `build` se
encontrarán los binarios de los dos programas.

El Path Tracer se puede ejecutar con los siguientes argumentos:

    Usage: path_tracer [options ...]

    Options:
    Output file options:
        -o, --out_file       Output file name
        -w, --width          Output image width
        -h, --height         Output image height
        -c, --color_res      Output image color resolution
    Rendering options:
        -p, --pixel_rays     Number of points per pixel
        -t, --threads        Number of hardware concurrent threads
        -s, --scene          Scene to render
    -?, --help             Show this help message and quit

El Tone Mapper permite guardar imágenes con formato PPM o HDR (por defecto
usa ppm). Se puede utilizar para convertir imágenes PPM HDR en HDR si no se
indica ningún operador de tone mapping.
Se ejecuta de la siguiente forma:

    Usage: tone_mapper input-file.ppm [options ...] [output-file.{ppm|hdr}]

    Options:
    -exposure step      Multiply each pixel by 2^step to adjust the exposure
    -clamp              Discard al values greater than 255 (1 in floating point precission)
    -equalize           Linear transformation of all values from minimum to the maximum (normalization)
    -clamp-and-equalize value
                        Clamp all values greater than 'value' and equalize the rest of them
    -gamma-curve gamma  Apply a gamma curve to all the values
    -clamp-and-gamma-curve value gamma
                        Apply a gamma curve after clamping all the values greater than 'value'
    -reinhard02 a l      Apply the Reinhard 2002 operator with a given 'a' key value
    -mantiuk08 a s      Apply the Mantiuk 2008 operator with a given 'a' key value and 's' value
    -h, -help           Show this help message and quit

    Use the string 'default' to indicate the default value
    Default values:
    step = 0
    value = 1
    gamma = 2.2
    a = 0.16
    s = 0.6

    If no output-file is provided, the image is saved as: out_'input-file'.ppm

# Escenas
El Path Tracer tiene 5 escenas ya configuradas. Se pueden seleccionar
utilizando la opción `-s` seguida de uno de los siguientes números.

0. Contiene dos esferas, una dieléctrica con un índice de refracción de 1,5 y
otra de material plástico. Está iluminada con una luz de área en el techo.
Esta es la escena que se usa por defecto si no se selecciona ninguna o se
selecciona una que no existe.
1. Es igual que la escena 0, pero la luz de área se ha sustituido por una luz
puntual.
2. Contiene tres conejos, uno con material especular, otro dieléctrico y otro
plástico.
3. Contiene un dragón con material especular.
4. Tiene tres esferas, una detrás de otra, y se puede utilizar para probar la
profundidad de campo. Para activarla la cámara *thin lens*, hace falta
modificar descomentar la línea `#define DOF` en `camera.cpp` y volver a
compilar.

En el fichero `path_tracer/sample_scenes.hpp` hay muchos ejemplos de escenas, y pueden de guía para crear escenas nuevas.

Las imágenes se generan con un formato PPM modificado para guardar imágenes HDR, que no se puede abrir con programas de visión de imágenes. Para poder ver los resultados, hace falta aplicar el Tone Mapper sobre la imagen.

El siguiente es un ejemplo completo para poder generar y visualizar una imagen:

    build/path_tracer -s 1 -p 40 -o imagen_hdr
    build/tone_mapper imagen_hdr.ppm -clamp-and-gamma-curve 1 2.2 imagen.ppm
    display imagen.ppm

La mayoría de visores de imágenes soportan el formato PPM.

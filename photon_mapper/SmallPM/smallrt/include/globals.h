/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "flags.h"

#ifndef Real
#define Real float
#endif

#ifndef MAX_NB_OBJECTS_LEAF
#define MAX_NB_OBJECTS_LEAF 6
#endif


#ifndef NB_SAMPLES_ANTIALIASING 
#define NB_SAMPLES_ANTIALIASING 1
#endif

#ifndef MAX_NB_SPECULAR_BOUNCES
#define MAX_NB_SPECULAR_BOUNCES 5
#endif

#ifndef MAX_NB_TRANSMISSIVE_BOUNCES
#define MAX_NB_TRANSMISSIVE_BOUNCES 5
#endif

#ifndef MAX_NB_INTEREFLECTION_BOUNCES
#define MAX_NB_INTEREFLECTION_BOUNCES 4
#endif

#ifndef NB_SAMPLES_HEMISPHERE
#define NB_SAMPLES_HEMISPHERE 4
#endif

#ifndef _SCENE_TO_USE_
#define _SCENE_TO_USE_ 0
#endif

#endif
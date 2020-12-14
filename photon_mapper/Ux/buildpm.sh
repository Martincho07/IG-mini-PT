#!/bin/bash

g++ -no-pie ../SmallPM/src/main.cpp ../SmallPM/src/Random.cpp ../SmallPM/src/PhotonMapping.cpp ../SmallPM/src/RenderEngine.cpp ../SmallPM/smallrt/lib/smallrt.a -I../SmallPM/smallrt/include -I../SmallPM/include/ -O3 -o smallpm

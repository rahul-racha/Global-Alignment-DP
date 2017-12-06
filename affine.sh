#!/bin/bash
#chmod +x affine.sh if permission denied
g++ -o agp global-align.cpp AGP.cpp
./agp

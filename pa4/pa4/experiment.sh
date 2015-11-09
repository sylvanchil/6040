#!/bin/bash
#experiment #1
./filt filters/box9.filt images/square.png experiments/1/box9OnSquare.png -t
./filt filters/tent9.filt images/square.png experiments/1/tent9OnSquare.png -t
./filt filters/bell9.filt images/square.png experiments/1/bell9OnSquare.png -t
#experiment #2
./filt filters/hp.filt images/checkers.png experiments/2/hpOnCheckers.png -t
./filt filters/sobol-horiz.filt images/checkers.png experiments/2/sbhOnCheckers.png -t
./filt filters/sobol-vert.filt images/checkers.png experiments/2/sbvOnCheckers.png -t
#experiment #3
./filt newfilter/donut.filt images/brushes.png experiments/3/donutOnBrushes.png -t
./filt newfilter/star.filt images/brushes.png experiments/3/starOnBrushes.png -t
#experiment gabor
./filt -g 0 4 4 images/brushes.png experiments/gabor/g044OnBrushes.png -t
./filt -g 0 4 8 images/brushes.png experiments/gabor/g048OnBrushes.png -t
./filt -g 45 4 8 images/brushes.png experiments/gabor/g4548OnBrushes.png -t
./filt -g 45 4 4 images/brushes.png experiments/gabor/g4544OnBrushes.png -t


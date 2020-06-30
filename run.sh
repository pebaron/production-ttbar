#!/bin/bash

cd /home/petr/GitLab/unfolding/production
make clean
make &> log.txt
cat log.txt 
Unfold_x
cd -

#/bin/sh

sudo docker run -it --rm -v "$(pwd)":/home/progtest/build gitlab.fit.cvut.cz:5000/bi-pa2/virtual-machine/pa2vm:latest

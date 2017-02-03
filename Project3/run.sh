#!/bin/bash
#
#$ -cwd
#$ -j y
#$ -S /bin/bash
#

#MPI_DIR=/opt/mpich/gnu/
HPL_DIR=/opt/hpl/mpich-hpl/
 
#NSLOTS = $1
# OpenMPI part. Uncomment the following code and comment the above code
# to use OpemMPI rather than MPICH

#MPI_DIR=/opt/openmpi/
#HPL_DIR=/opt/hpl/openmpi-hpl/

mpirun -np $1 ./parallel.o $2

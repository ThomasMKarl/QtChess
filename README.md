#QtChess (Beta)

## Requirements

- ISO C++ 17 compliant compiler
- GNU Make
- mpark variant
- Qt5
- (optional) any MPI implementation for cluster support
- (optional) doxygen for documentation
- (optional) LaTeX for pdf documentation

## Compile

edit Makefile, if needed

type *make help*

## Usage

run *bin/qtchess* for GUI

run *bin/qtchesscmd* for command line interface

run *mpirun ... bin/qtchesscmd_mpi* or *mpirun ... bin/qtchess_mpi* for cluster versions
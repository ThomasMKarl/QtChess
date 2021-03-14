#include "cluster/cluster.h"

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);

  qtc::Board game = qtc::Board::newgame();
  std::vector<std::string> possibleMoves = game.update();

  const MPI_Comm communicator = MPI_COMM_WORLD; 
  qtc::move(game,
	    qtc::mpi::mpiComputeBestMove(game, possibleMoves, communicator));
    
  MPI_Finalize();
  
  return EXIT_SUCCESS;
}

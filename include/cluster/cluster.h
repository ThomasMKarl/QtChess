#ifndef CLUSTER_H
#define CLUSTER_H

#include "board/board.h"

namespace qtc {
namespace mpi {

class MpiExchangeHandler
{
 public:
  static MpiExchangeHandler create(const std::vector<std::string> FENpositions,
				   const MPI_Comm communicator = MPI_COMM_WORLD)
  {
    return MpiExchangeHandler(FENpositions, communicator);
  }
  
  MpiExchangeHandler(const MpiExchangeHandler& other) = default;
  MpiExchangeHandler& operator=(const MpiExchangeHandler& other) = default;
  MpiExchangeHandler(MpiExchangeHandler&& other) = default;
  MpiExchangeHandler& operator=(MpiExchangeHandler&& other) = default;
  
  
  ~MpiExchangeHandler()
  {
    for(auto& FENwindow : FENwindows)
      MPI_Win_free(&FENwindow);
  }

  std::string getFENposition(const unsigned int positionNumber,
			     const int targetRank = 0) const;
  void putMoveProbability(const unsigned int positionNumber,
			  const double probability,
			  const int targetRank = 0) const;
  unsigned int getBestMoveIndex() const;
  void sync(const int MPIassert = 0) const;
  
 private:
  MpiExchangeHandler(std::vector<std::string> FENpositions,
		     MPI_Comm communicator = MPI_COMM_WORLD)
  {
    FENwindows.resize(FENpositions.size());
    moveProbabilities.resize(FENpositions.size());
      
    unsigned int counter = 0;
    unsigned short int maxFENstringSize = 86;
    for(const auto &FENposition : FENpositions)
    {
      MPI_Win_create((void*)FENposition.data(),
		     maxFENstringSize,
		     1,
		     MPI_INFO_NULL,
		     communicator,
		     &FENwindows[counter++]);
    }
  }
  
  std::vector<MPI_Win> FENwindows{};
  std::vector<double> moveProbabilities{};
};

std::string mpiComputeBestMove(const Board &game,
			       const std::vector<std::string> possibleMoves,
			       const MPI_Comm communicator = MPI_COMM_WORLD);

};};

#endif

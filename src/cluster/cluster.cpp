#include "cluster/cluster.h"

  std::string qtc::mpi::MpiExchangeHandler::getFENposition(const unsigned int positionNumber,
							   const int targetRank) const
  {
    const unsigned short int maxFENstringSize = 85;
    std::string FENposition;
    FENposition.reserve(maxFENstringSize);
    
    MPI_Get(FENposition.data(),
	    maxFENstringSize,
	    MPI_CHAR,
	    targetRank,
	    1,
	    maxFENstringSize,
	    MPI_CHAR,
	    FENwindows[positionNumber]);
    
    return FENposition;
  }

  void qtc::mpi::MpiExchangeHandler::putMoveProbability(const unsigned int positionNumber,
							const double probability,
							const int targetRank) const
  {  
    MPI_Put(&probability,
	    1,
	    MPI_DOUBLE,
	    targetRank,
	    0,
	    1,
	    MPI_DOUBLE,
	    FENwindows[positionNumber]);
  }

  unsigned int qtc::mpi::MpiExchangeHandler::getBestMoveIndex() const
  {
    return std::distance(moveProbabilities.begin(),
                         std::max_element(moveProbabilities.begin(), moveProbabilities.end()));
  }

  void qtc::mpi::MpiExchangeHandler::sync(const int MPIassert) const
  {
    for(const auto& FENwindow : FENwindows)
      MPI_Win_fence(MPIassert, FENwindow);
  }


std::string qtc::mpi::mpiComputeBestMove(const Board &game,
					 const std::vector<std::string> possibleMoves,
					 const MPI_Comm communicator)
{
  int numberOfNodes;
  MPI_Comm_size(communicator, &numberOfNodes);
  
  int rank;
  MPI_Comm_rank(communicator, &rank);
  
  unsigned int numberOfPositionsPerRank = 0;
  std::vector<std::string> FENpositions{};
  
  if(rank == 0)
  { 
    const unsigned int numberOfPositions = possibleMoves.size();

    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned int> distribution(0,numberOfPositions);
    
    const unsigned int ceilPositionsPerRank = numberOfPositions/numberOfNodes;
    const unsigned int rest = numberOfPositions - ceilPositionsPerRank*numberOfNodes;
    
    for(auto &move : possibleMoves)
    {
      Board gameCopy = game;
      qtc::move(gameCopy, move);
      FENpositions.push_back(gameCopy.computeFENposition());
    }
    
    for(unsigned int i = 0; i < rest; ++i)
      FENpositions.push_back(FENpositions[distribution(generator)]);

    numberOfPositionsPerRank = FENpositions.size();
  }
  
  const MpiExchangeHandler mpiHandler = MpiExchangeHandler::create(FENpositions, communicator);
  mpiHandler.sync();
 
  for(unsigned int position = 0; position < numberOfPositionsPerRank; ++position)
  {
    const unsigned int globalPositionNumber = rank*numberOfPositionsPerRank + position;
    
    const std::string FENposition = mpiHandler.getFENposition(globalPositionNumber);
    
    const Board game = Board::createBoardFromFEN(FENposition);
    const double probability = computeWinProbability(game, 1000);
    
    mpiHandler.putMoveProbability(globalPositionNumber, probability);
  }
  
  mpiHandler.sync();

  return possibleMoves[mpiHandler.getBestMoveIndex()];
}

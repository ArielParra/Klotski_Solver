#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <stack>
#include <queue>
#include <random>

//#define OPTIMIZE_SOLUTION
#define COLORS
#define PRINT



#define SLEEP 0
#ifdef COLORS
#include "rlutil.h"
#endif

enum SolutionType {
  SOLUTION_FOUND,
  IN_PROGRESS,
  PARTIAL,
  NO_SOLUTION
};

struct Position{
  int x, y;

  bool operator==(const Position& other) const {
    return other.x == x && other.y == y;
  }
};


typedef enum PieceType : unsigned char{
  PT_EMPTY='&',
  PT_WALL='#',
  PT_PLAYER='*',
  PT_DOOR='-',
  PT_OBJECTIVE='.',
};

typedef enum Direction : unsigned char {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct MovementOrder{
  Direction dir;
  unsigned char id;

  // Equality operator
  bool operator==(const MovementOrder& other) const {
      return (dir == other.dir) && (id == other.id);
  }

  // Inequality operator
  bool operator!=(const MovementOrder& other) const {
      return !(*this == other);
  }

};

Direction getOppositeDir(Direction dir){
  switch(dir){
    case UP:
      return DOWN;
    case DOWN:
      return UP;
    case LEFT:
      return RIGHT;
    case RIGHT:
      return LEFT;
  }
}

class Block{
public:
  Block(){
    id=0;
  }

  Block(unsigned int _id, unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height, bool _isPlayer, unsigned int _reduction) : 
    id(_id), x(_x), y(_y), width(_width), height(_height), isPlayer(_isPlayer), reduction(_reduction){
  }

  unsigned int getWidth() const{
    return width;
  }

  unsigned int getHeight() const{
    return height;
  }

  unsigned int getID() const{
    return id;
  }

  unsigned int getReduction() const {
    return reduction;
  }

  unsigned int getX() const{
    return x;
  }

  unsigned int getY() const{
    return y;
  }

  bool canTravel(unsigned char tile){
    if(isPlayer && tile == PT_DOOR) return true;
    
    return tile == PT_EMPTY || tile == PT_OBJECTIVE;
  }

  void move(Direction direction){
    switch(direction){
      case UP:
        y--;
      break;
      case DOWN:
        y++;
      break;
      case LEFT:
        x--;
      break;
      case RIGHT:
        x++;
      break;
    }
  }

private:
  public:
  unsigned int x, y;

  unsigned int width, height;

  bool isPlayer;
  unsigned int id;
  unsigned int reduction;
};


namespace std {
    template <>
    struct hash<std::vector<std::vector<unsigned char>>> {
        size_t operator()(const std::vector<std::vector<unsigned char>>& vec, Block* blocks) const {
            std::hash<unsigned char> charHasher;
            size_t hash = 0;

            for (const auto& row : vec) {
                for (const unsigned char& elem : row) {
                    const unsigned char& corresponding = blocks[elem].id == 0 ? elem : blocks[elem].getReduction();
                    hash ^= charHasher(corresponding) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash;
        }
    };

    template <>
    struct hash<Position> {
      size_t operator()(const Position& pos) const {
        return hash<int>()(pos.x) ^ hash<int>()(pos.y);
      }
    };
}

class Solver;

class Board {
  public:
  void printBoard() const {
    #ifdef COLORS
    static int colours[255] = {rlutil::WHITE};
    colours['#'] = rlutil::GREY;
    colours['*'] = rlutil::YELLOW;
    colours['a'] = rlutil::RED;
    colours['b'] = rlutil::CYAN;
    colours['c'] = rlutil::BLUE;
    colours['d'] = rlutil::GREEN;
    colours['e'] = rlutil::MAGENTA;
    colours['f'] = rlutil::BROWN;
    colours['g'] = rlutil::LIGHTBLUE;
    colours['h'] = rlutil::LIGHTRED;
    colours['g'] = rlutil::LIGHTMAGENTA;
    colours['i'] = rlutil::LIGHTCYAN;

    #endif

    for(int y = 0; y < gameMap.size(); y++){
      for(int x = 0; x < gameMap[0].size(); x++){
        #ifdef COLORS
        rlutil::setColor(colours[gameMap[y][x]]);
        #endif

        std::cout << gameMap[y][x];
      }
      std::cout << "\n";
    }
    std:: cout << std::endl;

    #ifdef COLORS
    rlutil::msleep(SLEEP);
    if(SLEEP) rlutil::cls();
    #endif
  }

  Board(std::vector<std::string>& lines) : 
    gameMap(lines.size(), std::vector<unsigned char>(lines[0].size(),' ')),
    floorMap(lines.size(), std::vector<unsigned char>(lines[0].size(),' ')){
    bool encountered[255] = {0};

    std::unordered_map<int, std::unordered_map<int, unsigned int>> reductions;
    unsigned int nextReduction = 'a';

    for(int y = 0; y < lines.size(); y++){
      for(int x = 0; x < lines[0].size(); x++){
        bool isPlayer = false;

        gameMap[y][x] = (unsigned char)lines[y][x];
        switch(lines[y][x]){
          case PT_WALL:
          case PT_DOOR:
          case PT_OBJECTIVE:
          case PT_EMPTY:
            floorMap[y][x] = lines[y][x];
          case 0:
          break;
          case PT_PLAYER:
            isPlayer = true;
          default:
            floorMap[y][x] = PT_EMPTY;
            if(!encountered[lines[y][x]]){
              // find height
              int sY = y;
              int sX = x;

              while(sY < lines.size() && lines[sY][x] == lines[y][x]){
                sY++;
              }

              while(sX < lines[0].size() &&  lines[y][sX] == lines[y][x]){
                sX++;
              }

              int blockWidth = sX - x;
              int blockHeight = sY - y;

              if(reductions[blockWidth].find(blockHeight) == reductions[blockWidth].end()){
                reductions[blockWidth][blockHeight] = nextReduction++;
              }

              blocks[lines[y][x]] = Block(lines[y][x], x, y, blockWidth, blockHeight, isPlayer, reductions[blockWidth][blockHeight]);
              encountered[lines[y][x]] = true;
            }
        }
      }
    }
  }

  bool blockCanMove(Direction direction, unsigned char blockID){
    Block& targetBlock = blocks[blockID];

    switch(direction){
      case UP:
        if (targetBlock.getY() == 0) return false;
        for(int x = targetBlock.getX(); x < targetBlock.getX() + targetBlock.getWidth(); x++){
          if(!(0 <= x && x < gameMap[0].size())) continue;;
          if(!targetBlock.canTravel(gameMap[targetBlock.getY()-1][x])){
            return false;
          }
        }
        return true;

      case DOWN:
        if (targetBlock.getY()+targetBlock.getHeight() > gameMap.size()-1) return false;
        for(int x = targetBlock.getX(); x < targetBlock.getX() + targetBlock.getWidth(); x++){
          if(!(0 <= x && x < gameMap[0].size())) continue;

          if(!targetBlock.canTravel(gameMap[targetBlock.getY()+targetBlock.getHeight()][x])){
            return false;
          }
        }
        return true;

      case LEFT:
        if (targetBlock.getX() == 0) return false;
        for(int y = targetBlock.getY(); y < targetBlock.getY() + targetBlock.getHeight(); y++){
          if(!(0 <= y && y < gameMap.size())) continue;

            if(!targetBlock.canTravel(gameMap[y][targetBlock.getX()-1])){
              return false;
            }
        }
        return true;
      case RIGHT:
        if (targetBlock.getX() + targetBlock.getWidth() > gameMap[0].size()-1) return false;
        for(int y = targetBlock.getY(); y < targetBlock.getY() + targetBlock.getHeight(); y++){
          if(!(0 <= y && y < gameMap.size())) continue;

            if(!targetBlock.canTravel(gameMap[y][targetBlock.getX()+targetBlock.getWidth()])){
              return false;
            }
        }
        return true;
    }
    return false;
  }

  void moveBlock(Direction dir, unsigned char blockID){
    Block& targetBlock = blocks[blockID];
    assert(targetBlock.getID());
    switch(dir){
      case UP:
        for(int x = targetBlock.getX(); x < targetBlock.getX() + targetBlock.getWidth(); x++){
          gameMap[targetBlock.getY()-1][x] = blockID;
          gameMap[targetBlock.getY()+targetBlock.getHeight()-1][x] = floorMap[targetBlock.getY()+targetBlock.getHeight()-1][x];
        }
        break;
      case DOWN:
        for(int x = targetBlock.getX(); x < targetBlock.getX() + targetBlock.getWidth(); x++){
          gameMap[targetBlock.getY()+targetBlock.getHeight()][x] = blockID;
          gameMap[targetBlock.getY()][x] = floorMap[targetBlock.getY()][x];
        }
        break;
      case LEFT:
        for(int y = targetBlock.getY(); y < targetBlock.getY() + targetBlock.getHeight(); y++){
            gameMap[y][targetBlock.getX()-1] = blockID;
            gameMap[y][targetBlock.getX()+targetBlock.getWidth()-1] = floorMap[y][targetBlock.getX()+targetBlock.getWidth()-1];
        }
        break;
      case RIGHT:
        for(int y = targetBlock.getY(); y < targetBlock.getY() + targetBlock.getHeight(); y++){
            gameMap[y][targetBlock.getX()+targetBlock.getWidth()] = blockID;
            gameMap[y][targetBlock.getX()] = floorMap[y][targetBlock.getX()];
        }
        break;
    }
    targetBlock.move(dir);
  }

  bool gameWon(){
    for(auto& row : gameMap){
      for(auto& el : row){
        if(el == PT_OBJECTIVE) return false;
      }
    }

    return true;
  }


  private:
  public:
  Block blocks[255] = {};
  std::vector<std::vector<unsigned char>> gameMap;
  std::vector<std::vector<unsigned char>> floorMap;
  friend class Solver;
};

struct Solution{
  SolutionType type;
  int depth;
  size_t lastHash;
  MovementOrder order;
};

class Solver{
public:
  Solver(Board _b) : b(_b), original(_b) {
    
  }

  Board recoverState(size_t stateHash){
    Board recoveredBoard = original;

    std::stack<MovementOrder*> orders;

    auto* currentSolution = &memory.at(stateHash);
    while(currentSolution->lastHash != 0){
      orders.push(&currentSolution->order);
      currentSolution = &memory.at(currentSolution->lastHash);
    }

    while(orders.size()){
      MovementOrder* execute = orders.top();
      orders.pop();
      recoveredBoard.moveBlock(execute->dir, execute->id);
    }

    return recoveredBoard;
  }

  void printState(size_t stateHash){
    int targetDepth = memory.at(stateHash).depth;
    std::cout << "Printing state of depth " << targetDepth << std::endl;
    original.printBoard();

    std::stack<MovementOrder*> orders;

    int count = 0;
    auto* currentSolution = &memory.at(stateHash);
    while(currentSolution->lastHash != 0){
      std::cout << "\r" << count << "/" << targetDepth;
      orders.push(&currentSolution->order);
      currentSolution = &memory.at(currentSolution->lastHash);
      count++;
    }
    orders.push(&currentSolution->order);

    std::cout << "\n";
    int target = count;
    while(orders.size()){
      MovementOrder* execute = orders.top();
      orders.pop();
      std::cout << "Move " << (char)execute->id << " ";
      switch(execute->dir){
        case UP:
        std::cout << "UP";
        break;
        case DOWN:
        std::cout << "DOWN";
        break;
        case LEFT:
        std::cout << "LEFT";
        break;
        case RIGHT:
        std::cout << "RIGHT";
        break;
      }
      std::cout << std::endl;

    }
  }

  std::unordered_map<unsigned char, unsigned char> getMapping(Board from, Board to){
    std::unordered_map<unsigned char, unsigned char> mapping;
    std::unordered_map<Position, unsigned char> fromPosIds;
    std::unordered_map<Position, unsigned char> toPosIds;

    for(unsigned char i = 0; i < 255; i++){
      if(from.blocks[i].getID() != 0){
        fromPosIds[{from.blocks[i].getX(), from.blocks[i].getY()}] = i;
      }

      if(to.blocks[i].getID() != 0){
        toPosIds[{to.blocks[i].getX(), to.blocks[i].getY()}] = i;
      }
    }

    assert(fromPosIds.size() == toPosIds.size());

    for(auto& [pos, fromId] : fromPosIds){
      mapping[fromId] = toPosIds.at(pos);
    }

    return mapping;
  }

// Mapping is pruned -> to
  size_t rebindSolution(size_t pruneHash, size_t toHash, MovementOrder bridgingOrder, std::unordered_map<unsigned char, unsigned char> mapping){
    auto* bindToNode = &memory.at(toHash);
    auto* bindingNode = &memory.at(pruneHash);
    size_t toBindTo = toHash;
    size_t bindingHash = pruneHash;
    MovementOrder toGetTo = bridgingOrder; 
    Solution transferredNode;
    while(bindToNode->depth < bindingNode->depth){
      transferredNode = *bindingNode;
      bindingNode->lastHash = toBindTo;
      bindingNode->depth = bindToNode->depth + 1;
      bindingNode->order = toGetTo;
      memory[bindingHash].type = PARTIAL;

      bindToNode = bindingNode;
      bindingNode = &memory.at(transferredNode.lastHash);
      toBindTo = bindingHash;
      bindingHash = transferredNode.lastHash;
      toGetTo = {getOppositeDir(transferredNode.order.dir), mapping.at(transferredNode.order.id)};
    }

    return bindingHash;
  }

  size_t solve(){
    {
      auto startingState = std::hash<std::vector<std::vector<unsigned char>>>()(b.gameMap, b.blocks);
      memory[startingState] = Solution{IN_PROGRESS, 0, 0, {UP, 0}};
    }
    size_t lastHash = 0;
    MovementOrder lastOrder;

    while(true){
      search:
      depth++;
      for(unsigned char i = PT_PLAYER; i != PT_PLAYER - 1; i = (i + 1)%255){
        if(b.blocks[i].getID() == 0) continue;
        int startingDir = rand() % 4;
        for(int j = 0; j < 4; j++){
          int idir = (startingDir + j) % 4;
          Direction dir = (Direction)(idir);
          if(lastOrder != MovementOrder{getOppositeDir(dir), i} && b.blockCanMove(dir, i)){
            lastOrder = {dir, i};
            b.moveBlock(dir, i);

            auto movedHash = std::hash<std::vector<std::vector<unsigned char>>>()(b.gameMap, b.blocks);
            #ifdef PRINT
              std::cout << depth << ": " << (char)i << " moving " << (int)dir << " -> " << movedHash << "\n";
              b.printBoard();
            #endif

            if(i == PT_PLAYER){
              if (b.gameWon()){
                memory[movedHash] = Solution{SOLUTION_FOUND, depth, lastHash, {dir, i}};
                return movedHash;
              }
            }

            if (memory.find(movedHash) != memory.end()) {
              depth--;
              #ifdef OPTIMIZE_SOLUTION
              size_t recoverPoint;
              // Move solution subtree to branch from lower depth
              if(memory.at(movedHash).depth - depth < -1){
                std::cout << "Bridging branch " << depth << ":" << lastHash << " to " << memory.at(movedHash).depth << ":" << movedHash << "\n";
                recoverPoint = rebindSolution(movedHash, lastHash, {getOppositeDir(dir), i}, getMapping(recoverState(movedHash), b));
              }else if (memory.at(movedHash).depth - depth > 1){ // Move found subtree down to branch from here
                std::cout << "Bridging branch "  << memory.at(movedHash).depth << ":" << movedHash << " to " <<  depth << ":" << lastHash << "\n";
                recoverPoint = rebindSolution(lastHash, movedHash, {getOppositeDir(dir), i}, getMapping(b, recoverState(movedHash)));
              }else if (memory.at(movedHash).type == PARTIAL){
                std::cout << "Recovoring to partial\n";
                recoverPoint = movedHash;
              }else{
                // Continue with the previous block
                continue;
              }

              b = recoverState(recoverPoint);
              depth = memory.at(recoverPoint).depth;
              movedHash = recoverPoint;

              #ifdef PRINT
                std::cout << depth << ": " << (char)i << " moving " << (int)dir << " -> " << std::hex << movedHash << "\n";
                b.printBoard();
              #endif
              #else
              b.moveBlock(getOppositeDir(dir), i);
              continue;
              #endif
            }else{
              memory[movedHash] = {IN_PROGRESS, depth, lastHash, lastOrder};
            }

            lastHash = movedHash;
            goto search;
          }
        }
      }

      Solution& revertState = memory.at(lastHash);
      Solution& revertedLastAction = memory.at(memory.at(lastHash).lastHash);
      depth = revertedLastAction.depth;

      b.moveBlock(getOppositeDir(revertState.order.dir), revertState.order.id);
      #ifdef PRINT
      std::cout << "Deadlocked, reverting 1 depth\n";
      std::cout << depth << ": " << (char)revertedLastAction.order.id << " moving " << (int)revertedLastAction.order.dir << "\n";
      b.printBoard();
      #endif
      lastHash = revertState.lastHash;
    }
  }
  std::unordered_map<size_t, Solution> memory;
  int depth = 0;
  Board b;
  const Board original;
};

int main(){
  std::vector<std::string> matriz = {
    "&&&&&&&&&&",
    "&&&&&&&z&&",
    "&&######&&",
    "&&#a**b#&&",
    "&&#a**b#&&",
    "&&#cdde#&&",
    "&&#cfge#&&",
    "&&#h&&i#&&",
    "&&##--##&&",
    "&&&&&&&&..",
    "&&&&&&&&.."
  }; 


  std::vector<std::string> matriz2 = {
    "&&&&&&&&&&&&#",
    "&z&&&&&&&&&&#",
    "&&######&&&&#",
    "&&#a**h#&&&&#",
    "&&#b**g#&&&&#",
    "&&#cdef#&&&&#",
    "&&#ijkl#&&&&#",
    "&&#m&&n#&r&&#",
    "&&##--##&&&&#",
    "&&&&&&&&..&&#",
    "&&&&&&&&..&&#"
};
    

  Board b = Board(matriz2);

  for(int i = 0; i < 255; i++){
    if (b.blocks[i].id != 0){
      std::cout << "Block " << (char)b.blocks[i].id << "(" << b.blocks[i].x << " " << b.blocks[i].y << " " << b.blocks[i].width << " " << b.blocks[i].height << ") " << b.blocks[i].canTravel(PT_DOOR) << std::endl;
    }
  }

  b.printBoard();
  Solver s = (b);
  size_t solution = s.solve();

  std::cout << "Solution found\n";
  s.printState(solution);

  return 0;
}

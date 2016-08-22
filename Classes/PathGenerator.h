//
//  PathGenerator.h
//  SaveHostage
//
//  Created by 郭 晨 on 2/22/14.
//
//

#ifndef __SaveHostage__PathGenerator__
#define __SaveHostage__PathGenerator__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "TileNode.h"

using namespace cocos2d;
using namespace std;

typedef enum
{
    Road,
    Wall,
    Border,
}MapNode;

typedef enum
{
    Straight,
    Diagonal,
    
}adjType;

typedef struct
{
    int PosX;
    int PosY;
} Pos;

class PathGenerator
{
private:
//    static PathGenerator *_thePathGenerator;
    TMXTiledMap* _map;
    int _map_width;
    int _map_height;
    Point _start;
    Point _end;
    TileNode*** _nodes;
    std::vector<TileNode*> _opened_nodes;
    std::vector<TileNode*> _passed_nodes;
    
public:
    PathGenerator(TMXTiledMap* map);
    static PathGenerator* sharePathGenerator (TMXTiledMap *map);
    void initTileNodes();
    void resetTileNodes();
    bool canPass(int i, int j);
    bool inOpenNodes(TileNode* node);
    bool inPassedNodes(TileNode* node);
    TileNode* getMinFNode();
    void addToOpenNode (int x, int y, adjType adjtype, TileNode* parent);
    void addAdjacentOpenNodes(TileNode* node);
    void deletePassedNode (TileNode* node);
    std::vector<Point>* generatePath(Point start, Point end);
};

#endif /* defined(__SaveHostage__PathGenerator__) */

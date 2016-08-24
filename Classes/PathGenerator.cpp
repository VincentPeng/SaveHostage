//
//  PathGenerator.cpp
//  SaveHostage
//
//  Created by Chen Guo on 2/22/14.
//
//

#include "PathGenerator.h"


//PathGenerator* PathGenerator::_thePathGenerator = NULL;

PathGenerator::PathGenerator(TMXTiledMap* map)
{
    _map = map;
    _map_width = _map->getMapSize().width;
    _map_height = _map->getMapSize().height;
    _start = Point(-1,-1);
    _end = Point (-1,-1);
    initTileNodes();
    resetTileNodes();
}

PathGenerator* PathGenerator::sharePathGenerator (TMXTiledMap *map)
{
    static PathGenerator *_thePathGenerator = NULL;
    if (_thePathGenerator == NULL) {
        _thePathGenerator = new PathGenerator(map);
    }
    return _thePathGenerator;
}

void PathGenerator::initTileNodes()
{
    _nodes = new TileNode**[_map_width];
    for (int i = 0; i < _map_width; i++) {
        _nodes[i] = new TileNode*[_map_height];
    }
    for (int i = 0; i < _map_width; i++) {
        for (int j = 0; j < _map_height; j++) {
            _nodes[i][j] = new TileNode();
        }
    }
    _opened_nodes = std::vector<TileNode*>();
    _passed_nodes = std::vector<TileNode*>();
}

void PathGenerator::resetTileNodes()
{
    for (int i = 0; i < _map_width; i++) {
        for (int j = 0; j < _map_height; j++) {
            TileNode* node = _nodes[i][j];
            node->setF(0); node->setG(0);node->setH(0);node->setX(i);node->setY(j);node->setParent(NULL);
        }
    }
    _opened_nodes.clear();
    _passed_nodes.clear();
}

bool PathGenerator::canPass(int x, int y) {
    bool ret = true;
    int gid =_map->getLayer("meta")->getTileGIDAt(Point(x,y));
    unordered_map<string,Value> kmap = _map->getPropertiesForGID(gid).asValueMap();
    if(kmap.empty()) {
//        CCLOG("err: kmap is null!!");
    }
    else {
        Value str = kmap.at("Collidable");
//        CCLOG("%s",str.asString().c_str());
        if(str.asString().compare("true") == 0)
        {
            ret = false;
        }
    }
    return ret;
}

bool PathGenerator::inOpenNodes(TileNode *node)
{
    for (int i = 0; i < _opened_nodes.size(); i++) {
        if (node == _opened_nodes[i]) {
            return true;
        }
    }
    return false;
}

bool PathGenerator::inPassedNodes(TileNode *node)
{
    for (int i = 0; i < _passed_nodes.size(); i++) {
        if (node == _passed_nodes[i]) {
            return true;
        }
    }
    return false;
}

TileNode* PathGenerator::getMinFNode()
{
    std::sort(_opened_nodes.begin(), _opened_nodes.end(),
              [](const TileNode* ls, const TileNode* rs){return ls->getF() < rs->getF();});
    return _opened_nodes[0];
}


int descarteDistance (Point p1, Point p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return int(sqrt(pow(dx, 2) + pow(dy, 2)));
}

void PathGenerator::addToOpenNode(int x, int y, adjType adjtype, TileNode* parent)
{
    if (x < 0 || y < 0) {
        return;
    }
    if (!canPass(x, y)) {
        return;
    }
    TileNode* node = _nodes[x][y];
    if (inPassedNodes(node)) {
        return;
    }
    else if (!inOpenNodes(node))
    {
        _opened_nodes.push_back(node);
        int incf;
        if (adjtype == Straight)
            incf = 10;
        else
            incf = 14;
        
        node->setG(parent->getG() + incf);
        node->setH(descarteDistance(Point(node->getX(),node->getY()), _end) * 10);
        node->setF(node->getG() + node->getH());
        node->setParent(parent);
    }
}

void PathGenerator::addAdjacentOpenNodes(TileNode* node)
{
    int x = node->getX(); int y = node->getY();
    addToOpenNode(x - 1, y,Straight, node);
    addToOpenNode(x, y - 1,Straight, node);
    addToOpenNode(x + 1, y,Straight, node);
    addToOpenNode(x, y + 1,Straight, node);
    addToOpenNode(x - 1, y - 1,Diagonal, node);
    addToOpenNode(x - 1, y + 1,Diagonal, node);
    addToOpenNode(x + 1, y - 1,Diagonal, node);
    addToOpenNode(x + 1, y + 1,Diagonal, node);
}

void PathGenerator::deletePassedNode(TileNode *node)
{
    std::vector<TileNode *>::iterator it = _opened_nodes.begin();
    for( ; it != _opened_nodes.end(); ++it) {
        if(*it == node) {
            _opened_nodes.erase(it);
            break;
        }
    }
}

Point convertCoordinate2Pixel (int x, int y, int mapHeight)
{
    return Point((x + 0.5)*BLKWIDTH,(mapHeight - y - 0.5)*BLKWIDTH);
}

std::vector<Point>* PathGenerator::generatePath(Point start, Point end)
{
    this->resetTileNodes();
    _start = start; _end = end;
    vector<Point>* path = new vector<Point>();
//    path->push_back(start);
    TileNode* startNode = _nodes[int(start.x)][int(start.y)];
    startNode->setParent(NULL);
    _opened_nodes.push_back(startNode);
    TileNode* pathNode = NULL;
    while (true) {
        pathNode = getMinFNode();
        addAdjacentOpenNodes(pathNode);
        _passed_nodes.push_back(pathNode);
        deletePassedNode(pathNode);
        if (pathNode->getX() == int(end.x) && pathNode->getY() == int(end.y)) {
            break;
        }
    }
    while (pathNode) {
        path->push_back(convertCoordinate2Pixel(pathNode->getX(), pathNode->getY(),_map_height));
//        path->push_back(Point(pathNode->getX(),pathNode->getY()));
        pathNode = pathNode->getParent();
    }
    std::reverse(path->begin(), path->end());
    return path;
}

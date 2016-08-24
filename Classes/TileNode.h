//
//  TileNode.h
//  SaveHostage
//
//  Created by Chen Guo on 2/22/14.
//
//

#ifndef __SaveHostage__TileNode__
#define __SaveHostage__TileNode__

#include <iostream>

#define BLKWIDTH 30.0

class TileNode
{
private:
    int A_F;
    int A_H;
    int A_G;
    int P_X;
    int P_Y;
    TileNode* parent;
public:
    TileNode();
    
    void setF(int f);
    void setH(int h);
    void setG(int g);
    void setX(int x);
    void setY(int y);
    void setParent(TileNode* parent);
    int getF() const;
    int getG() const;
    int getH() const;
    int getX() const;
    int getY() const;
    TileNode* getParent() const;
};

#endif /* defined(__SaveHostage__TileNode__) */

//
//  TileNode.cpp
//  SaveHostage
//
//  Created by Chen Guo on 2/22/14.
//
//

#include "TileNode.h"

TileNode::TileNode()
{
    A_F = 0;
    A_G = 0;
    A_H = 0;
    P_X = 0;
    P_Y = 0;
}

int TileNode::getF() const
{
    return A_F;
}

int TileNode::getG() const
{
    return A_G;
}

int TileNode::getH() const
{
    return A_H;
}

int TileNode::getX() const
{
    return P_X;
}

int TileNode::getY() const
{
    return P_Y;
}

TileNode* TileNode::getParent() const
{
    return parent;
}

void TileNode::setF(int f)
{
    A_F = f;
}

void TileNode::setG(int g)
{
    A_G = g;
}

void TileNode::setH(int h)
{
    A_H = h;
}

void TileNode::setX(int x)
{
    P_X = x;
}

void TileNode::setY(int y)
{
    P_Y = y;
}

void TileNode::setParent (TileNode* vparent)
{
    parent = vparent;
}


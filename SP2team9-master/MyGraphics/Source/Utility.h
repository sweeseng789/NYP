/******************************************************************************/
/*!
\file	Utility.cpp
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Position Class
*/
/******************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, Position rhs);


#endif 
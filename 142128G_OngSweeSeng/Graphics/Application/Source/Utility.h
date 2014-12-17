#ifndef UTILITY_H
#define UTILITY_H
#include "Vertex.h"
#include "Mtx44.h"


/****************************************************************************/
/*!
\file	Utility.h
\author Ong Swee Seng
\brief Utility.h is used to provide position parameters
*/
/****************************************************************************/

Position operator*(const Mtx44& lhs, const Position& rhs);

#endif
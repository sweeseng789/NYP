#include "SceneNode.h"
//#include "../SceneManager.h"
#include "../SceneGame.h"
#include "../SceneMenu.h"
#include "Vector3.h"

#include <cstdlib>

CSceneNode::CSceneNode(void)
: theModel( NULL )
, theChildren( NULL )
, theTransform ( NULL )
, sceneNodeID (-1)
{
}

CSceneNode::CSceneNode(const int sceneNodeID)
{
	CSceneNode();
	SetSceneNodeID( sceneNodeID );
}


CSceneNode::~CSceneNode(void)
{
	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = theChildren[i];
			delete aChild;
			aChild = NULL;
		}
		theChildren.clear();
	}

	if (theModel)
	{
		delete theModel;
		theModel = NULL;
	}

	if (theTransform != NULL)
	{
		delete theTransform;
		theTransform = NULL;
	}
}


void CSceneNode::Draw(void)
{
	if (theTransform)
	{
		theTransform->PreRendering();
		if (theModel)
			theModel->Draw(CModel::s_HIGH);

		if (theChildren.size() != 0)
		{
			CNode* aChild = NULL;
			for (unsigned i=0; i<theChildren.size(); i++)
			{
				aChild = theChildren[i];
				aChild->Draw();
			}
		}

		theTransform->PostRendering();
	}
}

//Main game draw
void CSceneNode::Draw(SceneGame* theSceneManager)
{
	this->theModel->getMesh();
	if (theTransform)
	{
		theTransform->PreRendering();

		theSceneManager->PreRendering(theTransform, false, theModel->getMesh());
		if (theModel)
			theModel->Draw(CModel::s_HIGH);
		theSceneManager->PostRendering(theModel->getMesh());

		if (theChildren.size() != 0)
		{
			CNode* aChild = NULL;
			for (unsigned i=0; i<theChildren.size(); i++)
			{
				aChild = theChildren[i];
				((CSceneNode*)aChild)->Draw(theSceneManager);
			}
		}
		/*system("cls");
		std::cout << theTransform->GetTransform().a[0] << ", " << theTransform->GetTransform().a[4] << ", " << theTransform->GetTransform().a[8] << ", " << theTransform->GetTransform().a[12] << std::endl;
		std::cout << theTransform->GetTransform().a[1] << ", " << theTransform->GetTransform().a[5] << ", " << theTransform->GetTransform().a[9] << ", " << theTransform->GetTransform().a[13] << std::endl;
		std::cout << theTransform->GetTransform().a[2] << ", " << theTransform->GetTransform().a[6] << ", " << theTransform->GetTransform().a[10] << ", " << theTransform->GetTransform().a[14] << std::endl;
		std::cout << theTransform->GetTransform().a[3] << ", " << theTransform->GetTransform().a[7] << ", " << theTransform->GetTransform().a[11] << ", " << theTransform->GetTransform().a[15] << std::endl;*/


		//theTransform->PostRendering();
	}
}

//Menu draw
void CSceneNode::Draw(SceneMenu* theSceneManager)
{
	this->theModel->getMesh();
	if (theTransform)
	{
		theTransform->PreRendering();

		theSceneManager->PreRendering(theTransform, false, theModel->getMesh());
		if (theModel)
			theModel->Draw(CModel::s_HIGH);
		theSceneManager->PostRendering(theModel->getMesh());

		if (theChildren.size() != 0)
		{
			CNode* aChild = NULL;
			for (unsigned i = 0; i<theChildren.size(); i++)
			{
				aChild = theChildren[i];
				((CSceneNode*)aChild)->Draw(theSceneManager);
			}
		}
	}
}

void CSceneNode::SetModel(CModel* theModel)
{
	this->theModel = theModel;
}

int CSceneNode::SetNode(CTransform* aNewTransform, CModel* aNewModel)
{
	this->theModel = aNewModel;
	this->theTransform = aNewTransform;
	// Set sceneNodeID to 1 as this is the root node
	sceneNodeID = 1;
	return sceneNodeID;
}

void CSceneNode::SetSceneNodeID(const int sceneNodeID)
{
	this->sceneNodeID = sceneNodeID;
}

int CSceneNode::AddChild(CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode();
	aNewTransform->SetRotate(1, 1, 1, 1);
	aNewNode->SetNode( aNewTransform, aNewModel );
	aNewNode->SetSceneNodeID( sceneNodeID*10 + (theChildren.size()+1) );
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::AddChild(const int sceneNodeID, CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode( sceneNodeID );
	aNewNode->SetNode( aNewTransform, aNewModel );
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::GetSceneNodeID(void)
{
	return sceneNodeID;
}

CSceneNode* CSceneNode::GetNode(const int sceneNodeID)
{
	if (this->sceneNodeID == sceneNodeID)
		return this;

	CSceneNode* theTarget = NULL;
	if (theChildren.size() != 0)
	{
		CSceneNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = (CSceneNode*)theChildren[i];

			theTarget = ((CSceneNode*)aChild)->GetNode( sceneNodeID );
			if (theTarget != NULL)
				break;
		}
	}

	return theTarget;
}

CSceneNode* CSceneNode::getSelf()
{
	return this;
}

void CSceneNode::ApplyTranslate( const float dx, const float dy, const float dz )
{
	if (theTransform)
		theTransform->SetTranslate( dx, dy, dz );
}


void CSceneNode::ApplyRotate( const float angle, const float rx, const float ry, const float rz )
{
	if (theTransform)
	{
		// Then rotate the children
		theTransform->SetRotate( angle, rx, ry, rz );
	}
}


// Get top left corner of the group
Vector3 CSceneNode::GetTopLeft(void)
{
	if (theTransform == NULL)
		return Vector3( theModel->GetTopLeft().x, 
theModel->GetTopLeft().y,
theModel->GetTopLeft().z);
	else
	{
		return (theTransform->GetTransform() * theModel->GetTopLeft());
	}
}

// Get bottom right corner of the group
Vector3 CSceneNode::GetBottomRight(void)
{
	if (theTransform == NULL)
		return Vector3(theModel->GetBottomRight().x,
			theModel->GetBottomRight().y,
			theModel->GetBottomRight().z);
	else
		return (theTransform->GetTransform() * theModel->GetBottomRight());
}

void CSceneNode::SetColor(const float red, const float green, const float blue)
{
	theModel->SetColor(red, green, blue);
}

// Return the number of children in this group
int CSceneNode::GetNumOfChild(void)
{
	return (int)theChildren.size();
}

// Get top left corner of a child
bool CSceneNode::GetTopLeft(const int m_iChildIndex, Vector3& Vector3_TopLeft)
{
	Vector3_TopLeft = Vector3(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i < theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			Vector3_TopLeft = theTransform->GetTransform() * aChild->GetTopLeft();
			return true;
		}
	}
	return false;
}

// Get bottom right corner of a child
bool CSceneNode::GetBottomRight(const int m_iChildIndex, Vector3& Vector3_BottomRight)
{
	Vector3_BottomRight = Vector3(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i < theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			Vector3_BottomRight = theTransform->GetTransform() * aChild->GetBottomRight();
			return true;
		}
	}
	return false;
}

void CSceneNode::SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue)
{
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i < theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			aChild->SetColor(red, green, blue);
		}
	}
}
void CSceneNode::findChildById(int ID, CSceneNode* &node)
{
	for (std::vector<CNode*>::iterator it = theChildren.begin(); it != theChildren.end(); ++it)
	{
		CSceneNode *sceneNode = dynamic_cast<CSceneNode*>(*it);

		if (sceneNode->GetSceneNodeID() == ID)
		{
			node = sceneNode;
		}
	}

	node = NULL;
}

CTransform* CSceneNode::getTransform()
{
	return theTransform;
}

CModel* CSceneNode::getModel()
{
	return theModel;
}

void CSceneNode::switchResolution(CModel::RESOLUTION currRes)
{
	/*CSceneNode* aChild = NULL;
	for (unsigned i = 0; i < theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			aChild->SetColor(red, green, blue);
		}
	}*/
	theModel->switchRes(currRes);
	for (int a = 0; a < theChildren.size(); ++a)
	{
		CSceneNode* child = (CSceneNode*)theChildren[a];
		child->getModel()->switchRes(currRes);
	}
}


enum FLOCKING
{
	SEPARATE,
	COHESION,
	IGNORE,
	NUM_FLOCKING,
};
//I hate this

//FLOCKING flockit;
//flockit = IGNORE;

//If player is within cohesion Ring == Move towards it
//if (distance < 50.f)
//{

//}
//If the player is within separation ring == move away
//else if (distance < 10)
//{
	//Get Rekt Bois
//}
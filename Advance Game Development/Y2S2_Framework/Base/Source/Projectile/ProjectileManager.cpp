#include "ProjectileManager.h"

static const int theMaxNumberOfProjectiles = 50;

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectileManager::CProjectileManager(void)
	: theListOfProjectiles(NULL)
	, NumOfActiveProjectile(0)
	, CurrentEmptyProjectile(0)
	, ProjectileList(NULL)
{
	/*theListOfProjectiles = new CProjectile*[theMaxNumberOfProjectiles];
	for (int i=0; i<theMaxNumberOfProjectiles; i++)
	{
		theListOfProjectiles[i] = new CProjectile();
	}
	Boundary_TopLeft		= Vector3( 300.0f, 300.0f, 300.0f);
	Boundary_BottomRight	= Vector3( -300.0f, 0.0f, -300.0f);*/
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectileManager::~CProjectileManager(void)
{
	if (theListOfProjectiles)
	{
		for (int i=0; i<theMaxNumberOfProjectiles; i++)
		{
			delete theListOfProjectiles[i];
		}
		delete [] theListOfProjectiles;
		theListOfProjectiles = NULL;
	}

	while (ProjectileList.size() > 0)
	{
		CProjectile* projectile = ProjectileList.back();
		delete projectile;
		ProjectileList.pop_back();
	}
}

CProjectile* CProjectileManager::fetchProjectile()
{
	for (std::vector<CProjectile*>::iterator it = ProjectileList.begin(); it != ProjectileList.end(); ++it)
	{
		CProjectile* projectile = static_cast<CProjectile*>(*it);

		if (!projectile->GetStatus())
		{
			projectile->SetActivate(true);
			return projectile;
		}
	}

	for (unsigned a = 0; a < 10; ++a)
	{
		CProjectile* projectile = new CProjectile();
		projectile->SetActivate(true);
		ProjectileList.push_back(projectile);
	}

	CProjectile* projectile = ProjectileList.back();
	projectile->SetActivate(true);
	return projectile;
}

/********************************************************************************
 Add Projectile
 ********************************************************************************/
bool CProjectileManager::AddProjectile(Vector3 position, Vector3 direction, const float speed)
{
	// Find the next empty projectile
	//if (NumOfActiveProjectile < theMaxNumberOfProjectiles)
	//{
	//	int StartIndex = CurrentEmptyProjectile;
	//	// Loop until we find an empty slot
	//	while (theListOfProjectiles[CurrentEmptyProjectile]->GetStatus() == true)
	//	{
	//		CurrentEmptyProjectile++;
	//		if (CurrentEmptyProjectile >= theMaxNumberOfProjectiles)
	//			CurrentEmptyProjectile = 0;
	//		// If we have checked 'theMaxNumberOfProjectiles' number of slots, and
	//		// still have not found a vacancy, then stop this loop. As the slot at 
	//		// CurrentEmptyProjectile is not empty, we will not be able to add it in.
	//		if (CurrentEmptyProjectile == StartIndex)
	//			break;
	//	}

	//	if (IsActive(CurrentEmptyProjectile)==false)
	//	{
	//		theListOfProjectiles[CurrentEmptyProjectile]->SetPosition( position );
	//		theListOfProjectiles[CurrentEmptyProjectile]->SetDirection( direction );
	//		theListOfProjectiles[CurrentEmptyProjectile]->SetSpeed( speed );
	//		theListOfProjectiles[CurrentEmptyProjectile]->SetActivate( true );
	//		CurrentEmptyProjectile++;
	//		NumOfActiveProjectile++;

	//		return true;
	//	}
	//}
	//return false;

	CProjectile* newProjectile = fetchProjectile();
	if (newProjectile != NULL)
	{
		newProjectile->SetPosition(position);
		newProjectile->SetDirection(direction);
		newProjectile->SetSpeed(speed);
		return true;
	}
	else
	{
		return false;
	}

}

/********************************************************************************
 Set Projectile
 ********************************************************************************/
void CProjectileManager::SetProjectile(const int index, Vector3 position, Vector3 direction)
{
	theListOfProjectiles[index]->SetPosition( position );
	theListOfProjectiles[index]->SetDirection( direction );
	theListOfProjectiles[index]->SetActivate( true );
}

/********************************************************************************
 Remove Projectile
 ********************************************************************************/
void CProjectileManager::RemoveProjectile(const int index)
{
	if (IsValid( index ))
	{
		theListOfProjectiles[index]->SetActivate( false );
		NumOfActiveProjectile--;
	}
}

/********************************************************************************
 Get Maximum Number of Projectiles
 ********************************************************************************/
int CProjectileManager::GetMaxNumberOfProjectiles(void)
{
	return theMaxNumberOfProjectiles;
}

/********************************************************************************
 Get Number of Active Projectile
 ********************************************************************************/
int CProjectileManager::GetNumberOfActiveProjectiles(void)
{
	return NumOfActiveProjectile;
}

/********************************************************************************
 Get Projectile
 ********************************************************************************/
CProjectile* CProjectileManager::GetProjectile(const int index)
{
	if (IsValid( index ))
		return theListOfProjectiles[index];
	return NULL;
}

/********************************************************************************
 Check methods
 ********************************************************************************/
bool CProjectileManager::IsValid(const int index)
{
	if ((index<0) || (index>theMaxNumberOfProjectiles))
		return false;
	return true;
}

/********************************************************************************
 Check if a projectile is active
 ********************************************************************************/
bool CProjectileManager::IsActive(const int index)
{
	if (IsValid(index))
		return theListOfProjectiles[index]->GetStatus();
	else
		return true;	//	return true as we do not wish to use this index
}

/********************************************************************************
 Update
 ********************************************************************************/
void CProjectileManager::Update(const double dt)
{
	//for (int i=0; i<theMaxNumberOfProjectiles; i++)
	//{
	//	// Skip this projectile if it is not active
	//	if (theListOfProjectiles[i]->GetStatus() == false)
	//		continue;

	//	// Update the projectile
	//	theListOfProjectiles[i]->Update(dt);

	//	// Check if it is out of the boundaries
	//	Vector3 CheckThisPosition = theListOfProjectiles[i]->GetPosition();
	//	if (((CheckThisPosition.x > Boundary_TopLeft.x) || 
	//	     (CheckThisPosition.y > Boundary_TopLeft.y) ||
	//	     (CheckThisPosition.z > Boundary_TopLeft.z)) ||
	//		 ((CheckThisPosition.x < Boundary_BottomRight.x) ||
	//	     (CheckThisPosition.y < Boundary_BottomRight.y) ||
	//	     (CheckThisPosition.z < Boundary_BottomRight.z)) )
	//	{
	//		// Since it is out of the boundaries, then set it to inactive
	//		RemoveProjectile( i );
	//	}
	//}

	for (std::vector<CProjectile*>::iterator it = ProjectileList.begin(); it != ProjectileList.end(); ++it)
	{
		CProjectile* projectile = static_cast<CProjectile*>(*it);

		//skip if projectile is not active
		if (!projectile->GetStatus())
			continue;

		//Update Projectile
		projectile->Update(dt);
	}
}
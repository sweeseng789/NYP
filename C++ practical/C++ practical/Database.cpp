#include "Database.h"


CDatabase::CDatabase(void)
{
	head = tail = current = prev = NULL;

}


CDatabase::~CDatabase(void)
{
}

void CDatabase::Insert(int newValue)
{
	newNode = new CNode(newValue);
	if (head == NULL)
	{
		//LL is empty
		//prev = head = tail = newNode;
		head = newNode;
		tail = newNode;
		newNode->back = NULL;
		newNode->next = NULL;
	}
	else//head != NULL
	{
		if (newValue <= head->data)//insert to front
		{
			newNode->back = NULL;
			newNode->next = head;
			head->back = newNode;
			head = newNode;
		}
		else if(newValue >= tail->data)//insert to back
		{
			newNode->back = NULL;
			newNode->back = tail;
			tail->next = newNode;
			tail = newNode;
		}
		else //Middle insertion
		{
			current = head;
			while (current != NULL)
			{
				if(current->data >= newNode->data && prev->data < newNode->data)
				{
					prev->next = newNode;
					newNode->back = prev;
					newNode->next = current;
					current->back = newNode;
					break;
				}
				prev = current;
				current = current->next;
			}
		}
	}
}
	

void CDatabase::PrintAll(void)
{
	//Print all
	if (head != NULL)
	{
		current = head;
		cout << "Single: ";
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
	
		cout << endl;
			monsterStuff.printAll();
	}
	else
		cout << "LL Empty." << endl;
}

void CDatabase::PrintD()
{
	if (head != NULL)
	{
		current = tail;
		cout << "Doubly: ";
		while(current != NULL)
		{
			cout << current->data << " ";
			current = current->back;
		}

		cout << endl;
	}
	else
		cout << "LL Empty." << endl;
}

bool CDatabase::Delete(int toDelete)
{
	if (head != NULL) // check if LL is empty
	{
		//transverse through the LL
		current = head;
		while (current != NULL)
		{
			if (current->data == toDelete)
				break;
			else
			{
				prev = current;
				current = current->next;
			}
		}

		if (current == head)// the data to be deleted is in 1st node
		{
			
			if (head->next != NULL)//there are more than 1 node in the LL
			{
				head = head->next;
				head->back = NULL;
				delete current;
				return true;
			}
			else//only one node in the LL
			{
				delete current;
				head = tail = NULL;
				return true;
			}
		}
		else if (current == tail)// data to be deleted is in the last node
		{
			tail = prev;
			tail->next = NULL;
			tail->back = prev->back;
			delete current;
			return true;
		}
		else if (current == NULL)// no such data found in the LL
		{
			return false;
		}
		else// data to be deleted is somewhere in the middle
		{
			prev->next = current->next;
			current->next->back = prev;
			delete current;
			return true;
		}
	}
	else
		return false;
}

#include "Database.h"


CDatabase::CDatabase(void)
{
	head = tail = current = prev = NULL;

}


CDatabase::~CDatabase(void)
{
}

void CDatabase::Insert(int newValue, int newLevel, int newHealth, string newName)
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
		head->parameters->set(newName, newLevel, newHealth);
	}
	else//head != NULL
	{
		if (newValue <= head->data)//insert to front
		{
			newNode->back = NULL;
			newNode->next = head;
			newNode->parameters->set(newName, newLevel, newHealth);
			head->back = newNode;
			head = newNode;
		}
		else if(newValue >= tail->data)//insert to back
		{
			newNode->back = NULL;
			newNode->back = tail;
			newNode->parameters->set(newName, newLevel, newHealth);
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
					newNode->parameters->set(newName, newLevel, newHealth);
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
		while (current != NULL)
		{
			cout << "Rank: " << current->data << endl;
			current->parameters->printAll();
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LL Empty." << endl;
}

void CDatabase::PrintD()
{
	if (head != NULL)
	{
		current = tail;
		while(current != NULL)
		{
			cout << "Rank: " << current->data << endl;
			current->parameters->printAll();
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

bool CDatabase::RecordValidation(int newValue)
{
	if (head != NULL)
	{
		current = head;
		while(current != NULL)
		{
			if (current->data == newValue)
			{
				return true;
			}
			else
			{
				return false;
			}
			prev = current;
			current = current->next;
		}
	}
}

void CDatabase::EditRecord(int newValue, int newLevel, int newHealth, string newName)
{
	if (head != NULL)
	{
		current = head;
		while (current != NULL)
		{
			if (newValue == current->data)
			{
				current->parameters->set(newName, newLevel, newHealth);
			}
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LinkList is Empty" << endl;
}

void CDatabase::EditMonsterName(int newValue, string newName)
{
	if (head != NULL)
	{
		current = head;
		while (current != NULL)
		{
			if (newValue == current->data)
			{
				current->parameters->setName(newName);
			}
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LinkList is Empty" << endl;
}

void CDatabase::EditMonsterLevel(int newValue, int newLevel)
{
	if (head != NULL)
	{
		current = head;
		while (current != NULL)
		{
			if (newValue == current->data)
			{
				current->parameters->setLevel(newLevel);
			}
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LinkList is Empty" << endl;
}

void CDatabase::EditMonsterHealth(int newValue, int newHealth )
{
	if (head != NULL)
	{
		current = head;
		while (current != NULL)
		{
			if (newValue == current->data)
			{
				current->parameters->setHealth(newHealth);
			}
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LinkList is Empty" << endl;
}

void CDatabase::SearchFunction(string SearchWords)
{
	if (head != NULL)
	{
		current = head;
		string str1, str2;
		str2 = SearchWords;
		while (current != NULL)
		{
			str1 = current->parameters->getName();
			if (str1.find(str2) != string::npos)
			{
				cout << "Rank: " << current->data << endl;
				current->parameters->printAll();
			}
			else
			{
				cout << "Nothing found" << endl;
			}
			current = current->next;
		}
		cout << endl;
	}
	else
		cout << "LinkList is Empty" << endl;
}

bool CDatabase::detectFirstNode()
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
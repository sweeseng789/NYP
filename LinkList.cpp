#include "LinkList.h"


CLinkList::CLinkList(void)
{
	head = tail = current = prev = NULL;
}


CLinkList::~CLinkList(void)
{
}

void CLinkList::InsertForward(int newValue)
{
	newNode = new CNode(newValue);
	if (head == NULL)
	{
		//You know the LL is empty
		head = tail = newNode;
	}
	else
	{
		//Insert the new integer to the tail
		tail->next = newNode;
		tail = newNode;
	}
}

void CLinkList::InsertBackward(int newValue)
{
	newNode = new CNode(newValue);
	if (head == NULL)
	{
		//You know the LL is empty
		head = tail = newNode;
	}
	else
	{
		//Insert the new integer to the head
		newNode->next = head;
		head = newNode;
	}
}

void CLinkList::CheckNumber(int newValue)
{
	newNode = new CNode(newValue);

	if (head == NULL)
	{
		//LL is empty
		prev = head = tail = current = newNode;
	}
	else
	{
		if (head != NULL)
		{
			current = head;
			if(current != NULL)
			{
				if(newNode->data > current->data)
				{
					/*prev->next = newNode;
					newNode->next = current;*/
					current->next = newNode;
					current = newNode->next;
				}
				else
				{
					tail->next = newNode;
					tail = newNode;
				}

				prev = current;
				current=current->next;
			}
		}
		//Insert the new integer to the tail
		/*tail->next = newNode;
		tail = newNode;*/
	}
}

void CLinkList::PrintAll(void)
{
	//Print all
	if (head != NULL)
	{
		current = head;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}

		cout << endl;
	}
	else
		cout << "LL Empty." << endl;
}

bool CLinkList::Delete(int toDelete)
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

		//analyse the current ptr
		if (current == head)
		{
			// the data to be deleted is in 1st node
			if (head->next != NULL)
			{
				//there are more than 1 node in the LL
				head = head->next;
				delete current;
				return true;
			}
			else
			{
				//only one node in the LL
				delete current;
				head = tail = NULL;
				return true;
			}
		}
		else if (current == tail)
		{
			// data to be deleted is in the last node
			tail = prev;
			tail->next = NULL;
			delete current;
			return true;
		}
		else if (current == NULL)
		{
			// no such data found in the LL
			return false;
		}
		else
		{
			// data to be deleted is somewhere in the middle
			prev->next = current->next;
			delete current;
			return true;
		}
	}
	else
		return false;
}
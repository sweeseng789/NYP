#include "LinkList.h"


CLinkList::CLinkList(void)
{
	head = tail = current = prev = NULL;
	count = 0;
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

void CLinkList::Insert(int newValue)
{
	newNode = new CNode(newValue);

	if (head == NULL)
	{
		//LL is empty
		prev = current = head = tail = newNode;
		count++;
	}
	else//head != NULL
	{
	//	current = head;
	//	while(current != NULL)
	//	{
	//		if (current->data > newNode->data)
	//		{
	//			/*prev = current;
	//			current = current->next;
	//			prev->next = newNode;
	//			newNode->next = current;*/
	//			prev = current;
	//			current = current->next;
	//			prev->next = newNode;
	//			newNode->next = current;
	//			break;
	//		}
	//		else if(current->next == NULL)
	//		{
	//			tail->next = newNode;
	//			tail = newNode;
	//			break;
	//		}
	//		else if(current == head)
	//		{
	//			newNode->next = head;
	//			head = newNode;
	//			break;
	//		}
	//		newNode->next = current;
	//		prev->next = newNode;
	//		
	//	}
	//}

		//check if newValue is bigger or smaller
		if (newValue <= head->data)
		{
			//insert to front
			newNode->next = head;
			head = newNode;
		}
		else if(newValue >= tail->data)
		{
			//insert to back
			tail->next = newNode;
			tail = newNode;
		}
		//transverse till find the correct place to insert
			current = head;
			while(current != NULL)
			{
				if(current->data >= newNode->data)
				{	
					//do middle insertion]
					break;
				}
				prev = current;
				cout << "prev: " << prev->data << endl;
				
				current = current->next;
				cout << "current:" << current->data << endl;

				prev->next = newNode;
				newNode ->next = current;
			}
	}
	cout << "head:" << head->data << endl;
	cout << "tail:" << tail->data << endl;
	cout << endl;
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
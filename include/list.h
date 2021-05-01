#pragma once

#include<vector>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

#define Rehash 0.75
#define Num 8

template<class T>
struct HashElement
{
	T key;
	bool del;
	HashElement(const T& value) : key(value), del(false) {}
public:
	bool DelOrNotDel() { return del; }
	const T& GetKey() { return key; }
	void ItWasDeleted() { del = true; }
	void ItWasNotDeleted() { del = false; }
	void SetKey(const T& key1) { key = key1; }

};

template <class T>
class THashTable
{
	vector<HashElement<T>*> Table;
	int bufersize;//without deleted elements;
	int size;//with deleted elements;
public:
	THashtable() : Table(Num, nullptr), buffersize(Num), size(0) {}
	THashTable(const THashTable& a)
	{
		size = a.size;
		bufersize = a.bufersize;
		for (int i = 0; i < Table.size(); i++)
		{
			Table[i] = a.Table[i];
		}
	}
	int HashGorner(const T& key1, int Hashh)
	{
		int hash = 0;
		for (int i = 0; i < key1.size(); ++i)
		{
			hash += (Hashh * hash + key1[i]) % size;
		}
		return ((2 * hash + 1) % size);
	}
	int Hash1(T& key1)
	{
		return(HashGorner(key1, (size + 1)));
	}
	int Hash2(T& key1)
	{
		return(HashGorner(key1, size - 1));
	}
	void ReHash()
	{
		int newsize = size * 2;
		vector<HashElement<T>*> NewTable(newsize, nullptr);
		for (int i = 0; i < size; i++)
		{
			if ((Table[i] != nullptr) && (!Table[i].DelOrNotDel())//если существует элемент
			{
				int hash1 = Hash1(key1, size);
				int hash2 = Hash2(key1, size);
				int k = 0;
				while ((NewTable[hash1] != nullptr) && (k < newsize))
				{
					hash1 = (hash1 + hash2) % newsize;
					k++;
				}
				NewTable[hash1] = Table[i];
			}
			else//еcлии €чейка в старой €чейке пуста;
			{
				delete Table[i];//cell is empty;
			}
			Table[i] = nullptr;
		}
		Table = NewTable;
		size = newsize;
	}
	bool Insert(const T& key1)
	{
		if (((double)(bufersize)) / (double)(size) >= ReHash))//проверка на перехешировани€;
				ReHash();
		int hash1 = Hash1(key1, size);
		int hash2 = Hash2(key1, size);
		int deletededlement = -1;
		for (int i = 0; (buffer[hash1] != nullptr) && (i < buffer_size); i++)
		{
			if ((Table[hash1]->GetKey() == key1) && (!Table[hash1]->DelOrNotDel()))//вот тут надо перегрузить опрерации;
			{
				return false;
			}
			if ((Table[hash1]->DelOrNotDel()) && (deletededlement == -1))
			{
				deletededlement = hash1;
			}
			hash1 = (hash1 + hash2) % bufersize;
		}
		if (deletededlement == -1)
		{
			Table[h1] = new HashElement<T>(key1);
		}
		else
		{
			Table[deletededlement]->SetKey(key1);
			Table[deletededlement]->ItWasNotDeleted();
		}
		size++;
		return true;
	}
	bool Delete(const T& key1)
	{
		int hash1 = Hash1(key1, size);
		int hash2 = Hash2(key1, size);
		for (int i = 0; Table[hash1] != nullptr && i < buffersize; i++)
		{
			if (Table[hash1]->GetKey() == key1 && !Table[hash1]->DelOrNotDel()) //если нашли элемент
			{
				Table[hash1]->del = true;
				size--;
				return true;
			}
			hash1 = (hash1 + hash2) % bufersize;
		}
		return false;
	}
	bool Find(const T& key1) const
	{
		int hash1 = Hash1(key1, size);
		int hash2 = Hash2(key1, size);
		for (int i = 0; Table[hash1] != nullptr && i < buffersize; i++)
		{
			if ((Table[hash1]->GetKey() == key1) && !Table[hash1]->DelOrNotDel())
			{
				return true;
			}
			hash1 = (hash1 + hash2) % bufersize;
			i++;
		}
		return false;
	}
	~THashTable()
	{
		for (int i = 0; i < Table.size(); i++)
		{
			delete Table[i];
		}
	}
};
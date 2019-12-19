#include"hashtable.h"
#define SIZE 5000
//read file
vector<Company> ReadListCompany(string file_name)
{
	Company compObject;

	int i = 0;

	file_name = file_name + ".txt";

	vector<Company> comp;

	string token;

	ifstream fi;

	fi.open(file_name);

	if (fi.is_open())
	{
		getline(fi, token);
		while (!fi.eof())
		{
			getline(fi, token, '|');
			if (token == "")
				break;

			comp.push_back(compObject);

			comp[i].name = token;

			getline(fi, token, '|');
			comp[i].profit_tax = token;

			getline(fi, token, '\n');
			comp[i].address = token;

			i++;
		}

		fi.close();
	}
	else
		cout << "File not found" << endl;

	return comp;

}


void initCompanyName(Company* comp)
{
	for (int i = 0; i < SIZE; i++)
	{
		comp[i].name = "@";
	}
}

Company* CreateHashTable(vector<Company> list_company)
{
	Company* comp = NULL;
	comp = new Company[SIZE];

	unsigned int hashIndex;

	int n = list_company.size();

	initCompanyName(comp);

	for (int i = 0; i < list_company.size(); i++)
	{
		hashIndex = HashString(list_company[i].name) % SIZE;
		while (comp[hashIndex].name != "@")
		{
			hashIndex++;
		}

		comp[hashIndex] = list_company[i];
	}

	return comp;
}

void Insert(Company* hash_table, Company company)
{
	int hashIndex;

	for (int i = 0; i < SIZE; i++)
	{
		hashIndex = HashString(company.name) % SIZE;
		while (hash_table[hashIndex].name != "@")
		{
			hashIndex++;
		}
		hash_table[hashIndex] = company;
	}
}

Company Search(Company* hash_table, string company_name)
{
	int hashIndex;
	Company SearchComp;
	hashIndex = HashString(company_name) % SIZE;

	if (hash_table[hashIndex].name == company_name)
	{
		SearchComp = hash_table[hashIndex];
	}

	else if (hash_table[hashIndex].name == "@")
		cout << "Not found" << endl;

	return SearchComp;

}


long long power(long long a, long long b, long long c) {
	long long ans = 1;
	for (int i = 1; i <= b; i++) {
		ans *= a;
		ans %= c;
	}
	return ans;
}

unsigned long long int HashString(string company_name)
{
	string s;

	unsigned long long int hashKey = 0;

	int p = 31;

	unsigned long long int m = pow(10, 9) + 9;

	if (company_name.length() > 20)
		s = company_name.substr(company_name.length() - 20);
	else
		s = company_name;


	for (int i = 0; i < s.length(); i++)
	{
		unsigned long long int a = int(s[i]) % m;
		unsigned long long int b = power(p, i, m);

		hashKey = hashKey + ((a * b) % m);
	}
	return hashKey;
}


int main()
{
	vector<Company> compList;
	compList = ReadListCompany("MST");
	Company* comp = NULL;
	comp = new Company[SIZE];

	comp = CreateHashTable(compList);

	delete[]comp;
}



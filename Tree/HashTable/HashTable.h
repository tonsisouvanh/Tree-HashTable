#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

struct Company
{
	string name;
	string profit_tax;
	string address;
};

vector<Company> ReadListCompany(string file_name);
unsigned long long int HashString(string company_name);

long long power(long long a, long long b, long long c);
void initCompanyName(Company* comp);

Company Search(Company* hash_table, string company_name);
Company* CreateHashTable(vector<Company> list_company);
void Insert(Company* hash_table, Company company);

#endif
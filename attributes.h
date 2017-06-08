#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H
#include <vector>	
#include <string>

using namespace std;

typedef enum {
	T_VAL,
	F_VAL,
	UNDEFINED
} check_bool;

typedef struct
{
	int type;
	string name;
	int value;
	vector<int> exp_list;
	bool insert;
	vector<pair<string,int> > formal_list;
	bool have_sure_exit;
	check_bool is_true;
} STYPE;

#define YYSTYPE STYPE	// Tell Bison to use STYPE as the stack type

#endif


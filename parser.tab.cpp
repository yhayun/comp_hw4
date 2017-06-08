/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp" /* yacc.c:339  */

#include "attributes.h"
#include "output.hpp"
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;	
using namespace output;

extern int yylex();
extern int yylineno;

//DONT PUT ANY NON FUNCTION TYPES BELOW BYTE!!!!!	
	enum ttypes{
//EVERY TIME YOU TOUCH SOMETHING HERE U NEED TO CHANGE STUFF LIKE INT TO NAME
//JOHN IF U WANT TO CHANGE SOMETHING DON TDO IT WITH ASKING ME 
	 	TYPE_INT,
		TYPE_BOOL,
		TYPE_BYTE,
		TYPE_STRING,
		TYPE_FUNC_INT,
		TYPE_FUNC_BOOL,
		TYPE_FUNC_BYTE,
		TYPE_FUNC_VOID,
		TYPE_MAX
	};

//****************************************************************************************************
//                                   symblo table implementation:
//****************************************************************************************************
void int_to_name_push(int i, vector<const char*>& proto_names);
class info {
public:	
	string name;
	int offset;
	bool is_func;
	int type;
	vector<int> params;

//Methods:	
	info(string xname, int xoffset, int xtype){
		is_func = false;
		name = string(xname);
		offset = xoffset;
		type = xtype; 
		params = vector<int>();
	}

	/**
	 * compares this info with another
	 * @param  x [another info]
	 * @return   [bool]
	 */
	bool compare(info& x){
		if (name == x.name && is_func == x.is_func)
		return true;
	return false;
	}

	/**
	 * Compares between infos - returns true if equal.
	 * @param  a [left info]
	 * @param  b [right info]
	 * @return   [bool]
	 */
	bool info_compare(info& a, info& b){
		if (a.name == b.name && a.is_func == b.is_func)
			return true;
		return false;
	}
};


class glob_data {
	//symbol table main stack:
	vector<vector<info> > symb_stack;
	//track the offset of vars in the symbol stack global:
	stack<int> offset_stack;
public:
	//stores the current function declartions vars:
	//to keep track of the return type of function:
	int func_return;
	//Counts how many while loops so far:
	int is_while;

//Methods:
	glob_data(){
		is_while = 0;
		func_return = -1;
		symb_stack = vector<vector<info> >();
		symb_stack.push_back(vector<info>());
		offset_stack.push(0);
		info print_info("print",0,TYPE_FUNC_VOID);
		info printI_info("printi",0,TYPE_FUNC_VOID);
		print_info.is_func = 1;
		print_info.params.push_back(TYPE_STRING);
		printI_info.is_func = 1;
		printI_info.params.push_back(TYPE_INT);
		symb_stack.back().push_back(print_info);
		symb_stack.back().push_back(printI_info);
	}
	const char* int_to_name(int i){
      		if (i == TYPE_BYTE) return "BYTE";
        	if (i == TYPE_INT)  return "INT";
        	if (i == TYPE_BOOL) return "BOOL";
        	if (i == TYPE_STRING)  return "STRING";
                if (i == TYPE_FUNC_BYTE) return "BYTE";
                if (i == TYPE_FUNC_INT)  return "INT";
                if (i == TYPE_FUNC_BOOL) return "BOOL";
		if (i == TYPE_FUNC_VOID) return "VOID";
	}
	int type_to_ret_type(int i){
                if (i == TYPE_INT) return TYPE_FUNC_INT;
                if (i == TYPE_BOOL) return TYPE_FUNC_BOOL;
                if (i == TYPE_BYTE) return TYPE_FUNC_BYTE;
	}
	/**
	 * push a new scope to global symbol table.
	 */
	void push_table(){
		vector<info> new_stack = vector<info>();
		symb_stack.push_back(new_stack);
		offset_stack.push(offset_stack.top());
	}

	/**
	 * removes the current scope and prints its content.
	 */
	void pop_table(){
		//NOT COMPLETE:
		endScope();
		for (vector<info>::iterator it = symb_stack.back().begin(); it !=symb_stack.back().end(); ++it){
			if ((*it).is_func == 0)
				 printID((*it).name.c_str(), (*it).offset, int_to_name((*it).type));
			else{
				if ((*it).name == "print" || (*it).name == "printi") continue;
                                vector<const char*> proto_names = vector<const char*>();
                                for (vector<int>::iterator it1 = (*it).params.begin();it1 != (*it).params.end();++it1){
                                      int_to_name_push(*it1, proto_names);
				}
				cout<<(*it).name<<" "<<makeFunctionType(int_to_name((*it).type), proto_names)<<" "<<(*it).offset<<endl;
				
			}
		}
		symb_stack.pop_back();	

		
		offset_stack.pop();
	}

	/**
	 * Pushes info into current scope for normal vars
	 * @param x [info]
	 */
	void add_symbol( info& x ){
		symb_stack.back().push_back(x);
		offset_stack.top()++;
	}

	/**
	 * Pushes info into current scope for FUNCTION vars
	 * @param x [info]
	 */
	void add_symbol_func( info x){
		symb_stack.back().push_back(x);
	}

	/**
	 * finds info inside a vector and stores it in 'store_found' if found :: used by find_in_table.
	 * @param  v           [vector]
	 * @param  x           [info]
	 * @param  store_found [res info placement]
	 * @return             [bool]
	 */
	bool vector_contains (vector<info>& v, info& x, info& store_found){
		vector<info>::iterator it;
		for (it = v.begin(); it != v.end(); it++){
			if (x.compare(*it)){
				store_found = (*it);
				return true;
			}
		}
		return false;
	}

	/**
	 * looks for a symbol with given name in global symbol table.
	 * @param  name    [ifo's name]
	 * @param  value   [placement to store info]
	 * @param  is_func [boolean - search for function if true, else var]
	 * @return         [info.type or -1 if not found]
	 */
	int find_in_table (string name, info& value, bool is_func)
	{
	  vector<vector<info> >::reverse_iterator rit;
	  for( rit = symb_stack.rbegin(); rit != symb_stack.rend(); ++rit)
		{
			info temp(name, 0, 0);
			temp.is_func = is_func;
			if (vector_contains((*rit), temp, value)){
				return value.type;
			}
		}
	  return -1;
	}

	/**
	 * finds var with given name.
	 * @param  name  [info's name]
	 * @param  value [placement to store info]
	 * @return       [info.type or -1 if not found]
	 */
	int find_var (string name, info& value){
		//range of vars in the global enum.
		return find_in_table(name, value, false);
	}

	/**
	 *  finds function with given name.
	 * @param  name  [info's name]
	 * @param  value [placement to store info]
	 * @return       [info.type or -1 if not found]
	 */
	int find_func (string name, info& value){
		//range of functions in the global enum.
		return find_in_table(name, value, true);
	}

	/**
	 *  check if function with given name exists.
	 * @param  name  [info's name]
	 * @return       [info.type or -1 if not found]
	 */
	int has_func(string name){
		info value("dummy", 0, 0);
		//range of functions in the global enum.
		return find_in_table(name, value, true);
	}

	/**
	 * check if var with given name exists.
	 * @param  name  [info's name]
	 * @return       [info.type or -1 if not found]
	 */
	int has_var(string name){
		info value("dummy", 0, 0);
		//range of vars in the global enum.
		return find_in_table(name, value, false);
	}

	/**
	 * handles 'Statement' insertion to symbol table.
	 * @param x         [Statement's STYPE]
	 * @param new_scope [bool]
	 */
	void manange_insert( STYPE& x , bool new_scope){
		if (x.insert == false)
			return;	
		x.insert == false;

		info new_info(x.name, offset_stack.top(), x.type);

		if (new_scope){
			//single var in scope:
			push_table();
			add_symbol(new_info);
			pop_table();
			return;
		}
		//push into current table:
		add_symbol(new_info);
		return;
	}
	bool is_same_list(vector<int>& v1, vector<int>& v2){
             vector<int>::iterator it1 = (v1).begin();
             vector<int>::iterator it2 = v2.begin();
             for(;   it1 != v1.end() || it2 != v2.end(); ++it1, ++it2) {
             if (*it1 != *it2 && !(*it2 == TYPE_BYTE && *it1 == TYPE_INT))
            	 {
			return false;
             	 }
             }
             if (it1 != v1.end() || it2 != v2.end())
             {
		return false;
             }
	     return true;
	}
	void add_func_symbol_to_table(vector<pair<string,int> >& symb_vec){
                vector<pair<string,int> >::iterator it;
                int i = -1;
                for( it = symb_vec.begin(); it != symb_vec.end(); ++it){
                         info new_info = info((*it).first, i--,(*it).second);
                         add_symbol_func(new_info);
                }
	}

	/**
	 * Compare values with the operand in the relop string
	 * @param  val1  [left operand]
	 * @param  relop [comparsion string]
	 * @param  val2  [right operand]
	 * @return       [bool result]
	 */
	bool check_relop(int val1, string relop, int val2){
			if (relop == "==")
				return val1 == val2;
			else if (relop == "!=")
				return val1 != val2;
			else if (relop == "<")
				return val1 < val2;
			else if (relop == ">")
				return val1 > val2;	
			else if (relop == "<=")
				return val1 <= val2;
			else if (relop == ">=")
				return val1 >= val2;	
			else{
				cout << "ERROR  <>---- RELOP COMMAND NOT FOUND ---- <>  ERROR";	
				exit(1);	
			}
	}

	/**
	 * cacluates the binop result if the operands are constant numbers.
	 * @param  val1  [left operand]
	 * @param  binop [operand string]
	 * @param  val2  [right operand]
	 * @return       [operation value]
	 */
	int calc_binop(int val1, string binop, int val2){ 
			if (binop == "+")
				return val1 + val2;
			else if (binop == "-")
				return val1 - val2;
			else if (binop == "*")
				return val1 * val2;
			else if (binop == "/")
				return val1 / val2;		
			else{
				cout << "ERROR  <>---- BINOP NOT FOUND ---- <>  ERROR";	
				exit(1);	
			}
	}	

	int convert_type_func_to_var( int func_type){
		//This is a quick fix. that relys on the distance between
		//functions types and var types inside the enum.
		//might needed to be repaired later.
		return func_type -4;
	}
	
};


//****************************************************************************************************
//                                   Other functions:
//****************************************************************************************************
	int yyerror(char const * message);
	void int_to_name_push(int i, vector<const char*>& proto_names);

//****************************************************************************************************
//                                   Globals:
//****************************************************************************************************
	glob_data st;

#line 437 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    INT = 259,
    BYTE = 260,
    B = 261,
    BOOL = 262,
    TRUE = 263,
    FALSE = 264,
    RETURN = 265,
    IF = 266,
    NUM = 267,
    WHILE = 268,
    SWITCH = 269,
    CASE = 270,
    BREAK = 271,
    COLON = 272,
    SC = 273,
    COMMA = 274,
    LPAREN = 275,
    RPAREN = 276,
    LBRACE = 277,
    RBRACE = 278,
    ASSIGN = 279,
    ID = 280,
    STRING = 281,
    whitespace = 282,
    comment = 283,
    then = 284,
    ELSE = 285,
    AND = 286,
    OR = 287,
    RELOP = 288,
    BINOP = 289,
    NOT = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 524 "parser.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   409,   409,   420,   421,   423,   428,   448,   455,   458,
     459,   462,   463,   466,   469,   473,   479,   484,   494,   512,
     529,   533,   541,   553,   559,   565,   571,   578,   584,   596,
     608,   617,   620,   621,   624,   627,   632,   650,   661,   663,
     664,   670,   671,   672,   675,   680,   695,   707,   711,   717,
     727,   728,   732,   736,   748,   760,   772,   788
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "INT", "BYTE", "B", "BOOL",
  "TRUE", "FALSE", "RETURN", "IF", "NUM", "WHILE", "SWITCH", "CASE",
  "BREAK", "COLON", "SC", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "ASSIGN", "ID", "STRING", "whitespace", "comment", "then", "ELSE", "AND",
  "OR", "RELOP", "BINOP", "NOT", "$accept", "Program", "Funcs", "FuncDecl",
  "FuncDecl2", "RetType", "Formals", "FormalsList", "FormatDecl",
  "Statements", "Statement", "IFPART1", "WHILEPART1", "SWITCH1part",
  "Mark2", "CaseList", "CaseStat", "Call", "Mark1", "ExpList", "Type",
  "Exp", "PushMark", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -22

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-22)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,   -22,   -22,   -22,   -22,     5,   -22,    22,   -15,    -2,
     -22,   -22,   -22,   133,   -10,    12,    14,   -22,    26,    37,
     -22,    20,    89,   -22,   133,   133,    36,    49,    43,    74,
     -22,   -22,    63,   -22,    45,    56,   -22,    45,   -22,   -16,
      45,    62,    45,   -22,   133,    64,    45,   -22,   -22,    54,
     -22,    73,   -22,     4,    68,   -22,    71,    67,   -22,    76,
     -22,   -22,    45,    45,    45,    45,   120,    45,   135,   111,
     -22,    45,    41,   133,    86,    78,    73,   -22,    45,   -22,
      74,   -22,   -22,    17,     9,    70,   -22,   -22,   139,   -22,
     -22,    85,    98,   -22,   -22,     2,    95,   -22,   130,   -22,
     -22,   -22,    45,   102,   133,   -22,   -22,   -22,   133,   104,
     107,   108,   110,   -22,   -22
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     8,    41,    42,    43,     0,     2,     3,     0,     0,
       7,     1,     4,     0,     0,     0,     0,    31,     0,     0,
      57,     0,     0,    14,     0,     0,     0,     0,     0,     9,
      51,    52,    48,    21,     0,    46,    50,     0,    47,     0,
       0,     0,     0,    26,     0,    38,     0,     5,    15,    24,
      25,     0,    20,     0,     0,    10,    11,     0,    49,     0,
      53,    22,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,     0,    33,    17,     0,     6,
       0,    13,    44,    54,    55,    56,    45,    28,     0,    30,
      16,     0,    39,    19,    23,     0,     0,    32,     0,    12,
      29,    36,     0,     0,     0,    27,    18,    40,     0,     0,
       0,     0,     0,    34,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -22,   -22,   128,   -22,   -22,   -22,   -22,    59,   -22,   101,
     -21,   -22,   -22,   -22,   -22,    66,   -22,   -13,   -22,    48,
       6,    -1,   -22
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,     9,    54,    55,    56,    22,
      23,    24,    25,    26,    41,    75,    76,    38,    71,    91,
      28,    92,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      27,    48,    61,    49,    50,    11,    10,    13,   103,    27,
      29,    27,    27,    10,    39,    62,    63,    64,    65,   104,
      30,    31,    77,    14,    32,     1,     2,     3,    78,     4,
      33,    27,    34,    59,    40,    57,    60,    35,    36,    66,
      45,    68,    64,    65,    46,    72,    42,    37,    48,    63,
      64,    65,    94,    30,    31,    43,    27,    32,    51,    93,
      27,    83,    84,    85,    86,    34,    88,    52,    53,    58,
      35,    36,    62,    63,    64,    65,    45,    98,     2,     3,
      37,     4,    67,   109,    73,    70,    57,   110,    74,    79,
      80,    27,    81,     2,     3,    27,     4,    82,    95,    15,
      16,    96,    17,    18,    65,    19,   101,    62,    63,    64,
      65,    20,    47,   105,    21,     2,     3,   102,     4,   108,
     111,    15,    16,   112,    17,    18,   113,    19,   114,    62,
      63,    64,    65,    20,    90,    12,    21,     2,     3,    99,
       4,    87,    97,    15,    16,    69,    17,    18,   106,    19,
     107,    62,    63,    64,    65,    20,    89,     0,    21,     0,
     100,    62,    63,    64,    65,     0,    62,    63,    64,    65,
      62,    63,    64,    65
};

static const yytype_int8 yycheck[] =
{
      13,    22,    18,    24,    25,     0,     0,    22,     6,    22,
      20,    24,    25,     7,    15,    31,    32,    33,    34,    17,
       8,     9,    18,    25,    12,     3,     4,     5,    24,     7,
      18,    44,    20,    34,    20,    29,    37,    25,    26,    40,
      20,    42,    33,    34,    24,    46,    20,    35,    69,    32,
      33,    34,    73,     8,     9,    18,    69,    12,    22,    18,
      73,    62,    63,    64,    65,    20,    67,    18,    25,     6,
      25,    26,    31,    32,    33,    34,    20,    78,     4,     5,
      35,     7,    20,   104,    30,    21,    80,   108,    15,    21,
      19,   104,    25,     4,     5,   108,     7,    21,    12,    10,
      11,    23,    13,    14,    34,    16,    21,    31,    32,    33,
      34,    22,    23,    18,    25,     4,     5,    19,     7,    17,
      16,    10,    11,    16,    13,    14,    18,    16,    18,    31,
      32,    33,    34,    22,    23,     7,    25,     4,     5,    80,
       7,    21,    76,    10,    11,    44,    13,    14,    18,    16,
     102,    31,    32,    33,    34,    22,    21,    -1,    25,    -1,
      21,    31,    32,    33,    34,    -1,    31,    32,    33,    34,
      31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,    37,    38,    39,    40,    41,
      56,     0,    38,    22,    25,    10,    11,    13,    14,    16,
      22,    25,    45,    46,    47,    48,    49,    53,    56,    20,
       8,     9,    12,    18,    20,    25,    26,    35,    53,    57,
      20,    50,    20,    18,    58,    20,    24,    23,    46,    46,
      46,    22,    18,    25,    42,    43,    44,    56,     6,    57,
      57,    18,    31,    32,    33,    34,    57,    20,    57,    45,
      21,    54,    57,    30,    15,    51,    52,    18,    24,    21,
      19,    25,    21,    57,    57,    57,    57,    21,    57,    21,
      23,    55,    57,    18,    46,    12,    23,    51,    57,    43,
      21,    21,    19,     6,    17,    18,    18,    55,    17,    46,
      46,    16,    16,    18,    18
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    40,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    47,    48,
      49,    50,    51,    51,    52,    52,    53,    53,    54,    55,
      55,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     4,     5,     1,     1,     0,
       1,     1,     3,     2,     1,     2,     4,     3,     5,     4,
       2,     2,     3,     4,     2,     2,     2,     5,     4,     5,
       4,     0,     2,     1,     6,     7,     5,     3,     0,     1,
       3,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       1,     1,     1,     2,     3,     3,     3,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 409 "parser.ypp" /* yacc.c:1646  */
    {
					info func_info("dummy", -1, -1);
					if (st.find_func("main",func_info) < 0 || func_info.type != TYPE_FUNC_VOID 
						|| func_info.params.size() ){
						errorMainMissing(); 
						exit(1);
						}
                    st.pop_table();
				}
#line 1697 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 420 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1703 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 421 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1709 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 423 "parser.ypp" /* yacc.c:1646  */
    {	     if (!(yyvsp[-1]).have_sure_exit && st.func_return != TYPE_FUNC_VOID) {errorNotAllPaths(yylineno, (yyval).name.c_str()); exit(1);}			
                                                                    st.pop_table();
			 					    st.func_return = -1;
                        ;                                   }
#line 1718 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 428 "parser.ypp" /* yacc.c:1646  */
    {  
                                    // first we check if the func we just declared is already declared ?
                                    if (st.has_func((yyvsp[-3]).name) >= 0)
                                         {errorDef(yylineno, (yyvsp[-3]).name.c_str()); exit(1);}
                                    // check if we are doing main and a legal one ! if main already exist we recog it before !
                             //       if (!strcmp($2.name.c_str(), "main") && ($1.type != TYPE_FUNC_VOID || $4.formal_list.size() != 0)){
                               //         errorPrototypeMismatch(yylineno, "main" , vector<const char*>());
                                 //       exit(1);
                                 //       }
                                	info new_info((yyvsp[-3]).name, 0, (yyvsp[-4]).type);
                                	new_info.is_func = 1;
                                	for (vector<pair<string,int> >::iterator it = (yyvsp[-1]).formal_list.begin(); it != (yyvsp[-1]).formal_list.end(); ++it)
                                		new_info.params.push_back((*it).second);
                                	st.add_symbol_func(new_info);
                                	st.push_table();
                                	st.add_func_symbol_to_table((yyvsp[-1]).formal_list);			   				
							   }
#line 1740 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 448 "parser.ypp" /* yacc.c:1646  */
    {
					int t = -1;
					if ((yyvsp[0]).type == TYPE_INT) t = TYPE_FUNC_INT;
					if ((yyvsp[0]).type == TYPE_BOOL) t = TYPE_FUNC_BOOL;
					if ((yyvsp[0]).type == TYPE_BYTE) t = TYPE_FUNC_BYTE;
					st.func_return = t; (yyval).type = t;
			       }
#line 1752 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 455 "parser.ypp" /* yacc.c:1646  */
    {st.func_return = (TYPE_FUNC_VOID) ; (yyval).type = TYPE_FUNC_VOID;}
#line 1758 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 458 "parser.ypp" /* yacc.c:1646  */
    {(yyval).formal_list = vector<pair<string,int> >();}
#line 1764 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 459 "parser.ypp" /* yacc.c:1646  */
    {(yyval).formal_list = (yyvsp[0]).formal_list;}
#line 1770 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 462 "parser.ypp" /* yacc.c:1646  */
    {(yyval).formal_list.insert((yyval).formal_list.begin()  ,make_pair((yyvsp[0]).name ,(yyvsp[0]).type));}
#line 1776 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 463 "parser.ypp" /* yacc.c:1646  */
    {(yyval).formal_list = (yyvsp[0]).formal_list; (yyval).formal_list.insert((yyval).formal_list.begin(), make_pair((yyvsp[-2]).name,(yyvsp[-2]).type));}
#line 1782 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 466 "parser.ypp" /* yacc.c:1646  */
    {(yyval).type = (yyvsp[-1]).type; (yyval).name = (yyvsp[0]).name;}
#line 1788 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 469 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).have_sure_exit = (yyvsp[0]).have_sure_exit;
					st.manange_insert( (yyvsp[0]) , false);
					}
#line 1797 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 473 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).have_sure_exit = ((yyvsp[-1]).have_sure_exit || (yyvsp[0]).have_sure_exit) ? true : false; // doing or between of them
					st.manange_insert( (yyvsp[0]) , false);
					}
#line 1806 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 479 "parser.ypp" /* yacc.c:1646  */
    {
								  (yyval).have_sure_exit = (yyvsp[-1]).have_sure_exit;
								  (yyval).insert = false;
								  st.pop_table();
							    }
#line 1816 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 484 "parser.ypp" /* yacc.c:1646  */
    {
					if (st.has_func((yyvsp[-1]).name) >= 0|| st.has_var((yyvsp[-1]).name) >= 0) {
						errorDef(yylineno, (yyvsp[-1]).name.c_str()); 
						exit(1);
					}
				     	(yyval).type = (yyvsp[-2]).type;
					(yyval).name = (yyvsp[-1]).name;
					(yyval).insert = true;
					(yyval).have_sure_exit = false;
					}
#line 1831 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 494 "parser.ypp" /* yacc.c:1646  */
    {
					if (st.has_func((yyvsp[-3]).name) >= 0|| st.has_var((yyvsp[-3]).name) >= 0) {
						errorDef(yylineno, (yyvsp[-3]).name.c_str()); 
						exit(1);
					}
					if ((yyvsp[-4]).type != (yyvsp[-1]).type && !((yyvsp[-1]).type == TYPE_BYTE && (yyvsp[-4]).type == TYPE_INT)) { 
						errorMismatch(yylineno); 
						exit(1);
					}
					if ((yyvsp[-4]).type == TYPE_BYTE && (yyvsp[-1]).value > 255){
						errorByteTooLarge(yylineno, (yyvsp[-1]).name.c_str()); 
						exit(1);
					};
                                        (yyval).type = (yyvsp[-4]).type;
                                        (yyval).name = (yyvsp[-3]).name;
                                        (yyval).insert = true;
					(yyval).have_sure_exit = false;
						}
#line 1854 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 512 "parser.ypp" /* yacc.c:1646  */
    {
						(yyval).insert = false;
						int res = -1;
						if ((res = st.has_var((yyvsp[-3]).name)) < 0){ 
							errorUndef(yylineno, (yyvsp[-3]).name.c_str()); 
							exit(1);
						}
						if (res != (yyvsp[-1]).type && !(res == TYPE_INT && (yyvsp[-1]).type == TYPE_BYTE)){
							errorMismatch(yylineno); 
							exit(1);
						}
						if (res == TYPE_BYTE && (yyvsp[-1]).value > 255){
							errorByteTooLarge(yylineno, (yyvsp[-1]).name.c_str()); 
							exit(1);
						};
						(yyval).have_sure_exit = false;
					   }
#line 1876 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 529 "parser.ypp" /* yacc.c:1646  */
    { 
					(yyval).insert = false;
					(yyval).have_sure_exit = false;
				  }
#line 1885 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 533 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).have_sure_exit = true;
					(yyval).insert = false;
					if (st.func_return != TYPE_FUNC_VOID){
						errorMismatch(yylineno);
						exit(1);
					} 
				}
#line 1898 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 541 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).have_sure_exit = true;
					(yyval).insert = false;
					if (st.func_return != st.type_to_ret_type((yyvsp[-1]).type) && !(st.func_return == TYPE_FUNC_INT && (yyvsp[-1]).type == TYPE_BYTE)) {
						errorMismatch(yylineno);
						exit(1);
					}
					if (st.func_return == TYPE_FUNC_BYTE && (yyvsp[-1]).value > 255){
						errorByteTooLarge(yylineno, (yyvsp[-1]).name.c_str()); 
						exit(1);
					};
				}
#line 1915 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 553 "parser.ypp" /* yacc.c:1646  */
    {
							(yyval).have_sure_exit = ((yyvsp[-2]).have_sure_exit && (yyvsp[0]).have_sure_exit) ? true : false;
							(yyval).insert = false;
							st.manange_insert( (yyvsp[-2]) , true);
							st.manange_insert( (yyvsp[0]) , true);
						}
#line 1926 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 559 "parser.ypp" /* yacc.c:1646  */
    {	
								(yyval).have_sure_exit = false;
								(yyval).insert = false;
								st.manange_insert((yyvsp[0]), true);
					 		 }
#line 1936 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 565 "parser.ypp" /* yacc.c:1646  */
    {
								(yyval).insert = false;
								st.manange_insert( (yyvsp[0]) , true);
								st.is_while--;
								(yyval).have_sure_exit = false;
							}
#line 1947 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 571 "parser.ypp" /* yacc.c:1646  */
    {
						(yyval).insert = false;	
						if (!st.is_while) {
							errorUnexpectedBreak(yylineno); 
							exit(1);
						}
					}
#line 1959 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 578 "parser.ypp" /* yacc.c:1646  */
    {
										(yyval).insert = false;
										(yyval).have_sure_exit = false; 
									}
#line 1968 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 584 "parser.ypp" /* yacc.c:1646  */
    {
										if ((yyvsp[-1]).type != TYPE_BOOL){
											errorMismatch(yylineno);
											exit(1);
										}
										if ((yyvsp[-1]).is_true == F_VAL){
											errorDeadCode(yylineno); 
											exit(1);
										}	

								}
#line 1984 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 596 "parser.ypp" /* yacc.c:1646  */
    {
												if ((yyvsp[-1]).type != TYPE_BOOL){
													errorMismatch(yylineno);
													exit(1);
												}
												if ((yyvsp[-1]).is_true == F_VAL){
													errorDeadCode(yylineno);
													exit(1);
												}

											}
#line 2000 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 608 "parser.ypp" /* yacc.c:1646  */
    {
										if((yyvsp[-1]).type != TYPE_BYTE && (yyvsp[-1]).type != TYPE_INT){
											errorMismatch(yylineno);
											exit(1);
										}	

}
#line 2012 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 617 "parser.ypp" /* yacc.c:1646  */
    { st.is_while++;}
#line 2018 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 620 "parser.ypp" /* yacc.c:1646  */
    {}
#line 2024 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 621 "parser.ypp" /* yacc.c:1646  */
    {}
#line 2030 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 624 "parser.ypp" /* yacc.c:1646  */
    {
                                       	 		  st.manange_insert( (yyvsp[-2]) , true); 
							}
#line 2038 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 627 "parser.ypp" /* yacc.c:1646  */
    {
                                                          st.manange_insert( (yyvsp[-2]) , true);
							}
#line 2046 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 632 "parser.ypp" /* yacc.c:1646  */
    {
						//first we check that the function is defined
								info func_info("dummy", -1, -1);
								if (st.find_func((yyvsp[-4]).name,func_info) < 0){
									errorUndefFunc(yylineno, (yyvsp[-4]).name.c_str()); 
									exit(1);
								}

								vector<const char*> proto_names = vector<const char*>();
								for (vector<int>::iterator it1 = (func_info.params).begin();it1 != func_info.params.end();++it1){
									int_to_name_push(*it1, proto_names);
								}
								if (!st.is_same_list(func_info.params, (yyvsp[-1]).exp_list)){
									errorPrototypeMismatch(yylineno, (yyvsp[-4]).name.c_str(), proto_names);
									exit(1);
								}
								(yyval).type = st.convert_type_func_to_var( func_info.type);
							}
#line 2069 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 650 "parser.ypp" /* yacc.c:1646  */
    {
						//first we check that the function is defined
								info func_info("dummy", -1, -1);
								if (st.find_func((yyvsp[-2]).name,func_info) < 0){
									errorUndefFunc(yylineno, (yyvsp[-2]).name.c_str()); 
									exit(1);
								}

								(yyval).type = st.convert_type_func_to_var( func_info.type);
			}
#line 2084 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 661 "parser.ypp" /* yacc.c:1646  */
    {}
#line 2090 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 663 "parser.ypp" /* yacc.c:1646  */
    {(yyval).exp_list.push_back((yyvsp[0]).type);}
#line 2096 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 664 "parser.ypp" /* yacc.c:1646  */
    {
						(yyval).exp_list = (yyvsp[0]).exp_list;
						(yyval).exp_list.push_back((yyvsp[-2]).type);
					    }
#line 2105 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 670 "parser.ypp" /* yacc.c:1646  */
    {(yyval).type = TYPE_INT;}
#line 2111 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 671 "parser.ypp" /* yacc.c:1646  */
    {(yyval).type = TYPE_BYTE;}
#line 2117 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 672 "parser.ypp" /* yacc.c:1646  */
    {(yyval).type = TYPE_BOOL;}
#line 2123 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 675 "parser.ypp" /* yacc.c:1646  */
    {
							(yyval).is_true = (yyvsp[-1]).is_true;
							(yyval).type = (yyvsp[-1]).type;
							(yyval).value = (yyvsp[-1]).value;
							}
#line 2133 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 680 "parser.ypp" /* yacc.c:1646  */
    {
                         if ((yyvsp[-2]).is_true != UNDEFINED && (yyvsp[0]).is_true != UNDEFINED){
                         	(yyval).value = st.calc_binop((yyvsp[-2]).value,  (yyvsp[-1]).name, (yyvsp[0]).value);
                           	(yyval).is_true = ((yyval).value != 0) ? T_VAL : F_VAL ;
                         }else{
                            (yyval).is_true = UNDEFINED;
                         }
                         if (!((yyvsp[-2]).type == TYPE_INT || (yyvsp[-2]).type == TYPE_BYTE) || !((yyvsp[0]).type == TYPE_INT || (yyvsp[0]).type == TYPE_BYTE)){
                         	errorMismatch(yylineno);
                         	exit(1);
                         }
						else{
							(yyval).type =( (yyvsp[-2]).value >= (yyvsp[0]).value) ? (yyvsp[-2]).type : (yyvsp[0]).type;	
						}
					}
#line 2153 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 695 "parser.ypp" /* yacc.c:1646  */
    { 
					int res = -1;
					info new_info("",-1,-1);
					res = st.find_func((yyvsp[0]).name, new_info);
					(yyval).is_true = UNDEFINED;
					if (res >= 0) (yyval).type = res;
					else if ((res = st.find_var((yyvsp[0]).name, new_info)) >= 0) (yyval).type = res;
					else {
						errorUndef(yylineno, (yyvsp[0]).name.c_str()); 
						exit(1);
					}	
			     }
#line 2170 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 707 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval).type = (yyvsp[0]).type;
				(yyval).is_true = UNDEFINED;
				}
#line 2179 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 711 "parser.ypp" /* yacc.c:1646  */
    {
				(yyval).type = TYPE_INT;
				(yyval).name = (yyvsp[0]).name; 
				(yyval).value = (yyvsp[0]).value;
				(yyval).is_true = ((yyvsp[0]).value != 0) ? T_VAL : F_VAL ;
				 }
#line 2190 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 717 "parser.ypp" /* yacc.c:1646  */
    {
				if ((yyvsp[-1]).value > 255 || (yyvsp[-1]).value < 0){
					errorByteTooLarge(yylineno, (yyvsp[-1]).name.c_str());
					exit(1);
				} 
				(yyval).type = TYPE_BYTE;
				(yyval).name = (yyvsp[-1]).name;
				(yyval).value = (yyvsp[-1]).value;
				(yyval).is_true = ((yyvsp[-1]).value != 0) ? T_VAL : F_VAL ;
			}
#line 2205 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 727 "parser.ypp" /* yacc.c:1646  */
    {(yyval).type = TYPE_STRING;}
#line 2211 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 728 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).type = TYPE_BOOL;
					(yyval).is_true = T_VAL;
				}
#line 2220 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 732 "parser.ypp" /* yacc.c:1646  */
    {
					(yyval).type = TYPE_BOOL;
					(yyval).is_true = F_VAL;
				}
#line 2229 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 736 "parser.ypp" /* yacc.c:1646  */
    {
                                        (yyval).type = TYPE_BOOL;
                                        if ((yyvsp[0]).type != TYPE_BOOL) {
                                        	errorMismatch(yylineno); 
                                        	exit(1);
                                        }
                                        if ((yyvsp[0]).is_true != UNDEFINED){
                                        	(yyval).is_true =((yyvsp[0]).is_true == F_VAL) ? T_VAL : F_VAL ;
                                        }else{
                                        	(yyval).is_true = UNDEFINED;
                                        }     
                                  }
#line 2246 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 748 "parser.ypp" /* yacc.c:1646  */
    {
                                        (yyval).type = TYPE_BOOL;
                                        if ((yyvsp[-2]).type != TYPE_BOOL ||  (yyvsp[0]).type != TYPE_BOOL) {
                                        	errorMismatch(yylineno); 
                                        	exit(1);
                                        }
                                         if ((yyvsp[-2]).is_true != UNDEFINED && (yyvsp[0]).is_true != UNDEFINED){
                                        	(yyval).is_true =((yyvsp[-2]).is_true == T_VAL && (yyvsp[0]).is_true == T_VAL) ? T_VAL : F_VAL ;
                                        }else{
                                        	(yyval).is_true = UNDEFINED;
                                        }
				     }
#line 2263 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 760 "parser.ypp" /* yacc.c:1646  */
    {
                                        (yyval).type = TYPE_BOOL;
                                        if ((yyvsp[-2]).type != TYPE_BOOL ||  (yyvsp[0]).type != TYPE_BOOL) {
                                        	errorMismatch(yylineno); 
                                        	exit(1);
                                        }
                                        if ((yyvsp[-2]).is_true != UNDEFINED && (yyvsp[0]).is_true != UNDEFINED){
                                        	(yyval).is_true =  ((yyvsp[-2]).is_true == T_VAL || (yyvsp[0]).is_true == T_VAL) ? T_VAL : F_VAL ;
                                        }else{
                                        	(yyval).is_true = UNDEFINED;
                                        }
                                     }
#line 2280 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 772 "parser.ypp" /* yacc.c:1646  */
    {
						(yyval).type = TYPE_BOOL;
						if (!((yyvsp[-2]).type == TYPE_INT || (yyvsp[-2]).type == TYPE_BYTE) || !((yyvsp[0]).type == TYPE_INT || (yyvsp[0]).type == TYPE_BYTE)){
							errorMismatch(yylineno); 
							exit(1);
						}
                        if ((yyvsp[-2]).is_true != UNDEFINED && (yyvsp[0]).is_true != UNDEFINED){
                        	(yyval).is_true = st.check_relop((yyvsp[-2]).value,  (yyvsp[-1]).name, (yyvsp[0]).value ) ? T_VAL : F_VAL;
                        }else{
                        	(yyval).is_true = UNDEFINED;
                        }
					}
#line 2297 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 788 "parser.ypp" /* yacc.c:1646  */
    {
				st.push_table();
                        }
#line 2305 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2309 "parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 792 "parser.ypp" /* yacc.c:1906  */


int main()
{
	yyparse();
}

int yyerror(char const * message)
{
	errorSyn(yylineno);
	exit(1);
}

void int_to_name_push(int i, vector<const char*>& proto_names){
	if (i == TYPE_BYTE) proto_names.push_back("BYTE");
	if (i == TYPE_INT)  proto_names.push_back("INT");
	if (i == TYPE_BOOL) proto_names.push_back("BOOL");
	if (i == TYPE_STRING)  proto_names.push_back("STRING");
 
}

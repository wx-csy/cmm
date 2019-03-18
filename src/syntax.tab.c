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
#line 1 "syntax.y" /* yacc.c:339  */


#include <stdio.h>
#include "error.h"
#include "cst.h"

cst_node_t *cst;
int yylex(void);
void yyerror(const char*);

#define BUILD_CST_NODE0($$, ...) { \
        $$ = NULL; \
    }

#define BUILD_CST_NODE1($$, $1, fmt, ...) { \
        int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 1, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
    }

#define BUILD_CST_NODE2($$, $1, $2, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 2, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
    }

#define BUILD_CST_NODE3($$, $1, $2, $3, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 3, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
    }
    
#define BUILD_CST_NODE4($$, $1, $2, $3, $4, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 4, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
    }

#define BUILD_CST_NODE5($$, $1, $2, $3, $4, $5, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 5, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
    }
    
#define BUILD_CST_NODE6($$, $1, $2, $3, $4, $5, $6, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 6, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
        $$->child[5] = $6; \
    }
    
#define BUILD_CST_NODE7($$, $1, $2, $3, $4, $5, $6, $7, fmt, ...) { \
	int line = $1 ? $1->line : 0; \
        $$ = cst_node_ctor(line, 7, fmt " (%d)", ##__VA_ARGS__, line); \
        $$->child[0] = $1; \
        $$->child[1] = $2; \
        $$->child[2] = $3; \
        $$->child[3] = $4; \
        $$->child[4] = $5; \
        $$->child[5] = $6; \
        $$->child[6] = $7; \
    }


#line 145 "syntax.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif


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
    INT = 258,
    FLOAT = 259,
    ID = 260,
    TYPE = 261,
    IF = 262,
    WHILE = 263,
    RETURN = 264,
    STRUCT = 265,
    AND = 266,
    OR = 267,
    RELOP = 268,
    UMINUS = 269,
    LOWER_THAN_ELSE = 270,
    ELSE = 271
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef cst_node_t * YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 210 "syntax.tab.c" /* yacc.c:358  */

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
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   271

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,     2,     2,     2,     2,     2,     2,
      24,    25,    17,    15,    29,    16,    21,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
       2,    11,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    12,    13,    14,    20,
      26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   103,   103,   107,   108,   112,   113,   114,   118,   119,
     125,   126,   130,   131,   135,   136,   140,   146,   147,   151,
     152,   156,   157,   161,   167,   168,   172,   173,   177,   178,
     179,   180,   181,   183,   184,   190,   191,   195,   199,   200,
     204,   205,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     232,   233
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "IF",
  "WHILE", "RETURN", "STRUCT", "'='", "AND", "OR", "RELOP", "'+'", "'-'",
  "'*'", "'/'", "'!'", "UMINUS", "'.'", "'['", "']'", "'('", "')'",
  "LOWER_THAN_ELSE", "ELSE", "';'", "','", "'{'", "'}'", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,    61,   266,   267,   268,    43,    45,    42,    47,    33,
     269,    46,    91,    93,    40,    41,   270,   271,    59,    44,
     123,   125
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -37

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -54,     5,    18,   -54,    39,    16,   -54,     2,     4,
     -54,   -54,   -54,    -4,   -54,    19,   -10,    28,    39,    40,
     -54,    56,    69,    32,   -54,    69,    30,    39,   -54,    69,
      53,    51,    58,   -54,   -54,    59,    63,    -5,    79,    71,
     -54,   -54,    89,   -54,    39,   -54,   -54,    84,   -54,   -54,
      91,    92,    95,    72,    72,    72,    72,   -54,    90,    63,
     135,    72,   -54,    69,   -54,   -54,   101,    72,    72,   153,
     -17,   -17,   171,   -54,   -54,    72,    72,    72,    72,    72,
      72,    72,    72,   117,    72,   -54,   231,   -54,   -54,   116,
      98,   186,   201,   -54,   -54,   231,   242,   242,    68,    36,
      36,   -17,   -17,   -54,   216,    72,   -54,    94,    94,   -54,
     -54,   108,   -54,    94,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    10,    15,     0,     2,     4,     0,    11,    16,     0,
      13,     1,     3,    17,     6,     0,     8,     0,    36,     0,
       5,     0,     0,     0,     7,     0,     0,    36,    20,     0,
       0,    22,     0,    17,     9,     0,     0,    40,     0,    38,
      12,    35,    23,    19,     0,    18,    25,     0,    58,    59,
      57,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,     0,    37,     0,    21,    29,     0,     0,     0,     0,
      51,    52,     0,    24,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    41,    39,    54,    61,
       0,     0,     0,    31,    50,    42,    43,    44,    45,    46,
      47,    48,    49,    56,     0,     0,    53,     0,     0,    55,
      60,    32,    34,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   131,   -54,   119,    11,   -54,   -54,   -54,   -20,
     -54,    99,   -54,   121,    80,     1,    46,   -54,    81,   -54,
     -53,    37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    25,     7,     9,    10,    16,
      17,    30,    31,    57,    58,    59,    26,    27,    38,    39,
      60,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      69,    70,    71,    72,    83,    37,    61,    84,    86,    42,
       8,     6,    21,    89,    91,    92,     6,    21,    11,    22,
      19,    13,    95,    96,    97,    98,    99,   100,   101,   102,
      29,   104,   -14,    35,    18,   -36,   -36,   -36,     1,   -36,
     -36,   -36,     2,    37,    14,     1,     1,    20,   -36,     2,
       2,   -36,    89,    81,    82,    29,   -36,    83,    23,    32,
      84,    40,   -36,   -36,    47,    28,    48,    49,    50,    36,
      51,    52,    53,    41,    33,    48,    49,    50,    43,    54,
      44,    45,    55,    79,    80,    81,    82,    56,    54,    83,
      46,    55,    84,    23,   -27,    47,    56,    48,    49,    50,
      63,    51,    52,    53,    48,    49,    50,    62,   111,   112,
      54,    21,    65,    55,   114,    66,    67,    54,    56,    68,
      55,    73,   103,   106,    23,    56,    88,    75,    76,    77,
      78,    79,    80,    81,    82,   113,    12,    83,    24,    74,
      84,    34,   110,    64,    87,   105,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    83,     0,     0,    84,
       0,     0,     0,    85,    75,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,     0,     0,    84,     0,     0,
       0,    93,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,    83,     0,     0,    84,    94,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,     0,     0,
      84,   107,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,    83,     0,     0,    84,   108,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,     0,     0,
      84,   109,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,    83,     0,     0,    84,    78,    79,    80,    81,
      82,     0,     0,    83,     0,     0,    84
};

static const yytype_int8 yycheck[] =
{
      53,    54,    55,    56,    21,    25,    11,    24,    61,    29,
       5,     0,    22,    66,    67,    68,     5,    22,     0,    29,
      24,     5,    75,    76,    77,    78,    79,    80,    81,    82,
      19,    84,    30,     1,    30,     3,     4,     5,     6,     7,
       8,     9,    10,    63,    28,     6,     6,    28,    16,    10,
      10,    19,   105,    17,    18,    44,    24,    21,    30,     3,
      24,    31,    30,    31,     1,    25,     3,     4,     5,    23,
       7,     8,     9,    27,     5,     3,     4,     5,    25,    16,
      29,    23,    19,    15,    16,    17,    18,    24,    16,    21,
      31,    19,    24,    30,    31,     1,    24,     3,     4,     5,
      29,     7,     8,     9,     3,     4,     5,    28,   107,   108,
      16,    22,    28,    19,   113,    24,    24,    16,    24,    24,
      19,    31,     5,    25,    30,    24,    25,    11,    12,    13,
      14,    15,    16,    17,    18,    27,     5,    21,    17,    59,
      24,    22,   105,    44,    63,    29,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    24,    25,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      24,    25,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    24,    25,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      24,    25,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    24,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    10,    33,    34,    35,    37,    38,     5,    39,
      40,     0,    34,     5,    28,    36,    41,    42,    30,    24,
      28,    22,    29,    30,    45,    37,    48,    49,    25,    37,
      43,    44,     3,     5,    36,     1,    48,    41,    50,    51,
      31,    48,    41,    25,    29,    23,    31,     1,     3,     4,
       5,     7,     8,     9,    16,    19,    24,    45,    46,    47,
      52,    11,    28,    29,    43,    28,    24,    24,    24,    52,
      52,    52,    52,    31,    46,    11,    12,    13,    14,    15,
      16,    17,    18,    21,    24,    28,    52,    50,    25,    52,
      53,    52,    52,    28,    25,    52,    52,    52,    52,    52,
      52,    52,    52,     5,    52,    29,    25,    25,    25,    25,
      53,    47,    47,    27,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      37,    37,    38,    38,    39,    39,    40,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    49,    50,    50,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     0,     1,     1,     4,     4,
       3,     3,     1,     2,     4,     3,     2,     0,     2,     2,
       1,     3,     5,     7,     5,     2,     0,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     1
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
  switch (yytype)
    {
          case 3: /* INT  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1140 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* FLOAT  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1146 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* ID  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1152 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TYPE  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1158 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* IF  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1164 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* WHILE  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1170 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* RETURN  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1176 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* STRUCT  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1182 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* '='  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1188 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* AND  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1194 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* OR  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1200 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* RELOP  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1206 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* '+'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1212 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* '-'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1218 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* '*'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1224 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* '/'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1230 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* '!'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1236 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* UMINUS  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1242 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* '.'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1248 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* '['  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1254 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* ']'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1260 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* '('  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1266 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* ')'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1272 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* LOWER_THAN_ELSE  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1278 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* ELSE  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1284 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* ';'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1290 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* ','  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1296 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* '{'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1302 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* '}'  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1308 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* Program  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1314 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* ExtDefList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1320 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* ExtDef  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1326 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* ExtDecList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1332 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* Specifier  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1338 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* StructSpecifier  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1344 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* OptTag  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1350 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* Tag  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1356 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* VarDec  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1362 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* FunDec  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1368 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* VarList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1374 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* ParamDec  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1380 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* CompSt  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1386 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* StmtList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1392 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* Stmt  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1398 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* DefList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1404 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* Def  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1410 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* DecList  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1416 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* Dec  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1422 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* Exp  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1428 "syntax.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* Args  */
#line 82 "syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1434 "syntax.tab.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
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
#line 103 "syntax.y" /* yacc.c:1646  */
    { cst = (yyvsp[0]); (yyval) = NULL; }
#line 1698 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 107 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ExtDefList"); }
#line 1704 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 108 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "ExtDefList"); }
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 112 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1716 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 113 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1722 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 114 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1728 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 118 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "ExtDecList"); }
#line 1734 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 119 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDecList"); }
#line 1740 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 125 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Specifier"); }
#line 1746 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Specifier"); }
#line 1752 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "StructSpecifier"); }
#line 1758 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "StructSpecifier"); }
#line 1764 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 135 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "OptTag"); }
#line 1770 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 136 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "OptTag"); }
#line 1776 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 140 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Tag"); }
#line 1782 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 146 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "VarDec"); }
#line 1788 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 147 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "VarDec"); }
#line 1794 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 151 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "FunDec"); }
#line 1800 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 152 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "FunDec"); }
#line 1806 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 156 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "VarList"); }
#line 1812 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 157 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "VarList"); }
#line 1818 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 161 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ParamDec"); }
#line 1824 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 167 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "CompSt"); }
#line 1830 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 168 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-2]), (yyvsp[0]), "CompSt (Error)"); }
#line 1836 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 172 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "StmtList"); }
#line 1842 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 173 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "StmtList"); }
#line 1848 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 177 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1854 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 178 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Stmt (Error)"); }
#line 1860 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 179 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Stmt"); }
#line 1866 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 180 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1872 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 182 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1878 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 183 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE7((yyval), (yyvsp[-6]), (yyvsp[-5]), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1884 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 184 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1890 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 190 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "DefList"); }
#line 1896 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 191 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "DefList"); }
#line 1902 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Def"); }
#line 1908 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 199 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "DecList"); }
#line 1914 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 200 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "DecList"); }
#line 1920 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 204 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Dec"); }
#line 1926 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 205 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Dec"); }
#line 1932 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 211 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1938 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 212 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1944 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 213 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1950 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 214 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1956 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 215 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1962 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 216 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1968 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1974 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 218 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1980 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 219 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1986 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 220 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1992 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 221 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1998 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 222 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 2004 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 223 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 2010 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 224 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 2016 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 225 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 2022 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 226 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2028 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 227 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2034 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 228 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2040 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 232 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Args"); }
#line 2046 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 233 "syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Args"); }
#line 2052 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2056 "syntax.tab.c" /* yacc.c:1646  */
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
#line 236 "syntax.y" /* yacc.c:1906  */


int main() {
    yyparse();
    if (cmm_nr_error == 0) cst_node_print(cst, 0);
    cst_node_dtor(cst);
}

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, 0, 0, msg);
}


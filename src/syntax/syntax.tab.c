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
#line 1 "src/syntax/syntax.y" /* yacc.c:339  */


#include <stdio.h>
#include <cmm/error.h>
#include <syntax/cst.h>

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


#line 145 "src/syntax/syntax.tab.c" /* yacc.c:339  */

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
   by #include "syntax.tab.h".  */
#ifndef YY_YY_INCLUDE_SYNTAX_SYNTAX_TAB_H_INCLUDED
# define YY_YY_INCLUDE_SYNTAX_SYNTAX_TAB_H_INCLUDED
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
    ELSE = 264,
    RETURN = 265,
    STRUCT = 266,
    AND = 267,
    OR = 268,
    RELOP = 269,
    UMINUS = 270
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

#endif /* !YY_YY_INCLUDE_SYNTAX_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 212 "src/syntax/syntax.tab.c" /* yacc.c:358  */

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
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   270

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,     2,     2,     2,
      27,    28,    18,    16,    22,    17,    30,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
       2,    12,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    13,    14,    15,
      20
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    98,    98,   104,   105,   109,   110,   111,   115,   116,
     122,   123,   127,   128,   132,   133,   137,   143,   144,   148,
     149,   153,   154,   158,   164,   168,   169,   173,   174,   175,
     176,   177,   178,   184,   185,   189,   193,   194,   198,   199,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   226,   227
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "IF",
  "WHILE", "ELSE", "RETURN", "STRUCT", "'='", "AND", "OR", "RELOP", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "';'", "','", "'{'", "'}'", "'['", "']'",
  "'('", "')'", "'!'", "'.'", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec",
  "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    61,   267,   268,   269,    43,    45,    42,    47,
     270,    59,    44,   123,   125,    91,    93,    40,    41,    33,
      46
};
# endif

#define YYPACT_NINF -51

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-51)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   -51,     2,    16,   -51,     0,    -1,   -51,    47,    59,
     -51,   -51,   -51,    35,   -51,    63,    13,    64,     0,    39,
     -51,    80,    83,     0,   -51,    80,    66,     0,   -51,    80,
      60,    69,   -51,   -51,    75,    29,    32,    82,    84,   -51,
     -51,    79,   -51,     0,   -51,   -51,   -51,    78,    93,    94,
      44,    44,    44,    44,   -51,    85,    29,    62,    44,   -51,
      80,   -51,    14,    44,    44,    81,    42,   100,    42,   -51,
     -51,    44,    44,    44,    44,    44,    44,    44,    44,   -51,
      44,   102,   195,   -51,   -51,   119,    95,   138,   157,   -51,
     -51,   195,   200,   200,   215,    36,    36,    42,    42,   176,
     -51,    44,   -51,    29,    29,   -51,   -51,   101,   -51,    29,
     -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    10,    15,     0,     2,     4,     0,    11,    16,     0,
      13,     1,     3,    17,     6,     0,     8,     0,    34,     0,
       5,     0,     0,    34,     7,     0,     0,    34,    20,     0,
       0,    22,    17,     9,     0,    26,    38,     0,    36,    12,
      33,    23,    19,     0,    18,    56,    57,    55,     0,     0,
       0,     0,     0,     0,    28,     0,    26,     0,     0,    35,
       0,    21,     0,     0,     0,     0,    49,     0,    50,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     0,    39,    37,    52,    59,     0,     0,     0,    29,
      48,    40,    41,    42,    43,    44,    45,    46,    47,     0,
      54,     0,    51,     0,     0,    53,    58,    30,    32,     0,
      31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   117,   -51,   103,    10,   -51,   -51,   -51,   -20,
     -51,    86,   -51,   108,    70,   -44,    41,   -51,    87,   -51,
     -50,    38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    25,     7,     9,    10,    16,
      17,    30,    31,    54,    55,    56,    26,    27,    37,    38,
      57,    86
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      65,    66,    67,    68,    13,    36,     1,     8,    82,    41,
       6,     2,    85,    87,    88,     6,    11,    45,    46,    47,
      14,    91,    92,    93,    94,    95,    96,    97,    98,    29,
      99,    51,    45,    46,    47,    21,    48,    49,    22,    50,
      36,    52,    84,    53,    58,     1,    51,    45,    46,    47,
       2,    85,    23,    29,    77,    78,    52,    22,    53,   107,
     108,    51,    19,    80,    35,   110,    81,    28,    40,    80,
     -14,    52,    81,    53,    71,    72,    73,    74,    75,    76,
      77,    78,    18,    79,    20,    32,    34,    23,    42,    80,
      39,    43,    81,    71,    72,    73,    74,    75,    76,    77,
      78,    44,    89,    59,    22,    62,    60,   100,    80,    69,
     109,    81,    71,    72,    73,    74,    75,    76,    77,    78,
      63,    64,    12,   102,    33,    24,    70,    80,    90,    61,
      81,    71,    72,    73,    74,    75,    76,    77,    78,   106,
       0,   101,     0,     0,     0,     0,    80,    83,     0,    81,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,     0,     0,     0,    80,   103,     0,    81,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,     0,     0,    80,   104,     0,    81,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,    80,   105,     0,    81,    71,    72,    73,
      74,    75,    76,    77,    78,    74,    75,    76,    77,    78,
       0,     0,    80,     0,     0,    81,     0,    80,     0,     0,
      81,    75,    76,    77,    78,     0,     0,     0,     0,     0,
       0,     0,    80,     0,     0,    81
};

static const yytype_int8 yycheck[] =
{
      50,    51,    52,    53,     5,    25,     6,     5,    58,    29,
       0,    11,    62,    63,    64,     5,     0,     3,     4,     5,
      21,    71,    72,    73,    74,    75,    76,    77,    78,    19,
      80,    17,     3,     4,     5,    22,     7,     8,    25,    10,
      60,    27,    28,    29,    12,     6,    17,     3,     4,     5,
      11,   101,    23,    43,    18,    19,    27,    25,    29,   103,
     104,    17,    27,    27,    23,   109,    30,    28,    27,    27,
      23,    27,    30,    29,    12,    13,    14,    15,    16,    17,
      18,    19,    23,    21,    21,     5,     3,    23,    28,    27,
      24,    22,    30,    12,    13,    14,    15,    16,    17,    18,
      19,    26,    21,    21,    25,    27,    22,     5,    27,    24,
       9,    30,    12,    13,    14,    15,    16,    17,    18,    19,
      27,    27,     5,    28,    21,    17,    56,    27,    28,    43,
      30,    12,    13,    14,    15,    16,    17,    18,    19,   101,
      -1,    22,    -1,    -1,    -1,    -1,    27,    60,    -1,    30,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    30,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    -1,    30,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    -1,    30,    12,    13,    14,
      15,    16,    17,    18,    19,    15,    16,    17,    18,    19,
      -1,    -1,    27,    -1,    -1,    30,    -1,    27,    -1,    -1,
      30,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    11,    32,    33,    34,    36,    37,     5,    38,
      39,     0,    33,     5,    21,    35,    40,    41,    23,    27,
      21,    22,    25,    23,    44,    36,    47,    48,    28,    36,
      42,    43,     5,    35,     3,    47,    40,    49,    50,    24,
      47,    40,    28,    22,    26,     3,     4,     5,     7,     8,
      10,    17,    27,    29,    44,    45,    46,    51,    12,    21,
      22,    42,    27,    27,    27,    51,    51,    51,    51,    24,
      45,    12,    13,    14,    15,    16,    17,    18,    19,    21,
      27,    30,    51,    49,    28,    51,    52,    51,    51,    21,
      28,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       5,    22,    28,    28,    28,    28,    52,    46,    46,     9,
      46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    40,    40,    41,
      41,    42,    42,    43,    44,    45,    45,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     0,     1,     1,     4,     4,
       3,     3,     1,     2,     4,     2,     0,     2,     1,     3,
       5,     7,     5,     2,     0,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     3,     1,     1,     1,     3,     1
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
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1134 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* FLOAT  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1140 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* ID  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1146 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TYPE  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1152 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* IF  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1158 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* WHILE  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1164 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* ELSE  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1170 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* RETURN  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1176 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* STRUCT  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1182 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* '='  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1188 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* AND  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1194 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* OR  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1200 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* RELOP  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1206 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* '+'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1212 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* '-'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1218 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* '*'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1224 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* '/'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1230 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* UMINUS  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1236 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* ';'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1242 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* ','  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1248 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* '{'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1254 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* '}'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1260 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* '['  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1266 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* ']'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1272 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* '('  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1278 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* ')'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1284 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* '!'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1290 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* '.'  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1296 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* Program  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1302 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* ExtDefList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1308 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* ExtDef  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1314 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* ExtDecList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1320 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* Specifier  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1326 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* StructSpecifier  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1332 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* OptTag  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1338 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* Tag  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1344 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* VarDec  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1350 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* FunDec  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1356 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* VarList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1362 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* ParamDec  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1368 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* CompSt  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1374 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* StmtList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1380 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* Stmt  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1386 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* DefList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1392 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* Def  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1398 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* DecList  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1404 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* Dec  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1410 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* Exp  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1416 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* Args  */
#line 81 "src/syntax/syntax.y" /* yacc.c:1257  */
      { cst_node_dtor(((*yyvaluep))); }
#line 1422 "src/syntax/syntax.tab.c" /* yacc.c:1257  */
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
#line 98 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Program"); 
                                          if (cmm_nr_error == 0)
                                              cst_node_print((yyval), 0); }
#line 1688 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 104 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ExtDefList"); }
#line 1694 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 105 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "ExtDefList"); }
#line 1700 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 109 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1706 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 110 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1712 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 111 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDef"); }
#line 1718 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 115 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "ExtDecList"); }
#line 1724 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "ExtDecList"); }
#line 1730 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 122 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Specifier"); }
#line 1736 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 123 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Specifier"); }
#line 1742 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "StructSpecifier"); }
#line 1748 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "StructSpecifier"); }
#line 1754 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 132 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "OptTag"); }
#line 1760 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "OptTag"); }
#line 1766 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 137 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Tag"); }
#line 1772 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 143 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "VarDec"); }
#line 1778 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 144 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "VarDec"); }
#line 1784 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 148 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "FunDec"); }
#line 1790 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 149 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "FunDec"); }
#line 1796 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 153 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "VarList"); }
#line 1802 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 154 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "VarList"); }
#line 1808 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 158 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "ParamDec"); }
#line 1814 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 164 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "CompSt"); }
#line 1820 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 168 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "StmtList"); }
#line 1826 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "StmtList"); }
#line 1832 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 173 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1838 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 174 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Stmt"); }
#line 1844 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 175 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1850 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 176 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1856 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 177 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE7((yyval), (yyvsp[-6]), (yyvsp[-5]), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1862 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 178 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE5((yyval), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Stmt"); }
#line 1868 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "DefList"); }
#line 1874 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 185 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE0((yyval), "DefList"); }
#line 1880 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Def"); }
#line 1886 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 193 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "DecList"); }
#line 1892 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 194 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "DecList"); }
#line 1898 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 198 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Dec"); }
#line 1904 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 199 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Dec"); }
#line 1910 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 205 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1916 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 206 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1922 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 207 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1928 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 208 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1934 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 209 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1940 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 210 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1946 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 211 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1952 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 212 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1958 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 213 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1964 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 214 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1970 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 215 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE2((yyval), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1976 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 216 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1982 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 217 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1988 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 218 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE4((yyval), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 1994 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 219 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Exp"); }
#line 2000 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 220 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2006 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 221 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2012 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 222 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Exp"); }
#line 2018 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 226 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE3((yyval), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), "Args"); }
#line 2024 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 227 "src/syntax/syntax.y" /* yacc.c:1646  */
    { BUILD_CST_NODE1((yyval), (yyvsp[0]), "Args"); }
#line 2030 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2034 "src/syntax/syntax.tab.c" /* yacc.c:1646  */
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
#line 230 "src/syntax/syntax.y" /* yacc.c:1906  */


int main() {
    yyparse();
}

void yyerror(char const *msg) {
    cmm_error(CMM_ERROR_SYNTAX, 0, 0, msg);
}


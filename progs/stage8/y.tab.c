/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "exprtree.h"
	#include "exprtree.c"
	FILE* targetFile;
	FILE* dataFile;
	int yylex(void);
	extern FILE *yyin;
	extern char* yytext;
	int sptop=4096,bind;
	struct Typetable* typeptr,*typeptr2;
	char* typename,*classname,*typename2;
	struct Lsymbol* lptr;
	struct Classtable* Cptr;
	

#line 89 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    NUM = 258,
    PLUS = 259,
    MINUS = 260,
    MUL = 261,
    DIV = 262,
    ID = 263,
    begin = 264,
    END = 265,
    READ = 266,
    WRITE = 267,
    EOL = 268,
    IF = 269,
    then = 270,
    ELSE = 271,
    endif = 272,
    WHILE = 273,
    DO = 274,
    endwhile = 275,
    GT = 276,
    LT = 277,
    LE = 278,
    GE = 279,
    NE = 280,
    EQ = 281,
    ASSIGN = 282,
    BREAK = 283,
    CONTINUE = 284,
    INT = 285,
    STR = 286,
    DECL = 287,
    ENDDECL = 288,
    STRING = 289,
    MOD = 290,
    RET = 291,
    MAIN = 292,
    AND = 293,
    OR = 294,
    TYPEDECL = 295,
    ENDTYPE = 296,
    INIT = 297,
    ALLOC = 298,
    FREE = 299,
    CLASS = 300,
    ENDCLASS = 301,
    EXTENDS = 302,
    SELF = 303,
    NEW = 304
  };
#endif
/* Tokens.  */
#define NUM 258
#define PLUS 259
#define MINUS 260
#define MUL 261
#define DIV 262
#define ID 263
#define begin 264
#define END 265
#define READ 266
#define WRITE 267
#define EOL 268
#define IF 269
#define then 270
#define ELSE 271
#define endif 272
#define WHILE 273
#define DO 274
#define endwhile 275
#define GT 276
#define LT 277
#define LE 278
#define GE 279
#define NE 280
#define EQ 281
#define ASSIGN 282
#define BREAK 283
#define CONTINUE 284
#define INT 285
#define STR 286
#define DECL 287
#define ENDDECL 288
#define STRING 289
#define MOD 290
#define RET 291
#define MAIN 292
#define AND 293
#define OR 294
#define TYPEDECL 295
#define ENDTYPE 296
#define INIT 297
#define ALLOC 298
#define FREE 299
#define CLASS 300
#define ENDCLASS 301
#define EXTENDS 302
#define SELF 303
#define NEW 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

	struct tnode* p;
	int n;
	char* c;
	struct Paramstruct* paramptr;
	struct Typetable* type;
	struct Fieldlist* fieldlist;

#line 248 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   546

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  260

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,     2,     2,    54,     2,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    40,    40,    41,    42,    43,    44,    45,    46,    47,
      52,    53,    55,    56,    58,    59,    60,    62,    63,    65,
      66,    67,    69,    71,    72,    74,    76,    77,    85,    88,
      89,    92,    95,    96,    99,   102,   103,   106,   107,   108,
     111,   112,   114,   115,   116,   121,   122,   125,   139,   141,
     142,   143,   146,   149,   156,   157,   158,   161,   162,   164,
     167,   168,   173,   184,   188,   189,   193,   194,   195,   198,
     199,   200,   201,   202,   203,   204,   207,   210,   212,   215,
     218,   220,   221,   223,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   244,   245,   246,   247,   248,   249,   250,   254,
     257,   275,   277,   281,   283,   285,   290,   296,   297,   298
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "PLUS", "MINUS", "MUL", "DIV",
  "ID", "begin", "END", "READ", "WRITE", "EOL", "IF", "then", "ELSE",
  "endif", "WHILE", "DO", "endwhile", "GT", "LT", "LE", "GE", "NE", "EQ",
  "ASSIGN", "BREAK", "CONTINUE", "INT", "STR", "DECL", "ENDDECL", "STRING",
  "MOD", "RET", "MAIN", "AND", "OR", "TYPEDECL", "ENDTYPE", "INIT",
  "ALLOC", "FREE", "CLASS", "ENDCLASS", "EXTENDS", "SELF", "NEW", "'{'",
  "'}'", "'('", "')'", "','", "'['", "']'", "'.'", "$accept", "Program",
  "ClassDefBlock", "ClassDefList", "ClassDef", "Cname", "Fieldlists",
  "Fld", "MethodDecl", "MDecl", "MethodDefns", "TypeBlock",
  "TypeEntryList", "TypeEntry", "FieldList", "Field", "GdeclBlock",
  "GdeclList", "GDecl", "GidList", "Gid", "FdefBlock", "Fdef",
  "ParamList2", "ParamList", "Param", "Type", "LdeclBlock", "LDecList",
  "LDecl", "IdList", "MainBlock", "Body", "Retstmt", "Slist", "Stmt",
  "Breakstmt", "Continuestmt", "InputStmt", "OutputStmt", "AsgStmt",
  "Ifstmt", "Whilestmt", "expr", "Fieldd", "ArgList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     123,   125,    40,    41,    44,    91,    93,    46
};
# endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,    10,    23,    60,    64,   -29,    40,    -5,  -134,    31,
      49,  -134,    66,  -134,    83,    -1,   117,  -134,    64,   119,
    -134,  -134,   121,  -134,  -134,   127,   113,   177,  -134,    55,
    -134,    83,   117,  -134,   178,  -134,   117,  -134,  -134,     2,
    -134,   184,  -134,   188,   125,   -40,     4,  -134,  -134,  -134,
    -134,  -134,   153,   117,  -134,  -134,  -134,   199,   191,   101,
    -134,   106,  -134,   167,   119,   216,  -134,   177,   119,  -134,
    -134,    14,   174,  -134,   122,   218,   119,  -134,   195,    28,
    -134,   224,   181,  -134,   180,   187,  -134,   119,  -134,   119,
     192,     3,  -134,   139,   238,  -134,   119,  -134,  -134,   200,
     103,     5,  -134,  -134,  -134,   241,   150,  -134,   240,   202,
    -134,   195,   242,  -134,  -134,     8,  -134,  -134,  -134,   161,
     207,   208,   209,   211,   251,   252,  -134,   214,   215,   221,
     222,   223,    27,   159,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,   414,   229,  -134,   238,  -134,  -134,   270,    89,
      27,   273,    27,    27,    27,    27,  -134,  -134,   232,   234,
     282,   283,   290,   289,   382,   287,  -134,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,   296,   254,  -134,  -134,   484,   110,    80,    16,   295,
     331,   339,   375,  -134,  -134,   250,    42,   253,  -134,  -134,
     438,  -134,    -2,    -2,  -134,  -134,   507,   507,   507,   507,
     507,   507,   461,  -134,   147,   147,  -134,  -134,  -134,    27,
    -134,    27,   299,   309,   310,   293,   306,  -134,    27,   301,
    -134,  -134,  -134,   484,   137,   274,  -134,  -134,   240,   240,
     156,   277,  -134,    27,   132,   186,  -134,    27,   168,   240,
     318,   319,   170,  -134,   228,  -134,  -134,  -134,   326,  -134
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      11,     0,     0,     0,     0,    11,     0,     0,    30,    17,
       0,    13,     0,     1,     0,     0,     0,     9,     0,     0,
      28,    29,     0,    10,    12,     0,     0,     0,    36,     0,
      38,    53,     8,    46,     0,     7,     0,     5,    53,     0,
      33,     0,    18,    21,     0,    42,     0,    41,    35,    37,
      45,     6,     0,     4,     3,    31,    32,     0,     0,     0,
      20,     0,    24,     0,    51,     0,    39,     0,    51,     2,
      34,     0,     0,    19,     0,     0,     0,    23,    56,     0,
      50,     0,     0,    40,     0,    48,    22,    51,    16,     0,
       0,     0,    27,     0,     0,    44,     0,    52,    43,     0,
       0,     0,    15,    26,    55,     0,     0,    58,    68,     0,
      49,    56,     0,    14,    61,     0,    54,    57,    98,    99,
       0,     0,     0,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,    67,    74,    75,    69,    70,    71,
      72,    73,     0,   104,    62,     0,    25,    59,     0,   119,
       0,     0,     0,     0,     0,     0,    76,    77,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,   102,   118,     0,     0,   110,     0,
       0,     0,     0,   105,   106,     0,   116,     0,    89,    65,
       0,    63,    84,    85,    86,    88,    91,    90,    92,    93,
      94,    95,     0,    87,    96,    97,   109,    47,   103,     0,
     101,   119,     0,     0,     0,     0,     0,   108,   119,     0,
     107,    64,    80,   117,     0,     0,    78,    79,    68,    68,
       0,   115,   111,   119,     0,     0,   113,   119,     0,    68,
       0,     0,     0,   112,     0,    82,    83,   114,     0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,   335,  -134,   337,  -134,  -134,   291,   292,   -60,
     260,  -134,  -134,   334,  -134,   320,   340,  -134,   338,  -134,
     304,   332,   -24,  -134,   -59,   276,   -13,   262,  -134,   269,
    -134,    92,   231,  -134,   -70,  -133,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -130,  -134,  -121
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    10,    11,    12,    59,    60,    61,    62,
      91,     5,     7,     8,    39,    40,    16,    29,    30,    46,
      47,    32,    33,    84,    79,    80,    34,    94,   106,   107,
     115,    17,   109,   165,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   186
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     166,    77,   163,     6,   169,   170,    41,    27,    50,    85,
      38,    38,    64,    38,    77,    65,     2,    66,     6,   185,
     187,   147,   189,   190,   191,   192,    41,    86,   100,    50,
     118,     9,    28,   178,   200,   119,    20,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,    81,    92,    55,   102,    81,   113,     9,    67,     1,
      13,   126,   148,    27,     2,    92,    87,   103,   221,   127,
     128,   129,    14,   222,    81,   130,   131,   103,    22,   132,
     105,    95,    96,    81,   167,   168,   169,   170,    48,   233,
      19,   185,   118,   105,   228,    23,    15,   119,   185,   229,
     234,   171,   172,   173,   174,   175,   176,   240,    35,    58,
      37,   166,   166,   185,    75,   178,    25,   185,   179,   180,
      26,   166,   248,   126,    51,    31,   252,    38,    54,    42,
      75,   127,   128,   129,    72,   118,   220,   130,   131,    76,
     119,   132,   184,   120,   121,    69,   122,    38,   249,   250,
     123,   167,   168,   169,   170,    89,   112,    96,    38,    43,
     124,   125,   118,   218,   219,    44,   126,   119,   244,   245,
     120,   121,   104,   122,   127,   128,   129,   123,    63,   254,
     130,   131,   178,   116,   132,    45,    52,   124,   125,   118,
     242,   219,    57,   126,   119,   164,    58,   120,   121,    71,
     122,   127,   128,   129,   123,    68,   251,   130,   131,   246,
     219,   132,    70,   149,   124,   125,   150,    78,   151,    82,
     126,   253,   219,   257,   219,    88,    90,    93,   127,   128,
     129,   118,    97,    99,   130,   131,   119,    98,   132,   120,
     121,    96,   122,   118,    87,   258,   123,   108,   119,   114,
     111,   120,   121,   144,   122,   146,   124,   125,   123,   152,
     153,   154,   126,   155,   156,   157,   158,   159,   124,   125,
     127,   128,   129,   160,   126,   162,   130,   131,   183,   161,
     132,   188,   127,   128,   129,   193,   181,   194,   130,   131,
     195,   196,   132,   167,   168,   169,   170,   201,   197,   167,
     168,   169,   170,   227,   216,   217,   230,   235,   238,   241,
     171,   172,   173,   174,   175,   176,   171,   172,   173,   174,
     175,   176,   236,   237,   178,   239,   243,   179,   180,   247,
     178,   255,   256,   179,   180,   167,   168,   169,   170,   259,
      18,    21,   198,   167,   168,   169,   170,    24,   223,   101,
      73,    74,   171,   172,   173,   174,   175,   176,    36,    56,
     171,   172,   173,   174,   175,   176,   178,    49,    53,   179,
     180,    83,   110,   145,   178,   117,   182,   179,   180,   167,
     168,   169,   170,     0,   224,   118,     0,     0,     0,     0,
     119,     0,   225,     0,     0,   199,   171,   172,   173,   174,
     175,   176,     0,     0,     0,     0,     0,     0,     0,     0,
     178,     0,     0,   179,   180,     0,   126,     0,   167,   168,
     169,   170,     0,     0,   127,   128,   129,     0,   226,     0,
     130,   131,     0,     0,   132,   171,   172,   173,   174,   175,
     176,   177,   167,   168,   169,   170,     0,     0,     0,   178,
       0,   231,   179,   180,     0,     0,     0,     0,     0,   171,
     172,   173,   174,   175,   176,   167,   168,   169,   170,     0,
       0,     0,     0,   178,   232,     0,   179,   180,     0,     0,
       0,     0,   171,   172,   173,   174,   175,   176,   167,   168,
     169,   170,     0,     0,     0,     0,   178,     0,     0,   179,
     180,     0,     0,     0,     0,   171,   172,   173,   174,   175,
     176,   167,   168,   169,   170,     0,     0,     0,     0,   178,
       0,     0,   179,   180,     0,     0,     0,     0,    -1,    -1,
      -1,    -1,    -1,    -1,     0,     0,     0,     0,     0,     0,
       0,     0,   178,     0,     0,   179,   180
};

static const yytype_int16 yycheck[] =
{
     133,    61,   132,     8,     6,     7,    19,     8,    32,    68,
       8,     8,    52,     8,    74,    55,    45,    13,     8,   149,
     150,    13,   152,   153,   154,   155,    39,    13,    87,    53,
       3,     8,    33,    35,   164,     8,    41,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,    64,    76,    51,    51,    68,    51,     8,    54,    40,
       0,    34,    54,     8,    45,    89,    52,    91,    52,    42,
      43,    44,     8,    57,    87,    48,    49,   101,    47,    52,
      93,    53,    54,    96,     4,     5,     6,     7,    33,   219,
      50,   221,     3,   106,    52,    46,    32,     8,   228,    57,
     221,    21,    22,    23,    24,    25,    26,   228,    16,     8,
      18,   244,   245,   243,     8,    35,    50,   247,    38,    39,
      37,   254,   243,    34,    32,     8,   247,     8,    36,     8,
       8,    42,    43,    44,    33,     3,    56,    48,    49,    33,
       8,    52,    53,    11,    12,    53,    14,     8,    16,    17,
      18,     4,     5,     6,     7,    33,    53,    54,     8,    32,
      28,    29,     3,    53,    54,    52,    34,     8,   238,   239,
      11,    12,    33,    14,    42,    43,    44,    18,    53,   249,
      48,    49,    35,    33,    52,     8,     8,    28,    29,     3,
      53,    54,     8,    34,     8,    36,     8,    11,    12,     8,
      14,    42,    43,    44,    18,    52,    20,    48,    49,    53,
      54,    52,    13,    52,    28,    29,    55,    50,    57,     3,
      34,    53,    54,    53,    54,    51,     8,    32,    42,    43,
      44,     3,     8,    53,    48,    49,     8,    56,    52,    11,
      12,    54,    14,     3,    52,    17,    18,     9,     8,     8,
      50,    11,    12,    51,    14,    13,    28,    29,    18,    52,
      52,    52,    34,    52,    13,    13,    52,    52,    28,    29,
      42,    43,    44,    52,    34,    52,    48,    49,     8,    57,
      52,     8,    42,    43,    44,    53,    57,    53,    48,    49,
       8,     8,    52,     4,     5,     6,     7,    10,     8,     4,
       5,     6,     7,    53,     8,    51,    53,     8,    15,     8,
      21,    22,    23,    24,    25,    26,    21,    22,    23,    24,
      25,    26,    13,    13,    35,    19,    52,    38,    39,    52,
      35,    13,    13,    38,    39,     4,     5,     6,     7,    13,
       5,     7,    53,     4,     5,     6,     7,    10,    53,    89,
      59,    59,    21,    22,    23,    24,    25,    26,    18,    39,
      21,    22,    23,    24,    25,    26,    35,    29,    36,    38,
      39,    67,    96,   111,    35,   106,   145,    38,    39,     4,
       5,     6,     7,    -1,    53,     3,    -1,    -1,    -1,    -1,
       8,    -1,    53,    -1,    -1,    13,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    38,    39,    -1,    34,    -1,     4,     5,
       6,     7,    -1,    -1,    42,    43,    44,    -1,    53,    -1,
      48,    49,    -1,    -1,    52,    21,    22,    23,    24,    25,
      26,    27,     4,     5,     6,     7,    -1,    -1,    -1,    35,
      -1,    13,    38,    39,    -1,    -1,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    35,    13,    -1,    38,    39,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      39,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      26,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    45,    59,    60,    69,     8,    70,    71,     8,
      61,    62,    63,     0,     8,    32,    74,    89,    60,    50,
      41,    71,    47,    46,    62,    50,    37,     8,    33,    75,
      76,     8,    79,    80,    84,    89,    74,    89,     8,    72,
      73,    84,     8,    32,    52,     8,    77,    78,    33,    76,
      80,    89,     8,    79,    89,    51,    73,     8,     8,    64,
      65,    66,    67,    53,    52,    55,    13,    54,    52,    89,
      13,     8,    33,    65,    66,     8,    33,    67,    50,    82,
      83,    84,     3,    78,    81,    82,    13,    52,    51,    33,
       8,    68,    80,    32,    85,    53,    54,     8,    56,    53,
      82,    68,    51,    80,    33,    84,    86,    87,     9,    90,
      83,    50,    53,    51,     8,    88,    33,    87,     3,     8,
      11,    12,    14,    18,    28,    29,    34,    42,    43,    44,
      48,    49,    52,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    51,    85,    13,    13,    54,    52,
      55,    57,    52,    52,    52,    52,    13,    13,    52,    52,
      52,    57,    52,   101,    36,    91,    93,     4,     5,     6,
       7,    21,    22,    23,    24,    25,    26,    27,    35,    38,
      39,    57,    90,     8,    53,   101,   103,   101,     8,   101,
     101,   101,   101,    53,    53,     8,     8,     8,    53,    13,
     101,    10,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,     8,    51,    53,    54,
      56,    52,    57,    53,    53,    53,    53,    53,    52,    57,
      53,    13,    13,   101,   103,     8,    13,    13,    15,    19,
     103,     8,    53,    52,    92,    92,    53,    52,   103,    16,
      17,    20,   103,    53,    92,    13,    13,    53,    17,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    63,    63,    64,
      64,    64,    65,    66,    66,    67,    68,    68,    69,    70,
      70,    71,    72,    72,    73,    74,    74,    75,    75,    76,
      77,    77,    78,    78,    78,    79,    79,    80,    81,    82,
      82,    82,    83,    84,    85,    85,    85,    86,    86,    87,
      88,    88,    89,    90,    91,    91,    92,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    94,    95,    96,    97,
      98,    99,    99,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     4,     3,     4,     3,     3,     2,
       3,     0,     2,     1,     8,     7,     6,     1,     3,     2,
       1,     0,     3,     2,     1,     6,     2,     1,     3,     2,
       1,     4,     2,     1,     3,     3,     2,     2,     1,     3,
       3,     1,     1,     4,     4,     2,     1,     9,     1,     3,
       1,     0,     2,     1,     3,     2,     0,     2,     1,     3,
       3,     1,     8,     4,     3,     2,     2,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     5,     5,
       4,    10,     8,     8,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     4,     3,     4,     1,     3,     3,     4,     4,     3,
       3,     6,     8,     6,     8,     5,     3,     3,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 40 "parser.y"
                                                                        {return 0;}
#line 1657 "y.tab.c"
    break;

  case 3:
#line 41 "parser.y"
                                                                                {return 0;}
#line 1663 "y.tab.c"
    break;

  case 4:
#line 42 "parser.y"
                                                                              {return 0;}
#line 1669 "y.tab.c"
    break;

  case 5:
#line 43 "parser.y"
                                                                        {return 0;}
#line 1675 "y.tab.c"
    break;

  case 6:
#line 44 "parser.y"
                                                                                {return 0;}
#line 1681 "y.tab.c"
    break;

  case 7:
#line 45 "parser.y"
                                                                        {return 0;}
#line 1687 "y.tab.c"
    break;

  case 8:
#line 46 "parser.y"
                                                                    {return 0;}
#line 1693 "y.tab.c"
    break;

  case 9:
#line 47 "parser.y"
                                                                {return 0;}
#line 1699 "y.tab.c"
    break;

  case 10:
#line 52 "parser.y"
                                                {virtualFuncTableInit(targetFile,dataFile);}
#line 1705 "y.tab.c"
    break;

  case 17:
#line 62 "parser.y"
                {Cinstall((yyvsp[0].c),NULL);classname=(yyvsp[0].c);}
#line 1711 "y.tab.c"
    break;

  case 18:
#line 63 "parser.y"
                        {Cinstall((yyvsp[-2].c),(yyvsp[0].c));classname=(yyvsp[-2].c);}
#line 1717 "y.tab.c"
    break;

  case 19:
#line 65 "parser.y"
                                {}
#line 1723 "y.tab.c"
    break;

  case 20:
#line 66 "parser.y"
                                {}
#line 1729 "y.tab.c"
    break;

  case 21:
#line 67 "parser.y"
                                {}
#line 1735 "y.tab.c"
    break;

  case 22:
#line 69 "parser.y"
                                {ClassFinstall((yyvsp[-2].c),(yyvsp[-1].c));}
#line 1741 "y.tab.c"
    break;

  case 23:
#line 71 "parser.y"
                                {Lsymbolroot=NULL;reset_fnargumentsbinding();}
#line 1747 "y.tab.c"
    break;

  case 24:
#line 72 "parser.y"
                                        {}
#line 1753 "y.tab.c"
    break;

  case 25:
#line 74 "parser.y"
                                                {ClassMinstall(typelookuponly((yyvsp[-5].c)),(yyvsp[-4].c),(yyvsp[-2].paramptr));}
#line 1759 "y.tab.c"
    break;

  case 28:
#line 85 "parser.y"
                                                {printTypeTable();}
#line 1765 "y.tab.c"
    break;

  case 31:
#line 92 "parser.y"
                                        {typeinstallwithfields((yyvsp[-3].c),8,(yyvsp[-1].fieldlist));}
#line 1771 "y.tab.c"
    break;

  case 32:
#line 95 "parser.y"
                                {(yyval.fieldlist)=fieldappend((yyvsp[-1].fieldlist),(yyvsp[0].fieldlist));}
#line 1777 "y.tab.c"
    break;

  case 33:
#line 96 "parser.y"
                {(yyvsp[0].fieldlist)->fieldIndex=0; (yyval.fieldlist)=(yyvsp[0].fieldlist);}
#line 1783 "y.tab.c"
    break;

  case 34:
#line 99 "parser.y"
                        {(yyval.fieldlist)=fieldinstall((yyvsp[-1].c),(yyvsp[-2].type));}
#line 1789 "y.tab.c"
    break;

  case 35:
#line 102 "parser.y"
                                    {updateBinding();sptop=getSP();printGsymbolTable(); Lsymbolroot=NULL;reset_fnargumentsbinding();}
#line 1795 "y.tab.c"
    break;

  case 36:
#line 103 "parser.y"
                                {}
#line 1801 "y.tab.c"
    break;

  case 39:
#line 108 "parser.y"
                        {updateTypeToGsymbol((yyvsp[-2].c));}
#line 1807 "y.tab.c"
    break;

  case 42:
#line 114 "parser.y"
                                {Ginstall((yyvsp[0].c),NULL,1,-1,NULL,-1);}
#line 1813 "y.tab.c"
    break;

  case 43:
#line 115 "parser.y"
                                {Ginstall((yyvsp[-3].c),NULL,(yyvsp[-1].n),-1,NULL,-1);}
#line 1819 "y.tab.c"
    break;

  case 44:
#line 116 "parser.y"
                                {Ginstall((yyvsp[-3].c),NULL,-1,-1,(yyvsp[-1].paramptr),-1);}
#line 1825 "y.tab.c"
    break;

  case 47:
#line 125 "parser.y"
                                                                {//if($<type>1!=$<p>8->type){printf("invalid fn ret type");exit(0);}
								 //if(Glookup($<c>2)==NULL){printf("fn not declared globally\n");exit(0);}
								 //functypecheck($4,Glookup($<c>2));
								 (yyval.p)=(yyvsp[-1].p);
								 (yyval.p)->varname=(yyvsp[-7].c);
								 Lprint();
								 printf("%s\n",(yyval.p)->varname);
								 codeGen(targetFile,(yyval.p));
								 printf("%s\n",(yyval.p)->varname);
								 Lsymbolroot=NULL;reset_fnargumentsbinding();
								 }
#line 1841 "y.tab.c"
    break;

  case 48:
#line 139 "parser.y"
                                        {Linstall("self2",NULL);Linstall("self",NULL);}
#line 1847 "y.tab.c"
    break;

  case 49:
#line 141 "parser.y"
                                        {(yyval.paramptr)=addParam((yyvsp[-2].paramptr),(yyvsp[0].paramptr));}
#line 1853 "y.tab.c"
    break;

  case 50:
#line 142 "parser.y"
                                {(yyval.paramptr)=(yyvsp[0].paramptr);}
#line 1859 "y.tab.c"
    break;

  case 51:
#line 143 "parser.y"
                                        {(yyval.paramptr)=NULL;}
#line 1865 "y.tab.c"
    break;

  case 52:
#line 146 "parser.y"
                {(yyval.paramptr)=createParam((yyvsp[0].c),(yyvsp[-1].type));Linstall((yyvsp[0].c),(yyvsp[-1].type));}
#line 1871 "y.tab.c"
    break;

  case 53:
#line 149 "parser.y"
                {(yyval.type)= typelookup((yyvsp[0].c));}
#line 1877 "y.tab.c"
    break;

  case 59:
#line 164 "parser.y"
                                {Linstallbylistwithtype((yyvsp[-1].paramptr),(yyvsp[-2].type));}
#line 1883 "y.tab.c"
    break;

  case 60:
#line 167 "parser.y"
                                {(yyval.paramptr)=addParam((yyvsp[-2].paramptr),createParam((yyvsp[0].c),NULL));}
#line 1889 "y.tab.c"
    break;

  case 61:
#line 168 "parser.y"
                                {(yyval.paramptr)=createParam((yyvsp[0].c),NULL);}
#line 1895 "y.tab.c"
    break;

  case 62:
#line 174 "parser.y"
                                {(yyval.p)=(yyvsp[-1].p);
                                 (yyval.p)->right->val=tMAINLabel;
                                 Lprint();
                                 codeGen(targetFile,(yyval.p));
                                 Lsymbolroot=NULL;reset_fnargumentsbinding();
                                }
#line 1906 "y.tab.c"
    break;

  case 63:
#line 184 "parser.y"
                                        {(yyval.p) = createTree(-1,(yyvsp[-1].p)->type,NULL,tFBODY,NULL,NULL,(yyvsp[-2].p),(yyvsp[-1].p),NULL,Clookup(classname));}
#line 1912 "y.tab.c"
    break;

  case 64:
#line 188 "parser.y"
                                {(yyval.p) = createTree(-1,(yyvsp[-1].p)->type,NULL,tRET,NULL,NULL,(yyvsp[-1].p),NULL,NULL,NULL);}
#line 1918 "y.tab.c"
    break;

  case 65:
#line 189 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("void"),NULL,tRET,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 1924 "y.tab.c"
    break;

  case 66:
#line 193 "parser.y"
                                {(yyval.p)=createTree(-1,NULL,NULL,tCONNECT,NULL,NULL,(yyvsp[-1].p),(yyvsp[0].p),NULL,NULL);}
#line 1930 "y.tab.c"
    break;

  case 67:
#line 194 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1936 "y.tab.c"
    break;

  case 68:
#line 195 "parser.y"
                                {(yyval.p)=NULL;}
#line 1942 "y.tab.c"
    break;

  case 69:
#line 198 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1948 "y.tab.c"
    break;

  case 70:
#line 199 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1954 "y.tab.c"
    break;

  case 71:
#line 200 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1960 "y.tab.c"
    break;

  case 72:
#line 201 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1966 "y.tab.c"
    break;

  case 73:
#line 202 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1972 "y.tab.c"
    break;

  case 74:
#line 203 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1978 "y.tab.c"
    break;

  case 75:
#line 204 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 1984 "y.tab.c"
    break;

  case 76:
#line 207 "parser.y"
                                        {(yyval.p)=createTree(-1,NULL,NULL,tBREAK,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 1990 "y.tab.c"
    break;

  case 77:
#line 210 "parser.y"
                                        {(yyval.p)=createTree(-1,NULL,NULL,tCONTINUE,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 1996 "y.tab.c"
    break;

  case 78:
#line 212 "parser.y"
                                        {(yyval.p)=createTree(-1,NULL,NULL,tREAD,NULL,NULL,(yyvsp[-2].p),NULL,NULL,NULL);}
#line 2002 "y.tab.c"
    break;

  case 79:
#line 215 "parser.y"
                                        {(yyval.p)=createTree(-1,NULL,NULL,tWRITE,NULL,NULL,(yyvsp[-2].p),NULL,NULL,NULL);}
#line 2008 "y.tab.c"
    break;

  case 80:
#line 218 "parser.y"
                                {(yyval.p) = createTree(-1,NULL,NULL,tASSIGN,NULL,NULL,(yyvsp[-3].p),(yyvsp[-1].p),NULL,NULL);}
#line 2014 "y.tab.c"
    break;

  case 81:
#line 220 "parser.y"
                                                                {(yyval.p)=createTree(-1,NULL,NULL,tIF,NULL,NULL,(yyvsp[-7].p),(yyvsp[-4].p),(yyvsp[-2].p),NULL);}
#line 2020 "y.tab.c"
    break;

  case 82:
#line 221 "parser.y"
                                                        {(yyval.p)=createTree(-1,NULL,NULL,tIF,NULL,NULL,(yyvsp[-5].p),(yyvsp[-2].p),NULL,NULL);}
#line 2026 "y.tab.c"
    break;

  case 83:
#line 223 "parser.y"
                                                                {(yyval.p)=createTree(-1,NULL,NULL,tWHILE,NULL,NULL,(yyvsp[-5].p),(yyvsp[-2].p),NULL,NULL);}
#line 2032 "y.tab.c"
    break;

  case 84:
#line 225 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("int"),NULL,tADD,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2038 "y.tab.c"
    break;

  case 85:
#line 226 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("int"),NULL,tSUB,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2044 "y.tab.c"
    break;

  case 86:
#line 227 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("int"),NULL,tMUL,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2050 "y.tab.c"
    break;

  case 87:
#line 228 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("int"),NULL,tMOD,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2056 "y.tab.c"
    break;

  case 88:
#line 229 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("int"),NULL,tDIV,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2062 "y.tab.c"
    break;

  case 89:
#line 230 "parser.y"
                        {(yyval.p) = (yyvsp[-1].p);}
#line 2068 "y.tab.c"
    break;

  case 90:
#line 231 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tLT,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2074 "y.tab.c"
    break;

  case 91:
#line 232 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tGT,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2080 "y.tab.c"
    break;

  case 92:
#line 233 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tLE,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2086 "y.tab.c"
    break;

  case 93:
#line 234 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tGE,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2092 "y.tab.c"
    break;

  case 94:
#line 235 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tNE,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2098 "y.tab.c"
    break;

  case 95:
#line 236 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tEQ,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2104 "y.tab.c"
    break;

  case 96:
#line 237 "parser.y"
                                        {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tAND,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2110 "y.tab.c"
    break;

  case 97:
#line 238 "parser.y"
                                {(yyval.p) = createTree(-1,typelookup("bool"),NULL,tOR,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2116 "y.tab.c"
    break;

  case 98:
#line 239 "parser.y"
                                {(yyval.p)=createTree((yyvsp[0].n),typelookup("int"),NULL,tNUM,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2122 "y.tab.c"
    break;

  case 99:
#line 240 "parser.y"
                                {(yyval.p) = createTree(-1,typesearch((yyvsp[0].c)),(yyvsp[0].c),tVAR,Llookup((yyvsp[0].c)),Glookup((yyvsp[0].c)),NULL,NULL,NULL,Clookup((yyvsp[0].c)));}
#line 2128 "y.tab.c"
    break;

  case 100:
#line 241 "parser.y"
                                {(yyval.p) = (yyvsp[0].p);}
#line 2134 "y.tab.c"
    break;

  case 101:
#line 242 "parser.y"
                                {(yyval.p)= createTree(-1,typesearch((yyvsp[-3].c)),(yyvsp[-3].c),tARRAY,NULL,Glookup((yyvsp[-3].c)),(yyvsp[-1].p),NULL,NULL,NULL);}
#line 2140 "y.tab.c"
    break;

  case 102:
#line 244 "parser.y"
                                {(yyval.p) = createTree(-1,typesearch((yyvsp[-2].c)),(yyvsp[-2].c),tFUNC,NULL,Glookup((yyvsp[-2].c)),NULL,NULL,NULL,NULL);}
#line 2146 "y.tab.c"
    break;

  case 103:
#line 245 "parser.y"
                                {(yyval.p) = createTree(-1,typesearch((yyvsp[-3].c)),(yyvsp[-3].c),tFUNC,NULL,Glookup((yyvsp[-3].c)),(yyvsp[-1].p),NULL,NULL,NULL);}
#line 2152 "y.tab.c"
    break;

  case 104:
#line 246 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 2158 "y.tab.c"
    break;

  case 105:
#line 247 "parser.y"
                                {(yyval.p) = createTree(-1,NULL,NULL,tINIT,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2164 "y.tab.c"
    break;

  case 106:
#line 248 "parser.y"
                        {(yyval.p) = createTree(-1,NULL,NULL,tALLOC,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2170 "y.tab.c"
    break;

  case 107:
#line 249 "parser.y"
                                {(yyval.p) = createTree(-1,NULL,(yyvsp[-1].c),tNEW,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2176 "y.tab.c"
    break;

  case 108:
#line 250 "parser.y"
                                {(yyvsp[-1].p) = createTree(-1,typesearch((yyvsp[-1].c)),(yyvsp[-1].c),tTYPEFIELD,Llookup((yyvsp[-1].c)),Glookup((yyvsp[-1].c)),NULL,NULL,NULL,NULL);
	 			(yyval.p)= createTree(-1,NULL,NULL,tFREE,NULL,NULL,(yyvsp[-1].p),NULL,NULL,NULL);}
#line 2183 "y.tab.c"
    break;

  case 109:
#line 254 "parser.y"
                       {typename=(yyvsp[0].c);
		(yyvsp[0].p) = createTree(-1,typelookup((yyvsp[-2].p)->varname),(yyvsp[0].c),tFIELD,Llookup((yyvsp[-2].c)),Glookup((yyvsp[-2].c)),NULL,NULL,NULL,NULL);
		(yyval.p) = createTree(-1,fieldtypelookup((yyvsp[-2].p)->varname,typename),(yyvsp[-2].c),tDOT,Llookup((yyvsp[-2].c)),Glookup((yyvsp[-2].c)),(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);}
#line 2191 "y.tab.c"
    break;

  case 110:
#line 257 "parser.y"
                    {if(Glookup((yyvsp[-2].c))!=NULL && Glookup((yyvsp[-2].c))->Ctype!=NULL){
			typename=(yyvsp[-2].c);
			(yyvsp[-2].p) = createTree(-1,NULL,(yyvsp[-2].c),tCLASSOBJ,NULL,Glookup((yyvsp[-2].c)),NULL,NULL,NULL,NULL);
			(yyvsp[0].p) = createTree(-1,NULL,(yyvsp[0].c),tCLASSFIELD,NULL,Glookup(typename),NULL,NULL,NULL,NULL);
			(yyval.p) = createTree(-1,NULL,typename,tCLASSDOT,NULL,Glookup(typename),(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);
		}else{
			if(typesearch((yyvsp[-2].c))!=fieldtype((yyvsp[-2].c),(yyvsp[0].c))){
				typename=fieldtype((yyvsp[-2].c),(yyvsp[0].c))->name;
			}else{
				typename=typesearch((yyvsp[-2].c))->name;
			}
			typeptr=typesearch((yyvsp[-2].c));
			typeptr2=fieldtype((yyvsp[-2].c),(yyvsp[0].c));
			typename=(yyvsp[-2].c);
			(yyvsp[-2].p) = createTree(-1,typeptr,(yyvsp[-2].c),tTYPEFIELD,Llookup((yyvsp[-2].c)),Glookup((yyvsp[-2].c)),NULL,NULL,NULL,NULL);
			(yyvsp[0].p) = createTree(-1,typeptr,(yyvsp[0].c),tFIELD,Llookup(typename),Glookup(typename),NULL,NULL,NULL,NULL);
			(yyval.p) = createTree(-1,typeptr2,typename,tDOT,Llookup(typename),Glookup(typename),(yyvsp[-2].p),(yyvsp[0].p),NULL,NULL);
	}}
#line 2214 "y.tab.c"
    break;

  case 111:
#line 275 "parser.y"
                                        {(yyval.p)=createTree(0,NULL,(yyvsp[-3].c),tMETHOD,NULL,Glookup((yyvsp[-5].c)),(yyvsp[-1].p),NULL,NULL,NULL);
		}
#line 2221 "y.tab.c"
    break;

  case 112:
#line 277 "parser.y"
                                                {
		bind=getBindingForMethod2((yyvsp[-7].c),(yyvsp[-5].c));
		(yyval.p)=createTree(bind,NULL,(yyvsp[-5].c),tMETHOD,NULL,Glookup((yyvsp[-7].c)),(yyvsp[-1].p),NULL,NULL,Clookup(classname));
		}
#line 2230 "y.tab.c"
    break;

  case 113:
#line 281 "parser.y"
                                        {(yyval.p)=createTree(0,NULL,(yyvsp[-3].c),tSELFMETHOD,NULL,NULL,(yyvsp[-1].p),NULL,NULL,Clookup(classname));
		}
#line 2237 "y.tab.c"
    break;

  case 114:
#line 283 "parser.y"
                                                {(yyvsp[-5].p) = createTree(-1,NULL,(yyvsp[-5].c),tVAR,NULL,NULL,NULL,NULL,NULL,NULL);
		(yyval.p)=createTree(-1,NULL,(yyvsp[-3].c),tSELFMETHOD2,NULL,NULL,(yyvsp[-1].p),(yyvsp[-5].p),NULL,Clookup(classname));}
#line 2244 "y.tab.c"
    break;

  case 115:
#line 285 "parser.y"
                                {typename=(yyvsp[-2].c);typename2=(yyvsp[0].c);
		(yyvsp[-4].p) = createTree(-1,NULL,NULL,tSELF,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
		(yyvsp[-2].p) = createTree(-1,NULL,(yyvsp[-2].c),tCLASSFIELD2,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
		(yyvsp[0].p) = createTree(-1,findclassmemtype(classname,typename),typename2,tFIELD,Llookup((yyvsp[-4].c)),Glookup((yyvsp[-4].c)),NULL,NULL,NULL,NULL);
		(yyval.p) = createTree(-1,NULL,NULL,tDOT,Llookup((yyvsp[-4].c)),Glookup((yyvsp[-4].c)),createTree(-1,NULL,classname,tCLASSDOT,NULL,NULL,(yyvsp[-4].p),(yyvsp[-2].p),NULL,Clookup(classname)),(yyvsp[0].p),NULL,NULL);}
#line 2254 "y.tab.c"
    break;

  case 116:
#line 290 "parser.y"
                        {(yyvsp[-2].p) = createTree(-1,NULL,NULL,tSELF,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
			(yyvsp[0].p) = createTree(-1,NULL,(yyvsp[0].c),tCLASSFIELD2,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
			(yyval.p) = createTree(-1,NULL,classname,tCLASSDOT,NULL,NULL,(yyvsp[-2].p),(yyvsp[0].p),NULL,Clookup(classname));
			}
#line 2263 "y.tab.c"
    break;

  case 117:
#line 296 "parser.y"
                                {(yyval.p)=appendArgList((yyvsp[-2].p),(yyvsp[0].p));}
#line 2269 "y.tab.c"
    break;

  case 118:
#line 297 "parser.y"
                                {(yyval.p)=(yyvsp[0].p);}
#line 2275 "y.tab.c"
    break;

  case 119:
#line 298 "parser.y"
                                {(yyval.p)=NULL;}
#line 2281 "y.tab.c"
    break;


#line 2285 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 301 "parser.y"


int yyerror(char const *s)
{
    printf("yyerror %s and %s",s,yytext);
}

int main(int argc, char*argv[]) {
	typeinstall("int");
	typeinstall("str");
	typeinstall("bool");
	typeinstall("void");
	typeinstall("NULL");
	typeinstallwithfields("int",1,NULL);
	typeinstallwithfields("str",1,NULL);
	typeinstallwithfields("bool",1,NULL);
	typeinstallwithfields("void",1,NULL);
	typeinstallwithfields("NULL",1,NULL);
	targetFile=fopen("targetFile.xsm","w");
	if(targetFile==NULL){
		printf("file error\n");
	}
	dataFile=fopen("vFuncTable.txt","w");
	if(dataFile==NULL){
		printf("file error\n");
	}
	yyin=fopen(argv[1],"r");
	fprintf(targetFile,"%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",0,"###",0,0,0,0,1,0);
	yyparse();
	fclose(targetFile);
	return 0;
}

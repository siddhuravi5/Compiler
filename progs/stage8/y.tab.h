/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 164 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

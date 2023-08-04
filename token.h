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

#ifndef YY_YY_TOKEN_H_INCLUDED
# define YY_YY_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_EOF = 258,
    TOKEN_IDENT = 259,
    TOKEN_ERROR = 260,
    TOKEN_CHAR = 261,
    TOKEN_INTEGER = 262,
    TOKEN_STRING = 263,
    TOKEN_ARRAY = 264,
    TOKEN_AUTO = 265,
    TOKEN_VOID = 266,
    TOKEN_BOOLEAN = 267,
    TOKEN_FALSE = 268,
    TOKEN_TRUE = 269,
    TOKEN_IF = 270,
    TOKEN_FOR = 271,
    TOKEN_PRINT = 272,
    TOKEN_RETURN = 273,
    TOKEN_FUNCTION = 274,
    TOKEN_ELSE = 275,
    TOKEN_WHILE = 276,
    TOKEN_COLON = 277,
    TOKEN_SEMICOLON = 278,
    TOKEN_COMMA = 279,
    TOKEN_LPAREN = 280,
    TOKEN_RPAREN = 281,
    TOKEN_LCURLY = 282,
    TOKEN_RCURLY = 283,
    TOKEN_LBRACKET = 284,
    TOKEN_RBRACKET = 285,
    TOKEN_INCREMENT = 286,
    TOKEN_DECREMENT = 287,
    TOKEN_NOT = 288,
    TOKEN_EXPONENT = 289,
    TOKEN_MULT = 290,
    TOKEN_DIV = 291,
    TOKEN_MOD = 292,
    TOKEN_PLUS = 293,
    TOKEN_MINUS = 294,
    TOKEN_LT = 295,
    TOKEN_LTE = 296,
    TOKEN_GT = 297,
    TOKEN_GTE = 298,
    TOKEN_EQUAL = 299,
    TOKEN_NOTEQ = 300,
    TOKEN_AND = 301,
    TOKEN_OR = 302,
    TOKEN_ASSIGN = 303,
    TOKEN_FUNCCALL = 304,
    TOKEN_LIT_STR = 305,
    TOKEN_LIT_CHAR = 306,
    TOKEN_LIT_INT = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 87 "parser.bison"

    struct decl *decl;
    struct stmt *stmt;
    struct expr *expr;
    struct type *type;
    struct param_list *param_list;
    char *ident;
    int number;
    char letter;
    char *word;

#line 122 "token.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKEN_H_INCLUDED  */

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_HOME_GKARLOS_PROJECTS_AUTLIB_SRC_READ_AUT_PARSER_H_INCLUDED
# define YY_YY_HOME_GKARLOS_PROJECTS_AUTLIB_SRC_READ_AUT_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "/home/gkarlos/Projects/autlib/src/read/aut/aut.y" /* yacc.c:1909  */

  #include <aut/read/aut.h>

#line 48 "/home/gkarlos/Projects/autlib/src/read/aut/_parser_.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DES = 258,
    NUMBER = 259,
    ACTION_LABEL = 260,
    COMMA = 261,
    LPAREN = 262,
    RPAREN = 263,
    NEWLINE = 264,
    END_OF_FILE = 265,
    INVALID_TOKEN = 266,
    NUMBER_OOR = 267
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "/home/gkarlos/Projects/autlib/src/read/aut/aut.y" /* yacc.c:1909  */

  size_t uint;
  char *string;
  autDescriptor_t *descriptor;
  autTransition_t *transition;
  autError_t err;

#line 81 "/home/gkarlos/Projects/autlib/src/read/aut/_parser_.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner, aut_t **aut, autError_t *err);

#endif /* !YY_YY_HOME_GKARLOS_PROJECTS_AUTLIB_SRC_READ_AUT_PARSER_H_INCLUDED  */

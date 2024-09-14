#include "utility.h"
#include "config.h"

string tokentype_to_string(tokentype t)
{
   switch (t)
   {
   case EOSF:
      return "End of Source File";
      break;
   case WS:
      return "Whitespace";
      break;
   case LE:
      return "Less Than Equal To";
      break;
   case NE:
      return "Not Equal To";
      break;
   case LT:
      return "Less Than";
      break;
   case EQ:
      return "Equal To";
      break;
   case GE:
      return "Greater Than Equal To";
      break;
   case GT:
      return "Greater Than";
      break;
   case IF:
      return "Keyword if";
      break;
   case THEN:
      return "Keyword then";
      break;
   case ELSE:
      return "Keyword else";
      break;
   case BEGIN:
      return "Keyword begin";
      break;
   case END:
      return "Keyword end";
      break;
   case READ:
      return "Keyword read";
      break;
   case WRITE:
      return "Keyword write";
      break;
   case ID:
      return "Identifier";
      break;
   case INTLITERAL:
      return "Int Literal";
      break;
   case FLOATLITERAL:
      return "Float Literal";
      break;
   case ADDOP:
      return "Addition Op '+'";
      break;
   case SUBOP:
      return "Subtraction Op '-'";
      break;
   case MULTOP:
      return "Multiplication Op '*'";
      break;
   case DIVOP:
      return "Division Op '/'";
      break;
   case ASSIGNOP:
      return "Assignment Op '=:='";
      break;
   case LPAREN:
      return "Left Parenthesis '('";
      break;
   case RPAREN:
      return "Right Parenthesis ')'";
      break;
   case SEMICOLON:
      return "Semicolon ';'";
      break;
   case COMMA:
      return "Comma ','";
      break;
   case PERIOD:
      return "Period '.'";
      break;
   default:
      return "Non-existent tokentype";
   }
}

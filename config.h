// Define config information of the scanner

// Since arrays, not linked structure, are used as the basic data structure,
// the size of arrays used in the scanner need to be specified upfront
#define MAX_STATE_COUNT 16      // For transition graphs, define the maximum number of states allowed
#define MAX_CHARACTER_COUNT 256 // For transition graphs, define the maximum number of distinct characters allowed
#define MAX_SYMBOL_COUNT 100    // The maximum size of the Symbol/Literal table

#define ERROR_STR_LEN 10 // displayed length of the string that causes a lexical eror

// All tokens enumerated here.
// Note the difference from the required text:
// The token relop is not used.  A different token is used for every relational operator.
enum tokentype
{
   EOSF,
   WS,
   LE,
   NE,
   LT,
   EQ,
   GE,
   GT,
   IF,
   THEN,
   ELSE,
   BEGIN,
   END,
   READ,
   WRITE,
   ID,
   INTLITERAL,
   FLOATLITERAL,
   ADDOP,
   SUBOP,
   MULTOP,
   DIVOP,
   ASSIGNOP,
   LPAREN,
   RPAREN,
   SEMICOLON,
   COMMA,
   PERIOD
};

// A function to enhance readability of tokentype
// It takes a tokentype and returns a string, which is the name of the tokentype
string tokentype_to_string(tokentype);

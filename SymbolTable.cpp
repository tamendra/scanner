#include "utility.h"
#include "config.h"
#include "SymbolTable.h"

// Initialize the table to be empty
SymbolTable::SymbolTable()
{
   symbol_count = 0;
}

// Used by the scanner to install keyword during scanner initialization
void SymbolTable::installKeyword(string keyword, tokentype keyword_token)
{
   symbols[symbol_count].symbol = keyword;
   symbols[symbol_count].is_keyword = true;
   symbols[symbol_count].token = keyword_token;
   symbol_count++;
}

// Locate an identifier in a Symbol table.  If not found, install the identifier
// return identifier entry index if it is an identifier
// return keyword token if it is a keyword
// is_keyword is an output parameter
int SymbolTable::installIdentifier(string identifier, tokentype id_token, bool &is_keyword)
{
   for (int i = 0; i < symbol_count; i++)
      if (symbols[i].symbol == identifier)
      {
         is_keyword = symbols[i].is_keyword;
         if (is_keyword)
            return symbols[i].token; // return keyword
         else
            return i; // return the entry index of the identifier
      }

   // New identifier; install it
   symbols[symbol_count].symbol = identifier;
   symbols[symbol_count].is_keyword = false;
   symbols[symbol_count].token = id_token;
   is_keyword = symbols[symbol_count].is_keyword;

   symbol_count++;
   return symbol_count - 1; // return the entry index of the identifier
}

// Locate a literal in the Symbol Table.  If not found, install the literal in the Symbol Table
// return literal entry
int SymbolTable::installLiteral(string literal, tokentype literal_token)
{
   for (int i = 0; i < symbol_count; i++)
      if (symbols[i].symbol == literal)
      {
         return i; // return the entry index of the literal
      }

   // New literal
   symbols[symbol_count].symbol = literal;
   symbols[symbol_count].is_keyword = false;
   symbols[symbol_count].token = literal_token;
   symbol_count++;

   return symbol_count - 1; // return the entry of the identifier
}

// Print the content of the Symbol Table
void SymbolTable::print()
{
   cout << endl
        << endl;
   cout << "Symbol Table:" << endl;
   cout << "#\tLexeme\tToken" << endl;
   cout << "---------------------------------------------" << endl;
   for (int i = 0; i < symbol_count; i++)
   {
      cout << i << "\t" << symbols[i].symbol << "\t" // << symbols[i].token << " "
           << tokentype_to_string(symbols[i].token);

      //    if(symbols[i].is_keyword)
      //       cout << " <Keyword>";
      cout << endl;
   }
}

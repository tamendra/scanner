#include "utility.h"
#include "config.h"
#include "TransitionGraph.h"
#include "SymbolTable.h"
#include "Scanner.h"

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cout << "Incorrect number of command line arguments.  Use: scan filename" << endl;
      return -1;
   }

   SymbolTable symbol_table;      // initialize the symbol table
   Scanner scanner(symbol_table); // the symbol table is used by the scanner to store keywords, identifiers and literals

   ifstream program_file;
   program_file.open(argv[1]); // open the souce file
   if (program_file.fail())
   {
      cout << "cannot open " << argv[1] << endl;
      return -1;
   }

   bool success;
   string lexeme;
   tokentype token;
   int attribute; // The attibute of the token

   cout << endl;
   cout << "\t\t\t\tAttribute" << endl;
   cout << "Lexeme \tToken\t\t\tSymbol Table Line#" << endl;
   cout << "---------------------------------------------" << endl;
   for (;;)
   {
      // Fetch the next token
      success = scanner.nextToken(program_file, lexeme, token, attribute);

      if (success)
      {
         if (token == EOSF)
         {
            cout << lexeme;
            // cout << token << " ";
            cout << "\t" << tokentype_to_string(token);
            break; // end the loop
         }
         if (token != WS)
         { // Display all tokens and their attributes except for WS
            cout << lexeme;
            // cout << token << " ";
            cout << "\t" << tokentype_to_string(token);
            if (token == ID || token == INTLITERAL || token == FLOATLITERAL)
               cout << "\t\t" << attribute;
            cout << endl;
         }
      }
      else
      { // Lexical error
         cout << "Lexical Error: " << lexeme << endl;
         break;
      }
   }

   program_file.close();

   // Print out the content of the Symbol Table
   symbol_table.print();
}

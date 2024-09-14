class SymbolTable
{
public:
   // Initialize the table to be empty
   SymbolTable();

   // Used by the scanner to install keyword during scanner initialization
   void installKeyword(string keyword, tokentype keyword_token);

   // Locate an identifier in a Symbol table.  If not found, install the identifier
   // return identifier entry index if it is an identifier
   // return keyword token if it is a keyword
   // is_keyword is an output parameter
   int installIdentifier(string identifier, tokentype id_token, bool &is_keyword);

   // Locate a literal in the Symbol Table.  If not found, install the literal in the Symbol Table
   // return literal entry index
   int installLiteral(string identifier, tokentype id_token);

   // Print the content of the Symbol Table
   void print();

private:
   // Define the struct of the table entry
   struct SymbolEntry
   {
      string symbol;   // lexeme
      bool is_keyword; // whether the entry is a keyword or not
      tokentype token; // The corresponding token for the entry
   };

   // data members
   int symbol_count;                      // Total number of entries in the table
   SymbolEntry symbols[MAX_SYMBOL_COUNT]; // An array of symbol table
};
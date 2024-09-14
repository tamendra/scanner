// The Scanner class

class Scanner
{
public:
   Scanner(SymbolTable &input_symbol_table); // The scanner takes an outside Symbol Table

   // Identify next token from the source code
   // program_file is both input and output parameter
   // Return true if a token is identified.
   //   lexeme is an output parameter
   //   token is an output parameter
   //   attribute is an output parameter
   // Return false if a lexical error is found
   //   lexeme contains the string that causes the error
   bool nextToken(ifstream &program_file, string &lexeme, tokentype &token, int &attribute);

private:
   SymbolTable &symbol_table; // Note the reference definition "&".  The Symbol Table is a reference

   TransitionGraph TG_white_space; // Transition Graph for white space
   TransitionGraph TG_relop;       // Transition Graph for relation operators
   TransitionGraph TG_id;          // Transition Graph for identifiers
   TransitionGraph TG_int;         // Transition Graph for integer literals
};

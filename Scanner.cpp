#include "utility.h"
#include "config.h"
#include "SymbolTable.h"
#include "TransitionGraph.h"
#include "Scanner.h"

// Initilizes the Scanner
// It takes an input symbol table as a reference. (Call by reference)
// It then initializes the symbol table with enties for all the keywords
// It also sets up all transition graphs needed by the scanner
Scanner::Scanner(SymbolTable &input_symbol_table) : symbol_table(input_symbol_table)
{
   // The three keywords are installed into the symbol table first
   symbol_table.installKeyword("if", IF);
   symbol_table.installKeyword("then", THEN);
   symbol_table.installKeyword("else", ELSE);

   // The four varialbes below are used to initialize the transition graphs
   TransitionGraphConfig tg_config[MAX_STATE_COUNT * MAX_CHARACTER_COUNT];
   int tg_config_count;
   AcceptingStateConfig as_config[MAX_STATE_COUNT];
   int as_config_count;

   //*** Set up the transition graph for white spaces ***

   // From state 0 to state 1 on characters <Space>, <Tab> and <Return>
   tg_config[0].start_state = 0;
   tg_config[0].end_state = 1;
   tg_config[0].chars = " \t\n\f\r\v";
   tg_config[0].start_char = 1; // range is not used here
   tg_config[0].end_char = 0;
   tg_config[0].other = false;

   // From state 1 to state 1 on characters <Space>, <Tab> and <Return>
   tg_config[1].start_state = 1;
   tg_config[1].end_state = 1;
   tg_config[1].chars = " \t\n\f\r\v";
   tg_config[1].start_char = 1; // range is not used here
   tg_config[1].end_char = 0;
   tg_config[1].other = false;

   // From state 1 to state 2 on all characters other than <Space>, <Tab> and <Return>
   tg_config[2].start_state = 1;
   tg_config[2].end_state = 2;
   tg_config[2].chars = "";     // enumeration is not used here
   tg_config[2].start_char = 1; // range is not used here
   tg_config[2].end_char = 0;
   tg_config[2].other = true;

   // A total of 3 configuration entries used in array tg_config
   tg_config_count = 3;

   // Specify the accepting state for the transition graph for white spaces
   as_config[0].state_number = 2;
   as_config[0].token = WS;             // Corresponding tokentype
   as_config[0].need_retraction = true; // unget() is needed to put the current character back to the file stream

   // A total of 1 configuration entry used in array as_config
   // It means one accepting state
   as_config_count = 1;

   // Call setGraph to set up the transition graph for white spaces using the parameters
   TG_white_space.setGraph(tg_config, tg_config_count, as_config, as_config_count);

   //*** Setup the transition graph for relation operators ***

   // From state 0 to state 1 on character '<'
   tg_config[0].start_state = 0;
   tg_config[0].end_state = 1;
   tg_config[0].chars = "<";
   tg_config[0].start_char = 1; // range is not used here
   tg_config[0].end_char = 0;
   tg_config[0].other = false;

   // From state 0 to state 5 on character '='
   tg_config[1].start_state = 0;
   tg_config[1].end_state = 5;
   tg_config[1].chars = "=";
   tg_config[1].start_char = 1; // range is not used here
   tg_config[1].end_char = 0;
   tg_config[1].other = false;

   // From state 0 to state 6 on character '>'
   tg_config[2].start_state = 0;
   tg_config[2].end_state = 6;
   tg_config[2].chars = ">";
   tg_config[2].start_char = 1; // range is not used here
   tg_config[2].end_char = 0;
   tg_config[2].other = false;

   // From state 1 to state 2 on character '='
   tg_config[3].start_state = 1;
   tg_config[3].end_state = 2;
   tg_config[3].chars = "=";
   tg_config[3].start_char = 1; // range is not used here
   tg_config[3].end_char = 0;
   tg_config[3].other = false;

   // From state 1 to state 3 on character '>'
   tg_config[4].start_state = 1;
   tg_config[4].end_state = 3;
   tg_config[4].chars = ">";
   tg_config[4].start_char = 1; // range is not used here
   tg_config[4].end_char = 0;
   tg_config[4].other = false;

   // From state 1 to state 4 on all characters other than '=' and '>'
   // Note that there are three outcoming arrows from state 1,
   // you must setup '=' and '>' before setup "others".
   // Otherwise errors may occur
   tg_config[5].start_state = 1;
   tg_config[5].end_state = 4;
   tg_config[5].chars = "";     // enumeration is not used here
   tg_config[5].start_char = 1; // range is not used here
   tg_config[5].end_char = 0;
   tg_config[5].other = true;

   // From state 6 to state 7 on character '='
   tg_config[6].start_state = 6;
   tg_config[6].end_state = 7;
   tg_config[6].chars = "=";
   tg_config[6].start_char = 1; // range is not used here
   tg_config[6].end_char = 0;
   tg_config[6].other = false;

   // From state 6 to state 8 on all characters other than '='
   // Note that there are 2 outcoming arrow from state 6,
   // you must setup '=' before setup "others".
   // Otherwise errors may occur
   tg_config[7].start_state = 6;
   tg_config[7].end_state = 8;
   tg_config[7].chars = "";     // enumeration is not used here
   tg_config[7].start_char = 1; // range is not used here
   tg_config[7].end_char = 0;
   tg_config[7].other = true;

   // A total of 8 configuration entries used in array tg_config
   tg_config_count = 8;

   // Specify the accepting state for the transition graph for relation operators
   as_config[0].state_number = 2;
   as_config[0].token = LE;              // Corresponding tokentype
   as_config[0].need_retraction = false; // unget() is not needed for this accepting state

   as_config[1].state_number = 3;
   as_config[1].token = NE;              // Corresponding tokentype
   as_config[1].need_retraction = false; // unget() is not needed for this accepting state

   as_config[2].state_number = 4;
   as_config[2].token = LT;             // Corresponding tokentype
   as_config[2].need_retraction = true; // unget() is needed to put the current character back to the file stream

   as_config[3].state_number = 5;
   as_config[3].token = EQ;              // Corresponding tokentype
   as_config[3].need_retraction = false; // unget() is not needed for this accepting state

   as_config[4].state_number = 7;
   as_config[4].token = GE;              // Corresponding tokentype
   as_config[4].need_retraction = false; // unget() is not needed for this accepting state

   as_config[5].state_number = 8;
   as_config[5].token = GT;             // Corresponding tokentype
   as_config[5].need_retraction = true; // unget() is needed to put the current character back to the file stream

   // A total of 6 configuration entry used in array as_config
   // It means 6 accepting states
   as_config_count = 6;

   // Call setGraph to set up the transition graph for relation operators using the parameters
   TG_relop.setGraph(tg_config, tg_config_count, as_config, as_config_count);

   //*** Setup the transition graph for identifiers ***

   // From state 0 to state 1 on characters 'A'-'Z'
   tg_config[0].start_state = 0;
   tg_config[0].end_state = 1;
   tg_config[0].chars = ""; // enumeration is not used here
   tg_config[0].start_char = 'A';
   tg_config[0].end_char = 'Z';
   tg_config[0].other = false;

   // From state 0 to state 1 on characters 'a'-'z'
   tg_config[1].start_state = 0;
   tg_config[1].end_state = 1;
   tg_config[1].chars = ""; // enumeration is not used here
   tg_config[1].start_char = 'a';
   tg_config[1].end_char = 'z';
   tg_config[1].other = false;

   // From state 1 to state 1 on characters 'A'-'Z'
   tg_config[2].start_state = 1;
   tg_config[2].end_state = 1;
   tg_config[2].chars = ""; // enumeration is not used here
   tg_config[2].start_char = 'A';
   tg_config[2].end_char = 'Z';
   tg_config[2].other = false;

   // From state 1 to state 1 on characters 'a'-'z'
   tg_config[3].start_state = 1;
   tg_config[3].end_state = 1;
   tg_config[3].chars = ""; // enumeration is not used here
   tg_config[3].start_char = 'a';
   tg_config[3].end_char = 'z';
   tg_config[3].other = false;

   // From state 1 to state 1 on characters '0'-'9'
   tg_config[4].start_state = 1;
   tg_config[4].end_state = 1;
   tg_config[4].chars = ""; // enumeration is not used here
   tg_config[4].start_char = '0';
   tg_config[4].end_char = '9';
   tg_config[4].other = false;

   // From state 1 to state 2 on all characters other than 'A'-'Z', 'a'-'z' and '0'-'9'
   // Note that you must setup 'A'-'Z', 'a'-'z' and '0'-'9' before setup "others".
   // Otherwise errors may occur
   tg_config[5].start_state = 1;
   tg_config[5].end_state = 2;
   tg_config[5].chars = "";     // enumeration is not used here
   tg_config[5].start_char = 1; // range is not used here
   tg_config[5].end_char = 0;
   tg_config[5].other = true;

   // A total of 6 configuration entries used in array tg_config
   tg_config_count = 6;

   // Specify the accepting state for the transition graph for identifiers
   as_config[0].state_number = 2;
   as_config[0].token = ID;             // Corresponding tokentype
   as_config[0].need_retraction = true; // unget() is needed to put the current character back to the file stream

   // A total of 1 configuration entry used in array as_config
   // It means 1 accepting state
   as_config_count = 1;

   // Call setGraph to set up the transition graph for identifiers using the parameters
   TG_id.setGraph(tg_config, tg_config_count, as_config, as_config_count);

   //*** Setup the transition graph for numbers ***

   // From state 0 to state 1 on characters '0'-'9'
   tg_config[0].start_state = 0;
   tg_config[0].end_state = 1;
   tg_config[0].chars = ""; // enumeration is not used here
   tg_config[0].start_char = '0';
   tg_config[0].end_char = '9';
   tg_config[0].other = false;

   // From state 1 to state 1 on characters '0'-'9'
   tg_config[1].start_state = 1;
   tg_config[1].end_state = 1;
   tg_config[1].chars = ""; // enumeration is not used here
   tg_config[1].start_char = '0';
   tg_config[1].end_char = '9';
   tg_config[1].other = false;

   // From state 1 to state 2 on all characters other than '0'-'9'
   // Note that you must setup '0'-'9' before setup "others".
   // Otherwise errors may occur
   tg_config[2].start_state = 1;
   tg_config[2].end_state = 2;
   tg_config[2].chars = "";     // enumeration is not used here
   tg_config[2].start_char = 1; // range is not used here
   tg_config[2].end_char = 0;
   tg_config[2].other = true;

   // A total of 3 configuration entries used in array tg_config
   tg_config_count = 3;

   // Specify the accepting state for the transition graph for integer literals
   as_config[0].state_number = 2;
   as_config[0].token = INTLITERAL;     // Corresponding tokentype
   as_config[0].need_retraction = true; // unget() is needed to put the current character back to the file stream

   // A total of 1 configuration entry used in array as_config
   // It means 1 accepting state
   as_config_count = 1;

   // Call setGraph to set up the transition graph for integer literals using the parameters
   TG_int.setGraph(tg_config, tg_config_count, as_config, as_config_count);
}

// Identify next token from the source code
// program_file is both input and output parameter
// Return true if a token is identified.
//   lexeme is an output parameter
//   token is an output parameter
//   attribute is an output parameter
// Return false if a lexical error is found
//   lexeme contains the string that causes the error
// Note that the application order of the TGs matters.  For example, we want to
// apply TG for float literal before intLiteral and period.
bool Scanner::nextToken(ifstream &program_file, string &lexeme, tokentype &token, int &attribute)
{
   // string lexeme;

   // Before matching tokens, check for the special token EOSF (eof)
   if (program_file.fail() || program_file.eof())
   {
      // EOSF found
      lexeme = "eof";
      token = EOSF;
      attribute = token;
      return true;
   }
   else
   {
      // check to see if the next char is eof
      program_file.get();
      if (program_file.fail() || program_file.eof())
      {
         // EOSF found
         lexeme = "eof";
         token = EOSF;
         attribute = token;
         return true;
      }

      // Not EOFS, so put back the char and continue on to token recognition
      program_file.unget();
   }

   // TG-based token recognition below

   // Try white space first
   if (TG_white_space.getToken(program_file, token, lexeme))
   {
      attribute = token; // The attribute for WS is set to be WS itself
      return true;
   }

   // Try relop
   if (TG_relop.getToken(program_file, token, lexeme))
   {
      attribute = token; // The attribute for a relop is set to be the relop itself
      return true;
   }

   // Try identifier
   if (TG_id.getToken(program_file, token, lexeme))
   {
      bool is_keyword;
      // Install the identifier
      attribute = symbol_table.installIdentifier(lexeme, ID, is_keyword);
      if (is_keyword)
      {                                             // A keyword
         token = static_cast<tokentype>(attribute); // The token for a keyword is itself
      }
      return true;
   }

   // Try integer literal
   if (TG_int.getToken(program_file, token, lexeme))
   {
      // Install the literal
      attribute = symbol_table.installLiteral(lexeme, INTLITERAL);
      return true;
   }

   // None of the TGs match: Lexical error
   // get the string that causes the error
   lexeme = "";
   int cnt = 0;
   while (cnt < ERROR_STR_LEN)
   {
      unsigned char c = program_file.get();
      if (program_file.fail() || program_file.eof())
         break;
      else if (isspace(c))
         break; // see a white space
      else
      {
         lexeme.append(1, c);
         ++cnt;
      }
   }
   return false;
}

// Used to setup the transition graph
// chars and start_char/end_char may be used at the same time
// Rules:
// If the length of chars is zero, chars is not used
// If end_char < start_char, then start_char/end_char is not used
// If there is an "other" transition between two states a and b, it should be put after all other trnasitions between a and b
struct TransitionGraphConfig
{
   int start_state;
   int end_state;
   string chars;             // enumerate the chars that allow a transition from start_state to end_state
   unsigned char start_char; // contains the smallest char of the range of the chars that allow a transition from start_state to end_state
   unsigned char end_char;   // contains the largest char of the range of the chars that allow a transition from start_state to end_state
   bool other;               // other is always false when chars and/or start_char/end_char is used
                             // if other is true, neither chars nor start_char/end_char is used;
                             // it indicates all characters other than those already defined for the same start state will lead a transition from start_state to end_state
};

// Used to define the accepting state of a transition graph
struct AcceptingStateConfig
{
   int state_number;     // The state number of the accepting state
   tokentype token;      // The token that correponds to the accepting state
   bool need_retraction; // Whether or not unget() is needed once this accepting state is reached
};

// TransitionGraph always assumes that the start state is 0
class TransitionGraph
{
public:
   // Setup the transition graph using TransitionGraphConfig and AcceptingStateConfig arrays
   void setGraph(TransitionGraphConfig *tg_config, int tg_config_count,
                 AcceptingStateConfig *as_config, int as_config_count);

   // Transition graph tries to identify a token that corresponds to itself
   // Method getToken keeps fetching characters from program_file
   // if an accepting state is reached, output parameters token and lexeme are set and true is returned.
   // if the failing state (-1) is reached, false is returned
   bool getToken(ifstream &program_file, tokentype &token, string &lexeme);

private:
   // Private struct used to define the states in the transition graph
   struct StateStruct
   {
      bool is_accepting_state;
      tokentype token;      // the associated token, if it is an accepting state
      bool need_retraction; // if this is an accepting state, whether or not it is necessary to put a character back to the stream (unget()) if the accepting state is reached
   };

   // data members
   int graph[MAX_STATE_COUNT][MAX_CHARACTER_COUNT]; // transition graph.  E.g., graph[2]['a'] stores the next state for state 2 and letter 'a'
   StateStruct states[MAX_STATE_COUNT];             // an array of the states in the transition graph
};
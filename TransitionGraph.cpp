#include "utility.h"
#include "config.h"
#include "TransitionGraph.h"

// Setup the transition graph using TransitionGraphConfig and AcceptingStateConfig
void TransitionGraph::setGraph(TransitionGraphConfig *tg_config, int tg_config_count, AcceptingStateConfig *as_config, int as_config_count)
{
   // initialize the graph
   // initially, every transition goes to fail
   for (int i = 0; i < MAX_STATE_COUNT; i++)
      for (int j = 0; j < MAX_CHARACTER_COUNT; j++)
         graph[i][j] = -1; // -1 is assumed to be the state number for fail.  If -1 is reached, the whole transition graph fails to match.

   // initialize the state_array
   for (int i = 0; i < MAX_STATE_COUNT; i++)
   {
      states[i].is_accepting_state = false;
      states[i].need_retraction = false;
   }

   // construct the transition graph based on the input parameter tg_config
   for (int i = 0; i < tg_config_count; i++)
      if (!tg_config[i].other)
      {                                       // not other edge
         if (tg_config[i].chars.length() > 0) // chars is used
            for (unsigned int j = 0; j < tg_config[i].chars.length(); j++)
               // setup the next state for tg_config[i].start_state and tg_config[i].chars[j]
               graph[tg_config[i].start_state][tg_config[i].chars[j]] = tg_config[i].end_state;
         for (int j = tg_config[i].start_char; j <= tg_config[i].end_char; j++)
            // start_char <= end_char.  It means start_char/end_char is used. Setup the next state for tg_config[i].start_state and j
            graph[tg_config[i].start_state][j] = tg_config[i].end_state;
      }
      else // others edge
         for (int j = 0; j < MAX_CHARACTER_COUNT; j++)
            if (graph[tg_config[i].start_state][j] == -1)
               // for all other characters, the end state is set
               graph[tg_config[i].start_state][j] = tg_config[i].end_state;

   // construct the state array
   for (int i = 0; i < as_config_count; i++)
   {
      // set state as_config[i].state_number as the accepting state
      states[as_config[i].state_number].is_accepting_state = true;
      states[as_config[i].state_number].token = as_config[i].token;
      states[as_config[i].state_number].need_retraction = as_config[i].need_retraction;
   }
}

// Transition graph tries to identify a token that corresponds to itself
// Method getToken keeps fetching characters from program_file
// if an accepting state is reached, output parameters token and lexeme are set and true is returned.
// if the failing state (-1) is reached, false is returned
bool TransitionGraph::getToken(ifstream &program_file, tokentype &token, string &lexeme)
{
   unsigned char current_char;
   int char_count = 0;    // Count how many characters have been read from program_file
                          // If the transition fails, we will know how many characters need to be returned to the file stream (retract)
   string tmp_lexeme(""); // Store the string that has been read so far

   // Starting state is always state 0
   int current_state = 0;

   while (!states[current_state].is_accepting_state)
   {                                      // accepting state not reached
      current_char = program_file.get();  // fetch next character from the souce code
      char_count++;                       // increase the char counter
      tmp_lexeme.append(1, current_char); // append the new character

      current_state = graph[current_state][current_char]; // decide the next state based on current state and current char
                                                          // next state becomes the current state
      if (current_state == -1)
      { // transition failed
         for (int i = 0; i < char_count; i++)
            program_file.unget(); // return all characters read so far back to the file stream
         return false;            // return fail info (failed match)
      }
   }

   // Getting to this line means one accepting state has been reached

   token = states[current_state].token; // output the token
   lexeme = tmp_lexeme;                 // output the lexeme
   if (states[current_state].need_retraction)
   {                                                         // need to return one character (retract)
      program_file.unget();                                  // return the most recent read character back to the file stream
      lexeme = tmp_lexeme.erase(tmp_lexeme.length() - 1, 1); // remove the last character from the lexeme before outputting it
   }
   return true; // Indicate a success match
}



#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;


void RemoveGroupsInLoop( int _iteration_direction, int _order )
 {
  string message = "\nRemove all groups using ";
  if (CFG_ITERATE_NORMAL == _iteration_direction)
   message += "forward ";
  else
   message += "reverse ";

  message += "iteration, sorting: ";

  if (CFG_SORT_ALPHABET == _order)
   message += "alphabetical\n\n";
  else
   message += "original\n\n";

  fprintf(stderr, message.c_str());

  CFG_CloseFile(0);
  static CFG_File config;
  CFG_OpenFile("test_003.cfg", &config ); 
   
  CFG_SetGroupIterationDirection( _iteration_direction );

  for ( CFG_StartGroupIteration(_order); !CFG_IsLastGroup();)
   {  
    std::string tmp = CFG_GetSelectedGroupName();
    CFG_RemoveSelectedGroup();
    fprintf(stderr, " * Removed currently selected group %s.\n", tmp.c_str());    
   }

  CFG_AUTO_TEST_INTEGER( 0, CFG_GetGroupCount() )
 }

/* --------------------------------- */

/*

 TEST 003

 Group iteration

*/

int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(003)

  CFG_File config;
 
  if ( CFG_OK != CFG_OpenFile("test_003.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }
  
  CFG_BEGIN_AUTO_TEST
  
 /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Group iteration")

  const char * Firefox = "Firefox";
  const char * Thunderbird = "Thunderbird";
  const char * Seamonkey = "Seamonkey";
  const char * Waterweasel = "Waterweasel";
  const char * Skyfrog = "Skyfrog";

  const char * expected_groups_orig_forward[] = { Firefox, Thunderbird, Seamonkey, Waterweasel, Skyfrog };
  const char * expected_groups_orig_reverse[] = { Skyfrog, Waterweasel, Seamonkey, Thunderbird, Firefox };
  const char * expected_groups_alpha_forward[] = { Firefox, Seamonkey, Skyfrog, Thunderbird, Waterweasel };
  const char * expected_groups_alpha_reverse[] = { Waterweasel, Thunderbird, Skyfrog, Seamonkey, Firefox };
  int i = 0;

  for ( CFG_StartGroupIteration(CFG_SORT_ORIGINAL); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_forward[i] )
   }

  CFG_AUTO_TEST_INTEGER( CFG_SetGroupIterationDirection(CFG_ITERATE_REVERSE), CFG_ITERATE_NORMAL );
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ORIGINAL); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_reverse[i] )
   }

  CFG_AUTO_TEST_INTEGER( CFG_SetGroupIterationDirection(CFG_ITERATE_NORMAL), CFG_ITERATE_REVERSE );
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ALPHABET); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_alpha_forward[i] )
   }

  CFG_SetGroupIterationDirection(CFG_ITERATE_REVERSE);
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ALPHABET); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_alpha_reverse[i] )
   }

  CFG_SetGroupIterationDirection(CFG_ITERATE_NORMAL);

  /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Group iteration with removal")

  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ORIGINAL); !CFG_IsLastGroup();)
   {  
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_forward[i] )      
    if (!strcmp(CFG_GetSelectedGroupName(), Seamonkey ) )
     {
      CFG_RemoveSelectedGroup();
     }
    else
      {    
       CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_forward[i] )
       CFG_SelectNextGroup();       
      }     
     ++i;            
    }     

  /*  ----------------------------------------- */

  /*

  Now reopen the file and perfrom other removal tests

  */
  CFG_CloseFile(0);
  CFG_OpenFile("test_002.cfg", &config );


  /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Remove all groups")

  RemoveGroupsInLoop(CFG_ITERATE_NORMAL, CFG_SORT_ALPHABET);
  RemoveGroupsInLoop(CFG_ITERATE_REVERSE, CFG_SORT_ALPHABET);
  RemoveGroupsInLoop(CFG_ITERATE_NORMAL, CFG_SORT_ORIGINAL);
  RemoveGroupsInLoop(CFG_ITERATE_REVERSE, CFG_SORT_ORIGINAL);
  
  /*  ----------------------------------------- */ 
   
  /* Save current state to file
  CFG_SaveFile("test_002_generated.cfg", CFG_SORT_ORIGINAL, CFG_SPACE_ENTRIES);

  Close selected file (we would pass to it 'config' variable instead of 0, if it wasn't selected) */
  CFG_CloseFile(0);

  CFG_AUTO_SUMMARY

  return 0;
 }

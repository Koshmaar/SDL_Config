

#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*  ----------------------------------------- */


/*

 TEST 005
 
 Multiple value entries

*/
int main(int argc, char **argv)
 {  
  CFG_WRITE_HEADER(005)
  CFG_File config;
  
  if ( CFG_OK != CFG_OpenFile("test_005.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  /*  ----------------------------------------- */

  CFG_AUTO_TEST_INTEGER(CFG_GetNumberOfMultiValueEntries("ints"), 5);

  CFG_SelectMultiValueEntry("ints", 0);
  CFG_AUTO_TEST_INTEGER(CFG_ReadInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), 15);

  CFG_SelectMultiValueEntry("ints", 1);
  CFG_AUTO_TEST_INTEGER(CFG_ReadInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), -23);

  CFG_AUTO_TEST_HEADER("Entry maps")

  /* now 4 legal iterations, they *should* work: we're reading value and setting new one */
  for (CFG_StartMultiValueEntryIteration("maps"); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
    {    
     std::string map_name = CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
     fprintf(stderr, "map value: %s\n", map_name.c_str());
     CFG_AUTO_TEST_INTEGER(CFG_WriteText(CFG_MULTI_VALUE_ENTRY_ITERATION, "-aaaaa-"), CFG_OK)
     CFG_AUTO_TEST_TEXT(CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "-aaaaa-");
   }
  
  CFG_AUTO_TEST_HEADER("Entry ints")

  for (CFG_StartMultiValueEntryIteration("ints"); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
    {    
     Sint32 int_value = CFG_ReadInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
     fprintf(stderr, "int value: %i\n", int_value);         
     CFG_AUTO_TEST_INTEGER(CFG_WriteInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 15), CFG_OK)
     CFG_AUTO_TEST_INTEGER(CFG_ReadInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), 15);
   }                                               
  
  CFG_AUTO_TEST_HEADER("Entry floats");

  for (CFG_StartMultiValueEntryIteration("floats"); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
    {    
     float float_value = CFG_ReadFloat(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
     fprintf(stderr, "float value: %f\n", float_value);    
     CFG_AUTO_TEST_INTEGER(CFG_WriteFloat(CFG_MULTI_VALUE_ENTRY_ITERATION, 66.6f), CFG_OK)
     CFG_AUTO_TEST_FLOAT(CFG_ReadFloat(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), 66.6f);
   }                         

  CFG_AUTO_TEST_HEADER("Entry bools");
  
  for (CFG_StartMultiValueEntryIteration("bools"); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
   {    
    CFG_Bool bool_value = CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, CFG_False);
    fprintf(stderr, "CFG_Bool value: %u\n", bool_value);
    CFG_AUTO_TEST_INTEGER(CFG_WriteBool(CFG_MULTI_VALUE_ENTRY_ITERATION, CFG_True), CFG_OK)
    CFG_AUTO_TEST_BOOL(CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), CFG_True);
   }                                  

  CFG_AUTO_TEST_HEADER("Error on purpose");

  /* we're iterating through float values and obtaining strings just to see what happens when user makes such error */
  for (CFG_StartMultiValueEntryIteration("floats"); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
   {
    std :: string map_name = CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
    fprintf(stderr, "float value read as string: %s\n", map_name.c_str());
   }
  

  CFG_AUTO_TEST_HEADER("Remove from bools2");
  CFG_AUTO_TEST_BOOL(CFG_IsEntryMultiValue("bools2"), true);
  
  /* remove from bools2 all values which will make it look like this: "bools2 =" */

  for (CFG_StartMultiValueEntryIteration("bools2"); !CFG_IsLastMultiValueEntry();)
   {
    CFG_Bool bool_value = CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, CFG_False);
    fprintf(stderr, "bools2 value going to be removed: %u - \n", bool_value);
    CFG_RemoveMultiValueEntry();    
   }
 

  CFG_AUTO_TEST_BOOL(CFG_IsEntryMultiValue("bools2"), CFG_False);


  CFG_AUTO_TEST_HEADER("Test CFG_GetEntryType"); 

  CFG_AUTO_TEST_INTEGER(CFG_GetEntryType("bools"), CFG_BOOL);
  CFG_AUTO_TEST_INTEGER(CFG_GetEntryType("ints"), CFG_INTEGER);
  CFG_AUTO_TEST_INTEGER(CFG_GetEntryType("floats"), CFG_FLOAT);
  CFG_AUTO_TEST_INTEGER(CFG_GetEntryType("maps"), CFG_TEXT);
  CFG_AUTO_TEST_INTEGER(CFG_GetEntryType("blebleble"), 0);
    
  /* let's see how it will look when saved */

  CFG_SaveFile("test_005_final.cfg", CFG_SORT_CONTENT, CFG_SPACE_ENTRIES);
  CFG_SaveFile("test_005_compressed.cfg", CFG_SORT_ORIGINAL, CFG_COMPRESS_OUTPUT);  

  CFG_CloseFile(0);
  CFG_AUTO_SUMMARY

  return 0;
 }




#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;


/*  ----------------------------------------- */

void PrintEntryInfo()
 {
   int entry_type = CFG_GetEntryType(CFG_ENTRY_ITERATION);
   
   fprintf(stderr, "%s - type: %d\n", CFG_GetSelectedEntryName(), entry_type);

   switch (entry_type)
    {
     case CFG_BOOL: 
       fprintf(stderr, "  value: %d\n", CFG_ReadBool(CFG_ENTRY_ITERATION, 0));
     break;

     case CFG_INTEGER:      
       fprintf(stderr, "  value: %d\n", CFG_ReadInt(CFG_ENTRY_ITERATION, 0));
      break;

     case CFG_FLOAT:      
       fprintf(stderr, "  value: %f\n", CFG_ReadFloat(CFG_ENTRY_ITERATION, 0));
     break;

     case CFG_TEXT:
       fprintf(stderr, "  value: %s\n", CFG_ReadText(CFG_ENTRY_ITERATION, 0));    
     break;

    };            
 }


/*  ----------------------------------------- */

/*

 TEST 004

 Entry iteration

 Appareantly ist's not very automated

*/

int main(int argc, char **argv)
 {  
  CFG_WRITE_HEADER(004)
  CFG_File config;

  if ( CFG_OK != CFG_OpenFile("test_004.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  CFG_BEGIN_AUTO_TEST

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIteration over all entries of global group\n\n");
   
  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
   {    
    PrintEntryInfo();
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIteration over all entries of group [dupa]\n\n");

  CFG_SelectGroup("dupa");
   
  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
   {    
    PrintEntryInfo();
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nRemove all floats from group [dupa]\n\n");     

  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); )
   {
    if ( CFG_FLOAT == CFG_GetEntryType(CFG_ENTRY_ITERATION))
     CFG_RemoveSelectedEntry();
    else
     {
      CFG_SelectNextEntry();
     }
   }
 

  /*  ----------------------------------------- */

  fprintf(stderr, "\nSet all integers to 666, bools to false and text to \"wyxorothyghultorotan\"\n\n");     

  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry() )
   {
    int type = CFG_GetEntryType(CFG_ENTRY_ITERATION);

    if (CFG_INTEGER == type)
     CFG_WriteInt(CFG_ENTRY_ITERATION, 666 );

    if ( CFG_BOOL == type )
     CFG_WriteBool(CFG_ENTRY_ITERATION, false );

    if ( CFG_TEXT == type)
     CFG_WriteText(CFG_ENTRY_ITERATION, "wyxorothyghultorotan" );    
   }

  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry() )
   {
    int type = CFG_GetEntryType(CFG_ENTRY_ITERATION);

    if ( CFG_INTEGER == type)
     CFG_AUTO_TEST_INTEGER( CFG_ReadInt(CFG_ENTRY_ITERATION, 0 ), 666 )

    if ( CFG_BOOL == type)
     CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_ENTRY_ITERATION, true ), false  )

    if ( CFG_TEXT == type)
     CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_ENTRY_ITERATION, "error" ), "wyxorothyghultorotan" )
    
   }


  /*  ----------------------------------------- */


  CFG_SaveFile("test_004_nofloats.cfg");

  CFG_CloseFile(0);
  CFG_AUTO_SUMMARY

  return 0;
 }

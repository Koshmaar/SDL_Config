


#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;


/*  ----------------------------------------- */

void PrintEntryInfo(bool _all_values)
 {
   int entry_type = CFG_GetEntryType(CFG_ENTRY_ITERATION);
   
   fprintf(stderr, "%s - type: %d\n", CFG_GetSelectedEntryName(), entry_type);

   switch (entry_type)
    {
     case CFG_BOOL: 

      if (!_all_values)
       fprintf(stderr, "  value: %d\n", CFG_ReadBool(CFG_ENTRY_ITERATION, 0));
      else
      for (CFG_StartMultiValueEntryIteration( CFG_GetSelectedEntryName() ); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
       {    
        bool bool_value = CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
        fprintf(stderr, "  bool value: %d\n", bool_value);
       }                                           
     break;

     case CFG_INTEGER: 
     
      if (!_all_values)
       fprintf(stderr, "  value: %d\n", CFG_ReadInt(CFG_ENTRY_ITERATION, 0));
      else
      for (CFG_StartMultiValueEntryIteration( CFG_GetSelectedEntryName() ); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
       {    
        int int_value = CFG_ReadInt(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
        fprintf(stderr, "  int value: %d\n", int_value);
       }                                  
      break;

     case CFG_FLOAT: 
      
      if (!_all_values)
       fprintf(stderr, "  value: %f\n", CFG_ReadFloat(CFG_ENTRY_ITERATION, 0));
      else
      for (CFG_StartMultiValueEntryIteration( CFG_GetSelectedEntryName() ); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
       {    
        float float_value = CFG_ReadFloat(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
        fprintf(stderr, "  float value: %f\n", float_value);
       }
     break;

     case CFG_TEXT:

      if (!_all_values)
       fprintf(stderr, "  value: %s\n", CFG_ReadText(CFG_ENTRY_ITERATION, 0));
      else
      for (CFG_StartMultiValueEntryIteration( CFG_GetSelectedEntryName() ); !CFG_IsLastMultiValueEntry(); CFG_SelectNextMultiValueEntry())
       {    
        std::string txt_value = CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0);
        fprintf(stderr, "  text value: %s\n", txt_value.c_str());
       }
      
     break;

    };            
 }


/*  ----------------------------------------- */

/*

 TEST 006

 Group, entry and multi value iterations all at once

*/

int main(int argc, char **argv)
 {  
  CFG_WRITE_HEADER(006)
  CFG_File config;

  if ( CFG_OK != CFG_OpenFile("test_006.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  CFG_BEGIN_AUTO_TEST

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIteration over all entries of global group\n\n");
   
  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
   {    
    PrintEntryInfo(false);
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIteration over all entries of group [dupa]\n\n");

  CFG_SelectGroup("dupa");
   
  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
   {    
    PrintEntryInfo(false);
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIterate over all groups and and over all entries\n");
       
  for ( CFG_StartGroupIteration(); !CFG_IsLastGroup(); CFG_SelectNextGroup())
   {
    fprintf(stderr, "\n --- \nGroup: %s\n\n", CFG_GetSelectedGroupName());
  
    for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
     {    
      PrintEntryInfo(false);
     }
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nIterate over all groups, over their entries and over all multiple values of each one of them\n");
       
  for ( CFG_StartGroupIteration(); !CFG_IsLastGroup(); CFG_SelectNextGroup())
   {
    fprintf(stderr, "\n --- \nGroup: %s\n\n", CFG_GetSelectedGroupName());
  
    for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry())
     {    
      PrintEntryInfo(true);
     }

   }
  

  /*  ----------------------------------------- */

  fprintf(stderr, "\nRemove all floats from all groups (apart global)\n\n");     

  for ( CFG_StartGroupIteration(); !CFG_IsLastGroup(); CFG_SelectNextGroup())
   {
    for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); )
     {
      if ( CFG_FLOAT == CFG_GetEntryType(CFG_ENTRY_ITERATION))
       CFG_RemoveSelectedEntry();
      else
       {
        //PrintEntryInfo(false);
        CFG_SelectNextEntry();
       }
     }
   }

  /*  ----------------------------------------- */

  fprintf(stderr, "\nSet all integers to 666, bools to false and text to \"wyxorothyghultorotan\"\n\n");     

  for ( CFG_StartGroupIteration(); !CFG_IsLastGroup(); CFG_SelectNextGroup())
   {
    for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry() )
     {
      if ( CFG_INTEGER == CFG_GetEntryType(CFG_ENTRY_ITERATION))
       CFG_WriteInt(CFG_ENTRY_ITERATION, 666 );

      if ( CFG_BOOL == CFG_GetEntryType(CFG_ENTRY_ITERATION))
       CFG_WriteBool(CFG_ENTRY_ITERATION, false );

      if ( CFG_TEXT == CFG_GetEntryType(CFG_ENTRY_ITERATION))
       CFG_WriteText(CFG_ENTRY_ITERATION, "wyxorothyghultorotan" );

      fprintf(stderr, "%s\n", CFG_GetSelectedEntryName() );
     }
   }

  /* and also global group */
  CFG_SelectGroup(0);
  for (CFG_StartEntryIteration(); !CFG_IsLastEntry(); CFG_SelectNextEntry() )
   {
    if ( CFG_INTEGER == CFG_GetEntryType(CFG_ENTRY_ITERATION))
     CFG_WriteInt(CFG_ENTRY_ITERATION, 666 );

    if ( CFG_BOOL == CFG_GetEntryType(CFG_ENTRY_ITERATION))
     CFG_WriteBool(CFG_ENTRY_ITERATION, false );

    if ( CFG_TEXT == CFG_GetEntryType(CFG_ENTRY_ITERATION))
     CFG_WriteText(CFG_ENTRY_ITERATION, "wyxorothyghultorotan" );

    fprintf(stderr, "%s\n", CFG_GetSelectedEntryName() );
   }


  CFG_SaveFile("test_006_nofloats.cfg");

  CFG_CloseFile(0);
  CFG_AUTO_SUMMARY

  return 0;
 }

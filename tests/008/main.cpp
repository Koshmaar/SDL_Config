
#include <ctime>

#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;


CFG_String GenerateRandomEntryName()
 {
  CFG_String tmp;
  
  for (int i = 0; i < (rand() % 10) + 3; ++i)
   tmp += (rand() % (128 - 35)) + 35;

  return tmp;
 }

/*  ----------------------------------------- */

/*
 TEST 008

 Stress test, profiling

*/


int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(008)
  
  SDL_Init(SDL_INIT_TIMER);  
  

  CFG_File config_syntax;

  /* ------------------------------------------------------ */

  CFG_AUTO_TEST_HEADER("Stress test")

  int result = CFG_OpenFile("test_008.cfg", &config_syntax );
  
  if ( CFG_OK != result )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }
   
  /* Save current state to file */  
  CFG_SaveFile("test_008_generated.cfg", CFG_SORT_ORIGINAL, CFG_SPACE_ENTRIES);
      
  CFG_CloseFile(&config_syntax);
    
  /* ------------------------------------------------------ */

  CFG_AUTO_TEST_HEADER("Profile speed")

  srand(time(0));
  
  CFG_File config_speed;
  
  fprintf(stderr, "\n\n");
  int profile_all = 5;
  int total_generation_time = 0;
  int total_parsing_time = 0;
  int total_saving_time = 0;
  
  for (int k = 0; k < profile_all; ++k)
   {
    if ( CFG_OK != CFG_OpenFile(0, &config_speed))    
     {
      fprintf(stderr, "Critical error: %s", CFG_GetError());
      return 1;
     }

    const int create_groups = 2000;
    const int create_booleans = 5;
    const int create_integers = 10;
    const int create_floats = 7;
    const int create_texts = 4;

    CFG_AUTO_TEST_HEADER("Iteration")
      
    Uint32 time_start = SDL_GetTicks();    

    for (int i = 0; i < create_groups; ++i)
     {
      CFG_SelectGroup( GenerateRandomEntryName().c_str(), CFG_True );

      for (int j = 0; j < create_booleans; ++j)
       {
        CFG_WriteBool( GenerateRandomEntryName().c_str(), (rand() % 100) > 50 );
       }

      for (int j = 0; j < create_integers; ++j)
       {
        CFG_WriteInt(GenerateRandomEntryName().c_str(), (rand() % 20000 ) - 5000 );
       }

      for (int j = 0; j < create_floats; ++j)
       {
        CFG_WriteFloat(GenerateRandomEntryName().c_str(), ((rand() % 20000 ) - 5000.0f) / 123.0f );
       }

      for (int j = 0; j < create_texts; ++j)
       {
        CFG_WriteText(GenerateRandomEntryName().c_str(), GenerateRandomEntryName().c_str() );
       }
     }
       
    Uint32 time_end = SDL_GetTicks();
    Uint32 time_diff = time_end - time_start;
    fprintf(stderr, "\n Generated in: %i ms\n", time_diff);    
    total_generation_time += time_diff;
 
    time_start = SDL_GetTicks();
 
    CFG_SaveFile("test_008_profile.cfg", CFG_SORT_ORIGINAL, CFG_SPACE_ENTRIES);

 
    time_end = SDL_GetTicks();
    time_diff = time_end - time_start;

    fprintf(stderr, "\n Saved in: %i ms\n", time_diff);
    total_saving_time += time_diff;

    CFG_CloseFile(0);
    
    time_start = SDL_GetTicks();

    result = CFG_OpenFile("test_008_profile.cfg", &config_speed);

    time_end = SDL_GetTicks();
    time_diff = time_end - time_start;

    fprintf(stderr, "\n Parsed in: %i ms\n", time_diff);
    total_parsing_time += time_diff;


    if ( CFG_OK != result )
     {
      fprintf(stderr, "Error: %s", CFG_GetError());
      return 1;
     }

   CFG_CloseFile(0);
   
  }
  
  CFG_AUTO_TEST_HEADER("Results")
 
  fprintf(stderr, "\n\n Total average time of generation: %i ms\n", total_generation_time / profile_all );  
  fprintf(stderr, "\n Total average time of parsing: %i ms\n", total_parsing_time / profile_all );
  fprintf(stderr, "\n Total average time of saving: %i ms\n", total_saving_time / profile_all );

  SDL_Quit();
  
  return 0;
 }

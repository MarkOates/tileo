/*

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>

#include <AllegroFlare/FontBin.hpp>

#include <string>
#include <vector>
#include <iostream>


using AllegroFlare::FontBin;


static std::string resource_path(std::vector<std::string> components, std::string filename)
{
   std::string result;

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   for (auto &component : components) al_append_path_component(path, component.c_str());

   al_set_path_filename(path, filename.c_str());
   result = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

   std::cout << result << std::endl;

   return result;
}

bool shutdown_program = false;


class ProgramRunner
{
private:
   FontBin fonts;
public:
   ProgramRunner()
      : fonts()
   {}

   void initialize()
   {
      fonts.set_path("data/fonts");
      fonts["consolas.ttf -22"];
   }

   ~ProgramRunner();

   void render()
   {
      al_clear_to_color(al_color_name("orange"));
   }
};


int main(int argc, char **argv)
{
   al_init();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60.0);
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   ProgramRunner program_runner;

   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      case ALLEGRO_EVENT_TIMER:
         program_runner.render();
         break;
      }
   }

   return 0;
}

*/



#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/BitmapBin.hpp>

#include <Tileo/TileAtlas.hpp>
#include <Tileo/TileMapMeshRenderer.hpp>

#include <string>
#include <vector>
#include <iostream>


using AllegroFlare::FontBin;
using AllegroFlare::BitmapBin;

using Tileo::TileAtlas;


bool shutdown_program = false;


class ProgramRunner
{
private:
   FontBin fonts;
   BitmapBin bitmaps;
   std::string medium_font;
   TileAtlas tile_atlas;
   TileMapMeshRenderer tile_map_renderer;

public:
   ProgramRunner()
      : fonts()
      , bitmaps()
      , medium_font("consolas.ttf 32")
      , tile_atlas()
      , tile_map_renderer()
   {}

   void initialize()
   {
      fonts.set_path("data/fonts");
      bitmaps.set_path("data/bitmaps");
      fonts[medium_font];
      bitmaps["tiles_dungeon_v1.1.png"];
   }

   void load_map()
   {
      tile_atlas.load(bitmaps["tiles_dungeon_v1.1.png"], 16, 16);
      tile_map_renderer.set_tile_atlas_bitmap(tile_atlas.get_bitmap());
   }

   ~ProgramRunner()
   {}

   void render()
   {
      al_clear_to_color(al_color_name("orange"));
      al_draw_text(fonts[medium_font], al_color_name("purple"), 200, 200, 0, "Hello World!");
      //tile_map_renderer.render(20, 20);
      al_flip_display();
   }
};


int main(int argc, char **argv)
{
   al_init();
   al_install_keyboard();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920 * 3 / 2, 1080 * 3 / 2);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60.0);
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   ProgramRunner program_runner;
   program_runner.initialize();

   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      case ALLEGRO_EVENT_KEY_DOWN:
         if (this_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) shutdown_program = true;
         break;
      case ALLEGRO_EVENT_TIMER:
         program_runner.render();
         break;
      }
   }

   return 0;
}



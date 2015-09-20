#include <pebble.h>

#define KEY_IDENTIFIER 0
#define KEY_VALUE 1

static Window *watchface_window;
static TextLayer *watchface_time_layer;
static TextLayer *watchface_status_layer;

static BitmapLayer *emoji_layer; 
static GBitmap *emoji_bitmap;

static int pending_request = 0;

static void closingBell(struct tm *current_time){
 time_t temp = time(NULL);
 current_time = localtime(&temp);
 
 if(clock_is_24h_style() == true) {
    
   if((current_time->tm_hour == 16 && current_time->tm_min == 0)){
   		static const uint32_t const segments[] = {1000, 500, 2000};
		VibePattern pat = {.durations = segments,.num_segments = ARRAY_LENGTH(segments),};
		vibes_enqueue_custom_pattern(pat);
   
   	} 
  }
}

/*To change the time*/
static void update_time() {
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  static char buffer[] = "00:00";

  if(clock_is_24h_style() == true) {
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  text_layer_set_text(watchface_time_layer, buffer);
}


/*main window load*/
static void main_window_load(Window *window) {

  window_set_background_color(watchface_window, GColorWhite); 
  
  watchface_time_layer = text_layer_create(GRect(0, 110, 144, 50));
  text_layer_set_background_color(watchface_time_layer, GColorWhite);
  
  watchface_status_layer = text_layer_create(GRect(0, 10, 144, 50));
  text_layer_set_background_color(watchface_status_layer, GColorWhite);
  
  text_layer_set_text_color(watchface_time_layer, GColorBlack);
  text_layer_set_text_color(watchface_status_layer, GColorBlack);
  
  text_layer_set_text(watchface_time_layer, "00:00");
  text_layer_set_text(watchface_status_layer, "PStock Watchface");


  text_layer_set_font(watchface_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(watchface_time_layer, GTextAlignmentCenter);
  
  text_layer_set_font(watchface_status_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(watchface_status_layer, GTextAlignmentCenter);
  
  emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TEN);
  emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  bitmap_layer_set_background_color(emoji_layer, GColorClear);
  bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  
  window_set_background_color(watchface_window, GColorWhite);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(watchface_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(watchface_status_layer));
  
  
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(emoji_layer));


  update_time();
  
}

static void main_window_unload(Window *window) {
  text_layer_destroy(watchface_time_layer);
  text_layer_destroy(watchface_status_layer);
  gbitmap_destroy(emoji_bitmap);
  bitmap_layer_destroy(emoji_layer);

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
  
	closingBell(tick_time);


	// static char identifier_buffer[32];
	// snprintf(identifier_buffer, sizeof(identifier_buffer), "%d", tick_time->tm_sec);
	// text_layer_set_text(watchface_status_layer,identifier_buffer);

  
	if(tick_time->tm_sec % 10  == 0) {
		if(pending_request == 0) {
			pending_request = 1;
			DictionaryIterator *iter;
			app_message_outbox_begin(&iter);
			dict_write_uint8(iter, 0, 1);
			app_message_outbox_send();
		}
	}


}


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char identifier_buffer[32];
  static char value_buffer[3];
  static char watchface_status_layer_buffer[32];
  
  Tuple *t = dict_read_first(iterator);

  pending_request = 0;

  while(t != NULL) {

    switch(t->key) {
    case KEY_IDENTIFIER:
      snprintf(identifier_buffer, sizeof(identifier_buffer), "%s", t->value->cstring);
    case KEY_VALUE:
      snprintf(value_buffer, sizeof(value_buffer), "%d", (int)t->value->int32);
		switch((int)t->value->int32){
			case -1:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SLEEP);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));\
  				break;
			case 0:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ZERO);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
			case 1:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ONE);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
			case 2:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TWO);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 3:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_THREE);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 4:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FOUR);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 5:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FIVE);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 6:
  				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SIX);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 7:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SEVEN);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 8:
  				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_EIGHT);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 9:
				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_NINE);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
  			case 10:
  				bitmap_layer_destroy(emoji_layer);
				emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TEN);
  				emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  				bitmap_layer_set_background_color(emoji_layer, GColorClear);
  				bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  				layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  				break;
		}
    }

    t = dict_read_next(iterator);
  }
  
  snprintf(watchface_status_layer_buffer, sizeof(watchface_status_layer_buffer), "%s", identifier_buffer);
  text_layer_set_text(watchface_status_layer,watchface_status_layer_buffer);
}


static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  bitmap_layer_destroy(emoji_layer);
  emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ERROR);
  emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  bitmap_layer_set_background_color(emoji_layer, GColorClear);
  bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  
  text_layer_set_text(watchface_status_layer, "ERROR 1");
  layer_add_child(window_get_root_layer(watchface_window), text_layer_get_layer(watchface_status_layer));

  
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  bitmap_layer_destroy(emoji_layer);
  emoji_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ERROR);
  emoji_layer = bitmap_layer_create(GRect(25, 35, 91, 69));
  bitmap_layer_set_background_color(emoji_layer, GColorClear);
  bitmap_layer_set_bitmap(emoji_layer, emoji_bitmap);
  layer_add_child(window_get_root_layer(watchface_window), bitmap_layer_get_layer(emoji_layer));
  
  text_layer_set_text(watchface_status_layer, "ERROR 2");
  layer_add_child(window_get_root_layer(watchface_window), text_layer_get_layer(watchface_status_layer));
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {}
  

static void init() {

  watchface_window = window_create();

  window_set_window_handlers(watchface_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(watchface_window, true);
  
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
}

static void deinit() {
  window_destroy(watchface_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

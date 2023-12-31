// simple native example of logging

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

// embedded file example
unsigned int embedSize = 6;
unsigned char* embedData = "hello\0";

void cart_main() {
  null0_trace("Hello from filesystem.");
  
  // here is an example of a regular read, no special permissions
  unsigned int bytesRead = 0;
  unsigned char* cyberBytes = null0_file_read("cyber.txt", &bytesRead);
  if (bytesRead != 0) {
    null0_trace("read %d bytes from cyber.txt:\n%s", bytesRead, (char*) cyberBytes);
  } else {
    null0_trace("could not read cyber.txt.");
  }

  // here is an embedded-file, also no special permissions
  printf("(cart) embedding hello.txt (%d): %s\n", embedSize, embedData);
  if (null0_file_embed("hello.txt", &embedData, embedSize)) {
    unsigned int bytesReadEmbed;
    unsigned char* embedBytes = null0_file_read("hello.txt", &bytesReadEmbed);
    printf("(cart) read hello.txt (%d): %s\n", bytesReadEmbed, (char*) embedBytes);
  } else {
    printf("(cart) hello.txt not embedded.\n");
  }
}


bool Init(pntr_app* app) {
  if (!null0_load_cart("examples/cart/c/filesystem")) {
    null0_trace("Could not load examples/cart/c/filesystem as root-filesystem!");
    null0_unload();
    return false;
  }
  
  cart_main();
  
  // exit after init
  null0_unload();
  return false;
}


pntr_app Main(int argc, char* argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .fps = 60};
}
#include <manygames/extra_exceptions.hpp>
#include <manygames/image_converter.hpp>


int main(int, char**)
{

  manygames::size_mismatch barf("nothing");
  manygames::rgbcolor<unsigned char> trash(100,100,100);

  trash = manygames::gamma_convert_color<unsigned char>(trash, 1.3);
  return 0;
}

#include <manygames/image_converter.hpp>

#include <cmath>

namespace manygames
{ 
  template<>
  extern rgbcolor<double>
  convert_color<double,unsigned char>(const rgbcolor<unsigned char>& color)
  {

    //    cout << __PRETTY_FUNCTION__ << "---1" << endl;
    const double conversion_factor = 1.0 / double((unsigned char)(-1));

    // Just perform the conversion (no clipping).
    return rgbcolor<double>(color.r() * conversion_factor,
                            color.g() * conversion_factor,
                            color.b() * conversion_factor);
  }

  template<>
  extern rgbcolor<unsigned char>
  convert_color<unsigned char,double>(const rgbcolor<double>& color)
  {
    //    cout << __PRETTY_FUNCTION__ << "---2" << endl;
    const unsigned char cf = (unsigned char)(-1);
    
    // Convert/clip it.
    return rgbcolor<unsigned char>(std::min(cf, (unsigned char)(color.r() * cf)),
                                   std::min(cf, (unsigned char)(color.g() * cf)),
                                   std::min(cf, (unsigned char)(color.b() * cf)));
  }

  template<>
  extern rgbcolor<double>
  gamma_convert_color<double,double>(const rgbcolor<double>& color, double gamma)
  {
    return rgbcolor<double>(std::pow(color.r(), gamma),
                            std::pow(color.g(), gamma),
                            std::pow(color.b(), gamma));
  }

  
} // namespace manygames  

// left: red, right: cyan
// FF0000     00FFFF

#include <iostream>
#include "lodepng.h"

int main(int argc, char **argv) {

  if (argc != 4) {
    std::cout << "Usage: anaglyph <right_image> <left_image> <output_image> \n";
    return 0;
  }

  const char* rightFilename = argv[1];
  const char* leftFilename = argv[2];
  const char* outputFilename = argv[3];

  std::vector<unsigned char> rightImage;
  unsigned rightWidth, rightHeight;

  std::vector<unsigned char> leftImage;
  unsigned leftWidth, leftHeight;

  unsigned rightError = lodepng::decode(rightImage, rightWidth, rightHeight, rightFilename);
  if(rightError) std::cout << "decoder error " << rightError << ": " << lodepng_error_text(rightError) << std::endl;
  unsigned leftError = lodepng::decode(leftImage, leftWidth, leftHeight, leftFilename);
  if(leftError) std::cout << "decoder error " << leftError << ": " << lodepng_error_text(leftError) << std::endl;

  std::vector<unsigned char> newImage;
  newImage.assign(rightImage.size(), 0);

  for (unsigned i = 0; i < rightImage.size(); i+= 4) {
    newImage[i] = rightImage[i];
    newImage[i+1] = leftImage[i+1];
    newImage[i+2] = leftImage[i+2];
    newImage[i+3] = leftImage[i+3]; //Assuming images have same alpha
  }

  unsigned newImageError = lodepng::encode(outputFilename, newImage, rightWidth, rightHeight);

  if(newImageError) std::cout << "encoder error " << newImageError << ": "<< lodepng_error_text(newImageError) << std::endl;

  return 0;

}


#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/functions.h"

int main()
{
    bool isWhiteDominant = false;
    char characterChosen;

    sf::Image image = readInImage(listUsableImages());

    do
    {
        
        std::cout << "Is the picture chosen white or black dominant? (W / B): " << std::endl;
        std::cin >> characterChosen;

        if (characterChosen == 'W')
        {
            isWhiteDominant == true;
        }
        else
        {
            isWhiteDominant = false;
        }
    } while (characterChosen != 'W' && characterChosen != 'B');

    resizeImage(image);

    char asciiArr[30] = { 'N','@','#','W','$','9','8','7','6','5','4','3','2','2','1','0','?','!','a','b','c',';',':','+','=','-',',','.','_',' ' };

    //chars to match brightness to
    std::string shorter = " .'`^,:;Il!i><~+_-?][}{1)(|/";
    std::string asciiChars = " .'`^,:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    std::string asciiReversed = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^ `'. ";
    //get a pointer to the array of pixels

    //get size of image
    sf::Vector2u imageSize = image.getSize();

    //iterate over y pixels
    for (int y = 0; y < imageSize.y; y++)
    {
        //iterate over x pixels
        for (int x = 0; x < imageSize.x; x++)
        {

            //get color at x and y
            sf::Color color = image.getPixel(x, y);

            //get brightness of that color and match it to ascii value
            int asciiIndex  = matchBrightnessToASCII(getBrightnessValue(color));

            //output the corresponding ascii value
            if (isWhiteDominant)
            {
                std::cout << asciiReversed[asciiIndex];
            }
            else
            {
                std::cout << shorter[asciiIndex];
            }

        }

        //end line after x pixels has finished
        std::cout << std::endl;

    }

}


   
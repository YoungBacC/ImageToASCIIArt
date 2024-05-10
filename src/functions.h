#pragma once

#include<iostream>
#include<filesystem>
#include<vector>
#include<SFML/System.hpp>
#include<exception>

//function declarations
std::string listUsableImages();
std::string promptForImageName(const std::vector<std::string>& vec);
sf::Image readInImage(std::string fileName);
void convertImageToGrayScale(sf::Image);
int matchBrightnessToASCII(sf::Uint8 brightness);
void resizeImage(sf::Image& image);

//summary: lists the usable image filenames
std::string listUsableImages()
{
	//images vector
	std::vector<std::string> images;

	//relative path to image directory
	std::string pathDir = "../../../../images";

	std::cout << "Available images" << std::endl;
	std::cout << "---------------------------" << "\n";

	//range based for-loop to iterate over the files in the filesystem
	for (const auto& i : std::filesystem::directory_iterator(pathDir))
	{
		//cout the filenames
		std::cout << i.path().filename().string() << std::endl;

		//put the file names into images vector
		images.push_back(i.path().filename().string());
	}
	std::cout << std::endl;

	//prompt user to enter and image
	return promptForImageName(images);
}

std::string promptForImageName(const std::vector<std::string>& vec)
{
	//file name variable to store file name
	std::string fileName;

	//do while loop
	do
	{
		std::cout << "Please enter the image name you want to use" << std::endl;

		std::cin >> fileName;

	} while (std::count(vec.begin(), vec.end(), fileName) != 1); //check if value is in images vector

	//return the file name
	return fileName;
}

//summary: read an image into the sfml system
sf::Image readInImage(std::string fileName)
{
	//create image variable
	sf::Image imageChosen;
	
	//read in stream from file
	sf::FileInputStream stream;
	stream.open("../../../../images/" + fileName);

	//check if file was opened properly and load image from stream
	if (!imageChosen.loadFromStream(stream))
	{
		throw std::invalid_argument("could not load file");
	}
	else
	{
		std::cout << fileName << " loaded successfully" << std::endl;
	}
	
	//return the image
	return imageChosen;
}

void getBrightnessValue(sf::Image image)
{
	char asciiArr[30] = { 'Ñ','@','#','W','$','9','8','7','6','5','4','3','2','2','1','0','?','!','a','b','c',';',':','+','=','-',',','.','_',' ' };

	//get a pointer to the array of pixels
	const sf::Uint8* pixels = image.getPixelsPtr();
	sf::Vector2u imageSize = image.getSize();

	sf::Uint8 red;
	sf::Uint8 green;
	sf::Uint8 blue;
	sf::Uint8 alpha;

	for (int j = 0; j < imageSize.y; j++)
	{
		for (int j = 0; j < imageSize.y; j++)
		{
			red = pixels[4 * j];
			green = pixels[4 * j + 1];
			blue = pixels[4 * j + 2];
			alpha = pixels[4 * j + 3];

			//calculate brightness
			sf::Uint8 brightness = (red + green + blue)/3;

			std::cout << asciiArr[unsigned(matchBrightnessToASCII(brightness))];
		}

		std::cout << std::endl;
	}
}

int matchBrightnessToASCII(sf::Uint8 brightness)
{
	int value = (brightness / 255) * 30;

	return value;
}

void resizeImage(sf::Image& image)
{
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	// Calculate scaling factors
	float scaleX = static_cast<float>(100) / image.getSize().x;
	float scaleY = static_cast<float>(100) / image.getSize().y;

	// Create a render texture
	sf::RenderTexture render;
	render.create(100, 100);

	// Clear render texture
	render.clear(sf::Color::Transparent);

	// Set the scale of the sprite to perform the resizing
	sprite.setScale(sf::Vector2f(scaleX, scaleY));

	// Draw the resized sprite onto the render texture
	render.draw(sprite);

	// End drawing to the render texture
	render.display();

	// Retrieve the resized image from the render texture
	image = render.getTexture().copyToImage();;
}


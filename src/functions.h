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
int matchBrightnessToASCII(int brightness);
void resizeImage(sf::Image& image);
double getBrightnessValue(const sf::Color& color);

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

double getBrightnessValue(const sf::Color& color)
{
	//get average of RGB to get brightness
	double brightness = (double(color.r) + double(color.b) + double(color.g)) / 3.0;
	return brightness;
}

int matchBrightnessToASCII(int brightness)
{
	//calculate brightness with linear interpolation
	double value = (brightness / 255.0) * 20.0;

	//convert to interger value
	int newValue = std::floor(value);

	return newValue;
}

void resizeImage(sf::Image& image)
{
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	// Calculate scaling factors
	float scaleX = static_cast<float>(500) / image.getSize().x;
	float scaleY = static_cast<float>(250) / image.getSize().y;

	// Create a render texture
	sf::RenderTexture render;
	render.create(500, 250);

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


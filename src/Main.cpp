#include "Platform/Platform.hpp"
sf::RenderWindow window;
float x = 0, y = 0, z = 0, fpang = 0;
float playerHeight = 50;
bool drawLine(float x1, float y1, float x2, float y2);
void draw3dLine(float x1, float y1, float z1, float x2, float y2, float z2);
void drawPrism(float prX, float prY, float prZ, float prW, float prH, float prL);
void ctxDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void draw3dQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
void fillPrism(float prX, float prY, float prZ, float prW, float prH, float prL);
void fpDrawPillar(float prX, float prY, float prZ, float prW, float prH, float prL);
bool drawLine(float x1, float y1, float x2, float y2)
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	window.draw(line, 2, sf::Lines);
	return 1;
}
void draw3dLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float centerOfScreenX = 1024 / 2;
	float centerOfScreenY = 512 / 2;

	float x1Diff = x1 - x;
	float y1Diff = y1 - y;
	float z1Diff = z1 - z;
	float x2Diff = x2 - x;
	float y2Diff = y2 - y;
	float z2Diff = z2 - z;

	float translatedX1 = x1Diff * cos(-fpang) + z1Diff * sin(-fpang);
	float translatedZ1 = z1Diff * cos(-fpang) - x1Diff * sin(-fpang);
	float translatedX2 = x2Diff * cos(-fpang) + z2Diff * sin(-fpang);
	float translatedZ2 = z2Diff * cos(-fpang) - x2Diff * sin(-fpang);

	if (translatedZ1 < 0 || translatedZ2 < 0)
	{
		return;
	}

	float screenDistance = 400;

	float dispX1 = (translatedX1 / translatedZ1) * screenDistance + centerOfScreenX;
	float dispY1 = (y1Diff / translatedZ1) * screenDistance + centerOfScreenY;
	float dispX2 = (translatedX2 / translatedZ2) * screenDistance + centerOfScreenX;
	float dispY2 = (y2Diff / translatedZ2) * screenDistance + centerOfScreenY;

	drawLine(dispX1, dispY1, dispX2, dispY2);
}
void drawPrism(float prX, float prY, float prZ, float prW, float prH, float prL)
{
	draw3dLine(prX, prY, prZ, prX, prY, prZ + prL);
	draw3dLine(prX, prY, prZ, prX, prY + prH, prZ);
	draw3dLine(prX, prY + prH, prZ, prX, prY + prH, prZ + prL);
	draw3dLine(prX, prY, prZ + prL, prX, prY + prH, prZ + prL);

	draw3dLine(prX + prW, prY, prZ, prX + prW, prY, prZ + prL);
	draw3dLine(prX + prW, prY, prZ, prX + prW, prY + prH, prZ);
	draw3dLine(prX + prW, prY + prH, prZ, prX + prW, prY + prH, prZ + prL);
	draw3dLine(prX + prW, prY, prZ + prL, prX + prW, prY + prH, prZ + prL);

	draw3dLine(prX, prY, prZ, prX + prW, prY, prZ);
	draw3dLine(prX, prY + prH, prZ, prX + prW, prY + prH, prZ);
	draw3dLine(prX, prY, prZ + prL, prX + prW, prY, prZ + prL);
	draw3dLine(prX, prY + prH, prZ + prL, prX + prW, prY + prH, prZ + prL);
}
void ctxDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	sf::Vertex quad[] = {
		sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
		sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Green),
		sf::Vertex(sf::Vector2f(x3, y3), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(x4, y4), sf::Color::Magenta),
	};
	window.draw(quad, 4, sf::Quads);
}
void draw3dQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	float centerOfScreenX = 1024 / 2;
	float centerOfScreenY = 512 / 2;

	float x1Diff = x1 - x;
	float y1Diff = y1 - y;
	float z1Diff = z1 - z;
	float x2Diff = x2 - x;
	float y2Diff = y2 - y;
	float z2Diff = z2 - z;
	float x3Diff = x3 - x;
	float y3Diff = y3 - y;
	float z3Diff = z3 - z;
	float x4Diff = x4 - x;
	float y4Diff = y4 - y;
	float z4Diff = z4 - z;

	float translatedX1 = x1Diff * cos(-fpang) + z1Diff * sin(-fpang);
	float translatedZ1 = z1Diff * cos(-fpang) - x1Diff * sin(-fpang);
	float translatedX2 = x2Diff * cos(-fpang) + z2Diff * sin(-fpang);
	float translatedZ2 = z2Diff * cos(-fpang) - x2Diff * sin(-fpang);
	float translatedX3 = x3Diff * cos(-fpang) + z3Diff * sin(-fpang);
	float translatedZ3 = z3Diff * cos(-fpang) - x3Diff * sin(-fpang);
	float translatedX4 = x4Diff * cos(-fpang) + z4Diff * sin(-fpang);
	float translatedZ4 = z4Diff * cos(-fpang) - x4Diff * sin(-fpang);

	if (translatedZ1 < 0 || translatedZ2 < 0 || translatedZ3 < 0 || translatedZ4 < 0)
	{
		return;
	}

	float screenDistance = 400;

	float dispX1 = (translatedX1 / translatedZ1) * screenDistance + centerOfScreenX;
	float dispY1 = (y1Diff / translatedZ1) * screenDistance + centerOfScreenY;
	float dispX2 = (translatedX2 / translatedZ2) * screenDistance + centerOfScreenX;
	float dispY2 = (y2Diff / translatedZ2) * screenDistance + centerOfScreenY;

	float dispX3 = (translatedX3 / translatedZ3) * screenDistance + centerOfScreenX;
	float dispY3 = (y3Diff / translatedZ3) * screenDistance + centerOfScreenY;
	float dispX4 = (translatedX4 / translatedZ4) * screenDistance + centerOfScreenX;
	float dispY4 = (y4Diff / translatedZ4) * screenDistance + centerOfScreenY;
	std::vector<float> quadsToDraw = { dispX1, dispY1, dispX2, dispY2, dispX3, dispY3, dispX4, dispY4 };
	//quadsToDraw, quadsToDraw + 8, (int* a, int* b) { return b[8] - a[8]; }
	std::stable_sort(quadsToDraw.begin(), quadsToDraw.end());
	ctxDrawQuad(quadsToDraw[0], quadsToDraw[1], quadsToDraw[2], quadsToDraw[3], quadsToDraw[4], quadsToDraw[5], quadsToDraw[6], quadsToDraw[7]);
}
void fillPrism(float prX, float prY, float prZ, float prW, float prH, float prL)
{
	draw3dQuad(prX, prY, prZ, prX, prY, prZ + prL, prX + prW, prY, prZ + prL, prX + prW, prY, prZ);
	draw3dQuad(prX, prY, prZ, prX, prY, prZ + prL, prX, prY + prH, prZ + prL, prX, prY + prH, prZ);
	draw3dQuad(prX, prY, prZ, prX, prY + prH, prZ, prX + prW, prY + prH, prZ, prX + prW, prY, prZ);

	draw3dQuad(prX + prW, prY + prH, prZ + prL, prX + prW, prY + prH, prZ, prX + prW, prY, prZ, prX + prW, prY, prZ + prL);
	draw3dQuad(prX + prW, prY + prH, prZ + prL, prX + prW, prY + prH, prZ, prX, prY + prH, prZ, prX, prY + prH, prZ + prL);
	draw3dQuad(prX + prW, prY + prH, prZ + prL, prX + prW, prY, prZ + prL, prX, prY, prZ + prL, prX, prY + prH, prZ + prL);
}
void fpDrawPillar(float prX, float prY, float prZ, float prW, float prH, float prL)
{
	float propEnds = 0.03;
	float propIn = 0.66;
	prY = playerHeight - prH - prY;
	drawPrism(prX, prY, prZ, prW, prH * propEnds, prL);
	drawPrism(prX + prW * (1 - propIn) / 2, prY + prH * propEnds, prZ + prL * (1 - propIn) / 2, prW * propIn, prH - prH * propEnds, prL * propIn);
	drawPrism(prX, prY + prH - prH * propEnds, prZ, prW, prH * propEnds, prL);
	fillPrism(prX + prW * (1 - propIn) / 2, prY + prH * propEnds, prZ + prL * (1 - propIn) / 2, prW * propIn, prH - prH * propEnds, prL * propIn);
	fillPrism(prX, prY, prZ, prW, prH * propEnds, prL);
	fillPrism(prX, prY + prH - prH * propEnds, prZ, prW, prH * propEnds, prL);
}
int main()
{
	window.create(sf::VideoMode(1024, 512), "Game");
	sf::Event event;
	sf::RectangleShape center(sf::Vector2f(0, 0));
	center.setSize(sf::Vector2f(20, 20));
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			x += sin(fpang) * 5;
			z += cos(fpang) * 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			x -= sin(fpang) * 5;
			z -= cos(fpang) * 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			x += cos(fpang) * 5;
			z -= sin(fpang) * 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			x -= cos(fpang) * 5;
			z += sin(fpang) * 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			playerHeight += 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			playerHeight -= 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			fpang += 0.03f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			fpang -= 0.03f;
		}
		//ctx.fillRect(390, 290, 20, 20);
		//fillPrism(0, 0, 0, 50, 50, 50); // Tetromino
		//fillPrism(0, 50, 0, 50, 50, 50);
		//fillPrism(0, 100, 0, 50, 50, 50);
		//fillPrism(0, 0, 50, 50, 50, 50);
		//ctxDrawQuad(0,0,50,50,60,60,80,80);
		//drawPrism(0, 0, 0, 150, 25, 50);
		//fillPrism(0, 0, 0, 150, 25, 50);
		for (float i = 0; i < 50; i++)
		{
			fpDrawPillar(550, 0, 200 + 400 * i, 50, 300, 50);
			fpDrawPillar(200, 0, 200 + 400 * i, 50, 300, 50);
			fpDrawPillar(550, 360, 200 + 400 * i, 50, 300, 50);
			fpDrawPillar(200, 360, 200 + 400 * i, 50, 300, 50);
		}
		window.draw(center);
		window.display();
	}
}
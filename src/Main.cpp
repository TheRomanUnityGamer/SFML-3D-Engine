#include "Platform/Platform.hpp"
sf::RenderWindow window;
float x = 0, y = 0, z = 0, fov = 90, fpang = 0, fpYang = 0;
float velX = 0, velY = 0, velZ = 0;
int lvlV = 0;
bool doDraw = true;
sf::Color fillStyle;
std::vector<std::vector<float>> quadsToDraw;
float playerHeight = 100;
sf::Mouse mouse;
sf::Texture texture;
sf::RenderStates state;

struct vec3
{
	float x,y,z;
};

struct Model
{
	vec3 position;
	vec3 scale;
	char name[64];
};

void WriteToVec3(vec3 vector3, float x,float y,float z);
void WriteToVec3(vec3 vector3, float x,float y,float z)
{
	vector3.x = x;
	vector3.y = y;
	vector3.z = z;
	vector3 = vector3;
}

void LoadModel(Model mdl);
void LoadModel(Model mdl)
{
	std::string line;
	char* endPtr;
	std::ifstream file(mdl.name);
	if(file.is_open())
	{
		while(getline(file,line))
		{
			vec3 arg1;
			vec3 arg2;
			arg1.x = strtof(line,&endPtr,16);
			arg1.y = strtof(line,&endPtr,16);
			arg1.z = strtof(line,&endPtr,16);
			arg2.x = strtof(line,&endPtr,16);
			arg2.y = strtof(line,&endPtr,16);
			arg2.z = strtof(line,&endPtr,16);
			mdl.position = arg1;
			mdl.scale = arg2;
		}
		file.close();
	}
	std::cin.get();
}

void renderQuads();
bool collision3d(float x, float y, float z, float width, float height, float length, float x1, float y1, float z1, float width1, float height1, float length1);
bool collision3d(float x, float y, float z, float width, float height, float length, float x1, float y1, float z1, float width1, float height1, float length1)
{
	bool colX = x + width >= x1 && x1 + width1 >= x;
	bool colY = y + height >= y1 && y1 + height1 >= y;
	bool colZ = z + length >= z1 && z1 + length1 >= z;
	return colX && colY && colZ;
}

bool drawLine(float x1, float y1, float x2, float y2);
void draw3dLine(float x1, float y1, float z1, float x2, float y2, float z2);
void drawPrism(float prX, float prY, float prZ, float prW, float prH, float prL);
void ctxDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void draw3dQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
void fillPrism(float prX, float prY, float prZ, float prW, float prH, float prL);
void fpDrawPillar(float prX, float prY, float prZ, float prW, float prH, float prL);
float dist3d(float x1, float y1, float z1, float x2, float y2, float z2);
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
	float midTransZ1 = z1Diff * cos(-fpang) - x1Diff * sin(-fpang);
	float translatedY1 = y1Diff * cos(fpYang) + midTransZ1 * sin(-fpYang);
	float translatedZ1 = midTransZ1 * cos(-fpYang) - y1Diff * sin(-fpYang);
	float midTransZ2 = z2Diff * cos(-fpang) - x2Diff * sin(-fpang);
	float translatedX2 = x2Diff * cos(-fpang) + z2Diff * sin(-fpang);
	float translatedY2 = y2Diff * cos(fpYang) + midTransZ2 * sin(-fpYang);
	float translatedZ2 = midTransZ2 * cos(-fpYang) - y2Diff * sin(-fpYang);

	float dist = -100;

	float screenDistance = 310 + fov;

	float dispX1 = (translatedX1 / translatedZ1) * screenDistance + centerOfScreenX;
	float dispY1 = (translatedY1 / translatedZ1) * screenDistance + centerOfScreenY;
	float dispX2 = (translatedX2 / translatedZ2) * screenDistance + centerOfScreenX;
	float dispY2 = (translatedY2 / translatedZ2) * screenDistance + centerOfScreenY;

	if (translatedZ1 <= 0)
	{
		dispX1 = dispX1 * dist;
		dispY1 = dispY1 * dist;
	}
	if (translatedZ2 <= 0)
	{
		dispX2 = dispX2 * dist;
		dispY2 = dispY2 * dist;
	}

	drawLine(dispX1, dispY1, dispX2, dispY2);
}
void drawPrism(float prX, float prY, float prZ, float prW, float prH, float prL)
{
	prY = playerHeight - prH - prY;
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
		sf::Vertex(sf::Vector2f(x1, y1), fillStyle, sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2), fillStyle, sf::Vector2f(x2, y2)),
		sf::Vertex(sf::Vector2f(x3, y3), fillStyle, sf::Vector2f(x3, y3)),
		sf::Vertex(sf::Vector2f(x4, y4), fillStyle, sf::Vector2f(x4, y4)),
	};
	window.draw(quad, 4, sf::Quads, state);
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

	float midTransZ1 = z1Diff * cos(-fpang) - x1Diff * sin(-fpang);
	float midTransZ2 = z2Diff * cos(-fpang) - x2Diff * sin(-fpang);
	float midTransZ3 = z3Diff * cos(-fpang) - x3Diff * sin(-fpang);
	float midTransZ4 = z4Diff * cos(-fpang) - x4Diff * sin(-fpang);

	float translatedX1 = x1Diff * cos(-fpang) + z1Diff * sin(-fpang);
	float translatedY1 = y1Diff * cos(fpYang) + midTransZ1 * sin(-fpYang);
	float translatedZ1 = midTransZ1 * cos(-fpYang) - y1Diff * sin(-fpYang);
	float translatedX2 = x2Diff * cos(-fpang) + z2Diff * sin(-fpang);
	float translatedY2 = y2Diff * cos(fpYang) + midTransZ2 * sin(-fpYang);
	float translatedZ2 = midTransZ2 * cos(-fpYang) - y2Diff * sin(-fpYang);
	float translatedX3 = x3Diff * cos(-fpang) + z3Diff * sin(-fpang);
	float translatedY3 = y3Diff * cos(fpYang) + midTransZ3 * sin(-fpYang);
	float translatedZ3 = midTransZ3 * cos(-fpYang) - y3Diff * sin(-fpYang);
	float translatedX4 = x4Diff * cos(-fpang) + z4Diff * sin(-fpang);
	float translatedY4 = y4Diff * cos(fpYang) + midTransZ4 * sin(-fpYang);
	float translatedZ4 = midTransZ4 * cos(-fpYang) - y4Diff * sin(-fpYang);

	float screenDistance = 310 + fov;

	float dispX1 = (translatedX1 / translatedZ1) * screenDistance + centerOfScreenX;
	float dispY1 = (translatedY1 / translatedZ1) * screenDistance + centerOfScreenY;
	float dispX2 = (translatedX2 / translatedZ2) * screenDistance + centerOfScreenX;
	float dispY2 = (translatedY2 / translatedZ2) * screenDistance + centerOfScreenY;

	float dispX3 = (translatedX3 / translatedZ3) * screenDistance + centerOfScreenX;
	float dispY3 = (translatedY3 / translatedZ3) * screenDistance + centerOfScreenY;
	float dispX4 = (translatedX4 / translatedZ4) * screenDistance + centerOfScreenX;
	float dispY4 = (translatedY4 / translatedZ4) * screenDistance + centerOfScreenY;
	
	float dist = -100;
	
	if(translatedZ1 < 0 || translatedZ2 < 0 || translatedZ3 < 0 || translatedZ4 < 0)
	{
		if(lvlV == 2)
		{
			return;
		}
	}
	
	if (translatedZ1 <= 0 && lvlV != 2)
	{
		dispX1 = dispX1 * dist;
		dispY1 = dispY1 * dist;
	}

	if (translatedZ2 <= 0 && lvlV != 2)
	{
		dispX2 = dispX2 * dist;
		dispY2 = dispY2 * dist;
	}

	if (translatedZ3 <= 0 && lvlV != 2)
	{
		dispX3 = dispX3 * dist;
		dispY3 = dispY3 * dist;
	}

	if (translatedZ4 <= 0 && lvlV != 2)
	{
		dispX4 = dispX4 * dist;
		dispY4 = dispY4 * dist;
	}

	if (doDraw)
	{
		float avgTZ = (translatedZ1 + translatedZ2 + translatedZ3 + translatedZ4) / 4;
		quadsToDraw.push_back({ dispX1, dispY1, dispX2, dispY2, dispX3, dispY3, dispX4, dispY4, avgTZ });
	}
}
void fillPrism(float prX, float prY, float prZ, float prW, float prH, float prL)
{
	prY = playerHeight - prH - prY;
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
	//prY = playerHeight - prH - prY;
	drawPrism(prX, prY, prZ, prW, prH * propEnds, prL);
	drawPrism(prX + prW * (1 - propIn) / 2, prY + prH * propEnds, prZ + prL * (1 - propIn) / 2, prW * propIn, prH - prH * propEnds, prL * propIn);
	drawPrism(prX, prY + prH - prH * propEnds, prZ, prW, prH * propEnds, prL);
	fillPrism(prX + prW * (1 - propIn) / 2, prY + prH * propEnds, prZ + prL * (1 - propIn) / 2, prW * propIn, prH - prH * propEnds, prL * propIn);
	fillPrism(prX, prY, prZ, prW, prH * propEnds, prL);
	fillPrism(prX, prY + prH - prH * propEnds, prZ, prW, prH * propEnds, prL);
}
float dist3d(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2) * 1);
}

void sortquads();
void sortquads()
{
	std::sort(quadsToDraw.begin(), quadsToDraw.end(), [](const std::vector<float>& a, const std::vector<float>& b) {
		return a[2] < b[2];
	});
}

void renderQuads()
{
	for (float i = 0; i < quadsToDraw.size(); i++)
	{
		ctxDrawQuad(quadsToDraw[i][0], quadsToDraw[i][1], quadsToDraw[i][2], quadsToDraw[i][3], quadsToDraw[i][4], quadsToDraw[i][5], quadsToDraw[i][6], quadsToDraw[i][7]);
	}
}
void Inputs();
void Inputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velX = sin(fpang) * 5;
		velZ = cos(fpang) * 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velX = -sin(fpang) * 5;
		velZ = -cos(fpang) * 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velX = cos(fpang) * 5;
		velZ = -sin(fpang) * 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velX = -cos(fpang) * 5;
		velZ = sin(fpang) * 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		playerHeight += 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		playerHeight -= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		fpYang -= 0.03f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		fpYang += 0.03f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		fpang += 0.03f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		fpang -= 0.03f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		doDraw = !doDraw;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		lvlV = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		lvlV = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		lvlV = 2;
	}
	x = x + velX;
	playerHeight = playerHeight + velY;
	z = z + velZ;
	velX = 0;
	velY = 0;
	velZ = 0;
}
void Renderer();
void Renderer()
{
	if (lvlV == 0) // Pillars
	{
		for (int i = 0; i < 8; i++)
		{
			fillStyle = sf::Color::Red;
			fpDrawPillar(550, 0, 200 + 400 * i, 50, 300, 50);
			fpDrawPillar(200, 0, 200 + 400 * i, 50, 300, 50);

			fillStyle = sf::Color::Red;
			fpDrawPillar(550, 800, 200 + 400 * i, 50, 300, 50);
			fpDrawPillar(200, 800, 200 + 400 * i, 50, 300, 50);
		}
		sortquads();
		renderQuads();
		quadsToDraw.clear();
	}
	if (lvlV == 1) // Tetromino
	{
		fillStyle = sf::Color::Red;
		fillPrism(0, 0, 0, 50, 50, 50);
		fillPrism(0, 50, 0, 50, 50, 50);
		fillPrism(0, 100, 0, 50, 50, 50);
		fillPrism(0, 0, 50, 50, 50, 50);
		sortquads();
		renderQuads();
		quadsToDraw.clear();
	}
	if (lvlV == 2) // A Room
	{
		drawPrism(0,0,0,500,500,2);
		drawPrism(0,0,0,2,500,500);
		drawPrism(500,0,0,2,500,500);
		drawPrism(0,0,500,500,500,2);
		drawPrism(0,500,0,500,2,500);
		fillPrism(0,0,0,500,500,2);
		fillPrism(0,0,0,2,500,500);
		fillPrism(500,0,0,2,500,500);
		fillPrism(0,0,500,500,500,2);
		fillPrism(0,500,0,500,2,500);
		sortquads();
		renderQuads();
		quadsToDraw.clear();
	}
}
int main()
{
	window.create(sf::VideoMode(1024, 512), "3D Engine");
	sf::Event event;
	sf::RectangleShape center(sf::Vector2f(5, 5));
	texture.loadFromFile("content/sfml.png");
	center.setPosition(sf::Vector2f(1024 / 2, 512 / 2));
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		Inputs();
		Renderer();
		window.draw(center);
		window.display();
	}
}
#include "MorphRenderer.h"
#include "VertexArrayObject.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

syre::MorphRenderer::MorphRenderer()
{
	vao = VertexArrayObject::Create();
}

void syre::MorphRenderer::AddFrame(std::string fileName)
{
	std::vector<float> combinedVertBuffer;
	std::vector<glm::vec3> vertPos;
	std::vector<unsigned int> indexedVertices;
	std::vector<glm::vec2> vertUVs;
	std::vector<glm::vec3> vertNormals;

	//unordered map was based on content from cgtutorials;
	std::unordered_map<uint64_t, uint32_t> indexMap;

	if (fileName.substr(fileName.size() - 4, 4) == ".obj")
	{
		std::ifstream objToLoad;
		std::string curLine;
		objToLoad.open(fileName, std::ios::in);
		if (objToLoad)
		{
			while (std::getline(objToLoad, curLine))
			{
				if (curLine.at(0) == 'v')
				{
					switch (curLine.at(1))
					{
					case ' ':
						//printf("found vertex line\n");
						vertPos.push_back(Vector3Parser(curLine, 2));

						break;
					case 't':
						//printf("found uv coord line\n");
						vertUVs.push_back(Vector2Parser(curLine, 3));
						break;
					case 'n':
						//printf("found normal line\n");
						vertNormals.push_back(Vector3Parser(curLine, 3));
						break;
					}
				}
				else if (curLine.at(0) == 'f')
				{

					//printf("found face line\n");
					//Section below is heavily based on code from CG tutorials, this was necessary as my original mesh loading did not account for normals and uvs, I ran into a bit of a problem
					//when i realized opengl did not support multiple indexbuffer like .obj files do. The key difference is that i did not use the mesh builder class.
					glm::ivec3 vertexIndices;
					char tempChar;
					trim(curLine);
					std::stringstream stream = std::stringstream(curLine);
					stream >> tempChar;

					uint32_t edges[4];

					int i = 0;
					for (; i < 4; i++)
					{
						if (stream.peek() != EOF)
						{
							char tempChar;
							vertexIndices = glm::ivec3(0, 0, 0);
							stream >> vertexIndices.x >> tempChar >> vertexIndices.y >> tempChar >> vertexIndices.z;

							const uint64_t mask = 0b0'000000000000000000000'000000000000000000000'111111111111111111111;
							uint64_t key = ((vertexIndices.x & mask) << 42) | ((vertexIndices.y & mask) << 21) | (vertexIndices.z & mask);

							auto it = indexMap.find(key);

							if (it != indexMap.end()) {
								edges[i] = it->second;
							}
							else {
								// Construct a new vertex using the indices for the vertex


								combinedVertBuffer.push_back(vertPos[vertexIndices.x - 1].x); // where i got the error
								combinedVertBuffer.push_back(vertPos[vertexIndices.x - 1].y);
								combinedVertBuffer.push_back(vertPos[vertexIndices.x - 1].z);
								combinedVertBuffer.push_back(vertexIndices.y != 0 ? vertUVs[vertexIndices.y - 1].x : 0.0f);
								combinedVertBuffer.push_back(vertexIndices.y != 0 ? vertUVs[vertexIndices.y - 1].y : 0.0f);
								combinedVertBuffer.push_back(vertexIndices.z != 0 ? vertNormals[vertexIndices.z - 1].x : 0.0f);
								combinedVertBuffer.push_back(vertexIndices.z != 0 ? vertNormals[vertexIndices.z - 1].y : 0.0f);
								combinedVertBuffer.push_back(vertexIndices.z != 0 ? vertNormals[vertexIndices.z - 1].z : 0.0f);

								// Add to the mesh, get index of the added vertex
								uint32_t index = (combinedVertBuffer.size() / 8) - 1;
								// Cache the index based on our key
								indexMap[key] = index;
								// Add index to mesh, and add to edges list for if we are using quads
								edges[i] = index;
							}
						}
						else
						{
							break;
						}
					}
					if (i == 3&&Keys.size()==0) {
						indexedVertices.push_back(edges[0]);
						indexedVertices.push_back(edges[1]);
						indexedVertices.push_back(edges[2]);

					}
					//Handling for quad faces
					else if (i == 4&&Keys.size()==0) {
						indexedVertices.push_back(edges[0]);
						indexedVertices.push_back(edges[1]);
						indexedVertices.push_back(edges[2]);
						indexedVertices.push_back(edges[0]);
						indexedVertices.push_back(edges[2]);
						indexedVertices.push_back(edges[3]);
					}

				}
			}
			
			Frame newFrame;
			newFrame.VBO = VertexBuffer::Create();
			
			newFrame.VBO->Bind();
			newFrame.VBO->LoadData(combinedVertBuffer.data(), combinedVertBuffer.size());

			Keys.push_back(newFrame);

			if (Keys.size() == 0)
			{
				IndexBuffer::sptr ibo = IndexBuffer::Create();

				ibo->LoadData(indexedVertices.data(), sizeof(int), indexedVertices.size(), GL_UNSIGNED_INT);
				/*
				std::vector<BufferAttribute>  attribs;
				attribs.push_back(BufferAttribute(0, 3, GL_FLOAT, false, sizeof(float) * 8, NULL));
				attribs.push_back(BufferAttribute(1, 2, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 3));
				attribs.push_back(BufferAttribute(2, 3, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 5));
				*/

				vao->SetIndexBuffer(ibo);
			}
			
		}
		else
		{
			printf("file could not be opened");
		}

	}
	else
	{
		printf("not an obj");
	}
}
float syre::MorphRenderer::Update(float delta)
{
	if (Keys.size() == 0)
	{
		return -1;
	}
	timer += delta;
	if (timer > frameTime)
	{
		timer = 0.0f;
		curFrame++;

		std::vector<BufferAttribute>  attribs;
		attribs.push_back(BufferAttribute(0, 3, GL_FLOAT, false, sizeof(float) * 8, NULL));
		attribs.push_back(BufferAttribute(1, 2, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 3));
		attribs.push_back(BufferAttribute(2, 3, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 5));
		std::vector<BufferAttribute>  attribs2;
		attribs.push_back(BufferAttribute(3, 3, GL_FLOAT, false, sizeof(float) * 8, NULL));
		attribs.push_back(BufferAttribute(4, 2, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 3));
		attribs.push_back(BufferAttribute(5, 3, GL_FLOAT, false, sizeof(float) * 8, sizeof(float) * 5));
		if (curFrame == Keys.size())
		{
			curFrame = 0;
		}
		if (curFrame == Keys.size() - 1)
		{
			vao->AddVertexBuffer(Keys[curFrame].VBO, attribs);
			vao->AddVertexBuffer(Keys[0].VBO, attribs2);
		}
		else
		{
			vao->AddVertexBuffer(Keys[curFrame].VBO, attribs);
			vao->AddVertexBuffer(Keys[curFrame].VBO, attribs2);
		}
	}
	return timer / frameTime;
}
void syre::MorphRenderer::Render()
{
	
	vao->Render();
}
glm::vec3 syre::MorphRenderer::Vector3Parser(std::string line, int offset)
{
	std::string xCoord;
	std::string yCoord;
	std::string zCoord;
	int coordNum = 0;
	for (int i = offset; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			coordNum++;
		}
		else
		{
			switch (coordNum)
			{
			case 0:
				xCoord += line[i];
				break;
			case 1:
				yCoord += line[i];
				break;
			case 2:
				zCoord += line[i];
				break;
			}
		}
	}
	//std::cout << xCoord << std::endl << yCoord << std::endl << zCoord << std::endl;


	return glm::vec3(std::stof(xCoord), std::stof(yCoord), std::stof(zCoord));
}

glm::vec2 syre::MorphRenderer::Vector2Parser(std::string line, int offset)
{
	std::string xCoord;
	std::string yCoord;
	int coordNum = 0;
	for (int i = offset; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			coordNum++;
		}
		else
		{
			switch (coordNum)
			{
			case 0:
				xCoord += line[i];
				break;
			case 1:
				yCoord += line[i];
				break;
			}
		}
	}
	//std::cout << xCoord << std::endl << yCoord << std::endl;
	return glm::vec2(std::stof(xCoord), std::stof(yCoord));
}

void syre::MorphRenderer::FaceLineProcessor(std::string line, std::vector<unsigned int>& indexVec)
{
	int vertCounter = 0;
	std::string vertHolder;
	bool reading = false;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			vertCounter++;
		}
	}
	if (vertCounter == 3)
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (reading)
			{
				if (line[i] == '/')
				{


					indexVec.push_back(unsigned int(std::stoi(vertHolder) - 1));
					vertHolder = "";
				}
				else
				{
					vertHolder += line[i];
				}
			}
			else if (line[i] == ' ')
			{
				reading = true;
			}
		}
	}
	else if (vertCounter == 4)
	{
		int verts[4];
		int j = 0;
		for (int i = 0; i < line.size(); i++)
		{
			if (reading)
			{
				if (line[i] == '/')
				{
					reading = false;

					verts[j] = std::stoi(vertHolder);
					j++;
					//std::cout << vertHolder;
					vertHolder = "";
				}
				else
				{
					vertHolder += line[i];
				}
			}
			else if (line[i] == ' ')
			{
				reading = true;
			}
		}
		indexVec.push_back(verts[0]);
		indexVec.push_back(verts[1]);
		indexVec.push_back(verts[2]);
		indexVec.push_back(verts[0]);
		indexVec.push_back(verts[2]);
		indexVec.push_back(verts[3]);
	}
}

//Following code was borrowed from cg tutorials, that borrowed it from from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

void syre::MorphRenderer::ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

void syre::MorphRenderer::rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

void syre::MorphRenderer::trim(std::string& s)
{
	ltrim(s);
	rtrim(s);
}

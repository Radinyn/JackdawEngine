#include "glclasses.h"
#include "../../include/JackdawMath.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace jdw;

void loadObj(GLObject* glObj, const std::string& filepath, bool hasTexture, bool hasNormals)
{
	std::vector<Vec3f> verticies;
	std::vector<Vec2f> textureCoordinates;
	std::vector<Vec3f> normals;
	std::vector<GLfloat> vertexBufferVector;
	std::vector<GLuint> indexBufferVector;

	std::unordered_map<std::string, GLuint> indexCache;

	std::ifstream file(filepath);
	std::string line;

	enum {
		VERTEX = 1,
		TEXTURE = 2,
		NORMAL = 3,
		FACE = 4
	};

	std::unordered_map<std::string, int> table = {
		{"v ", VERTEX },
		{"vt", TEXTURE},
		{"vn", NORMAL },
		{"f ", FACE   },
	};

	int count = 0;
	GLuint index = 1;

	while (std::getline(file, line))
	{
		std::istringstream s(line.substr(2)), s2;
		Vec3f v; Vec2f v2;
		GLuint x;
		std::string key;

		switch (table[line.substr(0, 2)])
		{
		case VERTEX:
			s >> v.x >> v.y >> v.z;
			verticies.push_back(v);
			break;

		case TEXTURE:
			s >> v2.x >> v2.y;
			textureCoordinates.push_back(v2);
			break;

		case NORMAL:
			s >> v.x >> v.y >> v.z;
			normals.push_back(v);
			break;

		case FACE:
			if (!count)
				count = std::count(line.begin(), line.end(), ' ');

			std::replace(line.begin() + 2, line.end(), '/', ' ');
			s2.str(line.substr(2));

			for (int i = 0; i < count; i++)
			{
				s >> key;

				if (indexCache[key])
				{
					indexBufferVector.push_back(indexCache[key] - 1);

					// ignore the rest
					s2 >> x;
					if (hasTexture) s2 >> x;
					if (hasNormals) s2 >> x;
					continue;
				}

				indexBufferVector.push_back(index - 1);
				indexCache[key] = index;
				index++;

				s2 >> x; x--;
				vertexBufferVector.push_back(verticies[x].x);
				vertexBufferVector.push_back(verticies[x].y);
				vertexBufferVector.push_back(verticies[x].z);

				if (hasTexture)
				{
					s2 >> x; x--;
					vertexBufferVector.push_back(textureCoordinates[x].x);
					vertexBufferVector.push_back(textureCoordinates[x].y);
				}
				if (hasNormals)
				{
					s2 >> x; x--;
					vertexBufferVector.push_back(normals[x].x);
					vertexBufferVector.push_back(normals[x].y);
					vertexBufferVector.push_back(normals[x].z);
				}
			}
			break;

		default: break;
		}
	}
	file.close();

	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(&vertexBufferVector[0], vertexBufferVector.size() * sizeof(GLfloat));
	IndexBuffer* ib = new IndexBuffer(&indexBufferVector[0], indexBufferVector.size());
	VertexBufferLayout layout;
	va->bind();

	layout.push<GLfloat>(3);

	if (hasTexture)
		layout.push<GLfloat>(2);

	if (hasNormals)
		layout.push<GLfloat>(3);

	va->addBuffer(*vb, layout);


	delete glObj->pVA;
	delete glObj->pVB;
	delete glObj->pIB;

	glObj->pVA = va;
	glObj->pVB = vb;
	glObj->pIB = ib;
}
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "glm.hpp"
#include "Vertex.h"

using namespace std;
class FileReader {
public:
	static std::string ReadFromFile(char* filename) {
		std::string code;
		std::ifstream file;
		file.exceptions(std::ifstream::badbit); // enable exceptions on this file
		try 
		{
			file.open(filename);
			std::stringstream fileStream;
			fileStream << file.rdbuf();
			file.close();
			code = fileStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Failed to load file!" << std::endl;
			return nullptr;
		}
		return code;
	}
	static bool LoadOBJ(const char* fname, std::vector<Vertex> &vertices) {
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> tempVerts, tempUVs, tempNormals; // Used to store contents of OBJ file

		FILE * file = fopen(fname, "r");
		if (file == NULL) {
			std::cout << "Failed to open OBJ file" << std::endl;
			return false;
		}
		while (1) {
			char lineHeader[128];
			//Read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // End of file
			if (strcmp(lineHeader, "v") == 0) { // If first char is a v (vertex position)
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // Take 3 floats from line and push them into vertex X,Y,Z values
				tempVerts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) { // If texture coordinate
				glm::vec3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y); // Take x and y values
				tempUVs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z); // Take x and y values
				tempNormals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cout << "File too complex for parser" << std::endl;
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else {
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

			// For each vertex of each triangle
			for (unsigned int i = 0; i < vertexIndices.size(); i++) {

				// Get the indices of its attributes
				unsigned int vertexIndex = vertexIndices[i];
				unsigned int uvIndex = uvIndices[i];
				unsigned int normalIndex = normalIndices[i];

				// Get the attributes thanks to the index
				glm::vec3 vertex = tempVerts[vertexIndex - 1];
				glm::vec2 uv = tempUVs[uvIndex - 1];
				glm::vec3 normal = tempNormals[normalIndex - 1];

				// Put the attributes in buffers
				vertices.push_back(Vertex(vertex.x,vertex.y,vertex.z, 0.0f, Vertex::POSITION));
				vertices.push_back(Vertex(uv.x, uv.y, 0.0f, 0.0f, Vertex::TEXTURE));
				vertices.push_back(Vertex(normal.x, normal.y, normal.z, 0.0f, Vertex::NORMAL));

			}
		}
		fclose(file);
		return true;
	}
};
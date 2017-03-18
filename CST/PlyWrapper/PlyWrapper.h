#pragma once

#include "ply.h"

using namespace System;

namespace PlyWrapper
{
	public ref struct Vertex
	{
		float x, y, z;
	};

	typedef struct VertexNative {
		float x, y, z;             /* the usual 3-space position of a vertex */
	} VertexNative;

	PlyProperty vert_props[] = { /* list of property information for a vertex */
		{ "x", PLY_FLOAT, PLY_FLOAT, offsetof(VertexNative, x), 0, 0, 0, 0 },
		{ "y", PLY_FLOAT, PLY_FLOAT, offsetof(VertexNative, y), 0, 0, 0, 0 },
		{ "z", PLY_FLOAT, PLY_FLOAT, offsetof(VertexNative, z), 0, 0, 0, 0 },
	};

	public ref class PlyWrapper
	{
	private:
		
	public:
		static array<Vertex^>^ GetVerticesFromPlyFile(System::String^ path)
		{
			char *filename = new char[path->Length];

			for (int i = 0; i < path->Length; i++)
			{
				filename[i] = path[i];
			}

			int nelems;
			char **elem_names;
			int file_type;
			float version;
			PlyFile *plyFile = ply_open_for_reading("C:\\Users\\Alex Bousso\\Downloads\\Doll_small.ply", &nelems, &elem_names, &file_type, &version);

			delete filename;
			filename = nullptr;

			array<Vertex^>^ vertices = gcnew array<Vertex^>(nelems);
			VertexNative **vlist = new VertexNative*[nelems];
			//VertexNative **vlist = (VertexNative **)malloc(sizeof (VertexNative *)* nelems);

			for (int i = 0; i < nelems; i++)
			{
				char *elem_name = elem_names[i];

				if (!equal_strings("vertex", elem_name))
				{
					continue;
				}

				ply_get_property(plyFile, elem_name, &vert_props[0]);
				ply_get_property(plyFile, elem_name, &vert_props[1]);
				ply_get_property(plyFile, elem_name, &vert_props[2]);

				for (int j = 0; j < nelems; j++)
				{
					vlist[j] = new VertexNative;
					//vlist[j] = (VertexNative *)malloc(sizeof (VertexNative));
					ply_get_element(plyFile, (void *)vlist[j]);

					vertices[j] = gcnew Vertex();
					vertices[j]->x = vlist[j]->x;
					vertices[j]->y = vlist[j]->y;
					vertices[j]->z = vlist[j]->z;
				}
			}

			for (int i = 0; i < nelems; i++)
			{
				delete vlist[i];
				//free(vlist[i]);
			}
			delete vlist;
			//free(vlist);

			return vertices;
		}
	};
}
#include <string>
#ifndef _chunk_vector_
#define _chunk_vector_

#define CHUNK_SIZE 3
using namespace std;



class ChunkVector {
public:
	ChunkVector();
	~ChunkVector();
	int size();
	int get(int index);
	void set(int index, int value);
	void add(int value);
	void remove(int index);
	int getChunkNumber();
	void insert(int index, int value);
private:
	struct Chunk{
		int data[CHUNK_SIZE];
		int size;
		Chunk* next;

	};
	int elemNum;
	Chunk* front;
	int chunkNum;
};
#endif
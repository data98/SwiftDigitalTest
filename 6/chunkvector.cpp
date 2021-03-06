#include "chunkvector.h"

ChunkVector::ChunkVector() {
	elemNum = 0;
	front = NULL;
	chunkNum = 0;
}

ChunkVector::~ChunkVector() {
	while(front != NULL){
		Chunk* temp = front->next;
		delete front;
		front = temp;
	}
}

int ChunkVector::size() {
	return elemNum;
}

int ChunkVector::get(int index) {
	
	int count = 0;
	Chunk* temp = front;
	while(count + temp->size <= index){
		count += temp->size;
		temp = temp->next;
		
	}
	int a = index - count;
	return temp->data[a];
}

void ChunkVector::set(int index, int value) {
		int count = 0;
	Chunk* temp = front;
	while(count + temp->size <= index){
		count += temp->size;
		temp = temp->next;
		
	}
	int a = index - count;
	temp->data[a] = value;
}

void ChunkVector::add(int value) {
	if(front == NULL){
		front = new Chunk;
		chunkNum++;
		elemNum++;
		front->data[0] = value;
		front->size = 1;
		front->next = NULL;
	}else{
		Chunk* current = front;
		while(current->next != NULL){
			current = current->next;
		}
		if(current->size == CHUNK_SIZE){
			current->next = new Chunk;
			chunkNum++;
			current->next->next = NULL;
			current->next->size = 0;
			int half = CHUNK_SIZE/2 + CHUNK_SIZE%2;
			for(int i = half; i < CHUNK_SIZE; i++){
				current->next->data[current->next->size] = current->data[i];
				current->next->size +=1;
			}
			//current->next->size = CHUNK_SIZE - half;
			
			//current->size -= CHUNK_SIZE - half;
			current->size = half;
			current = current->next;
		}
		current->data[current->size] = value;
		current->size++;
		elemNum++;
	}
}

void ChunkVector::remove(int index) {
	int count = 0;
	Chunk* temp = front;
	Chunk* temp2 = NULL;
	while(count + temp->size <= index){
		count += temp->size;
		temp2 = temp;
		temp = temp->next;
	}
	int a = index - count;
	for(int i = a; i < temp->size-1; i++){
		temp->data[a] = temp->data[a+1];
	}
	temp->size -=1;
	elemNum--;
	if(temp->size == 0){
		if(temp2 == NULL){
			Chunk* temp3 = front->next;
			delete front;
			front = temp3;
		}else{
			temp2->next = temp->next;
			delete temp;
		}
		chunkNum--;
	}
}

int ChunkVector::getChunkNumber() {
	return chunkNum;
}

void ChunkVector::insert(int index, int value) {
	if (index == size()) {
		add(value);
		return;
	}
	int counter = 0;
	Chunk * curr = front;
	Chunk * prev = NULL;
	while (true) {
		if (counter + curr->size > index) {
			break;
		}
		counter += curr->size;
		prev = curr;
		curr = curr->next;
	}
	if (curr->size == CHUNK_SIZE) {
		chunkNum++;
		Chunk * tmp = new Chunk;
		tmp->next = curr->next;
		tmp->size = curr->size/2;
		curr->size -= tmp->size;
		for (int i=0; i<tmp->size; i++) {
			tmp->data[i] = curr->data[curr->size+i];
		}
		curr->next = tmp;
	}
	if (counter + curr->size <= index) {
		counter += curr->size;
		curr = curr->next;
	}
	int i;
	for (i=curr->size; i>index-counter; i--) {
		curr->data[i] = curr->data[i-1];
	}
	curr->data[i] = value;
	elemNum++;
	curr->size++;
}

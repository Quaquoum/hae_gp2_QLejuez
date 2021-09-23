#pragma once

class IntArray {
	int* data = nullptr;

public :
	IntArray() {
		data = new int[19492];
	};

	void set(int idx, int value) {
		//recup la donnée a la case idx et l'affecter

		data[idx] = value; // *(data + idx) = value;
	};

	int get(int idx) {
		//recup la donnée a la case idx et la retourner
		
		return data[idx];
	};
};

void add(int a, int b, int* solution) {


	a++;


	*solution = a + b;
	return;
}

int main() {
	int a = 1;
	int b = 2;
	int solution;

	add(a, b, &solution);

}




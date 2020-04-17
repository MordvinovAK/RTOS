#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;



class LKG
{
	int a, m, c, n;
	int* x;

public:
	LKG(int arg_x0, int arg_a, int arg_m, int arg_c, int arg_n)
	{
		a = arg_a;
		m = arg_m;
		c = arg_c;
		n = arg_n;
		x = new int[arg_n];
		x[0]=arg_x0;
	}
	int* calculate(int k)
	{
		x[k]=(a*x[k-1]+c) % m;
		k++;
		if (k<n)
			calculate(k);
		return x;
	}

	void output()
	{
		for(int i=0; i<n; i++)
			cout<<x[i]<<endl;
	}
};

void* psp(void* foo)
{
	LKG* obj = (LKG*) foo;
	obj->calculate(1);
	obj->output();
	return obj;
}

int main(int argc, char *argv[])
{
	int x0, a, m, c, n;
	x0 = atoi(argv[1]);
	a = atoi(argv[2]);
	m = atoi(argv[3]);
	c = atoi(argv[4]);
	n = atoi(argv[5]);

	LKG obj(x0, a, m, c, n);

	pthread_t lkg_thread;
	pthread_create(&lkg_thread, NULL, psp, &obj);
	pthread_join(lkg_thread, NULL);

	return EXIT_SUCCESS;
}

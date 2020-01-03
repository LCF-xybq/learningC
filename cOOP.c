#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	void (*speak)();
} animal;

typedef struct
{
	animal base;
	char color[20];
} cat;

typedef struct
{
	animal base;
} dog;

void Animal(animal* this, char* name, void (*func)())
{
	strcpy(this->name, name);
	this->speak = func;
}

void Introduce(animal* this)
{
	printf("I'm a %s.\n", this->name);
}

void CatSpeak()
{
	printf("miao\n");
}

void Cat(cat* this, const char* color)
{
	Animal((animal*)this, "cat", CatSpeak);
	strcpy(this->color, color);
}

void ShowColor(cat* this)
{
	printf("color of cat is %s.\n", this->color);
}

void DogSpeak()
{
	printf("wang.\n");
}

void Dog(dog* this)
{
	Animal((animal*)this, "dog", DogSpeak);
}

int main()
{
	cat whiteCat, blackCat;
	dog doge;

	Cat(&whiteCat, "white");
	Cat(&blackCat, "black");
	Dog(&doge);

	animal* animals[] = {&whiteCat, &blackCat, &doge};
	for (int i = 0; i < 3; i++)
	{
		Introduce(animals[i]);
		animals[i]->speak();
	}

	ShowColor(&whiteCat);
	ShowColor(&blackCat);

	return 0;
}

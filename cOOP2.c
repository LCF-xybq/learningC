#include <stdio.h>
#include <string.h>

typedef struct 
{
	int maxSpeed;
} Car;

typedef struct
{
	int price;
} ForSale;

typedef struct
{
	Car car;
	ForSale sale;
} FordCar;

void drive(Car* this)
{
	printf("speed is %d km/h\n", this->maxSpeed);
}

void sale(ForSale* this)
{
	printf("This price is %d\n", this->price);
}

void ford_car_sale(FordCar* this)
{
	printf("ford car will cost you %d.\nand it's speed is %d km/h\n", this->car.maxSpeed, this->sale.price);
}

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define FordCar2Car(a) ((Car*)&(a->car))
#define FordCar2ForSale(a) ((ForSale*)&(a->sale))
#define Car2FordCar(a) ((FordCar*)a)
#define ForSale2FordCar(a) ( (FordCar*)(((char*)a) - offsetof(FordCar, sale)))

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

int main()
{
    FordCar A;
    A.car.maxSpeed = 120;
    A.sale.price = 5000;

    printf("-----------------------------------------\n");
    FordCar* pford = &A;
    sale(FordCar2ForSale(pford));
    drive(FordCar2Car(pford));

    printf("-----------------------------------------\n");
    Car* pcar = FordCar2Car(pford);
    ForSale* pforSale = FordCar2ForSale(pford);
    ford_car_sale(Car2FordCar(pcar));
    ford_car_sale(ForSale2FordCar(pforSale));

    return 0;
}

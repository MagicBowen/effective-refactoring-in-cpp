#include <iostream>
#include <exception>

/////////////////////////////////////////////////////////
typedef unsigned int U32;

struct Product
{
    double price;
    U32 quantity;
};

/////////////////////////////////////////////////////////
void printPrice(const Product* product)
{
    double p = product->price * product->quantity;

    if(p >= 1000)
    {
        p *= 0.95;
    }
    else
    {
        p *= 0.99;
    }

    std::cout << "The price of product is "<< p << std::endl;
}

/////////////////////////////////////////////////////////
bool calcPrice(Product* products, U32 num, double* totalPrice)
{
    U32 i;
    double basePrice;
    double discountFactor;

    if(products != 0)
    {
        for(i = 0; i < num; i++)
        {
            basePrice = products[i].price * products[i].quantity;

            if(basePrice >= 1000)
            {
                discountFactor = 0.95;
            }
            else
            {
                discountFactor = 0.99;
            }

            basePrice *= discountFactor;

            *totalPrice += basePrice;
        }

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////
template<typename T1, typename T2>
void assertEqual(const int position,
		         const char* expectName,
		         const char* actualName,
				 const T1& expect,
				 const T2& actual)
{
	if(expect == actual) return;

	std::cout << "LINE " << position << " ERROR: " << actualName << "(" << actual << ") is not equal expect " << expectName << "(" << expect << ")" <<std::endl;
	throw std::exception();
}

#define ASSERT_EQ(EXPECT, ACTUAL) assertEqual(__LINE__, #EXPECT, #ACTUAL, EXPECT, ACTUAL)

///////////////////////////////////////////////////////
int main()
{
    Product products[2];

    products[0].price = 500;
    products[0].quantity = 2;

    products[1].price = 5;
    products[1].quantity = 100;

    std::cout << "The expect price of product 0 is " << ((500 * 2) * 0.95) << std::endl;
    printPrice(&products[0]);

    std::cout << "The expect price of product 1 is " << ((100 * 5) * 0.99) << std::endl;
    printPrice(&products[1]);

    double totalPrice = 0;
    calcPrice(products, 2, &totalPrice);

    ASSERT_EQ(((500 * 2) * 0.95) + ((100 * 5) * 0.99), totalPrice);

    std::cout << std::endl << "OK!!!" << std::endl;
	return 0;
}

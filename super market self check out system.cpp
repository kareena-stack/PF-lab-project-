#include <stdio.h>

#define N 8   

int codes[N] = {101, 102, 103, 104, 105, 106, 107, 108};
char names[N][20] = {"Milk", "Bread", "Eggs", "Rice", "Sugar", "Oil", "Tea", "Biscuits"};
float prices[N] = {280, 150, 400, 320, 180, 650, 520, 90};
int stock[N] = {20, 15, 10, 25, 30, 12, 18, 40};


int cartQty[N] = {0, 0, 0, 0, 0, 0, 0, 0};

void showProducts()
{
    int i;
    printf("\nCode  Name        Price   Stock\n");
    printf("-------------------------------\n");
    for (i = 0; i < N; i++)
    {
        printf("%d   %-10s  %5.0f   %d\n", codes[i], names[i], prices[i], stock[i]);
    }
}

int findProduct(int code)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (codes[i] == code)
        {
            return i;
        }
    }
    return -1;
}


void addItem()
{
    int code, qty, i;

    printf("Enter product code: ");
    scanf("%d", &code);
    i = findProduct(code);

    if (i == -1)
    {
        printf("Wrong code!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty <= 0)
    {
        printf("Quantity must be more than 0!\n");
    }
    else if (qty + cartQty[i] > stock[i])
    {
        printf("Not enough stock! Only %d available.\n", stock[i]);
    }
    else
    {
        cartQty[i] = cartQty[i] + qty;
        printf("%s added to cart.\n", names[i]);
    }
}


void removeItem()
{
    int code, qty, i;

    printf("Enter product code to remove: ");
    scanf("%d", &code);
    i = findProduct(code);

    if (i == -1)
    {
        printf("Wrong code!\n");
        return;
    }

    printf("Enter quantity to remove: ");
    scanf("%d", &qty);

    if (qty <= 0 || qty > cartQty[i])
    {
        printf("Invalid quantity!\n");
    }
    else
    {
        cartQty[i] = cartQty[i] - qty;
        printf("Removed.\n");
    }
}


float showCart()
{
    int i;
    float total = 0;

    printf("\nItem        Qty   Price   Amount\n");
    printf("--------------------------------\n");
    for (i = 0; i < N; i++)
    {
        if (cartQty[i] > 0)
        {
            printf("%-10s  %d    %5.0f   %6.0f\n", names[i], cartQty[i],
                   prices[i], prices[i] * cartQty[i]);
            total = total + prices[i] * cartQty[i];
        }
    }
    printf("--------------------------------\n");
    printf("Total: %.0f\n", total);
    return total;
}

void checkout()
{
    int i;
    float total = 0, discount = 0, finalBill, cash;

    for (i = 0; i < N; i++)
    {
        total = total + prices[i] * cartQty[i];
    }

    if (total == 0)
    {
        printf("Your cart is empty!\n");
        return;
    }

    showCart();

    if (total >= 2000)
    {
        discount = total * 0.10;
        printf("10%% discount: -%.0f\n", discount);
    }
    finalBill = total - discount;
    printf("Final bill: %.0f\n", finalBill);

    printf("Enter cash: ");
    scanf("%f", &cash);
    while (cash < finalBill)
    {
        printf("Not enough cash! Enter again: ");
        scanf("%f", &cash);
    }

    printf("\n===== RECEIPT =====\n");
    showCart();
    printf("Discount: %.0f\n", discount);
    printf("Paid: %.0f\n", cash);
    printf("Change: %.0f\n", cash - finalBill);
    printf("Thank you for shopping!\n");

    for (i = 0; i < N; i++)
    {
        stock[i] = stock[i] - cartQty[i];
        cartQty[i] = 0;
    }
}

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n===== SELF CHECKOUT =====\n");
        printf("1. Show products\n");
        printf("2. Add item\n");
        printf("3. Remove item\n");
        printf("4. Show cart\n");
        printf("5. Checkout\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            showProducts();
        }
        else if (choice == 2)
        {
            addItem();
        }
        else if (choice == 3)
        {
            removeItem();
        }
        else if (choice == 4)
        {
            showCart();
        }
        else if (choice == 5)
        {
            checkout();
        }
        else if (choice != 0)
        {
            printf("Invalid choice!\n");
        }
    }

    printf("come again soon goodbye customer!\n");
    return 0;
}

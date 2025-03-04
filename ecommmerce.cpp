#include <iostream>
using namespace std;

const int MAX_PRODUCTS = 10;
const int MAX_CART_ITEMS = 10;
const int MAX_ORDERS = 10;
const int MAX_ORDER_ITEMS = 10;
const int STRING_LENGTH = 20;

class Product {
private:
    char id[STRING_LENGTH];
    char name[STRING_LENGTH];
    double price;

public:
    Product() {
        id[0] = '\0';
        name[0] = '\0';
        price = 0.0;
    }

    Product(const char* pid, const char* pname, double pprice) {
        int i = 0;
        while (pid[i] != '\0' && i < STRING_LENGTH - 1) {
            id[i] = pid[i];
            i++;
        }
        id[i] = '\0';

        i = 0;
        while (pname[i] != '\0' && i < STRING_LENGTH - 1) {
            name[i] = pname[i];
            i++;
        }
        name[i] = '\0';

        price = pprice;
    }

    const char* getId() const { return id; }
    const char* getName() const { return name; }
    double getPrice() const { return price; }

    bool isEqual(const char* otherId) const {
        int i = 0;
        while (id[i] != '\0' && otherId[i] != '\0') {
            if (id[i] != otherId[i]) return false;
            i++;
        }
        return id[i] == '\0' && otherId[i] == '\0';
    }
};

class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;
    };

    CartItem items[MAX_CART_ITEMS];
    int itemCount;

public:
    ShoppingCart() : itemCount(0) {}

    void addProduct(const Product& product) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].product.isEqual(product.getId())) {
                items[i].quantity++;
                return;
            }
        }

        if (itemCount < MAX_CART_ITEMS) {
            items[itemCount].product = product;
            items[itemCount].quantity = 1;
            itemCount++;
        }
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

    void clear() {
        itemCount = 0;
    }

    int getItemCount() const {
        return itemCount;
    }

    const Product& getProduct(int index) const {
        return items[index].product;
    }

    int getQuantity(int index) const {
        return items[index].quantity;
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i].product.getPrice() * items[i].quantity;
        }
        return total;
    }
};

class Order {
private:
    int id;
    double totalAmount;
    
    struct OrderItem {
        char productId[STRING_LENGTH];
        char name[STRING_LENGTH];
        double price;
        int quantity;

        OrderItem() {
            productId[0] = '\0';
            name[0] = '\0';
            price = 0.0;
            quantity = 0;
        }
    };
    
    OrderItem items[MAX_ORDER_ITEMS];
    int itemCount;

public:
    Order() : id(0), totalAmount(0.0), itemCount(0) {}

    Order(int orderId, const ShoppingCart& cart) : id(orderId), itemCount(0) {
        totalAmount = cart.getTotalAmount();
        
        for (int i = 0; i < cart.getItemCount() && i < MAX_ORDER_ITEMS; i++) {
            const Product& product = cart.getProduct(i);
            
            int j = 0;
            while (product.getId()[j] != '\0' && j < STRING_LENGTH - 1) {
                items[itemCount].productId[j] = product.getId()[j];
                j++;
            }
            items[itemCount].productId[j] = '\0';
            
            j = 0;
            while (product.getName()[j] != '\0' && j < STRING_LENGTH - 1) {
                items[itemCount].name[j] = product.getName()[j];
                j++;
            }
            items[itemCount].name[j] = '\0';
            
            items[itemCount].price = product.getPrice();
            items[itemCount].quantity = cart.getQuantity(i);
            
            itemCount++;
        }
    }

    int getId() const { return id; }
    double getTotalAmount() const { return totalAmount; }
    int getItemCount() const { return itemCount; }
    
    const char* getProductId(int index) const { return items[index].productId; }
    const char* getName(int index) const { return items[index].name; }
    double getPrice(int index) const { return items[index].price; }
    int getQuantity(int index) const { return items[index].quantity; }
};

void displayProducts(const Product products[], int productCount) {
    cout << "\n===== PRODUCTS =====\n";
    cout.width(15); cout << left << "Product ID";
    cout.width(15); cout << left << "Name";
    cout.width(10); cout << left << "Price" << "\n";
    
    for (int i = 0; i < productCount; i++) {
        cout.width(15); cout << left << products[i].getId();
        cout.width(15); cout << left << products[i].getName();
        cout.width(10); cout << left << products[i].getPrice() << "\n";
    }
}

void viewProducts(const Product products[], int productCount, ShoppingCart& cart) {
    char continueAdding = 'Y';
    
    while (continueAdding == 'Y' || continueAdding == 'y') {
        displayProducts(products, productCount);

        cout << "\nEnter the ID of the product you want to add in the shopping cart: ";
        char productId[STRING_LENGTH];
        cin >> productId;

        bool found = false;
        for (int i = 0; i < productCount; i++) {
            if (products[i].isEqual(productId)) {
                cart.addProduct(products[i]);
                found = true;
                cout << "Product added successfully!\n";
                break;
            }
        }

        if (!found) {
            cout << "Product not found!\n";
        }

        cout << "Do you want to add another product to the shopping cart? (Y/N): ";
        cin >> continueAdding;
    }
}

void viewShoppingCart(ShoppingCart& cart, Order orders[], int& orderCount, int& nextOrderId) {
    if (cart.isEmpty()) {
        cout << "Shopping cart is empty!\n";
        return;
    }

    cout << "\n===== SHOPPING CART =====\n";
    cout.width(15); cout << left << "Product ID";
    cout.width(15); cout << left << "Name";
    cout.width(10); cout << left << "Price";
    cout.width(10); cout << left << "Quantity" << "\n";

    for (int i = 0; i < cart.getItemCount(); i++) {
        cout.width(15); cout << left << cart.getProduct(i).getId();
        cout.width(15); cout << left << cart.getProduct(i).getName();
        cout.width(10); cout << left << cart.getProduct(i).getPrice();
        cout.width(10); cout << left << cart.getQuantity(i) << "\n";
    }

    cout << "\nTotal Amount: " << cart.getTotalAmount() << "\n";
    cout << "Do you want to check out all the products? (Y/N): ";
    char checkout;
    cin >> checkout;

    if (checkout == 'Y' || checkout == 'y') {
        if (orderCount < MAX_ORDERS) {
            orders[orderCount] = Order(nextOrderId++, cart);
            orderCount++;
            cout << "You have successfully checked out the products!\n";
            cart.clear();
        }
        else {
            cout << "Maximum order limit reached!\n";
        }
    }
}

void viewOrders(const Order orders[], int orderCount) {
    if (orderCount == 0) {
        cout << "No orders yet!\n";
        return;
    }

    cout << "\n===== ORDERS =====\n";
    
    for (int i = 0; i < orderCount; i++) {
        cout << "Order ID: " << orders[i].getId() << "\n";
        cout << "Total Amount: " << orders[i].getTotalAmount() << "\n";
        cout << "Order Details:\n";
        cout.width(15); cout << left << "Product ID";
        cout.width(15); cout << left << "Name";
        cout.width(10); cout << left << "Price";
        cout.width(10); cout << left << "Quantity" << "\n";
        
        for (int j = 0; j < orders[i].getItemCount(); j++) {
            cout.width(15); cout << left << orders[i].getProductId(j);
            cout.width(15); cout << left << orders[i].getName(j);
            cout.width(10); cout << left << orders[i].getPrice(j);
            cout.width(10); cout << left << orders[i].getQuantity(j) << "\n";
        }
        cout << "\n";
    }
}

int main() {
    Product products[MAX_PRODUCTS] = {
        Product("ABC", "Paper", 20),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Paper", 20),
        Product("TRE", "Pencil", 10),
        Product("ASD", "Paper", 20),
        Product("ZXC", "Pencil", 10),
        Product("RTY", "Notebook", 30),
        Product("FGH", "Eraser", 5)
    };
    int productCount = 8;

    ShoppingCart cart;
    Order orders[MAX_ORDERS];
    int orderCount = 0;
    int nextOrderId = 1;

    bool running = true;
    int choice = 0;
    
    while (running) {
        cout << "\n===== MENU =====\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewProducts(products, productCount, cart);
                break;
            case 2:
                viewShoppingCart(cart, orders, orderCount, nextOrderId);
                break;
            case 3:
                viewOrders(orders, orderCount);
                break;
            case 4:
                cout << "Thank you for using my system!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
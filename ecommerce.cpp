#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Product {
private:
    string productId;
    string name;
    double price;

public:
    Product(string id, string n, double p) : productId(id), name(n), price(p) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
};

class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;

        CartItem(Product p, int q) : product(p), quantity(q) {}
    };

    vector<CartItem> items; // List of items in the cart

public:
    void addProduct(const Product& product, int quantity) {
        // Check if product already exists in cart
        for (auto& item : items) {
            if (item.product.getProductId() == product.getProductId()) {
                item.quantity += quantity;
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
    }

    // Empties the shopping cart
    vector<CartItem> getItems() const { return items; }
    void clearCart() {
        items.clear();
    }

    double getTotalAmount() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.product.getPrice() * item.quantity;
        }
        return total;
    }

    bool isEmpty() const {
        return items.empty();
    }
};

class Order {
private:
    int orderId;
    vector<pair<Product, int>> products; // Product and quantity
    double totalAmount;

public:
    Order(int id, const vector<pair<Product, int>>& prods, double total)
        : orderId(id), products(prods), totalAmount(total) {}

    int getOrderId() const { return orderId; }
    vector<pair<Product, int>> getProducts() const { return products; }
    double getTotalAmount() const { return totalAmount; }
};

// Function to validate if a string contains only digits
bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

// Function to get valid numeric input from user
int getNumericInput() {
    string input;
    bool numeric = true;
    
    while (numeric) {
        getline(cin, input);
        if (isNumeric(input)) {
            return stoi(input);
        }
        cout << "Invalid input. Please enter a number: ";
    }
}

// Function to get valid yes/no input from user
bool getYesNoInput() {
    string input;
    bool yesNoInput = true;

    while (yesNoInput) {
        getline(cin, input);
        if (input == "Y" || input == "y") {
            return true;
        } else if (input == "N" || input == "n") {
            return false;
        }
        cout << "Invalid input. Please enter Y or N: ";
    }
}

int main() {
    // List of available products
    vector<Product> products = {
        Product("ABC", "Paper", 20),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Glue", 30),
        Product("TRE", "Ballpen", 10),
        Product("ASD", "Folder", 10),
        Product("ZXC", "Marker", 30),
        Product("RTY", "Notebook", 50),
        Product("FGH", "Eraser", 5)
    };

    ShoppingCart cart;
    vector<Order> orders; // List of completed orders
    int nextOrderId = 1; // Order ID counter
    bool isRunning = true;

    while (isRunning) {
        // Display menu
        cout << "\n===== MENU =====\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice = getNumericInput();

        switch (choice) {
            case 1: {
                // View Products
                cout << "\n===== PRODUCTS =====\n";
                cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << endl;
                cout << "---------------------------------------\n";

                for (const auto& product : products) {
                    cout << left << setw(15) << product.getProductId()
                         << setw(15) << product.getName()
                         << setw(10) << fixed << setprecision(2) << product.getPrice() << endl;
                }

                bool addMoreProducts = true;
                while (addMoreProducts) {
                    cout << "\nEnter the ID of the product you want to add in the shopping cart: ";
                    string productId;
                    getline(cin, productId);

                    // Find the product
                    bool found = false;
                    for (const auto& product : products) {
                        if (product.getProductId() == productId) {
                            found = true;
                            
                            // Ask for quantity
                            cout << "Enter quantity: ";
                            int quantity = getNumericInput();
                            
                            if (quantity <= 0) {
                                cout << "Quantity must be greater than 0!" << endl;
                            } else {
                                cart.addProduct(product, quantity);
                                cout << "Product added successfully!" << endl;
                            }
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Product not found!" << endl;
                    }

                    cout << "Do you want to add another product to the shopping cart? (Y/N): ";
                    addMoreProducts = getYesNoInput();
                }
                break;
            }
            case 2: {
                // View Shopping Cart
                cout << "\n===== SHOPPING CART =====\n";
                
                if (cart.isEmpty()) {
                    cout << "Your shopping cart is empty!" << endl;
                } else {
                    cout << left << setw(15) << "Product ID" << setw(15) << "Name" 
                         << setw(10) << "Price" << setw(10) << "Quantity" << endl;
                    cout << "-------------------------------------------\n";

                    auto items = cart.getItems();
                    for (const auto& item : items) {
                        cout << left << setw(15) << item.product.getProductId()
                             << setw(15) << item.product.getName()
                             << setw(10) << fixed << setprecision(2) << item.product.getPrice()
                             << setw(10) << item.quantity << endl;
                    }

                    cout << "\nTotal Amount: ₱" << fixed << setprecision(2) << cart.getTotalAmount() << endl;

                    cout << "\nDo you want to check out all the products? (Y/N): ";
                    bool checkout = getYesNoInput();

                    if (checkout) {
                        // Create order
                        vector<pair<Product, int>> orderProducts;
                        auto items = cart.getItems();
                        for (const auto& item : items) {
                            orderProducts.push_back({item.product, item.quantity});
                        }

                        orders.push_back(Order(nextOrderId++, orderProducts, cart.getTotalAmount()));
                        
                        cout << "\n===== CHECKOUT SUMMARY =====\n";
                        cout << left << setw(15) << "Product ID" << setw(15) << "Name" 
                             << setw(10) << "Price" << setw(10) << "Quantity" << endl;
                        cout << "-------------------------------------------\n";

                        for (const auto& item : items) {
                            cout << left << setw(15) << item.product.getProductId()
                                 << setw(15) << item.product.getName()
                                 << setw(10) << fixed << setprecision(2) << item.product.getPrice()
                                 << setw(10) << item.quantity << endl;
                        }

                        cout << "\nTotal Amount: ₱" << fixed << setprecision(2) << cart.getTotalAmount() << endl;
                        cout << "You have successfully checked out the products!" << endl;
                        
                        // Clear cart after checkout
                        cart.clearCart();
                    }
                }
                break;
            }
            case 3: {
                // View Orders
                cout << "\n===== ORDERS =====\n";
                
                if (orders.empty()) {
                    cout << "No orders found!" << endl;
                } else {
                    for (const auto& order : orders) {
                        cout << "Order ID: " << order.getOrderId() << endl;
                        cout << "Total Amount: ₱" << fixed << setprecision(2) << order.getTotalAmount() << endl;
                        cout << "Order Details:" << endl;
                        cout << left << setw(15) << "Product ID" << setw(15) << "Name" 
                             << setw(15) << "Price" << setw(15) << "Quantity" << endl;
                        
                        auto products = order.getProducts();
                        for (const auto& item : products) {
                            cout << left << setw(15) << item.first.getProductId()
                                 << setw(15) << item.first.getName()
                                 << setw(15) << fixed << setprecision(2) << item.first.getPrice()
                                 << setw(15) << item.second << endl;
                        }
                        cout << "\n";
                    }
                }
                break;
            }
            case 4:
                cout << "Thank you for using my system. Goodbye!" << endl;
                isRunning = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
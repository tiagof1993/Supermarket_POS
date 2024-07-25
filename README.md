# SUPERMARKET_POS

This work aims to simulate the register and payment process in a small supermarket. For that, a C++ program was developed to perform the operations associated with those processes, namely the register of products, payment, and the creation of a receipt.

Initially, a .txt file composed of a list of products, prices, and IVA values is read and a randomly generated EAN13 code is associated with each product in the list. The .txt file represents the repository of all the products available in the supermarket at the time of the first register operation.

The register process is done by continuously requesting an EAN13 code value until a -1 input is read. Each time a product is picked from the repository list, it is erased from that list, so that it cannot be picked twice. 

When all the products are registered, the payment is performed by requesting an available payment method (Cash, Card, or MBWay). If the picked method is a Card or MBWay, the payment is processed automatically. Otherwise, there's the need to assess if the Cash value is equal or superior to the necessary amount. If the present value is below the necessary, a message will be printed, notifying the situation and the amount of money that is still to be paid. If the value is higher than the necessary amount, a message will be printed with the value of the change to be returned to the customer.

At the end of each register+payment operation, a receipt will be printed, and at the end of all operations, these receipts will be written in a .txt file.

## Usage Example

./SUPERMARKET_POS supermarket_repository.txt



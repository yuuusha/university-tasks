CREATE TABLE Flower (
    Flower_id INTEGER PRIMARY KEY NOT NULL,
    Name NVARCHAR(50),
    Price FLOAT
);

CREATE TABLE Bouquet (
    Bouquet_id INTEGER PRIMARY KEY NOT NULL,
    Name NVARCHAR(50),
    Price FLOAT
);

CREATE TABLE BouquetFlower (
    Bouquet_id INTEGER NOT NULL, 
    Flower_id INTEGER NOT NULL,
    Quantity INTEGER
);

CREATE TABLE Client (
    Client_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Last_name NVARCHAR(50),
    First_name NVARCHAR(50),
    Middle_name NVARCHAR(50),
    Date_of_birth DATE,
    Client_address NVARCHAR(50),
    Phone_number NVARCHAR(50),
    Email NVARCHAR(50),
    Discount FLOAT
);

CREATE TABLE Orders (
    Order_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Client_id INTEGER NOT NULL,
    Order_date DATE
);

CREATE TABLE AdditionalProduct (
    AdditionalProduct_id INTEGER PRIMARY KEY NOT NULL,
    Name NVARCHAR(50),
    Price FLOAT
);

CREATE TABLE Warehouse (
    Warehouse_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Warehouse_address NVARCHAR(50)
);

CREATE TABLE Supplier (
    Supplier_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Organization_name NVARCHAR(50)
);

CREATE TABLE Cashier (
    Cashier_id INTEGER PRIMARY KEY NOT NULL,
    Last_name NVARCHAR(50),
    First_name NVARCHAR(50),
    Middle_name NVARCHAR(50),
    Date_of_birth DATE,
    Phone_number NVARCHAR(50),
    Experience INTEGER
);

CREATE TABLE ProductWarehouse (
    Product_id INTEGER NOT NULL,
    Warehouse_id INTEGER NOT NULL,
    Quantity INTEGER,
    PRIMARY KEY (Product_id, Warehouse_id)
);

CREATE TABLE SupplierProduct (
    Supplier_id INTEGER NOT NULL,
    Product_id INTEGER NOT NULL,
    PRIMARY KEY (Supplier_id, Product_id)
);

CREATE TABLE ProductsInReceipt (
    Receipt_id INTEGER NOT NULL,
    Product_id INTEGER NOT NULL,
    Quantity INTEGER,
    PRIMARY KEY (Receipt_id, Product_id)
);

CREATE TABLE Receipt (
    Receipt_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Order_id INTEGER UNIQUE NOT NULL,
    Cashier_id INTEGER,
    Issue_date DATE,
    Amount FLOAT
);

CREATE TABLE Product (
    Product_id INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
    Type_id INTEGER NOT NULL,
	Name NVARCHAR(50),
    Price FLOAT
);

CREATE TABLE ProductType (
    Type_id INTEGER PRIMARY KEY NOT NULL,
    Name NVARCHAR(50)
);

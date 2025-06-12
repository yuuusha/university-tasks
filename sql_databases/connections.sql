ALTER TABLE BouquetFlower
ADD CONSTRAINT FK_BouquetFlower_Flower FOREIGN KEY (Flower_id) REFERENCES Flower(Flower_id),
CONSTRAINT FK_BouquetFlower_Bouquet FOREIGN KEY (Bouquet_id) REFERENCES Bouquet(Bouquet_id);

ALTER TABLE Orders
ADD CONSTRAINT FK_Orders_Client FOREIGN KEY (Client_id) REFERENCES Client(Client_id);

ALTER TABLE Receipt
ADD CONSTRAINT FK_Receipt_Orders FOREIGN KEY (Order_id) REFERENCES Orders(Order_id),
CONSTRAINT FK_Receipt_Cashier FOREIGN KEY (Cashier_id) REFERENCES Cashier(Cashier_id);

ALTER TABLE ProductsInReceipt
ADD CONSTRAINT FK_ProductsInReceipt_Receipt FOREIGN KEY (Receipt_id) REFERENCES Receipt(Receipt_id),
CONSTRAINT FK_ProductsInReceipt_Product FOREIGN KEY (Product_id) REFERENCES Product(Product_id);

ALTER TABLE ProductWarehouse
ADD CONSTRAINT FK_ProductWarehouse_Product FOREIGN KEY (Product_id) REFERENCES Product(Product_id),
CONSTRAINT FK_ProductWarehouse_Warehouse FOREIGN KEY (Warehouse_id) REFERENCES Warehouse(Warehouse_id);

ALTER TABLE SupplierProduct
ADD CONSTRAINT FK_SupplierProduct_Supplier FOREIGN KEY (Supplier_id) REFERENCES Supplier(Supplier_id),
CONSTRAINT FK_SupplierProduct_Product FOREIGN KEY (Product_id) REFERENCES Product(Product_id);

ALTER TABLE Product
ADD CONSTRAINT FK_Product_ProductType FOREIGN KEY (Type_id) REFERENCES ProductType(Type_id);

ALTER TABLE AdditionalProduct
ADD CONSTRAINT FK_AdditionalProduct_Product FOREIGN KEY (AdditionalProduct_id) REFERENCES Product(Product_id);

ALTER TABLE Bouquet
ADD CONSTRAINT FK_Bouquet_Product FOREIGN KEY (Bouquet_id) REFERENCES Product(Product_id);

ALTER TABLE Flower
ADD CONSTRAINT FK_Flower_Product FOREIGN KEY (Flower_id) REFERENCES Product(Product_id);


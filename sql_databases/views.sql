sp_helptext v_BouquetFlower;
sp_helptext v_Receipt;
sp_helptext v_SellProduct;

DROP VIEW v_BouquetFlower;
DROP VIEW v_Receipt;
DROP VIEW v_SellProduct;

SELECT * FROM v_BouquetFlower;
SELECT * FROM v_Receipt;
SELECT * FROM v_SellProduct;

CREATE VIEW v_BouquetFlower
WITH ENCRYPTION
AS  
SELECT dbo.Bouquet.Name, dbo.Flower.Name AS Expr1, dbo.BouquetFlower.Quantity, dbo.Bouquet.Price
FROM dbo.Bouquet INNER JOIN  
	dbo.BouquetFlower ON dbo.Bouquet.Bouquet_id = dbo.BouquetFlower.Bouquet_id INNER JOIN  
	dbo.Flower ON dbo.BouquetFlower.Flower_id = dbo.Flower.Flower_id;

CREATE VIEW v_Receipt
WITH ENCRYPTION
AS  
SELECT dbo.Receipt.Receipt_id, dbo.Cashier.Last_name, dbo.Receipt.Issue_date, dbo.Product.Name, dbo.ProductsInReceipt.Quantity, dbo.Receipt.Amount  
FROM dbo.ProductsInReceipt INNER JOIN  
	dbo.Receipt ON dbo.ProductsInReceipt.Receipt_id = dbo.Receipt.Receipt_id INNER JOIN  
	dbo.Product ON dbo.ProductsInReceipt.Product_id = dbo.Product.Product_id INNER JOIN  
	dbo.Cashier ON dbo.Receipt.Cashier_id = dbo.Cashier.Cashier_id  
WHERE (dbo.Receipt.Issue_date >= DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()), 0)) AND (dbo.Receipt.Issue_date < DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()) + 1, 0));

CREATE VIEW v_SellProduct
WITH ENCRYPTION
AS
SELECT 
    PR.Name AS Product_Name,
    SUM(PIR.Quantity) AS Total_Quantity_Sold,
    SUM(PIR.Quantity * PR.Price * (1 - C.Discount)) AS Total_Sales_Amount
FROM 
    Receipt R
JOIN 
    Orders O ON R.Order_id = O.Order_id
JOIN 
    ProductsInReceipt PIR ON R.Receipt_id = PIR.Receipt_id
JOIN 
    Product PR ON PIR.Product_id = PR.Product_id
JOIN 
    Client C ON O.Client_id = C.Client_id
WHERE 
    O.Order_date >= DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()), 0) 
    AND O.Order_date < DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()) + 1, 0)
GROUP BY 
    PR.Name;

CREATE VIEW v_Receipt_Insert
AS
SELECT *
FROM Receipt
WHERE (Receipt.Issue_date >= DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()), 0)) AND (Receipt.Issue_date < DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()) + 1, 0))
WITH CHECK OPTION;

INSERT INTO v_Receipt_Insert
VALUES (11, 3, '2024-02-13', 100);

INSERT INTO v_Receipt_Insert
VALUES (11, 3, '2024-04-13', 100);
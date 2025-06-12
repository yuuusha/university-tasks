CREATE VIEW dbo.v_SellProduct
WITH SCHEMABINDING
AS
SELECT 
	Product.Product_id,
    Product.Name AS Product_Name,
    SUM(ISNULL(ProductsInReceipt.Quantity, 0)) AS Total_Quantity_Sold,
    SUM(ISNULL(ProductsInReceipt.Quantity * Product.Price * (1 - Client.Discount), 0)) AS Total_Sales_Amount,
	COUNT_BIG(*) AS DummyColumnForIndex
FROM 
    dbo.Receipt
JOIN 
    dbo.Orders ON dbo.Receipt.Order_id = dbo.Orders.Order_id
JOIN 
    dbo.ProductsInReceipt ON dbo.Receipt.Receipt_id = dbo.ProductsInReceipt.Receipt_id
JOIN 
    dbo.Product ON dbo.ProductsInReceipt.Product_id = dbo.Product.Product_id
JOIN 
    dbo.Client ON dbo.Orders.Client_id = dbo.Client.Client_id
GROUP BY 
    dbo.Product.Product_id, dbo.Product.Name;



SET NUMERIC_ROUNDABORT OFF;
SET ANSI_PADDING, ANSI_WARNINGS, CONCAT_NULL_YIELDS_NULL, ARITHABORT, QUOTED_IDENTIFIER, ANSI_NULLS ON;
GO

SELECT * FROM v_SellProduct;

CREATE UNIQUE CLUSTERED INDEX IX_v_SellProduct ON v_SellProduct (Product_id);

DROP INDEX IX_v_SellProduct ON v_SellProduct 

DROP VIEW v_SellProduct;

SELECT * FROM v_SellProduct WITH (NOEXPAND);
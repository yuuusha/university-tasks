DROP TRIGGER trg_InsteadOfInsertProductInReceipt;

CREATE TRIGGER trg_InsteadOfInsertProductInReceipt
ON ProductsInReceipt
INSTEAD OF INSERT
AS
BEGIN

    IF EXISTS (
        SELECT i.Product_id
        FROM inserted i
        INNER JOIN (
            SELECT Product_id, SUM(Quantity) AS TotalQuantity
            FROM ProductWarehouse
            GROUP BY Product_id
        ) AS pw ON i.Product_id = pw.Product_id
        WHERE i.Quantity > ISNULL(pw.TotalQuantity, 0)
    )
    BEGIN

        RAISERROR ('Ќедостаточно товара на складе дл€ добавлени€ в чек.', 16, 1);
    END
    ELSE
    BEGIN

        INSERT INTO ProductsInReceipt (Receipt_id, Product_id, Quantity)
        SELECT Receipt_id, Product_id, Quantity
        FROM inserted;

        PRINT '“овар успешно добавлен в чек.';
    END
END;

SELECT * FROM Orders;
SELECT * FROM Receipt;
SELECT * FROM Product;
SELECT * FROM ProductWarehouse;
SELECT * FROM ProductsInReceipt;

INSERT INTO ProductsInReceipt (Receipt_id, Product_id, Quantity) VALUES
(10, 9, 100);

DELETE FROM ProductsInReceipt
WHERE Receipt_id = 10 AND Product_id = 9;
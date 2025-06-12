CREATE TRIGGER trg_InsertProduct
ON Product
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;

    INSERT INTO Flower (Flower_id, Name, Price)
    SELECT inserted.Product_id, inserted.Name, inserted.Price
    FROM inserted
    WHERE inserted.Type_id = 1;

    INSERT INTO Bouquet (Bouquet_id, Name, Price)
    SELECT inserted.Product_id, inserted.Name, inserted.Price
    FROM inserted
    WHERE inserted.Type_id = 2;

    INSERT INTO AdditionalProduct (AdditionalProduct_id, Name, Price)
    SELECT inserted.Product_id, inserted.Name, inserted.Price
    FROM inserted
    WHERE inserted.Type_id = 3;
END;

SELECT * FROM Product;
SELECT * FROM Flower;
SELECT * FROM Bouquet;
SELECT * FROM AdditionalProduct;


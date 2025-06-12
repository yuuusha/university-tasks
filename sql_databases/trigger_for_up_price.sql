CREATE TRIGGER trg_UpdateBouquetPrice
ON Flower
AFTER UPDATE
AS
BEGIN
    IF UPDATE(Price) 
    BEGIN
        UPDATE Bouquet
        SET Price = Bouquet.Price + (inserted.Price - deleted.Price)  
        FROM Bouquet
        INNER JOIN BouquetFlower ON Bouquet.Bouquet_id = BouquetFlower.Bouquet_id
        INNER JOIN inserted ON BouquetFlower.Flower_id = inserted.Flower_id
        INNER JOIN deleted ON BouquetFlower.Flower_id = deleted.Flower_id
        WHERE BouquetFlower.Flower_id = inserted.Flower_id;
    END;
END;

SELECT * FROM Flower;
SELECT * FROM Bouquet;

UPDATE Flower
SET Price = 10
WHERE Flower_id = 1;


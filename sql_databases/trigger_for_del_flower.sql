DROP TRIGGER trg_DeleteFlower;

CREATE TRIGGER trg_DeleteFlower
ON Flower
AFTER DELETE
AS
BEGIN

    DELETE FROM BouquetFlower
    WHERE Flower_id IN (SELECT deleted.Flower_id FROM deleted);

END;

INSERT INTO Product(Type_id, Name, Price) VALUES
(1, 'Цветок1', 100),
(2, 'Букет1', 100);

SELECT * FROM Flower;
SELECT * FROM Bouquet;

INSERT INTO BouquetFlower (Bouquet_id, Flower_id, Quantity) VALUES
(27, 26, 1),
(27, 1, 1);

SELECT f.Name
FROM Flower f
JOIN BouquetFlower bf ON f.Flower_id = bf.Flower_id
WHERE bf.Bouquet_id = 27;

DELETE FROM Flower
WHERE Flower_id = 26;

DELETE FROM BouquetFlower WHERE Bouquet_id = 27;
DELETE FROM Bouquet WHERE Bouquet_id = 27;
SELECT f.Name AS Flower_Name, bf.Quantity
FROM BouquetFlower bf
JOIN Flower f ON bf.Flower_id = f.Flower_id
WHERE bf.Bouquet_id = 12;
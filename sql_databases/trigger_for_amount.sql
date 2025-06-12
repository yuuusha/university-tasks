CREATE TRIGGER trg_CalculateAmount
ON ProductsInReceipt
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;

    UPDATE r
    SET Amount = 
        (SELECT SUM(pr.Quantity * p.Price) * MAX(c.Discount)
         FROM ProductsInReceipt AS pr
         INNER JOIN Product AS p ON pr.Product_id = p.Product_id
         LEFT JOIN Receipt AS rc ON pr.Receipt_id = rc.Receipt_id
         LEFT JOIN Orders AS o ON rc.Order_id = o.Order_id
         LEFT JOIN Client AS c ON o.Client_id = c.Client_id
         WHERE pr.Receipt_id = r.Receipt_id)
    FROM Receipt AS r
    INNER JOIN inserted AS i ON r.Receipt_id = i.Receipt_id;
END;

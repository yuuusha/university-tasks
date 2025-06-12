DROP TRIGGER trg_CheckOrderCountBeforeUpdateDiscount;

CREATE TRIGGER trg_CheckOrderCountBeforeUpdateDiscount
ON Client
INSTEAD OF UPDATE
AS
BEGIN
    IF UPDATE(Discount)
    BEGIN
        IF NOT EXISTS (
            SELECT 1
            FROM inserted i
            INNER JOIN (
                SELECT Client_id, COUNT(*) AS OrderCount
                FROM Orders
                GROUP BY Client_id
            ) o ON i.Client_id = o.Client_id
            WHERE o.OrderCount < 10
        )
        BEGIN
            RAISERROR ('Клиент должен иметь минимум 10 заказов для обновления скидки.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END
        ELSE
        BEGIN
            UPDATE c
            SET c.Discount = i.Discount
            FROM Client c
            JOIN inserted i ON c.Client_id = i.Client_id;
            PRINT 'Скидка успешно обновлена.';
        END;
    END;
END;


INSERT INTO Client(Last_name, First_name, Middle_name, Date_of_birth, Client_address, Phone_number, Email, Discount) VALUES
('Иванова', 'Ивана', 'Ивановна', '1990-05-15', 'Москва, ул. Пушкина, д.10, кв.7', '+7 (999) 123-45-60', 'ivanova@example.com', 0.0);

SELECT * FROM Client;
SELECT * FROM Orders;

DELETE FROM Client WHERE Client_id = 11;

UPDATE Client
SET Discount = 0.1
WHERE Client_id = 11;

UPDATE Client
SET Discount = 0.15
WHERE Client_id = 4;
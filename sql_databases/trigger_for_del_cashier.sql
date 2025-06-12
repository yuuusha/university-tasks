CREATE TRIGGER trg_InsteadOfDeleteCashier
ON Cashier
INSTEAD OF DELETE
AS
BEGIN
    UPDATE Cashier
    SET is_deleted = 1
    WHERE Cashier_id IN (SELECT Cashier_id FROM deleted);
END;

INSERT INTO Cashier (Cashier_id, Last_name, First_name, Middle_name, Date_of_birth, Phone_number, Experience) VALUES
(4, 'Иванова', 'Галина', 'Ивановна', '1985-05-10', '+7 (999) 123-45-60', 5);

SELECT * FROM Cashier;

DELETE FROM Cashier 
WHERE Cashier_id = 4;
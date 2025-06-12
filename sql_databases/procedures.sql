-- вернуть кассира который продал на большую сумму \ больше товаров за период
CREATE PROCEDURE GetTopEarningCashier
    @StartDate DATETIME,
    @EndDate DATETIME,
    @IsTotalAmount BIT -- 1 - большая сумма, 0 - больше товаров
AS
BEGIN
    SET NOCOUNT ON;

    IF @IsTotalAmount = 1
    BEGIN
        SELECT TOP 1
            Cashier.Last_name AS TopEarningCashier,
            SUM(Receipt.Amount) AS TotalEarnings
        FROM
            Receipt
		JOIN Cashier ON Cashier.Cashier_id = Receipt.Cashier_id
        WHERE
            Receipt.Issue_date >= @StartDate AND Receipt.Issue_date < @EndDate
        GROUP BY
            Cashier.Last_name
        ORDER BY
            TotalEarnings DESC;
    END
    ELSE
    BEGIN
        SELECT TOP 1
			Cashier.Last_name AS TopSellingCashier,
			SUM(ProductsInReceipt.Quantity) AS TotalSales
		FROM
			dbo.ProductsInReceipt
			INNER JOIN
			dbo.Receipt ON ProductsInReceipt.Receipt_id = Receipt.Receipt_id
			INNER JOIN
			dbo.Cashier ON Receipt.Cashier_id = Cashier.Cashier_id
		WHERE
			Receipt.Issue_date >= @StartDate AND Receipt.Issue_date < @EndDate
		GROUP BY
			Cashier.Last_name
		ORDER BY
			TotalSales DESC;
    END
END;

EXEC GetTopEarningCashier '2024-04-01', '2024-04-30', 0;
EXEC GetTopEarningCashier '2024-04-01', '2024-04-30', 1;

DROP PROCEDURE IF EXISTS GetTopEarningCashier;

--

-- вернуть прибыль за период
CREATE PROCEDURE CalculateProfit
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @Profit DECIMAL(18, 2);

    SELECT @Profit = SUM(Amount)
    FROM Receipt
    WHERE Issue_date >= @StartDate AND Issue_date < DATEADD(DAY, 1, @EndDate);

    RETURN @Profit;
END;

DECLARE @Profit DECIMAL(18, 2);
EXEC @Profit = CalculateProfit '2024-04-01', '2024-04-30';
SELECT @Profit AS TotalProfit;

DROP PROCEDURE IF EXISTS CalculateProfit;

--

--вернуть количество заказов за период
CREATE PROCEDURE GetOrderCountByPeriod
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    SET NOCOUNT ON;

	DECLARE @Ord DECIMAL(6);

    SELECT @Ord = COUNT(*)
    FROM Orders
    WHERE Order_date >= @StartDate AND Order_date < @EndDate;

	RETURN @Ord
END;

DECLARE @Ord DECIMAL(6);
EXEC @Ord = GetOrderCountByPeriod '2024-04-01', '2024-04-30';
SELECT @Ord AS TotalOrders;

DROP PROCEDURE IF EXISTS GetOrderCountByPeriod;

--

--вернуть сумму покупок каждого клиента за период
CREATE PROCEDURE CalculateTotalSalesByClient
	@StartDate DATE,
	@EndDate DATE
AS
BEGIN
    DECLARE @ClientId INT;
    DECLARE @TotalSales DECIMAL(18, 2);

    CREATE TABLE #SalesByClient (
        ClientId INT,
        TotalSales DECIMAL(18, 2)
    );

    DECLARE clientCursor CURSOR FOR
        SELECT Client_id FROM Client;

    OPEN clientCursor;

    SET @ClientId = 0;
    SET @TotalSales = 0;

    FETCH NEXT FROM clientCursor INTO @ClientId;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SELECT @TotalSales = SUM(r.Amount)
        FROM Orders o
        INNER JOIN Receipt r ON o.Order_id = r.Order_id
        WHERE o.Client_id = @ClientId AND (o.Order_date >= @StartDate AND o.Order_date < @EndDate);

		IF @TotalSales > 0
		BEGIN
			INSERT INTO #SalesByClient (ClientId, TotalSales)
			VALUES (@ClientId, @TotalSales);
		END;

        FETCH NEXT FROM clientCursor INTO @ClientId;
    END;

    CLOSE clientCursor;
    DEALLOCATE clientCursor;

    SELECT * FROM #SalesByClient;

    DROP TABLE #SalesByClient;
END;

EXEC CalculateTotalSalesByClient '2024-04-01', '2024-04-30';

DROP PROCEDURE IF EXISTS CalculateTotalSalesByClient;

--

--добавить клиента и получить его id для дальнейших действий
CREATE PROCEDURE AddClientAndGetId
    @FirstName NVARCHAR(50),
    @LastName NVARCHAR(50),
    @ClientId INT OUTPUT
AS
BEGIN
    DECLARE @InsertedClients TABLE (
        ClientId INT
    );

    INSERT INTO Client (First_name, Last_name)
    OUTPUT inserted.Client_id INTO @InsertedClients (ClientId)
    VALUES (@FirstName, @LastName);

    SELECT @ClientId = ClientId FROM @InsertedClients;
END;

DECLARE @ClientId INT;

EXEC AddClientAndGetId
    @FirstName = 'Виола',
    @LastName = 'Тараканова',
    @ClientId = @ClientId OUTPUT;

SELECT @ClientId AS 'InsertedClientId';

SELECT * FROM Client;
DELETE FROM Client WHERE Client_id = 11;

DROP PROCEDURE IF EXISTS AddClientAndGetId;
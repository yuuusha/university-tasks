package org.example;

import com.example.grpc.EmployeeRequest;
import com.example.grpc.EmployeeResponse;
import com.example.grpc.EmployeeServiceGrpc;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class EmployeeServer {
    private static final int PORT = 9090;
    private static HikariDataSource dataSource;

    public static void main(String[] args) throws Exception {
        setupDataSource();

        Server server = ServerBuilder.forPort(PORT)
                .addService(new EmployeeServiceImpl())
                .build();

        System.out.println("gRPC Server started on port " + PORT);
        server.start();
        server.awaitTermination();
    }

    private static void setupDataSource() {
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl("jdbc:postgresql://localhost:5432/homework13");
        config.setUsername("postgres");
        config.setPassword("admin");
        config.setMaximumPoolSize(10);

        dataSource = new HikariDataSource(config);
    }

    static class EmployeeServiceImpl extends EmployeeServiceGrpc.EmployeeServiceImplBase {
        @Override
        public void addEmployee(EmployeeRequest request, StreamObserver<EmployeeResponse> responseObserver) {
            try (Connection conn = dataSource.getConnection()) {
                String sql = "INSERT INTO employees (last_name, first_name, middle_name, gender, birth_date, phone, hire_date, fire_date, position, salary, is_manager, department_id) " +
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) RETURNING id";

                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setString(1, request.getLastName());
                    stmt.setString(2, request.getFirstName());
                    stmt.setString(3, request.getMiddleName());
                    stmt.setString(4, request.getGender());
                    stmt.setDate(5, java.sql.Date.valueOf(request.getBirthDate()));
                    stmt.setString(6, request.getPhone());
                    stmt.setDate(7, java.sql.Date.valueOf(request.getHireDate()));
                    stmt.setDate(8, request.getFireDate().isEmpty() ? null : java.sql.Date.valueOf(request.getFireDate()));
                    stmt.setString(9, request.getPosition());
                    stmt.setDouble(10, request.getSalary());
                    stmt.setBoolean(11, request.getIsManager());
                    stmt.setInt(12, request.getDepartmentId());

                    if (stmt.execute()) {
                        stmt.getResultSet().next();
                        int employeeId = stmt.getResultSet().getInt(1);

                        EmployeeResponse response = EmployeeResponse.newBuilder()
                                .setEmployeeId(employeeId)
                                .setErrorMessage("")
                                .build();

                        responseObserver.onNext(response);
                        responseObserver.onCompleted();
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                EmployeeResponse response = EmployeeResponse.newBuilder()
                        .setEmployeeId(-1)
                        .setErrorMessage("Database error: " + e.getMessage())
                        .build();

                responseObserver.onNext(response);
                responseObserver.onCompleted();
            }
        }
    }
}

